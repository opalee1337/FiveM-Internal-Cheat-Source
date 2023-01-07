#pragma once
#include <Includes.h>

namespace SDK
{
	namespace Players
	{
		float g_sethealth( float health );
		float g_setarmor( float armor );
		Vectors::Vec3 VisualPos( DWORD64 ped );
	}
	namespace Camera
	{
		DWORD64 GetCam( );
		Vectors::Vec3 g_crosshair_pos( );
		Vectors::Vec3 g_tps_angles( );
		Vectors::Vec3 m_fps_angles( Vectors::Vec3 Out );
		Vectors::Vec3 m_tps_angles( Vectors::Vec3 Out );
	}
	namespace ObjectNavigation
	{
		
	}
}