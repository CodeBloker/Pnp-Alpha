#pragma once

#include <map>
#include <vector>

template <typename D>
class JupMethodCaller
{
public:
	JupMethodCaller() {}
	virtual ~JupMethodCaller() {}

	using JupMethod = int(*)(void *, D&);

	template <typename T>
	static JupMethod transformMethod(int (T::*t)(D&)) {
		return reinterpret_cast<JupMethod>(*reinterpret_cast<void **>(&t));
	}

	virtual void* This() = 0;

	virtual int Initialize() = 0;

	virtual int RegisterMethod() = 0;
	//eg:	appendMethod("generalMethod", transformMethod<T>(&T::generalMethod));	

	virtual std::vector<std::string> GetMethodItems() final {
		if (m_mapItem2Method.empty())
			RegisterMethod();
		std::vector<std::string> keys;
		for (const auto&[name, method] : m_mapItem2Method)
			keys.push_back(name);
		return keys;
	}

	virtual int RunMethod(const std::string& item, D& data) final {
		if (m_mapItem2Method.count(item))
			return runMethod(m_mapItem2Method[item], data);
		return runMethod(transformMethod<JupMethodCaller>(&JupMethodCaller::generalMethod), data);
	}

protected:
	virtual void appendMethod(const std::string& item, JupMethod method) final {
		m_mapItem2Method.emplace(item, method);
	}

private:
	virtual int generalMethod([[maybe_unused]] D& data) final {
		return 0;
	}

	virtual int runMethod(JupMethod method, D& data) final {
		return (*method)(This(), data);
	}

private:
	std::map<std::string, JupMethod> m_mapItem2Method;
};

