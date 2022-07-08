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
	g_sdk.m_interfaces.m_engine			= this->get_interface<i_engine>(g_sdk.m_modules.m_engine_dll, VERSION_ENGINE_STRING);
	g_sdk.m_interfaces.m_entity_list	= this->get_interface<i_client_entity_list>(g_sdk.m_modules.m_client_dll, VERSION_CLIENT_ENTITY_LIST_STRING);
	g_sdk.m_interfaces.m_model_info		= this->get_interface<i_model_info>(g_sdk.m_modules.m_engine_dll, VERSION_MODEL_INFO_STRING);
	g_sdk.m_interfaces.m_mdl_cache		= this->get_interface<i_mdl_cache>(g_sdk.m_modules.m_engine_dll, VERSION_MODEL_CACHE_STRING);
}