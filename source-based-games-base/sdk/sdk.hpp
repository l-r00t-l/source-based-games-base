#pragma once
#include "pch.h"

/* d3dx9 */
#include <d3d9.h>
#include <d3dx9.h>


/* dependencies */
#include "../ext/singleton/singleton.h"
#include "../ext/logger/logger.h"

/* utils */
#include "utils/utils.h"

/* modules */
#include "modules/modules.h"

/* game */
#include "game/entity.h"
// #include "game/player.h"

/* interfaces */
#include "interfaces/interfaces.h"
#include "interfaces/classes/i_client.h"
#include "interfaces/classes/i_engine.h"
#include "interfaces/classes/i_client_entity_list.h"
#include "interfaces/classes/i_client_entity.h"
#include "interfaces/classes/i_model_info.h"
#include "interfaces/classes/i_model_cache.h"
#include "interfaces/classes/i_multiplayer_physics.h"
#include "interfaces/classes/i_engine_trace.h"
#include "interfaces/classes/i_breakable_with_prop_data.h"
#include "interfaces/classes/i_client_mode_shared.h"
#include "interfaces/classes/i_event_manager.h"
#include "interfaces/classes/i_globals.h"
#include "interfaces/classes/i_prediction.h"
#include "interfaces/classes/i_move_helper.h"
#include "interfaces/classes/i_game_movement.h"

/* netvars */
#include "netvar-manager/netvar_manager.h"

/* hooks */
#include "../src/hooks/hooks.h"

/* event manager */
#include "event-manager/event_manager.h"


/* other */
#include "other/studio.h"
#include "other/cmd.h"

/* math */
#include "math/math.h"

class c_sdk {
public:
	struct m_interfaces_t {
		i_base_client_dll*			m_client{};
		i_engine*					m_engine{};
		i_client_entity_list*		m_entity_list{};
		i_model_info*				m_model_info{};
		i_mdl_cache*				m_mdl_cache{};
		i_client_mode_shared*		m_client_mode{};
		void*						m_key_values{};
		i_game_event_manager*		m_event_manager{};
		IDirect3DDevice9*			m_direct_device{};
		i_global_vars_base*			m_globals{};
		i_prediction*				m_prediction{};
		i_move_helper*				m_move_helper{};
		i_game_movement*			m_game_movement{};
	}m_interfaces{};

	struct m_module_list_t
	{
		HMODULE m_client_dll{};
		HMODULE m_engine_dll{};
		HMODULE m_vgui_dll{};
		HMODULE m_vgui2_dll{};
		HMODULE m_tier_dll{};
		HMODULE m_mat_sys_dll{};
		HMODULE m_localize_dll{};
		HMODULE m_shader_dll{};
		HMODULE m_data_cache_dll{};
		HMODULE m_vstd_dll{};
		HMODULE m_physics_dll{};
		HMODULE m_file_system_dll{};
		HMODULE m_server_dll{};
		HMODULE m_studio_render_dll{};
	}m_modules{};
	
	struct m_return_address_t {
		uint8_t* m_client = nullptr;
		uint8_t* m_engine = nullptr;
	}m_return_adress{};
	
	struct local_data_t
	{
		vec3_t m_shoot_pos{};
	}m_local_data{};

	c_base_player* m_local{};

	void m_update_local_player()
	{
		m_local = reinterpret_cast<c_base_player*>(m_interfaces.m_entity_list->get_entity(m_interfaces.m_engine->get_local_player_index()));
	}
};

inline c_sdk g_sdk = c_sdk();

#define TIME_TO_TICKS(time_) ((int)(0.5f + (float)((time_)) / g_sdk.m_interfaces.m_globals->m_interval_per_tick))
#define TICKS_TO_TIME(tick) (float)((tick) * g_sdk.m_interfaces.m_globals->m_interval_per_tick)