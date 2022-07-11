#include "event_manager.h"
#include "pch.h"
#include "../sdk.hpp"
#include "../game/player.h"

void c_events::player_hurt(i_game_event* event, const char* event_name) const
{
	const auto event_name_hashed = g_utils.run_time(event_name);
	const auto user_id	= g_sdk.m_interfaces.m_engine->get_player_for_user_id(event->get_int("userid"));
	const auto attacker = g_sdk.m_interfaces.m_engine->get_player_for_user_id(event->get_int("attacker"));

	if (event_name_hashed != g_utils.compile_time("player_hurt"))
		return;

	const auto hurt_player = static_cast<c_base_player*>(g_sdk.m_interfaces.m_entity_list->get_entity(user_id));

	if (!hurt_player || !hurt_player->is_player())
		return;

	auto get_hitbox_by_hitgroup = [](const int hitgroup) -> int
	{
		switch (hitgroup)
		{
		case hitgroup_head:
			return hitbox_head;
		case hitgroup_chest:
			return hitbox_chest;
		case hitgroup_stomach:
			return hitbox_stomach;
		case hitgroup_leftarm:
			return hitbox_left_hand;
		case hitgroup_rightarm:
			return hitbox_right_hand;
		case hitgroup_leftleg:
			return hitbox_right_calf;
		case hitgroup_rightleg:
			return hitbox_left_calf;
		case hitgroup_neck:
			return hitbox_neck;
		default:
			return hitbox_pelvis;
		}
	};

	auto get_hitbox_name_from_hitgroup = [get_hitbox_by_hitgroup](const int hitgroup) -> std::string
	{
		switch (get_hitbox_by_hitgroup(hitgroup))
		{
		case hitbox_head:
			return "head";
		case hitbox_chest:
			return "chest";
		case hitbox_stomach:
			return "stomach";
		case hitbox_pelvis:
			return "pelvis";
		case hitbox_right_upper_arm:
		case hitbox_right_forearm:
		case hitbox_right_hand:
			return "left arm";
		case hitbox_left_upper_arm:
		case hitbox_left_forearm:
		case hitbox_left_hand:
			return "right arm";
		case hitbox_right_thigh:
		case hitbox_right_calf:
			return "left leg";
		case hitbox_left_thigh:
		case hitbox_left_calf:
			return "right leg";
		case hitbox_right_foot:
			return "left foot";
		case hitbox_left_foot:
			return "right foot";
		default:
			return "generic";
		}
	};

	if (attacker == g_sdk.m_interfaces.m_engine->get_local_player_index()) 
	{
		player_info_t info{};
		g_sdk.m_interfaces.m_engine->get_player_info(hurt_player->get_index(), &info);

		std::string hit_str = "Hit ";
		{
			hit_str += info.m_name;
			hit_str += " for ";
			hit_str += std::to_string(event->get_int("dmg_health"));
			hit_str += " in ";
			hit_str += get_hitbox_name_from_hitgroup(event->get_int("hitgroup"));
		}

		// Output type
		c_logger::get()->printf(log_t::debug, hit_str.c_str());
	}
}

void c_events::player_death(i_game_event* event, const char* event_name) const
{
	if (g_utils.run_time(event_name) != g_utils.compile_time("player_death"))
		return;
}

void c_events::fire_game_event(i_game_event* event)
{
	if (!event || !g_sdk.m_local || !g_sdk.m_local->is_alive())
		return;

	const auto event_name = event->get_name();

	player_hurt(event, event_name);
	player_death(event, event_name);
}

void c_events::init()
{
	c_logger::get()->printf(log_t::info, "initalizing event manager ...");
	g_sdk.m_interfaces.m_event_manager->add_listener(this, "player_hurt", false);
	g_sdk.m_interfaces.m_event_manager->add_listener(this, "player_death", false);
}

void c_events::destroy()
{
	c_logger::get()->printf(log_t::warning, "destroying event manager...");
	g_sdk.m_interfaces.m_event_manager->remove_listener(this);
}
