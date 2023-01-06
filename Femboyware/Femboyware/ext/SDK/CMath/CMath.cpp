#pragma once
#include "CMath.h"

namespace CMath
{
	Vectors::Vec2 WorldToScreen( Vectors::Vec3 ScreenPos )
	{
		auto& io = ImGui::GetIO( );
		Vectors::Vec2 tempVec2( 0.0f , 0.0f );
		reinterpret_cast<bool( __fastcall* )( Vectors::Vec3* , float* , float* )>( Offsets::g_world_to_screen )( &ScreenPos , &tempVec2.x , &tempVec2.y );
		tempVec2.x *= io.DisplaySize.x;
		tempVec2.y *= io.DisplaySize.y;
		return tempVec2;
	}

	Vectors::Vec3 GetBone( DWORD64 ped , int32_t bone )
	{
	 return (Vectors::Vec3) Vectors::Vec3( 0 , 0, 0);
	}
	Vectors::Vec2 GetBoneWorldToScreen( DWORD64 ped , int32_t bone )
	{
		return (Vectors::Vec2) Vectors::Vec2( 0 , 0 );
	}
}