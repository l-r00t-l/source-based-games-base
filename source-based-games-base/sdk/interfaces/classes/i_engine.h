#pragma once
#include <functional>
#include "../../utils/utils.h"
#include "../../math/matrix.h"
#include "../../math/qangle.h"

struct player_info_t
{
	int64_t m_something;

	union
	{
		int64_t m_steam_id64; //0x0008 - SteamID64
		struct
		{
			int32_t m_xuid_low;
			int32_t m_xuid_high;
		};
	};

	char m_name[128];
	int m_user_id;
	char m_steam_id[20];
	char pad_0x00A8[0x10];
	unsigned long m_un_steam_id;
	char m_friends_name[128];
	bool m_is_bot;
	bool m_is_hltv;
	unsigned int m_custom_files[4];
	unsigned char m_files_downloaded;
};

class i_engine {
public:
	bool get_player_info(const int ent_num, player_info_t* info) 
	{
		return g_utils.call_vfunc<bool, const int, player_info_t*>(this, 8, ent_num, info);
	}

	bool con_is_visible()
	{
		return g_utils.call_vfunc<bool>(this, 11);
	}

	int get_local_player_index()
	{
		return g_utils.call_vfunc<int>(this, 12);
	}

	bool is_in_game()
	{
		return g_utils.call_vfunc<bool>(this, 26);
	}
	bool is_connected()
	{
		return g_utils.call_vfunc<bool>(this, 27);
	}

	const VMatrix& world_to_screen_matrix() 
	{
		return g_utils.call_vfunc<const VMatrix&>(this, 37); //(__thiscall*)(void*)  (this)
	}

	void set_view_angles(const qangle_t& view_angle)
	{
		g_utils.call_vfunc<void, const qangle_t&>(this, 19, view_angle);
	}

	int get_player_for_user_id(const int user_id)
	{
		return g_utils.call_vfunc<int, const int>(this, 9, user_id);
	}
};