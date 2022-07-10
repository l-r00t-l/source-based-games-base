#pragma once
// #include "../sdk.hpp"
#include "../../ext/singleton/singleton.h"
#include <Windows.h>

#define CSGO

#ifndef MY_ASSERT
#define MY_ASSERT
#define ASSERT(_EXPR, additional_info)	assert(_EXPR && additional_info); if (!(_EXPR)) c_logger::get()->printf(log_t::critical, additional_info);
#endif

#ifdef CSGO
#pragma region version_strings
#define VERSION_CLIENT_STRING				"VClient018"
#define VERSION_CLIENT_ENTITY_LIST_STRING	"VClientEntityList003"
#define VERSION_ENGINE_STRING				"VEngineClient014"
#define VERSION_MATERIAL_SYSTEM_STRING		"VMaterialSystem080"
#define VERSION_STUDIO_RENDER_STRING		"VStudioRender026"
#define VERSION_ENGINE_TRACE_CLIENT_STRING	"EngineTraceClient004"
#define VERSION_SURFACE_STRING				"VGUI_Surface031"
#define VERSION_VGUI_PANEL_STRING			"VGUI_Panel009"
#define VERSION_VENGINE_VGUI_STRING			"VEngineVGui001"
#define VERSION_DEBUG_OVERLAY_STRING		"VDebugOverlay004"
#define VERSION_MODEL_INFO_STRING			"VModelInfoClient004"
#define VERSION_MODEL_CACHE_STRING			"MDLCache004"
#pragma endregion
#endif
class c_interfaces : public c_singleton<c_interfaces>
{
public:
	void init() const;
	template<typename interface_>
	interface_* get_interface(const char* module_name, const char* interface_name) const;
	template<typename interface_>
	interface_* get_interface(HMODULE module, const char* interface_name) const;
};