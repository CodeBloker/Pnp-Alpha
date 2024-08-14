#ifndef _HVS_CHECKSUM_H_
#define _HVS_CHECKSUM_H_
extern "C" __declspec(dllexport) unsigned short	_stdcall crc16(unsigned char* pDataBuffer, unsigned int length);
extern "C" __declspec(dllexport) unsigned short	_stdcall crc16_fast(unsigned char* pDataBuffer, unsigned int length);

#endif /* _HVS_CHECKSUM_H_ */