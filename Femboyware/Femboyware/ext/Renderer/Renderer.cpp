#pragma once
#include <Renderer.h>

namespace Renderer
{
	bool isonscreen( Vectors::Vec2 coords )
	{
		if ( coords.x < 0.1f || coords.y < 0.1 || coords.x > ImGui::GetIO( ).DisplaySize.x || coords.y > ImGui::GetIO( ).DisplaySize.y )
		{
			return false;
		}
		else {
			return true;
		}
	}
	void DrawLine( Vectors::Vec2 dst , Vectors::Vec2 src , ImColor col , float thickness )
	{
		if ( isonscreen( dst ) && isonscreen( src ) )
		{
			ImGui::GetBackgroundDrawList( )->AddLine( { src.x, src.y } , { dst.x, dst.y } , col , thickness );
		}

	}
	void DrawRect( Vectors::Vec2 dst , Vectors::Vec2 src , ImColor col , bool Filled )
	{
		if ( Filled )
		{
			if ( isonscreen( dst ) && isonscreen( src ) )
			{
				ImGui::GetBackgroundDrawList( )->AddRectFilled( { src.x, src.y } , { dst.x, dst.y } , col );
			}
		}
		else
		{
			if ( isonscreen( dst ) && isonscreen( src ) )
			{
				ImGui::GetBackgroundDrawList( )->AddRect( { src.x, src.y } , { dst.x, dst.y } , col );
			}
		}
	}
	void DrawHealthBar( Vectors::Vec2 pos , Vectors::Vec2 dim , ImColor col )
	{
		DrawLine( pos , Vectors::Vec2( pos.x , pos.y - dim.y ) , col , dim.x );
	}
}