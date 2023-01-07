#pragma once
#include <Includes.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndHandling(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
HRESULT __stdcall D3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndHandling);
			ImGui::CreateContext();
			ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 14.0f);
			ImGui_ImplWin32_Init(window);
			ImGui_ImplDX11_Init(pDevice, pContext);
			Offsets::Offsets();

			init = true;
		}
		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (GetAsyncKeyState(VK_F4) & 1)
		Variables::Menu::Show = !Variables::Menu::Show;

	ImGui::GetIO().MouseDrawCursor = Variables::Menu::Show;

	if (Variables::Menu::Show)
	{
		ImGui::Begin("FemboyWare | by Cringe1337#7720 & Ramsey#1337", nullptr);
		{
			if (ImGui::BeginTabBar("##Tabbar"))
			{
				if (ImGui::BeginTabItem("Aimbot"))
				{
					ImGui::Checkbox("Enable Aimbot", &Variables::Aimbot::Enable);
					const char* Bones[4] = { "Head", "Neck", "Body", "Pelvis" };
					ImGui::Combo("Bones", &Variables::Aimbot::Bones, Bones, 4);
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Wallhack"))
				{
					ImGui::Checkbox("Enable", &Variables::ESP::Enable);
					ImGui::Checkbox("Box", &Variables::ESP::Box);
					ImGui::Checkbox("Skeleton", &Variables::ESP::Skeleton);
					ImGui::Checkbox("Snaplines", &Variables::ESP::Snaplines);
					ImGui::Checkbox("Healthbar", &Variables::ESP::Healthbar);
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Misc"))
				{
					if (ImGui::Button("Max Health"))
					{
						SDK::Players::g_sethealth(200);
					}
					if (ImGui::Button("Assault Rifle"))
					{
						Offsets::pLocalPlayerHandle = Offsets::pointer_to_handle(Offsets::g_localplayer);
						Offsets::give_weapon(Offsets::pLocalPlayerHandle, 0xBFEFFF6D, 250, 1);
					}
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
		}
		ImGui::End();

	}

	Aimbot::Aimbot();
	Wallhack::Wallhack();
	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD __stdcall AttachHook(LPVOID lpReserved)
{
	bool hook = false;
	do
	{
		if (d3d11::init(d3d11::RenderType::D3D11) == d3d11::Status::Success)
		{
			d3d11::bind(8, (void**)&oPresent, D3D11Present);
			hook = true;
		}
	} while (!hook);
	return TRUE;
}

BOOL __stdcall DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == 1)
	{
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, AttachHook, hMod, 0, nullptr);
	}
	else if (dwReason == 0)
	{
		d3d11::unload();
	}
	return TRUE;
}