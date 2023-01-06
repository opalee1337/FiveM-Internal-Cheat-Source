#include <d3d11hook.h>
#include <Windows.h>
#include <assert.h>

#if hookd3d11
# include <dxgi.h>
# include <d3d11.h>
#endif

#if d3d11_MINHOOK
# include "minhook/include/MinHook.h"
#endif

#ifdef _UNICODE
# define d3d11_TEXT(text) L##text
#else
# define d3d11_TEXT(text) text
#endif

#define d3d11_ARRAY_SIZE(arr) ((size_t)(sizeof(arr)/sizeof(arr[0])))

static d3d11::RenderType::Enum g_renderType = d3d11::RenderType::None;
static uint150_t* g_methodsTable = NULL;

d3d11::Status::Enum d3d11::init(RenderType::Enum _renderType)
{
	if (g_renderType != RenderType::None)
	{
		return Status::AlreadyInitializedError;
	}

	if (_renderType != RenderType::None)
	{
		
			WNDCLASSEX windowClass;
			windowClass.cbSize = sizeof(WNDCLASSEX);
			windowClass.style = CS_HREDRAW | CS_VREDRAW;
			windowClass.lpfnWndProc = DefWindowProc;
			windowClass.cbClsExtra = 0;
			windowClass.cbWndExtra = 0;
			windowClass.hInstance = GetModuleHandle(NULL);
			windowClass.hIcon = NULL;
			windowClass.hCursor = NULL;
			windowClass.hbrBackground = NULL;
			windowClass.lpszMenuName = NULL;
			windowClass.lpszClassName = d3d11_TEXT("d3d11");
			windowClass.hIconSm = NULL;

			::RegisterClassEx(&windowClass);

			HWND window = ::CreateWindow(windowClass.lpszClassName, d3d11_TEXT("d3d11 DirectX Window"), WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);

			if (_renderType == RenderType::D3D11)
			{
#if hookd3d11
				HMODULE libD3D11;
				if ((libD3D11 = ::GetModuleHandle(d3d11_TEXT("d3d11.dll"))) == NULL)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::ModuleNotFoundError;
				}

				void* D3D11CreateDeviceAndSwapChain;
				if ((D3D11CreateDeviceAndSwapChain = ::GetProcAddress(libD3D11, "D3D11CreateDeviceAndSwapChain")) == NULL)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				D3D_FEATURE_LEVEL featureLevel;
				const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0 };

				DXGI_RATIONAL refreshRate;
				refreshRate.Numerator = 60;
				refreshRate.Denominator = 1;

				DXGI_MODE_DESC bufferDesc;
				bufferDesc.Width = 100;
				bufferDesc.Height = 100;
				bufferDesc.RefreshRate = refreshRate;
				bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
				bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

				DXGI_SAMPLE_DESC sampleDesc;
				sampleDesc.Count = 1;
				sampleDesc.Quality = 0;

				DXGI_SWAP_CHAIN_DESC swapChainDesc;
				swapChainDesc.BufferDesc = bufferDesc;
				swapChainDesc.SampleDesc = sampleDesc;
				swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				swapChainDesc.BufferCount = 1;
				swapChainDesc.OutputWindow = window;
				swapChainDesc.Windowed = 1;
				swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
				swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

				IDXGISwapChain* swapChain;
				ID3D11Device* device;
				ID3D11DeviceContext* context;

				if (((long(__stdcall*)(
					IDXGIAdapter*,
					D3D_DRIVER_TYPE,
					HMODULE,
					UINT,
					const D3D_FEATURE_LEVEL*,
					UINT,
					UINT,
					const DXGI_SWAP_CHAIN_DESC*,
					IDXGISwapChain**,
					ID3D11Device**,
					D3D_FEATURE_LEVEL*,
					ID3D11DeviceContext**))(D3D11CreateDeviceAndSwapChain))(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevels, 1, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &featureLevel, &context) < 0)
				{
					::DestroyWindow(window);
					::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
					return Status::UnknownError;
				}

				g_methodsTable = (uint150_t*)::calloc(205, sizeof(uint150_t));
				::memcpy(g_methodsTable, *(uint150_t**)swapChain, 18 * sizeof(uint150_t));
				::memcpy(g_methodsTable + 18, *(uint150_t**)device, 43 * sizeof(uint150_t));
				::memcpy(g_methodsTable + 18 + 43, *(uint150_t**)context, 144 * sizeof(uint150_t));

#if d3d11_MINHOOK
				MH_Initialize();
#endif

				swapChain->Release();
				swapChain = NULL;

				device->Release();
				device = NULL;

				context->Release();
				context = NULL;

				::DestroyWindow(window);
				::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

				g_renderType = RenderType::D3D11;

				return Status::Success;
#endif
			}
	 

			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

			return Status::NotSupportedError;
		
	}

	return Status::Success;
}

void d3d11::unload()
{
	if (g_renderType != RenderType::None)
	{
#if d3d11_USE_MINHOOK
		MH_DisableHook(MH_ALL_HOOKS);
#endif

		::free(g_methodsTable);
		g_methodsTable = NULL;
		g_renderType = RenderType::None;
	}
}

d3d11::Status::Enum d3d11::bind(uint16_t _index, void** _original, void* _function)
{
	// TODO: Need own detour function

	assert(_index >= 0 && _original != NULL && _function != NULL);

	if (g_renderType != RenderType::None)
	{
#if d3d11_MINHOOK
		void* target = (void*)g_methodsTable[_index];
		if (MH_CreateHook(target, _function, _original) != MH_OK || MH_EnableHook(target) != MH_OK)
		{
			return Status::UnknownError;
		}
#endif

		return Status::Success;
	}

	return Status::NotInitializedError;
}

void d3d11::unbind(uint16_t _index)
{
	assert(_index >= 0);

	if (g_renderType != RenderType::None)
	{
#if d3d11_MINHOOK
		MH_DisableHook((void*)g_methodsTable[_index]);
#endif
	}
}

d3d11::RenderType::Enum d3d11::getRenderType()
{
	return g_renderType;
}

uint150_t* d3d11::getMethodsTable()
{
	return g_methodsTable;
} 