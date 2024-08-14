#include "VisaCaller.h"

VisaCaller::VisaCaller()
{
}

VisaCaller::~VisaCaller()
{
}

ViStatus VisaCaller::viOpenDefaultRM(ViPSession vi)
{
	return ::viOpenDefaultRM(vi);
}

ViStatus VisaCaller::viFindRsrc(ViSession sesn, ViString expr, ViPFindList vi, ViPUInt32 retCnt, ViChar _VI_FAR desc[])
{
	return ::viFindRsrc(sesn, expr, vi, retCnt, desc);
}

ViStatus VisaCaller::viFindNext(ViFindList vi, ViChar _VI_FAR desc[])
{
	return ::viFindNext(vi, desc);
}

ViStatus VisaCaller::viParseRsrc(ViSession rmSesn, ViRsrc rsrcName, ViPUInt16 intfType, ViPUInt16 intfNum)
{
	return ::viParseRsrc(rmSesn, rsrcName, intfType, intfNum);
}

ViStatus VisaCaller::viParseRsrcEx(ViSession rmSesn, ViRsrc rsrcName, ViPUInt16 intfType,
									ViPUInt16 intfNum, ViChar _VI_FAR rsrcClass[],
									ViChar _VI_FAR expandedUnaliasedName[],
									ViChar _VI_FAR aliasIfExists[])
{
	return ::viParseRsrcEx(rmSesn, rsrcName, intfType, intfNum, rsrcClass, expandedUnaliasedName, aliasIfExists);
}

ViStatus VisaCaller::viOpen(ViSession sesn, ViRsrc name, ViAccessMode mode, ViUInt32 timeout, ViPSession vi)
{
	return ::viOpen(sesn, name, mode, timeout, vi);
}


/*- Resource Template Operations --------------------------------------------*/

ViStatus VisaCaller::viClose(ViObject vi)
{
	return ::viClose(vi);
}

ViStatus VisaCaller::viSetAttribute(ViObject vi, ViAttr attrName, ViAttrState attrValue)
{
	return ::viSetAttribute(vi, attrName, attrValue);
}

ViStatus VisaCaller::viGetAttribute(ViObject vi, ViAttr attrName, void _VI_PTR attrValue)
{
	return ::viGetAttribute(vi, attrName, attrValue);
}

ViStatus VisaCaller::viStatusDesc(ViObject vi, ViStatus status, ViChar _VI_FAR desc[])
{
	return ::viStatusDesc(vi, status, desc);
}

ViStatus VisaCaller::viTerminate(ViObject vi, ViUInt16 degree, ViJobId jobId)
{
	return ::viTerminate(vi, degree, jobId);
}


ViStatus VisaCaller::viLock(ViSession vi, ViAccessMode lockType, ViUInt32 timeout, ViKeyId requestedKey, ViChar _VI_FAR accessKey[])
{
	return ::viLock(vi, lockType, timeout, requestedKey, accessKey);
}


ViStatus VisaCaller::viUnlock(ViSession vi)
{
	return ::viUnlock(vi);
}

ViStatus VisaCaller::viEnableEvent(ViSession vi, ViEventType eventType, ViUInt16 mechanism, ViEventFilter context)
{
	return ::viEnableEvent(vi, eventType, mechanism, context);
}

ViStatus VisaCaller::viDisableEvent(ViSession vi, ViEventType eventType, ViUInt16 mechanism)
{
	return ::viDisableEvent(vi, eventType, mechanism);
}

ViStatus VisaCaller::viDiscardEvents(ViSession vi, ViEventType eventType, ViUInt16 mechanism)
{
	return ::viDiscardEvents(vi, eventType, mechanism);
}

ViStatus VisaCaller::viWaitOnEvent(ViSession vi, ViEventType inEventType, ViUInt32 timeout, ViPEventType outEventType, ViPEvent outContext)
{
	return ::viWaitOnEvent(vi, inEventType, timeout, outEventType, outContext);
}

ViStatus VisaCaller::viInstallHandler(ViSession vi, ViEventType eventType, ViHndlr handler,	ViAddr userHandle)
{
	return ::viInstallHandler(vi, eventType, handler, userHandle);
}

ViStatus VisaCaller::viUninstallHandler(ViSession vi, ViEventType eventType, ViHndlr handler, ViAddr userHandle)
{
	return ::viUninstallHandler(vi, eventType, handler, userHandle);
}


/*- Basic I/O Operations ----------------------------------------------------*/

ViStatus VisaCaller::viRead(ViSession vi, ViPBuf buf, ViUInt32 cnt, ViPUInt32 retCnt)
{
	return ::viRead(vi, buf, cnt, retCnt);
}

ViStatus VisaCaller::viReadAsync(ViSession vi, ViPBuf buf, ViUInt32 cnt, ViPJobId  jobId)
{
	return ::viReadAsync(vi, buf, cnt, jobId);
}

ViStatus VisaCaller::viReadToFile(ViSession vi, ViConstString filename, ViUInt32 cnt, ViPUInt32 retCnt)
{
	return ::viReadToFile(vi, filename, cnt, retCnt);
}

ViStatus VisaCaller::viWrite(ViSession vi, ViBuf  buf, ViUInt32 cnt, ViPUInt32 retCnt)
{
	return ::viWrite(vi, buf, cnt, retCnt);
}

ViStatus VisaCaller::viWriteAsync(ViSession vi, ViBuf  buf, ViUInt32 cnt, ViPJobId  jobId)
{
	return ::viWriteAsync(vi, buf, cnt, jobId);
}

ViStatus VisaCaller::viWriteFromFile(ViSession vi, ViConstString filename, ViUInt32 cnt, ViPUInt32 retCnt)
{
	return ::viWriteFromFile(vi, filename, cnt, retCnt);
}

ViStatus VisaCaller::viAssertTrigger(ViSession vi, ViUInt16 protocol)
{
	return ::viAssertTrigger(vi, protocol);
}

ViStatus VisaCaller::viReadSTB(ViSession vi, ViPUInt16 status)
{
	return ::viReadSTB(vi, status);
}

ViStatus VisaCaller::viClear(ViSession vi)
{
	return ::viClear(vi);
}


/*- Formatted and Buffered I/O Operations -----------------------------------*/

ViStatus VisaCaller::viSetBuf(ViSession vi, ViUInt16 mask, ViUInt32 size)
{
	return ::viSetBuf(vi, mask, size);
}


ViStatus VisaCaller::viFlush(ViSession vi, ViUInt16 mask)
{
	return ::viFlush(vi, mask);
}


ViStatus VisaCaller::viBufWrite(ViSession vi, ViBuf  buf, ViUInt32 cnt, ViPUInt32 retCnt)
{
	return ::viBufWrite(vi, buf, cnt, retCnt);
}

ViStatus VisaCaller::viBufRead(ViSession vi, ViPBuf buf, ViUInt32 cnt, ViPUInt32 retCnt)
{
	return ::viBufRead(vi, buf, cnt, retCnt);
}


ViStatus VisaCaller::viPrintf(ViSession vi, ViString writeFmt, ...)
{
	
	va_list list;
	va_start(list, writeFmt);
	ViStatus rtn;
	
	rtn = ::viPrintf(vi, writeFmt, va_pass(list));

	va_end(list);
	
	return rtn;
	
}

ViStatus VisaCaller::viVPrintf(ViSession vi, ViString writeFmt, ViVAList params)
{	
	return ::viVPrintf(vi, writeFmt, params);
}

ViStatus VisaCaller::viSPrintf(ViSession vi, ViPBuf buf, ViString writeFmt, ...)
{
	va_list list;
	va_start(list, writeFmt);
	ViStatus rtn;
	
	rtn = ::viSPrintf(vi, buf, writeFmt, va_pass(list));

	va_end(list);

	return rtn;
}

ViStatus VisaCaller::viVSPrintf(ViSession vi, ViPBuf buf, ViString writeFmt, ViVAList parms)
{
	return ::viVSPrintf(vi, buf, writeFmt, parms);
}


ViStatus VisaCaller::viScanf(ViSession vi, ViString readFmt, ...)
{
	va_list list;
	va_start(list, readFmt);
	ViStatus rtn;
	
	rtn = ::viScanf(vi, readFmt, va_pass(list));

	va_end(list);

	return rtn;
}

ViStatus VisaCaller::viVScanf(ViSession vi, ViString readFmt, ViVAList params)
{
	return ::viVScanf(vi, readFmt, params);
}

ViStatus VisaCaller::viSScanf(ViSession vi, ViBuf buf, ViString readFmt, ...)
{
	va_list list;
	va_start(list, readFmt);
	ViStatus rtn;
	
	rtn = ::viSScanf(vi, buf, readFmt, va_pass(list));

	va_end(list);

	return rtn;
}

ViStatus VisaCaller::viVSScanf(ViSession vi, ViBuf buf, ViString readFmt, ViVAList parms)
{
	return ::viVSScanf(vi, buf, readFmt, parms);
}


ViStatus VisaCaller::viQueryf(ViSession vi, ViString writeFmt, ViString readFmt, ...)
{
	va_list list;
	va_start(list, readFmt);
	ViStatus rtn;
	
	rtn = ::viQueryf(vi, writeFmt, readFmt, va_pass(list));

	va_end(list);

	return rtn;
}

ViStatus VisaCaller::viVQueryf(ViSession vi, ViString writeFmt, ViString readFmt, ViVAList params)
{
	return ::viVQueryf(vi, writeFmt, readFmt, params);
}