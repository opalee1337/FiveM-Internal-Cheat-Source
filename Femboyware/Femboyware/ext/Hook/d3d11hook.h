#ifndef __d3d11_H__
#define __d3d11_H__

#include <stdint.h>

#define hookd3d11  1
#define d3d11_MINHOOK    1

#define d3d11_ARCH_X64 0
#define d3d11_ARCH_X86 0

#if defined(_M_X64)	
# undef  d3d11_ARCH_X64
# define d3d11_ARCH_X64 1
#else
# undef  d3d11_ARCH_X86
# define d3d11_ARCH_X86 1
#endif

#if d3d11_ARCH_X64
typedef uint64_t uint150_t;
#else
typedef uint32_t uint150_t;
#endif

namespace d3d11
{
	struct Status
	{
		enum Enum
		{
			UnknownError = -1,
			NotSupportedError = -2,
			ModuleNotFoundError = -3,

			AlreadyInitializedError = -4,
			NotInitializedError = -5,

			Success = 0,
		};
	};

	struct RenderType
	{
		enum Enum
		{
			None,
			D3D11,
			Auto
		};
	};

	Status::Enum init(RenderType::Enum renderType);
	void unload();

	Status::Enum bind(uint16_t index, void** original, void* function);
	void unbind(uint16_t index);

	RenderType::Enum getRenderType();
	uint150_t* getMethodsTable();
}

#endif 