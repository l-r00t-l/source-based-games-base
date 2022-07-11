#pragma once
#include "../../ext/singleton/singleton.h"
#include "../../ext/minhook/minhook.h"
#include "../../sdk/other/cmd.h"

#include <Windows.h>
#include <stdint.h>

#ifndef MY_ASSERT
#define MY_ASSERT
#define ASSERT(_EXPR, additional_info)	assert(_EXPR && additional_info); if (!(_EXPR)) c_logger::get()->printf(log_t::critical, additional_info);
#endif

#define HOOK(address, function, original, additional_info) if(MH_STATUS _result = MH_CreateHook(address, &function, reinterpret_cast<void**>(&(original)))) \
{ \
	if (_result != MH_OK) \
		c_logger::get()->printf(log_t::critical, additional_info); \
} \
class c_user_cmd;
class i_client_mode_shared;

using _create_move		= bool(__thiscall*)(i_client_mode_shared*, float, c_user_cmd*);
using _alloc_key_values = void* (__thiscall*)(void*, const int32_t);



class c_hooks : public c_singleton<c_hooks>
{
private:
	HWND window{};
protected:
	static bool __stdcall hk_create_move(float frame_time, c_user_cmd* cmd);
	static void* __stdcall hk_alloc_key_values(const int32_t size);
	static void init_wnd_proc();
	static long __stdcall hk_wnd_proc(HWND window, UINT msg, WPARAM wparam, LPARAM lparam);
public:

	struct originals_t
	{
		_create_move m_create_move				= nullptr;
		_alloc_key_values m_alloc_key_values	= nullptr;
		WNDPROC m_wnd_proc{};

	}m_originals{};

	static void init();
	static void restore();

};

