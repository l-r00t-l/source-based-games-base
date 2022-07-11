#include "pch.h"

#include "interfaces.h"
#include "../sdk.hpp"

template<typename interface_>
interface_* c_interfaces::get_interface(const char* module_name, const char* interface_name) const
{
	const HINSTANCE module = GetModuleHandle(module_name);

	if (!module)
		return nullptr;
	using _create_interface = interface_ * (__cdecl*)(const char*, int*);
	const _create_interface create_interface = reinterpret_cast<_create_interface>(GetProcAddress(module, "CreateInterface"));

	return create_interface(interface_name, nullptr);
}


template<typename interface_>
interface_* c_interfaces::get_interface(HMODULE module, const char* interface_name) const
{
	if (!module)
		return nullptr;

	using _create_interface = interface_ * (__cdecl*)(const char*, int*);
	const _create_interface create_interface = reinterpret_cast<_create_interface>(GetProcAddress(module, "CreateInterface"));
	return create_interface(interface_name, nullptr);
}


void c_interfaces::init() const
{
	c_logger::get()->printf(log_t::info, "initalizing interface list ...");
	g_sdk.m_interfaces.m_client			= this->get_interface<i_base_client_dll>(g_sdk.m_modules.m_client_dll, VERSION_CLIENT_STRING);
	g_sdk.m_interfaces.m_client_mode	= **reinterpret_cast<i_client_mode_shared***>((*reinterpret_cast<unsigned int**>(g_sdk.m_interfaces.m_client))[10] + 5);
	g_sdk.m_interfaces.m_engine			= this->get_interface<i_engine>(g_sdk.m_modules.m_engine_dll, VERSION_ENGINE_STRING);
	g_sdk.m_interfaces.m_entity_list	= this->get_interface<i_client_entity_list>(g_sdk.m_modules.m_client_dll, VERSION_CLIENT_ENTITY_LIST_STRING);
	g_sdk.m_interfaces.m_model_info		= this->get_interface<i_model_info>(g_sdk.m_modules.m_engine_dll, VERSION_MODEL_INFO_STRING);
	g_sdk.m_interfaces.m_mdl_cache		= this->get_interface<i_mdl_cache>(g_sdk.m_modules.m_data_cache_dll, VERSION_MODEL_CACHE_STRING);
	g_sdk.m_interfaces.m_event_manager	= this->get_interface<i_game_event_manager>(g_sdk.m_modules.m_engine_dll, VERSION_EVENT_MANAGER_STRING);
	g_sdk.m_interfaces.m_direct_device	= **reinterpret_cast<IDirect3DDevice9***>(g_utils.find_sig(g_sdk.m_modules.m_shader_dll, "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 0x1);
	g_sdk.m_interfaces.m_globals		= **reinterpret_cast<i_global_vars_base***>((*reinterpret_cast<uintptr_t**>(g_sdk.m_interfaces.m_client))[11] + 0xA); // A1 ? ? ? ? 5E 8B 40 10 + 0x1
	g_sdk.m_interfaces.m_prediction		= this->get_interface<i_prediction>(g_sdk.m_modules.m_client_dll, VERSION_CLIENT_PREDICTION_STRING);
	g_sdk.m_interfaces.m_game_movement	= this->get_interface<i_game_movement>(g_sdk.m_modules.m_client_dll, VERSION_GAME_MOVEMENT_STRING);
	g_sdk.m_interfaces.m_move_helper	= **reinterpret_cast<i_move_helper***>(c_utils::find_sig(g_sdk.m_modules.m_client_dll, "8B 0D ? ? ? ? 8B 45 ? 51 8B D4 89 02 8B 01") + 0x2);

	if (const HINSTANCE handle = GetModuleHandle("vstdlib.dll"))
		g_sdk.m_interfaces.m_key_values = reinterpret_cast<void* (__cdecl*)()>(GetProcAddress(handle, "KeyValuesSystem"))();

	ASSERT(g_sdk.m_interfaces.m_client != nullptr, "m_interfaces.m_client is nullptr");
	ASSERT(g_sdk.m_interfaces.m_client_mode != nullptr, "m_interfaces.m_client_mode is nullptr");
	ASSERT(g_sdk.m_interfaces.m_engine != nullptr, "m_interfaces.m_engine is nullptr");
	ASSERT(g_sdk.m_interfaces.m_entity_list != nullptr, "m_interfaces.m_entity_list is nullptr");
	ASSERT(g_sdk.m_interfaces.m_model_info != nullptr, "m_interfaces.m_model_info is nullptr");
	ASSERT(g_sdk.m_interfaces.m_mdl_cache != nullptr, "m_interfaces.m_mdl_cache is nullptr");
	ASSERT(g_sdk.m_interfaces.m_key_values != nullptr, "m_interfaces.m_key_values is nullptr");
	ASSERT(g_sdk.m_interfaces.m_event_manager	!= nullptr, "m_interfaces.m_event_manager is nullptr");
	ASSERT(g_sdk.m_interfaces.m_direct_device != nullptr, "m_interfaces.m_direct_device is nullptr");
	ASSERT(g_sdk.m_interfaces.m_globals != nullptr, "m_interfaces.m_globals is nullptr");
	ASSERT(g_sdk.m_interfaces.m_prediction != nullptr, "m_interfaces.m_prediction is nullptr");
	ASSERT(g_sdk.m_interfaces.m_game_movement != nullptr, "m_interfaces.m_game_movement is nullptr");
	ASSERT(g_sdk.m_interfaces.m_move_helper != nullptr, "m_interfaces.m_move_helper is nullptr");
}