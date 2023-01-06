#pragma once
#include <Includes.h>

namespace CMath
{
	Vectors::Vec2 WorldToScreen( Vectors::Vec3 ScreenPos );
	Vectors::Vec3 GetBone( DWORD64 ped , int32_t bone );
	Vectors::Vec2 GetBoneWorldToScreen( DWORD64 ped , int32_t bone );
}