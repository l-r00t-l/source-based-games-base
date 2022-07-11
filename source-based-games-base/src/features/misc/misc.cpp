#include "pch.h"
#include "misc.h"
#include "../../../sdk/sdk.hpp"
// #include "../../../sdk/game/entity.h"
#include "../../../sdk/game/player.h"

void c_misc::bunnyhop(c_user_cmd* cmd)
{
	if (g_sdk.m_local->get_move_type() == move_type_ladder
		|| g_sdk.m_local->get_move_type() == move_type_noclip)
		return;

	if (cmd->m_buttons & in_jump && !(g_sdk.m_local->get_flags() & fl_on_ground))
		cmd->m_buttons &= ~in_jump;
}

void c_misc::run(c_user_cmd* cmd)
{
	bunnyhop(cmd);
}
