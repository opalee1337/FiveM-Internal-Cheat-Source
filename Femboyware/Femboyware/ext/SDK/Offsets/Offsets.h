#pragma once
#include <Includes.h>

namespace Offsets
{
	inline DWORD64 g_world , g_camera , g_replayinterface, g_bone_mask , g_localplayer , g_world_to_screen;

	inline DWORD g_armor , g_world_ptr , g_replayinterface_ptr , g_health , g_entity_type; 

	void Offsets( );
}