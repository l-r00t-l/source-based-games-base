#pragma once

/* microsoft */
#include <vector>
#include <Windows.h>
#include <string>
#include <cmath>
#include <string_view>
#include <chrono>
#include <thread>
#include <array>

/* dependencies */
#include "../ext/singleton/singleton.h"
#include "../ext/logger/logger.h"

#include "utils/utils.h"
#include "modules/modules.h"
#include "interfaces/interfaces.h"

/* game */
#include "game/entity.h"
// #include "game/player.h"

/* interfaces */
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

/* netvars */
#include "netvar-manager/netvar_manager.h"

/* hooks */
#include "../src/hooks/hooks.h"

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
	c_base_player* m_local{};

	void m_update_local_player()
	{
		m_local = reinterpret_cast<c_base_player*>(m_interfaces.m_entity_list->get_entity(m_interfaces.m_engine->get_local_player_index()));
	}
};

inline c_sdk g_sdk = c_sdk();