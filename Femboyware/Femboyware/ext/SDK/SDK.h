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
		Vectors::Vec3 g_crosshair_pos( );
		Vectors::Vec3 g_tps_angles( );
	}
	namespace ObjectNavigation
	{
		
	}
}