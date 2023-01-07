#pragma once
#include <Includes.h>

namespace Vectors
{
	class Vec2 final
	{
	public:

		float x , y;

		Vec2( const float x , const float y ) : x( x ) , y( y ) {}
		constexpr Vec2( ) : x( 0.0f ) , y( 0.0f ) { };
		float  operator[] ( size_t idx ) const { IM_ASSERT( idx == 0 || idx == 1 ); return ( &x ) [ idx ]; }
		float& operator[] ( size_t idx ) { IM_ASSERT( idx == 0 || idx == 1 ); return ( &x ) [ idx ]; }
	};

	class Vec3 final
	{
	public:

		float x , y , z;

		Vec3( const float x , const float y , const float z ) : x( x ) , y( y ) , z( z ) {}
		Vec3 operator + ( const Vec3& rhs ) const { return Vec3( x + rhs.x , y + rhs.y , z + rhs.z ); }
		Vec3 operator - ( const Vec3& rhs ) const { return Vec3( x - rhs.x , y - rhs.y , z - rhs.z ); }
		Vec3 operator * ( const float& rhs ) const { return Vec3( x * rhs , y * rhs , z * rhs ); }
		Vec3 operator / ( const float& rhs ) const { return Vec3( x / rhs , y / rhs , z / rhs ); }
		bool operator == ( const Vec3& rhs ) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
		Vec3& operator += ( const Vec3& rhs ) { return *this = *this + rhs; }
		Vec3& operator -= ( const Vec3& rhs ) { return *this = *this - rhs; }
		Vec3& operator *= ( const float& rhs ) { return *this = *this * rhs; }
		Vec3& operator /= ( const float& rhs ) { return *this = *this / rhs; }
		float Length( ) const { return sqrt( x * x + y * y + z * z ); }
		Vec3 Normalize( ) const { return *this * ( 1 / Length( ) ); }
		Vec3 Multiple( const Vec3 caca ) const { return Vec3( x * caca.x , y * caca.y , z * caca.z ); }

		float Distance( const Vec3& rhs ) const { return ( *this - rhs ).Length( ); }
		void Invert( ) { *this *= -1; }
		static Vec3 FromM128( __m128 in ) { return Vec3( in.m128_f32 [ 0 ] , in.m128_f32 [ 1 ] , in.m128_f32 [ 2 ] ); }
	};

	class Vec4
	{
	public:
		float x , y , z , w;
	};
}