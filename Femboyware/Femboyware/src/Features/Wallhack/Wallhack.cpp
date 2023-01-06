#pragma once
#include <Wallhack.h>

namespace Wallhack
{
	void Wallhack( )
	{
		if ( Variables::ESP::Enable )
		{
			uintptr_t pedinterface = *(uintptr_t*) ( Offsets::g_replayinterface + 0x18 );

			for ( int i = 0; i < 255; i++ )
			{
				uintptr_t pedlist = *(uintptr_t*) ( pedinterface + 0x100 );
				uintptr_t ped = *(uintptr_t*) ( pedlist + ( i * 0x10 ) );   if ( !ped ) continue;
				if ( ped == Offsets::g_localplayer ) continue;

				Vectors::Vec3 PedPosVec3 = SDK::Players::VisualPos( ped );

				Vectors::Vec2 PedPos = CMath::WorldToScreen( PedPosVec3 );

				if ( Variables::ESP::Box )
				{
					ImGui::GetBackgroundDrawList( )->AddCircleFilled( { PedPos.x, PedPos.y } , 5 , ImColor( 255 , 255 , 255 ) , 100 ); 
				}
			}
		}
	}
}