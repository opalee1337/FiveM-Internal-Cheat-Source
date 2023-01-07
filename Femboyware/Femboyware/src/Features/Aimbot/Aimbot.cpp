#pragma once
#include <Aimbot.h>

namespace Aimbot
{
	
	uintptr_t GetBestTarget( )
	{
		uintptr_t ClosestPlayer = 0;
		float closestdist = FLT_MAX;
		float dist;
		uintptr_t pedinterface = *(uintptr_t*) ( Offsets::g_replayinterface + 0x18 );

		for ( int i = 0; i < 255; i++ )
		{
			uintptr_t pedlist = *(uintptr_t*) ( pedinterface + 0x100 );
			uintptr_t CPed = *(uintptr_t*) ( pedlist + ( i * 0x10 ) );   if ( !CPed ) continue;



			if ( CPed == Offsets::g_localplayer ) continue;
			float Health = *(float*) ( CPed + 0x280 );
			if ( Health <= 0 ) continue;





			Vectors::Vec3 PedPosVec3 = SDK::Players::VisualPos( CPed );
			Vectors::Vec2 PedPos = CMath::WorldToScreen( PedPosVec3 );

			Vectors::Vec2 Head = CMath::GetBoneWorldToScreen( CPed , 0x796E );


			Vectors::Vec2 middle = Vectors::Vec2( GetSystemMetrics( SM_CXSCREEN ) / 2 , GetSystemMetrics( SM_CYSCREEN ) / 2 );
			dist = CMath::pythag( middle , Head );



			if ( dist < closestdist )
			{
				closestdist = dist;
				ClosestPlayer = CPed;
			}





		}
		return ClosestPlayer;
	}
	void Aimbot()
	{
		if ( Variables::Aimbot::Enable )
		{


			if ( GetAsyncKeyState( VK_RBUTTON ) & 0x8000 ) {
				DWORD64 cam = SDK::Camera::GetCam( );
				Vectors::Vec3 CrosshairPos = SDK::Camera::g_crosshair_pos( );
				auto bone = CMath::GetBone( GetBestTarget( ) , 0x796E );
				switch ( Variables::Aimbot::Bones )
				{
				case 1:
					bone = CMath::GetBone( GetBestTarget( ) , 0x9995);
					break;
				case 2:
					bone = CMath::GetBone( GetBestTarget( ) , 0x60f2);
					break;
				case 3:
					bone = CMath::GetBone( GetBestTarget( ) , 0x2E28);
					break;
				}
				Vectors::Vec3 aimpos = bone;

				Vectors::Vec3 distance( CrosshairPos.x - aimpos.x , CrosshairPos.y - aimpos.y , CrosshairPos.z - aimpos.z );

				float Distance = distance.Length( );
				Vectors::Vec3 Out = Vectors::Vec3( ( aimpos.x - CrosshairPos.x ) / Distance , ( aimpos.y - CrosshairPos.y ) / Distance , ( aimpos.z - CrosshairPos.z ) / Distance );

				SDK::Camera::m_fps_angles( Out );
				SDK::Camera::m_tps_angles( Out );
			}

		}
		 
	}
}