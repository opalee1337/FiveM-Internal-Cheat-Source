#pragma once
#include <SDK.h>

namespace SDK
{
	namespace Players
	{
		float g_sethealth( float health )
		{
			return *(float*) ( Offsets::g_localplayer + Offsets::g_health ) = health;
		}
		float g_setarmor( float armor )
		{
			return *(float*) ( Offsets::g_localplayer + Offsets::g_armor ) = armor;
		}
		Vectors::Vec3 VisualPos( DWORD64 ped )
		{
			return *(Vectors::Vec3*) ( ped + 0x90 ); 
		}
	}
	namespace Camera
	{
		DWORD64 GetCam( )
		{
			if ( Offsets::g_camera )
				return *(DWORD64*) ( Offsets::g_camera + 0x0 );
		};
		Vectors::Vec3 g_crosshair_pos( )
		{
			return *(Vectors::Vec3*) ( GetCam( ) + 0x60 );
		}
		Vectors::Vec3 g_tps_angles( )
		{
			return *(Vectors::Vec3*) ( GetCam( ) + 0x03D0 );
		}
		Vectors::Vec3 m_fps_angles( Vectors::Vec3 Out )
		{
			return *(Vectors::Vec3*) ( GetCam( ) + 0x40 ) = Out;
		}
		Vectors::Vec3 m_tps_angles( Vectors::Vec3 Out )
		{
			return *(Vectors::Vec3*) ( GetCam( ) + 0x3D0 ) = Out;
		}
	}
}