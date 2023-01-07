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

	Vectors::Vec3 GetBone( DWORD64 CPed , unsigned int bone ) {
		__m128 a1;
		Offsets::g_bone_mask( CPed , &a1 , bone );
		return Vectors::Vec3::FromM128( a1 );
	}
	Vectors::Vec2 GetBoneWorldToScreen( DWORD64 CPed , unsigned int bone )
	{
		return WorldToScreen( GetBone( CPed , bone ) );
	}
	float pythag( Vectors::Vec2 src , Vectors::Vec2 dst )
	{
		return sqrtf( pow( src.x - dst.x , 2 ) + pow( src.y - dst.y , 2 ) );
	}
}