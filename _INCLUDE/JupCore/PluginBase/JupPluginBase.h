#pragma once
#include "JupCore_export.h"
#include "StdAfx.h"
#include "Base/JupGlobal.h"
#include "Base/JupReflectClass.h"
#include "PluginBase/JupCaller.h"
#include "PluginBase/JupError.h"
#include "PluginBase/JupVersion.h"

#define JUP_REFLECT_CLASS(Class, Name) \
public:	\
	inline StringList Get##Name##Names() { return m_Reflect##Name.keys(); }	\
	template<typename T>	\
	inline void Register##Name() { m_Reflect##Name.registerClass<T>(); }	\
public:	\
	virtual Class* Create##Name(const std::string& classname);	\
private:	\
	JupReflectClass<Class> m_Reflect##Name;


#define JUP_REFLECT_SHARED_CLASS(Class, Name) \
public:	\
	inline StringList Get##Name##Names() { return m_Reflect##Name.keys(); }	\
	template<typename T>	\
	inline void Register##Name() { m_Reflect##Name.registerClass<T>(); }	\
public:	\
	virtual Class* Create##Name(const std::string& classname);	\
private:	\
	JupReflectClass<Class> m_Reflect##Name;	\
	std::vector<std::shared_ptr<Class>> m_##Name##SharedPtrs;


class JUPCORE_EXPORT JupPluginBase
{
	JUP_DISABLE_COPY(JupPluginBase)

public:
	JupPluginBase();
	virtual ~JupPluginBase();

	friend class JupPluginLoader;
	friend class JupCallerService;

public:
	std::unique_ptr<JupError> m_error;
	std::unique_ptr<JupVersion> m_version;
	std::unique_ptr<JupSubDialog> m_rootDlg;

	/*Reflect Caller*/
	JUP_REFLECT_CLASS(JupCaller, Caller)

	/*Reflect Sub Dialog*/
	JUP_REFLECT_SHARED_CLASS(JupSubDialog, SubDlg)
};

