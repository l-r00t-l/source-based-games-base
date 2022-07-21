#include "pch.h"
#include "engine_prediction.h"

#include "../sdk.hpp"
#include "../game/player.h"

#pragma region old
// void c_engine_prediction::init()
// {
// 	// c_logger::get()->printf(log_t::info, "initalizing engine prediction ...");
// 	
// 	/* setup prediction data */
// 	m_prediction_player = *reinterpret_cast<uintptr_t*>(c_utils::find_sig(g_sdk.m_modules.m_client_dll, "8B 47 40 A3") + 0x4);
// 	m_prediction_speed = *reinterpret_cast<uintptr_t*>(c_utils::find_sig(g_sdk.m_modules.m_client_dll, "0F 5B C0 89 35") + 0x5);
//
// 	/* setup backup data */
// 	m_backup_data.m_tick_count		= g_sdk.m_interfaces.m_globals->m_tick_count;
// 	m_backup_data.m_frame_count		= g_sdk.m_interfaces.m_globals->m_frame_count;
// 	m_backup_data.m_current_time	= g_sdk.m_interfaces.m_globals->m_current_time;
// 	m_backup_data.m_frame_time		= g_sdk.m_interfaces.m_globals->m_frame_time;
// 	m_backup_data.m_in_prediction	= g_sdk.m_interfaces.m_prediction->m_in_prediction;
// 	m_backup_data.m_is_first_time_predicted = g_sdk.m_interfaces.m_prediction->m_first_time_predicted;
// }
//
// void c_engine_prediction::begin(c_user_cmd* cmd)
// {
// 	/* @ref: https://github.com/perilouswithadollarsign/cstrike15_src/blob/f82112a2388b841d72cb62ca48ab1846dfcc11c8/game/client/prediction.cpp#L899 */
// 	*reinterpret_cast<c_user_cmd**>(reinterpret_cast<uintptr_t>(g_sdk.m_local) + 0x3348) = cmd;
// 	*reinterpret_cast<c_user_cmd**>(reinterpret_cast<uintptr_t>(g_sdk.m_local) + 0x3298) = cmd;
// 	cmd->m_buttons |= *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(g_sdk.m_local) + 0x3344);
// 	cmd->m_buttons &= ~*reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(g_sdk.m_local) + 0x3340);
//
// 	/* setup pred vars */
// 	*reinterpret_cast<int*>(c_engine_prediction::get()->m_prediction_player)	= reinterpret_cast<uintptr_t>(g_sdk.m_local);
// 	*reinterpret_cast<int*>(c_engine_prediction::get()->m_prediction_speed)		= cmd ? cmd->m_random_seed : -1;
//
// 	/* fix time */
// 	g_sdk.m_interfaces.m_globals->m_current_time = TICKS_TO_TIME(g_sdk.m_local->get_tick_base());
// 	g_sdk.m_interfaces.m_globals->m_frame_time = g_sdk.m_interfaces.m_prediction->m_engine_paused
// 		? 0.f
// 		: g_sdk.m_interfaces.m_globals->m_interval_per_tick;
// 	g_sdk.m_interfaces.m_globals->m_tick_count = g_sdk.m_local->get_tick_base();
//
// 	/* setup vars */
// 	g_sdk.m_interfaces.m_prediction->m_in_prediction = true;
// 	g_sdk.m_interfaces.m_prediction->m_first_time_predicted = false;
//
// 	g_sdk.m_interfaces.m_game_movement->start_track_prediction_errors(g_sdk.m_local);
// 	g_sdk.m_interfaces.m_move_helper->set_host(g_sdk.m_local);
//
// 	/* remove if not working */
// 	if (cmd->m_weapon_select != 0)
// 		if (const auto& weapon = g_sdk.m_local->get_active_weapon())
// 			g_sdk.m_local->select_item(weapon->get_name().c_str(), cmd->m_weapon_select);
//
// 	/* impulse fix */
// 	const auto vehicle = g_sdk.m_local->get_vehicle().get();
// 	if (cmd->m_impulse && (!vehicle || g_sdk.m_local->using_standard_weapons_in_vehicle()))
// 		g_sdk.m_local->get_impulse() = cmd->m_impulse;
//
// 	const int buttons_changed = cmd->m_buttons ^ *reinterpret_cast<int*>(g_sdk.m_local->get_address() + 0x3208);
//
// 	*reinterpret_cast<int*>(g_sdk.m_local->get_address() + 0x31FC) = *reinterpret_cast<int*>(g_sdk.m_local->get_address() + 0x3208);
// 	*reinterpret_cast<int*>(g_sdk.m_local->get_address() + 0x3208) = cmd->m_buttons;
// 	*reinterpret_cast<int*>(g_sdk.m_local->get_address() + 0x3200) = cmd->m_buttons & buttons_changed;
// 	*reinterpret_cast<int*>(g_sdk.m_local->get_address() + 0x3204) = buttons_changed & ~cmd->m_buttons;
//
// 	g_sdk.m_interfaces.m_prediction->check_moving_ground(g_sdk.m_local, g_sdk.m_interfaces.m_globals->m_frame_time);
//
// 	if (g_sdk.m_local->physics_run_think(0))
// 		g_sdk.m_local->get_pre_think();
//
// 	if (g_sdk.m_local->get_next_think_tick() > 0 && g_sdk.m_local->get_next_think_tick() <= g_sdk.m_local->get_tick_base())
// 	{
// 		g_sdk.m_local->get_next_think_tick() = -1;
// 		g_sdk.m_local->get_think();
// 	}
//
// 	g_sdk.m_interfaces.m_prediction->setup_move(g_sdk.m_local, cmd, g_sdk.m_interfaces.m_move_helper, &c_engine_prediction::get()->m_move_data);
// 	g_sdk.m_interfaces.m_prediction->set_local_view_angles(cmd->m_view_angles);
// 	g_sdk.m_interfaces.m_game_movement->process_movement(g_sdk.m_local, &c_engine_prediction::get()->m_move_data);
// 	g_sdk.m_interfaces.m_prediction->finish_move(g_sdk.m_local, cmd, &c_engine_prediction::get()->m_move_data);
// 	g_sdk.m_interfaces.m_move_helper->process_impacts();
// 	g_sdk.m_interfaces.m_move_helper->set_host(nullptr);
// 	g_sdk.m_interfaces.m_game_movement->finish_track_prediction_errors(g_sdk.m_local);
// 	g_sdk.m_interfaces.m_game_movement->reset();
//
// 	/* inaccuracy calculation */
// // 	if (g_sdk.m_local->get_active_weapon())
// // 		g_sdk.m_local->get_active_weapon()->update_accuracy_penalty();
//
// 	g_sdk.m_local_data.m_shoot_pos = g_sdk.m_local->get_shoot_pos();
// }
//
// void c_engine_prediction::end() const
// {
// 	if (!m_prediction_player || !m_prediction_speed)
// 		return;
//
// 	g_sdk.m_interfaces.m_globals->m_current_time = m_backup_data.m_current_time;
// 	g_sdk.m_interfaces.m_globals->m_frame_time = m_backup_data.m_frame_time;
// 	g_sdk.m_interfaces.m_globals->m_tick_count = m_backup_data.m_tick_count;
//
// 	*reinterpret_cast<c_user_cmd**>(g_sdk.m_local->get_address() + 0x3348) = nullptr;
// 	*reinterpret_cast<int*>(m_prediction_player) = -1;
// 	*reinterpret_cast<int*>(m_prediction_speed) = -1;
// }
// /* @TODO: finish later */
// void c_engine_prediction::update()
// {
//
// }
//
// void c_engine_prediction::store_netvars()
// {
//
// }
//
// void c_engine_prediction::restore_netvars()
// {
//
// }
//
#pragma endregion


void c_engine_prediction::init()
{
    static auto prediction_seed = c_utils::find_sig(g_sdk.m_modules.m_client_dll, "0F 5B C0 89 35") + 0x5;
    m_prediction_seed = *reinterpret_cast<uintptr_t*>(prediction_seed);
    
    m_backup_data.m_current_time    = g_sdk.m_interfaces.m_globals->m_current_time;
    m_backup_data.m_frame_time      = g_sdk.m_interfaces.m_globals->m_frame_time;
}


void c_engine_prediction::begin(c_user_cmd* cmd)
{
    *reinterpret_cast<int*>(m_prediction_seed) = 0;
    g_sdk.m_interfaces.m_globals->m_current_time = TICKS_TO_TIME(g_sdk.m_local->get_tick_base());
    g_sdk.m_interfaces.m_globals->m_frame_time      = g_sdk.m_interfaces.m_globals->m_interval_per_tick;

    g_sdk.m_interfaces.m_move_helper->set_host(g_sdk.m_local);
    g_sdk.m_interfaces.m_prediction->setup_move(g_sdk.m_local, cmd, g_sdk.m_interfaces.m_move_helper, &m_move_data);
    g_sdk.m_interfaces.m_game_movement->process_movement(g_sdk.m_local, &m_move_data);
    g_sdk.m_interfaces.m_prediction->finish_move(g_sdk.m_local, cmd, &m_move_data);
    g_sdk.m_interfaces.m_move_helper->set_host(nullptr);

    g_sdk.m_local_data.m_shoot_pos = g_sdk.m_local->get_shoot_pos();
}

void c_engine_prediction::end()
{
    g_sdk.m_interfaces.m_globals->m_current_time = m_backup_data.m_current_time;
    g_sdk.m_interfaces.m_globals->m_frame_time = m_backup_data.m_frame_time;
    
    *reinterpret_cast<int*>(m_prediction_seed) = -1;
}

