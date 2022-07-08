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


/* interfaces */
#include "interfaces/classes/i_client.h"
#include "interfaces/classes/i_engine.h"
#include "interfaces/classes/i_client_entity_list.h"
#include "interfaces/classes/i_model_info.h"
#include "interfaces/classes/i_model_cache.h"
#include "interfaces/classes/i_multiplayer_physics.h"
#include "interfaces/classes/i_engine_trace.h"
#include "interfaces/classes/i_breakable_with_prop_data.h"

/* netvars */
#include "netvar-manager/netvar_manager.h"

/* other */
#include "other/studio.h"

/* math */
#include "math/math.h"

class c_sdk {
public:
	struct m_interfaces_t {
		i_base_client_dll* m_client{};
		i_engine* m_engine{};
		i_client_entity_list* m_entity_list{};
		i_model_info* m_model_info{};
		i_mdl_cache* m_mdl_cache{};
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
	
	c_base_player* m_local{};

	void m_update_local_player()
	{
		m_local = reinterpret_cast<c_base_player*>(m_interfaces.m_entity_list->get_entity(m_interfaces.m_engine->get_local_player_index()));
	}
};

inline c_sdk g_sdk = c_sdk();