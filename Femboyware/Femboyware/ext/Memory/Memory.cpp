#pragma once
#include "Memory.h"

namespace Memory
{
	DWORD_PTR GetProcBase( DWORD processID )
	{
		DWORD_PTR baseAddress = 0;
		HANDLE processHandle = OpenProcess( PROCESS_ALL_ACCESS , FALSE , processID );
		HMODULE* moduleArray;
		LPBYTE moduleArrayBytes;
		DWORD bytesRequired;
		if ( processHandle )
		{
			if ( K32EnumProcessModules( processHandle , NULL , 0 , &bytesRequired ) )
			{
				if ( bytesRequired )
				{
					moduleArrayBytes = (LPBYTE) LocalAlloc( LPTR , bytesRequired );
					if ( moduleArrayBytes )
					{
						unsigned int moduleCount;
						moduleCount = bytesRequired / sizeof( HMODULE );
						moduleArray = (HMODULE*) moduleArrayBytes;
						if ( EnumProcessModules( processHandle , moduleArray , bytesRequired , &bytesRequired ) )
						{
							baseAddress = (DWORD_PTR) moduleArray [ 0 ];
						}
						LocalFree( moduleArrayBytes );
					}
				}
			}
			CloseHandle( processHandle );
		}
		return baseAddress;
	}
	DWORD64 SignatureScanEx( DWORD64 BaseAddy , const char* Signature , size_t resultindex )
	{
		static auto patternToByte = [ ] ( const char* pattern )
		{
			auto       bytes = std::vector<int> {};
			const auto start = const_cast<char*>( pattern );
			const auto end = const_cast<char*>( pattern ) + strlen( pattern );

			for ( auto current = start; current < end; ++current )
			{
				if ( *current == '?' )
				{
					++current;
					if ( *current == '?' )
						++current;
					bytes.push_back( -1 );
				}
				else
					bytes.push_back( strtoul( (const char*) current , &current , 16 ) );
			}
			return bytes;
		};

		const auto dosHeader = (PIMAGE_DOS_HEADER) BaseAddy;
		const auto ntHeaders = (PIMAGE_NT_HEADERS) ( (std::uint8_t*) BaseAddy + dosHeader->e_lfanew );

		const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
		auto       patternBytes = patternToByte( Signature );
		const auto scanBytes = reinterpret_cast<std::uint8_t*>( BaseAddy );

		const auto s = patternBytes.size( );
		const auto d = patternBytes.data( );

		size_t nFoundResults = 0;

		for ( auto i = 0ul; i < sizeOfImage - s; ++i )
		{
			bool found = true;

			for ( auto j = 0ul; j < s; ++j )
			{
				if ( scanBytes [ i + j ] != d [ j ] && d [ j ] != -1 )
				{
					found = false;
					break;
				}
			}

			if ( found )
			{
				if ( resultindex != 0 )
				{
					if ( nFoundResults < resultindex )
					{
						nFoundResults++;
						found = false;
					}
					else
						return reinterpret_cast<uint64_t>( &scanBytes [ i ] );
				}
				else
					return reinterpret_cast<uint64_t>( &scanBytes [ i ] );
			}
		}

		return NULL;
	}

	DWORD64 ResolveRelativeAddress( uint64_t Address , int InstructionLength )
	{
		DWORD Offset = *(DWORD*) ( Address + ( InstructionLength - 4 ) );
		return Address + InstructionLength + Offset;
	}

	DWORD64 SignatureScan( const char* Signature , size_t resulindex , int InstructionLength )
	{
		auto returnval = SignatureScanEx( (DWORD64) GetModuleHandleA( nullptr ) , Signature , resulindex );

		if ( InstructionLength != 0 )
			returnval = ResolveRelativeAddress( returnval , InstructionLength );

		return returnval;
	}
}