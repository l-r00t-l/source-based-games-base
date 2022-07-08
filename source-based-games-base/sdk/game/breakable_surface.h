#pragma once
#include "entity.h"
#include "../netvar-manager/netvar_manager.h"

class c_breakable_surface : public c_base_entity, public i_breakable_with_prop_data
{
public:
	// GET_NETVAR(bool, is_broken, _("DT_BreakableSurface"), _("m_bIsBroken"));
	GET_NETVAR(is_broken, "CBreakableSurface->m_bIsBroken", bool);
};
