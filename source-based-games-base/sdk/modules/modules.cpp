#include "pch.h"
#include "modules.h"


void c_modules::init() const
{
	c_logger::get()->printf(log_t::info, "initalizing module list ...");
	g_sdk.m_modules.m_client_dll		= GetModuleHandle("client.dll");
	g_sdk.m_modules.m_engine_dll		= GetModuleHandle("engine.dll");
	g_sdk.m_modules.m_vgui_dll			= GetModuleHandle("vguimatsurface.dll");
	g_sdk.m_modules.m_mat_sys_dll		= GetModuleHandle("materialsystem.dll");
	g_sdk.m_modules.m_vstd_dll			= GetModuleHandle("vstdlib.dll");
	g_sdk.m_modules.m_data_cache_dll	= GetModuleHandle("datacache.dll");
	g_sdk.m_modules.m_shader_dll		= GetModuleHandle("shaderapidx9.dll");
	
	ASSERT(g_sdk.m_modules.m_client_dll != nullptr, "m_modules.m_client_dll is nullptr");
	ASSERT(g_sdk.m_modules.m_engine_dll != nullptr, "m_modules.m_engine_dll is nullptr");
	ASSERT(g_sdk.m_modules.m_vgui_dll != nullptr, "m_modules.m_vgui_dll is nullptr");
	ASSERT(g_sdk.m_modules.m_mat_sys_dll != nullptr, "m_modules.m_mat_sys_dll is nullptr");
	ASSERT(g_sdk.m_modules.m_vstd_dll != nullptr, "m_modules.m_vstd_dll is nullptr");
	ASSERT(g_sdk.m_modules.m_data_cache_dll != nullptr, "m_modules.m_data_cache_dll is nullptr");
	ASSERT(g_sdk.m_modules.m_shader_dll != nullptr, "m_modules.m_shader_dll is nullptr");

	g_sdk.m_return_adress.m_client = g_utils.find_sig(g_sdk.m_modules.m_client_dll, "FF 52 04 85 C0 74 0C 56") + 0x3;
	g_sdk.m_return_adress.m_engine = g_utils.find_sig(g_sdk.m_modules.m_engine_dll, "FF 52 04 85 C0 74 0C 56") + 0x3;
	// Ret address
// 	constexpr long long buffer = 0x69690004C201B0;
// 	static std::string sig = "55 8B EC 56 8B F1 33 C0 57 8B 7D 08"; // \xE8\x00\x00\x00\x00\x84\xC0\x75\x15\xFF\x75\x10
// 
// 	LPCWSTR modules[]
// 	{
// 		L"client.dll",
// 		L"engine.dll",
// 		L"server.dll",
// 		L"studiorender.dll",
// 		L"materialsystem.dll",
// 		L"server.dll"
// 	};
// 
// 	for (const auto base : modules)
// 	{
// 		WriteProcessMemory(GetCurrentProcess(), c_utils::find_sig(GetModuleHandleW(base), sig), &buffer, 5, nullptr);
// 	}
}
