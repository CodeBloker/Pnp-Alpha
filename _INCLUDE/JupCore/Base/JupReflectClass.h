#pragma once

#include <map>
#include <vector>

template<typename B>
class JupReflectClass
{
	template<typename T>
	using IfCompatible = typename std::enable_if<std::is_convertible<T*, B*>::value, bool>::type;

public:
	//首先要注册创建的类
	template<typename T, IfCompatible<T> = true>
	void registerClass() {
		//&constructorHelper<T>其实是获取创建的函数指针,核心功能。
		constructors().emplace(std::string(typeid(T).name()).substr(strlen("class ")), &constructorHelper<T>);
	}

	B *createObject(const std::string& className) {
		Constructor constructor = constructors()[className];
		if (constructor == nullptr) {
			return nullptr;
		}
		return (*constructor)();	//执行new T函数，创建对应实例
	}

	std::vector<std::string> keys() {
		std::vector<std::string> keys;
		for (const auto&[name, method] : m_instance)
			keys.push_back(name);
		return keys;
	}

private:
	typedef B* (*Constructor)();

	template<typename T>
	static B* constructorHelper() {
		return new T;
	}

	std::map<std::string, Constructor> &constructors() {
		return m_instance;
	}

	std::map<std::string, Constructor> m_instance;
};