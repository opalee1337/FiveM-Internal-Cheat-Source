#pragma once
#include <Includes.h>

namespace CMath
{
	Vectors::Vec2 WorldToScreen( Vectors::Vec3 ScreenPos );
	Vectors::Vec3 GetBone( DWORD64 CPed , unsigned int bone );
	Vectors::Vec2 GetBoneWorldToScreen( DWORD64 CPed , unsigned int bone );
	float pythag( Vectors::Vec2 src , Vectors::Vec2 dst );
}