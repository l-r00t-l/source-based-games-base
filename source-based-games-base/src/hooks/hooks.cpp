#include "hooks.h"

/* sdk */
#include "../../sdk/sdk.hpp"

/* features */
#include "../features/misc/misc.h"

bool __stdcall c_hooks::hk_create_move(float frame_time, c_user_cmd* cmd)
{
	if (!cmd || !cmd->m_command)
		return c_hooks::get()->m_originals.m_create_move(g_sdk.m_interfaces.m_client_mode, frame_time, cmd);

	g_sdk.m_update_local_player();

	if (c_hooks::get()->m_originals.m_create_move(g_sdk.m_interfaces.m_client_mode, frame_time, cmd))
		g_sdk.m_interfaces.m_engine->set_view_angles(cmd->m_view_angles);

	c_misc::get()->run(cmd);
	
	return false;

}

void* __stdcall c_hooks::hk_alloc_key_values(const int32_t size)
{
	if (const uint32_t address = reinterpret_cast<uint32_t>(_ReturnAddress());
		address == reinterpret_cast<uint32_t>(g_sdk.m_return_adress.m_engine) ||
		address == reinterpret_cast<uint32_t>(g_sdk.m_return_adress.m_client))
		return nullptr;
	
	return c_hooks::get()->m_originals.m_alloc_key_values(g_sdk.m_interfaces.m_key_values, size);
}


void c_hooks::init()
{
	c_logger::get()->printf(log_t::info, "initalizing hooks ...");
	if (MH_Initialize() != MH_OK)
	{
		c_logger::get()->printf(log_t::critical, "unable to initalize minhook");
		return;
	}

	void* a_create_move = g_utils.get_vfunc(g_sdk.m_interfaces.m_client_mode, 24);
	void* a_alloc_key_values = g_utils.get_vfunc(g_sdk.m_interfaces.m_key_values, 1);

	HOOK(a_alloc_key_values, hk_alloc_key_values, c_hooks::get()->m_originals.m_alloc_key_values, "couldn't place hook hk_alloc_key_values");
	HOOK(a_create_move, hk_create_move, c_hooks::get()->m_originals.m_create_move, "couldn't place hook hk_create_move");


	MH_EnableHook(MH_ALL_HOOKS);
}

void c_hooks::restore()
{
	c_logger::get()->printf(log_t::warning, "restoring hooks ...");
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}
