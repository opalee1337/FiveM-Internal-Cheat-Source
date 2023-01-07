#pragma once
#include <d3d11.h>
#include <iostream>
#include <string>
#include <vector>
#include <Psapi.h>
#include <xmmintrin.h>

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <imgui_internal.h>


#include <Memory.h>

#include <Variables.h>

#include <Vectors.h>

#include <Renderer.h>

#include <Offsets.h>
#include <SDK.h>
#include <CMath.h>

#include <Aimbot.h>
#include <Wallhack.h>

#include <d3d11hook.h>

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

inline Present oPresent;
inline HWND window {}; 
inline WNDPROC oWndProc {};		  
inline ID3D11Device* pDevice {}; 
inline ID3D11DeviceContext* pContext {}; 
inline ID3D11RenderTargetView* mainRenderTargetView {};
