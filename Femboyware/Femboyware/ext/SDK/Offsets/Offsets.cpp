#pragma once
#include "Offsets.h"

namespace Offsets
{
	void Offsets()
	{
		DWORD_PTR BaseAddy = Memory::GetProcBase( GetCurrentProcessId( ) );

	 
		if ( (GetModuleHandleA) ( "FiveM_GTAProcess.exe" ) || (GetModuleHandleA) ( "FiveM_b2545_GameProcess.exe" ) )
		{
			g_world_ptr = 0x247F840;
			g_replayinterface_ptr = 0x1EFD4C8;
		}
		if ( (GetModuleHandleA) ( "FiveM_b2545_GTAProcess.exe" ) || (GetModuleHandleA) ( "FiveM_b2545_GameProcess.exe" ) )
		{
			g_world_ptr = 0x25667E8;
			g_replayinterface_ptr = 0x1F2E7A8;
		}
		if ( (GetModuleHandleA) ( "FiveM_b2699_GTAProcess.exe" ) || (GetModuleHandleA) ( "FiveM_b2699_GameProcess.exe" ) )
		{
			g_world_ptr = 0x26684D8;
			g_replayinterface_ptr = 0x20304C8;
		}
		if ( (GetModuleHandleA) ( "FiveM_b2189_GTAProcess.exe" ) || (GetModuleHandleA) ( "FiveM_b2189_GameProcess.exe" ) )
		{
			g_world_ptr = 0x24E6D90;
			g_replayinterface_ptr = 0x026332B8;
		}

		g_world = *(DWORD64*) ( BaseAddy + g_world_ptr );
		g_replayinterface = *(DWORD64*) ( BaseAddy + g_replayinterface_ptr );
		g_camera = Memory::SignatureScan( "48 8B 05 ? ? ? ? 48 8B 98 ? ? ? ? EB" , 0 , 7 ); 
		g_world_to_screen = Memory::SignatureScan( "48 89 5C 24 ?? 55 56 57 48 83 EC 70 65 4C 8B 0C 25" , 0 , 0 );
		g_bone_mask = (g_bone_mask_t) ( Memory::SignatureScan( "48 8B 01 41 8B E8 48 8B F2" , 0 , 0 ) - 0x14 );
		pointer_to_handle = (pointer_handler_t) Memory::SignatureScan( "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10 33 DB" , 0 , 0 );
		give_weapon = (give_weapon_t) Memory::SignatureScan( "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 41 8A E9 41 8B F0 8B FA E8 ? ? ? ?" , 0 , 0 ); 
		g_localplayer = *(DWORD64*) ( g_world + 0x8 );
	}
}