#pragma once
#include "classes.h"
#include "../interfaces/classes/i_client_entity.h"
#include "../netvar-manager/netvar_manager.h"
#include "../utils/utils.h"
#include "enums.h"



class c_base_entity : public i_client_entity
{
public:
// 	GET_NETVAR(int, get_team, _("DT_BaseEntity"), _("m_iTeamNum"));
// 	GET_NETVAR(int, get_collision_group, _("DT_BaseEntity"), _("m_CollisionGroup"));
// 	GET_NETVAR_OFFSET(e_move_type, get_move_type, _("DT_BaseEntity"), _("m_nRenderMode"), 0x1);
// 	GET_NETVAR_OFFSET(const matrix_t, get_coordinate_frame, _("DT_BaseEntity"), _("m_CollisionGroup"), -0x30);
	GET_NETVAR(get_team, "CBaseEntity->m_iTeamNum", int);
// 	int& get_team()
// 	{
// 		static const uint32_t offset = c_netvars::get()->m_database[g_utils.compile_time("CBaseEntity->m_iTeamNum")];
// 		return *reinterpret_cast<int*>(uint32_t(this) + offset);
// 	}
	GET_NETVAR(get_collision_group, "CBaseEntity->m_CollisionGroup", int);
	GET_NETVAR_OFFSET(get_move_type, "CBaseEntity->m_nRenderMode", 0x1, e_move_type);
	GET_NETVAR_OFFSET(get_coordinate_frame, "CBaseEntity->m_CollisionGroup", -0x30, const matrix_t);
};
