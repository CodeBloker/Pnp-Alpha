#pragma once
#ifndef _JUPGLOBAL_
#define _JUPGLOBAL_

#include <string>
#include <list>
#include <vector>
#include <map>
#include <variant>

using StringList = std::vector<std::string>;
using StringPair = std::pair<std::string, std::string>;
using StringMap = std::map<std::string, std::string>;
using BaseVariant = std::variant<std::string, int, double>;
using BaseVariantMap = std::map<std::string, BaseVariant>;

#define JUP_DISABLE_COPY(Class) \
    Class(const Class &) = delete;\
    Class &operator=(const Class &) = delete;

#define JUP_DISABLE_MOVE(Class) \
    Class(Class &&) = delete; \
    Class &operator=(Class &&) = delete;

#define JUP_DISABLE_COPY_MOVE(Class) \
    JUP_DISABLE_COPY(Class) \
    JUP_DISABLE_MOVE(Class)

template <typename T> inline T *JGetPtrHelper(T *ptr) { return ptr; }
template <typename Ptr> inline auto JGetPtrHelper(Ptr &ptr) -> decltype(ptr.operator->()) { return ptr.operator->(); }

#define JUP_DECLARE_PRIVATE(Class) \
    inline Class##Private* d_func() \
    { return reinterpret_cast<Class##Private *>(JGetPtrHelper(d_ptr)); } \
    inline const Class##Private* d_func() const \
    { return reinterpret_cast<const Class##Private *>(JGetPtrHelper(d_ptr)); } \
    friend class Class##Private; \
	std::unique_ptr<Class##Private> d_ptr;

#define JUP_DECLARE_PUBLIC(Class)                                    \
    inline Class* q_func() { return static_cast<Class *>(q_ptr); } \
    inline const Class* q_func() const { return static_cast<const Class *>(q_ptr); } \
    friend class Class; \
	Class* const q_ptr = nullptr;

#define JUP_D(Class) Class##Private * const d = d_func()
#define JUP_Q(Class) Class * const q = q_func()

template <typename TKey, typename TVal>
static std::vector<TKey> GetMapKeys(const std::map<TKey, TVal>& map)
{
	std::vector<TKey> keys;
	for (const auto&[key, value] : map)
		keys.push_back(key);
	return keys;
}

template <typename T, typename Arg>
class JupTransformMethod
{
	using Type = void(*)(void*, Arg&);
public:
	static Type transform(void(T::*t)(Arg&)) {
		return reinterpret_cast<Type>(*reinterpret_cast<void **>(&t));
	}
};

#include <shared_mutex>

using JReadLock = std::shared_lock<std::shared_mutex>;
using JWriteLock = std::unique_lock<std::shared_mutex>;

// 检查类是否有构造函数的SFINAE模板
template <typename T, typename... Args> 
class HasConstructor 
{
private:
	template <typename U>
	static constexpr std::true_type has(decltype(U(std::declval<Args>()...))*);
	template <typename U>
	static constexpr std::false_type has(...);
public:
	static constexpr bool value = decltype(has<T>(nullptr))::value;
};

template<typename T, typename std::enable_if<std::is_class_v<T>, bool>::type = true>
class JupSingletonPointer
{
public:
	T* Get() {
		JReadLock lock(m_mutex);
		if (m_pointer)
			return m_pointer.get();
		else {
			lock.release()->unlock_shared();
			if constexpr (HasConstructor<T>::value == true)
				return Create();
			else
				return nullptr;
		}
	}

	template<typename...Args>
	T* Create(Args&&... args) {
		JWriteLock lock(m_mutex);
		if (m_pointer == nullptr) {
			if constexpr (HasConstructor<T>::value == false) {
				T* t = std::apply([](auto &&...args)->T* { return new T(args...); }, std::tuple<T>(args...));
				m_pointer = std::unique_ptr<T>(t);
			}		
			else
				m_pointer = std::unique_ptr<T>(new T);
		}
		return m_pointer.get();
	}

	void Destroy() {
		JWriteLock lock(m_mutex);
		m_pointer.reset();
	}

private:
	inline static std::shared_mutex m_mutex;
	inline static std::unique_ptr<T> m_pointer;
};

#define JUP_STATIC(Class)						\
protected:										\
	friend class HasConstructor<Class>;	\
	friend class JupSingletonPointer<Class>;	\
	Class();									\
	JUP_DISABLE_COPY(Class)						\
public:											\
	~Class();

#define JUP_STATIC_HELPER(Class)						\
public:													\
	static Class* GetInstance() {						\
		return JupSingletonPointer<Class>().Get(); }	\
	static void FreeInstance() {						\
		JupSingletonPointer<Class>().Destroy(); }	

template<typename T, typename std::enable_if<std::is_class_v<T>, bool>::type = true>
class JupGlobalPointers
{
public:
	bool Contains(const std::string& id) {
		JReadLock lock(m_mutex);
		return m_pointers.count(id);
	}

	StringList Keys() {
		JReadLock lock(m_mutex);
		StringList list;
		for (const auto&[key, point] : m_pointers) {
			list.push_back(key);
		}
		return list;
	}

	std::shared_ptr<T> Get(const std::string& id) {
		JReadLock lock(m_mutex);
		if (m_pointers.count(id))
			return m_pointers.at(id);
		else {
			lock.release()->unlock_shared();
			if constexpr (HasConstructor<T>::value == true)
				return Create(id);
			else 
				return nullptr;
		}		 
	}

	template<typename...Args>
	std::shared_ptr<T> Create(const std::string& id, Args&&... args) {
		JWriteLock lock(m_mutex);
		if constexpr (HasConstructor<T>::value == false) {
			T* t = std::apply([](auto &&...args)->T* { return new T(args...); }, std::tuple<T>(args...));
			m_pointers[id] = std::shared_ptr<T>(t);
		}	
		else
			m_pointers[id] = std::shared_ptr<T>(new T);
		return m_pointers[id];
	}

	void Remove(const std::string& id) {
		JWriteLock lock(m_mutex);
		m_pointers.erase(id);
	}

	void RemoveAll() {
		JWriteLock lock(m_mutex);
		std::map<std::string, std::shared_ptr<T>>().swap(m_pointers);
	}

//private:
//	template <typename... Args>
//	inline static T* createHelper(Args &&...args) {
//		return new T(args...);
//	}

private:
	inline static std::shared_mutex m_mutex;
	inline static std::map<std::string, std::shared_ptr<T>> m_pointers;
};

#endif /* _JUPGLOBAL_ */