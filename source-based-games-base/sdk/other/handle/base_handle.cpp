#include "base_handle.h"
// #include "../../interfaces/interfaces.h"
#include "../../sdk.hpp"

i_handle_entity* c_base_handle::get() const
{
	return g_sdk.m_interfaces.m_entity_list->get_entity(g_sdk.m_interfaces.m_engine->get_local_player_index());
}