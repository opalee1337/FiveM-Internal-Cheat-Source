#pragma once
#include <Includes.h>

namespace Memory
{
	DWORD_PTR GetProcBase( DWORD processID );
	DWORD64 SignatureScanEx( DWORD64 BaseAddy , const char* Signature , size_t resultindex );
	DWORD64 ResolveRelativeAddress( uint64_t Address , int InstructionLength );
	DWORD64 SignatureScan( const char* Signature , size_t resulindex , int InstructionLength );
}