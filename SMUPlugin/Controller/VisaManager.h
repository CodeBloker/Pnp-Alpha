#pragma once

#include "SmuDefine.h"
#include "visa.h"

#ifndef _X86_
	 #pragma comment(lib, "visa64.lib")
#else
	 #pragma comment(lib, "visa32.lib")
#endif

// Variable parameter wrapping definition
template<unsigned char count>
struct SVaPassNext
{
	SVaPassNext<count - 1> big;
	unsigned long dw;
};
template<> struct SVaPassNext<0> {};
//SVaPassNext : A structure that determines how many parameters are allowed at compile time

class CVaPassNext
{
public:
	SVaPassNext<50> svapassnext;		// Up to 50 parameters

	CVaPassNext(va_list & args) {
		try
		{
			memcpy(&svapassnext, args, sizeof(svapassnext));
		}
		catch (...) {}
	}
};

#define va_pass(valist) CVaPassNext(valist).svapassnext


class VisaManager
{
public:
	VisaManager();
	~VisaManager();

	ViStatus viOpenDefaultRM (ViPSession vi);
	ViStatus viFindRsrc      (ViSession sesn, ViString expr, ViPFindList vi, ViPUInt32 retCnt, ViChar _VI_FAR desc[]);
	ViStatus viFindNext      (ViFindList vi, ViChar _VI_FAR desc[]);
	ViStatus viParseRsrc     (ViSession rmSesn, ViRsrc rsrcName, ViPUInt16 intfType, ViPUInt16 intfNum);
	ViStatus viParseRsrcEx   (ViSession rmSesn, ViRsrc rsrcName, ViPUInt16 intfType,
										ViPUInt16 intfNum, ViChar _VI_FAR rsrcClass[],
										ViChar _VI_FAR expandedUnaliasedName[],
										ViChar _VI_FAR aliasIfExists[]);
	ViStatus viOpen          (ViSession sesn, ViRsrc name, ViAccessMode mode, ViUInt32 timeout, ViPSession vi);

	/*- Resource Template Operations --------------------------------------------*/

	ViStatus viClose         (ViObject vi);
	ViStatus viSetAttribute  (ViObject vi, ViAttr attrName, ViAttrState attrValue);
	ViStatus viGetAttribute  (ViObject vi, ViAttr attrName, void _VI_PTR attrValue);
	ViStatus viStatusDesc    (ViObject vi, ViStatus status, ViChar _VI_FAR desc[]);
	ViStatus viTerminate     (ViObject vi, ViUInt16 degree, ViJobId jobId);

	ViStatus viLock          (ViSession vi, ViAccessMode lockType, ViUInt32 timeout, ViKeyId requestedKey, ViChar _VI_FAR accessKey[]);
	ViStatus viUnlock        (ViSession vi);
	ViStatus viEnableEvent   (ViSession vi, ViEventType eventType, ViUInt16 mechanism, ViEventFilter context);
	ViStatus viDisableEvent  (ViSession vi, ViEventType eventType, ViUInt16 mechanism);
	ViStatus viDiscardEvents (ViSession vi, ViEventType eventType, ViUInt16 mechanism);
	ViStatus viWaitOnEvent   (ViSession vi, ViEventType inEventType, ViUInt32 timeout, ViPEventType outEventType, ViPEvent outContext);
	ViStatus viInstallHandler(ViSession vi, ViEventType eventType, ViHndlr handler,	ViAddr userHandle);
	ViStatus viUninstallHandler(ViSession vi, ViEventType eventType, ViHndlr handler, ViAddr userHandle);

	/*- Basic I/O Operations ----------------------------------------------------*/

	ViStatus viRead          (ViSession vi, ViPBuf buf, ViUInt32 cnt, ViPUInt32 retCnt);
	ViStatus viReadAsync     (ViSession vi, ViPBuf buf, ViUInt32 cnt, ViPJobId  jobId);
	ViStatus viReadToFile    (ViSession vi, ViConstString filename, ViUInt32 cnt, ViPUInt32 retCnt);
	ViStatus viWrite         (ViSession vi, ViBuf  buf, ViUInt32 cnt, ViPUInt32 retCnt);
	ViStatus viWriteAsync    (ViSession vi, ViBuf  buf, ViUInt32 cnt, ViPJobId  jobId);
	ViStatus viWriteFromFile (ViSession vi, ViConstString filename, ViUInt32 cnt, ViPUInt32 retCnt);
	ViStatus viAssertTrigger (ViSession vi, ViUInt16 protocol);
	ViStatus viReadSTB       (ViSession vi, ViPUInt16 status);
	ViStatus viClear         (ViSession vi);

	/*- Formatted and Buffered I/O Operations -----------------------------------*/

	ViStatus viSetBuf        (ViSession vi, ViUInt16 mask, ViUInt32 size);
	ViStatus viFlush         (ViSession vi, ViUInt16 mask);

	ViStatus viBufWrite      (ViSession vi, ViBuf  buf, ViUInt32 cnt, ViPUInt32 retCnt);
	ViStatus viBufRead       (ViSession vi, ViPBuf buf, ViUInt32 cnt, ViPUInt32 retCnt);

	ViStatus viPrintf        (ViSession vi, ViString writeFmt, ...);
	ViStatus viVPrintf       (ViSession vi, ViString writeFmt, ViVAList params);
	ViStatus viSPrintf       (ViSession vi, ViPBuf buf, ViString writeFmt, ...);
	ViStatus viVSPrintf      (ViSession vi, ViPBuf buf, ViString writeFmt, ViVAList parms);

	ViStatus viScanf         (ViSession vi, ViString readFmt, ...);
	ViStatus viVScanf        (ViSession vi, ViString readFmt, ViVAList params);
	ViStatus viSScanf        (ViSession vi, ViBuf buf, ViString readFmt, ...);
	ViStatus viVSScanf       (ViSession vi, ViBuf buf, ViString readFmt, ViVAList parms);

	ViStatus viQueryf        (ViSession vi, ViString writeFmt, ViString readFmt, ...);
	ViStatus viVQueryf       (ViSession vi, ViString writeFmt, ViString readFmt, ViVAList params);
};