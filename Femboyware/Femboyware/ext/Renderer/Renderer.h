#pragma once
#include <Includes.h>

namespace Renderer
{
	bool isonscreen( Vectors::Vec2 coords );
	void DrawLine( Vectors::Vec2 dst , Vectors::Vec2 src , ImColor col , float thickness = 1 );
	void DrawRect( Vectors::Vec2 dst , Vectors::Vec2 src , ImColor col , bool Filled = false );
	void DrawHealthBar( Vectors::Vec2 pos , Vectors::Vec2 dim , ImColor col );
}