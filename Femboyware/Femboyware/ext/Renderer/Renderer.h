#pragma once
#include <Includes.h>

namespace Renderer
{
	bool isonscreen( Vectors::Vec2 coords );
	void DrawLine( Vectors::Vec2 dst , Vectors::Vec2 src , ImColor col , float thickness = 1 );
}