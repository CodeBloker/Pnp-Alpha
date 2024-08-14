#include "VisaManager.h"

VisaManager::VisaManager()
{
}

VisaManager::~VisaManager()
{
}

ViStatus VisaManager::viOpenDefaultRM(ViPSession vi)
{
	return ::viOpenDefaultRM(vi);
}

ViStatus VisaManager::viFindRsrc(ViSession sesn, ViString expr, ViPFindList vi, ViPUInt32 retCnt, ViChar _VI_FAR desc[])
{
	return ::viFindRsrc(sesn, expr, vi, retCnt, desc);
}

ViStatus VisaManager::viFindNext(ViFindList vi, ViChar _VI_FAR desc[])
{
	return ::viFindNext(vi, desc);
}

ViStatus VisaManager::viParseRsrc(ViSession rmSesn, ViRsrc rsrcName, ViPUInt16 intfType, ViPUInt16 intfNum)
{
	return ::viParseRsrc(rmSesn, rsrcName, intfType, intfNum);
}

ViStatus VisaManager::viParseRsrcEx(ViSession rmSesn, ViRsrc rsrcName, ViPUInt16 intfType,
									ViPUInt16 intfNum, ViChar _VI_FAR rsrcClass[],
									ViChar _VI_FAR expandedUnaliasedName[],
									ViChar _VI_FAR aliasIfExists[])
{
	return ::viParseRsrcEx(rmSesn, rsrcName, intfType, intfNum, rsrcClass, expandedUnaliasedName, aliasIfExists);
}

ViStatus VisaManager::viOpen(ViSession sesn, ViRsrc name, ViAccessMode mode, ViUInt32 timeout, ViPSession vi)
{
	return ::viOpen(sesn, name, mode, timeout, vi);
}


/*- Resource Template Operations --------------------------------------------*/

ViStatus VisaManager::viClose(ViObject vi)
{
	return ::viClose(vi);
}

ViStatus VisaManager::viSetAttribute(ViObject vi, ViAttr attrName, ViAttrState attrValue)
{
	return ::viSetAttribute(vi, attrName, attrValue);
}

ViStatus VisaManager::viGetAttribute(ViObject vi, ViAttr attrName, void _VI_PTR attrValue)
{
	return ::viGetAttribute(vi, attrName, attrValue);
}

ViStatus VisaManager::viStatusDesc(ViObject vi, ViStatus status, ViChar _VI_FAR desc[])
{
	return ::viStatusDesc(vi, status, desc);
}

ViStatus VisaManager::viTerminate(ViObject vi, ViUInt16 degree, ViJobId jobId)
{
	return ::viTerminate(vi, degree, jobId);
}


ViStatus VisaManager::viLock(ViSession vi, ViAccessMode lockType, ViUInt32 timeout, ViKeyId requestedKey, ViChar _VI_FAR accessKey[])
{
	return ::viLock(vi, lockType, timeout, requestedKey, accessKey);
}


ViStatus VisaManager::viUnlock(ViSession vi)
{
	return ::viUnlock(vi);
}

ViStatus VisaManager::viEnableEvent(ViSession vi, ViEventType eventType, ViUInt16 mechanism, ViEventFilter context)
{
	return ::viEnableEvent(vi, eventType, mechanism, context);
}

ViStatus VisaManager::viDisableEvent(ViSession vi, ViEventType eventType, ViUInt16 mechanism)
{
	return ::viDisableEvent(vi, eventType, mechanism);
}

ViStatus VisaManager::viDiscardEvents(ViSession vi, ViEventType eventType, ViUInt16 mechanism)
{
	return ::viDiscardEvents(vi, eventType, mechanism);
}

ViStatus VisaManager::viWaitOnEvent(ViSession vi, ViEventType inEventType, ViUInt32 timeout, ViPEventType outEventType, ViPEvent outContext)
{
	return ::viWaitOnEvent(vi, inEventType, timeout, outEventType, outContext);
}

ViStatus VisaManager::viInstallHandler(ViSession vi, ViEventType eventType, ViHndlr handler,	ViAddr userHandle)
{
	return ::viInstallHandler(vi, eventType, handler, userHandle);
}

ViStatus VisaManager::viUninstallHandler(ViSession vi, ViEventType eventType, ViHndlr handler, ViAddr userHandle)
{
	return ::viUninstallHandler(vi, eventType, handler, userHandle);
}


/*- Basic I/O Operations ----------------------------------------------------*/

ViStatus VisaManager::viRead(ViSession vi, ViPBuf buf, ViUInt32 cnt, ViPUInt32 retCnt)
{
	return ::viRead(vi, buf, cnt, retCnt);
}

ViStatus VisaManager::viReadAsync(ViSession vi, ViPBuf buf, ViUInt32 cnt, ViPJobId  jobId)
{
	return ::viReadAsync(vi, buf, cnt, jobId);
}

ViStatus VisaManager::viReadToFile(ViSession vi, ViConstString filename, ViUInt32 cnt, ViPUInt32 retCnt)
{
	return ::viReadToFile(vi, filename, cnt, retCnt);
}

ViStatus VisaManager::viWrite(ViSession vi, ViBuf  buf, ViUInt32 cnt, ViPUInt32 retCnt)
{
	return ::viWrite(vi, buf, cnt, retCnt);
}

ViStatus VisaManager::viWriteAsync(ViSession vi, ViBuf  buf, ViUInt32 cnt, ViPJobId  jobId)
{
	return ::viWriteAsync(vi, buf, cnt, jobId);
}

ViStatus VisaManager::viWriteFromFile(ViSession vi, ViConstString filename, ViUInt32 cnt, ViPUInt32 retCnt)
{
	return ::viWriteFromFile(vi, filename, cnt, retCnt);
}

ViStatus VisaManager::viAssertTrigger(ViSession vi, ViUInt16 protocol)
{
	return ::viAssertTrigger(vi, protocol);
}

ViStatus VisaManager::viReadSTB(ViSession vi, ViPUInt16 status)
{
	return ::viReadSTB(vi, status);
}

ViStatus VisaManager::viClear(ViSession vi)
{
	return ::viClear(vi);
}


/*- Formatted and Buffered I/O Operations -----------------------------------*/

ViStatus VisaManager::viSetBuf(ViSession vi, ViUInt16 mask, ViUInt32 size)
{
	return ::viSetBuf(vi, mask, size);
}


ViStatus VisaManager::viFlush(ViSession vi, ViUInt16 mask)
{
	return ::viFlush(vi, mask);
}


ViStatus VisaManager::viBufWrite(ViSession vi, ViBuf  buf, ViUInt32 cnt, ViPUInt32 retCnt)
{
	return ::viBufWrite(vi, buf, cnt, retCnt);
}

ViStatus VisaManager::viBufRead(ViSession vi, ViPBuf buf, ViUInt32 cnt, ViPUInt32 retCnt)
{
	return ::viBufRead(vi, buf, cnt, retCnt);
}


ViStatus VisaManager::viPrintf(ViSession vi, ViString writeFmt, ...)
{
	
	va_list list;
	va_start(list, writeFmt);
	ViStatus rtn;
	
	rtn = ::viPrintf(vi, writeFmt, va_pass(list));

	va_end(list);
	
	return rtn;
	
}

ViStatus VisaManager::viVPrintf(ViSession vi, ViString writeFmt, ViVAList params)
{	
	return ::viVPrintf(vi, writeFmt, params);
}

ViStatus VisaManager::viSPrintf(ViSession vi, ViPBuf buf, ViString writeFmt, ...)
{
	va_list list;
	va_start(list, writeFmt);
	ViStatus rtn;
	
	rtn = ::viSPrintf(vi, buf, writeFmt, va_pass(list));

	va_end(list);

	return rtn;
}

ViStatus VisaManager::viVSPrintf(ViSession vi, ViPBuf buf, ViString writeFmt, ViVAList parms)
{
	return ::viVSPrintf(vi, buf, writeFmt, parms);
}


ViStatus VisaManager::viScanf(ViSession vi, ViString readFmt, ...)
{
	va_list list;
	va_start(list, readFmt);
	ViStatus rtn;
	
	rtn = ::viScanf(vi, readFmt, va_pass(list));

	va_end(list);

	return rtn;
}

ViStatus VisaManager::viVScanf(ViSession vi, ViString readFmt, ViVAList params)
{
	return ::viVScanf(vi, readFmt, params);
}

ViStatus VisaManager::viSScanf(ViSession vi, ViBuf buf, ViString readFmt, ...)
{
	va_list list;
	va_start(list, readFmt);
	ViStatus rtn;
	
	rtn = ::viSScanf(vi, buf, readFmt, va_pass(list));

	va_end(list);

	return rtn;
}

ViStatus VisaManager::viVSScanf(ViSession vi, ViBuf buf, ViString readFmt, ViVAList parms)
{
	return ::viVSScanf(vi, buf, readFmt, parms);
}


ViStatus VisaManager::viQueryf(ViSession vi, ViString writeFmt, ViString readFmt, ...)
{
	va_list list;
	va_start(list, readFmt);
	ViStatus rtn;
	
	rtn = ::viQueryf(vi, writeFmt, readFmt, va_pass(list));

	va_end(list);

	return rtn;
}

ViStatus VisaManager::viVQueryf(ViSession vi, ViString writeFmt, ViString readFmt, ViVAList params)
{
	return ::viVQueryf(vi, writeFmt, readFmt, params);
}