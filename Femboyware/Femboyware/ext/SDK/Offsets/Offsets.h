#pragma once
#include <Includes.h>

namespace Offsets
{
	inline DWORD64 g_world , g_camera , g_replayinterface , g_localplayer , g_world_to_screen;

	inline DWORD g_armor , g_world_ptr , g_replayinterface_ptr , g_health , g_entity_type; 

	inline DWORD pLocalPlayerHandle = 0x0;

	typedef BOOL(__fastcall* g_bone_mask_t)(DWORD64 CPed, __m128* virtualbonepos, unsigned int bone);
	inline g_bone_mask_t g_bone_mask = nullptr;

	using pointer_handler_t = int32_t(*)(intptr_t pointer);
	inline pointer_handler_t pointer_to_handle = nullptr; 

	using give_weapon_t = void(*)(int32_t ped, uintptr_t hash, int ammo, bool equip_now);
	inline give_weapon_t give_weapon = nullptr;

	void Offsets( );
}