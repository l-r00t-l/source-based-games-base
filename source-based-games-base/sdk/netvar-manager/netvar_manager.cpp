#include "pch.h"

#include "netvar_manager.h"
#include "../interfaces/classes/i_client.h"
#include "../sdk.hpp"


void c_netvars::init()
{
	c_logger::get()->printf(log_t::info, "initalizing netvar manager...");
	for (client_class_t* client = g_sdk.m_interfaces.m_client->get_all_classes(); client; client = client->m_next)
	{
		if (recv_table_t* table = client->m_recv_table)
			dump(client->m_network_name, table, 0);
	}
}

void c_netvars::dump(const std::string_view base, recv_table_t* table, const uint32_t offset /*= 0*/)
{
	// Looping thru props
	for (auto i = 0; i < table->m_props_count; ++i)
	{
		const recv_prop_t* prop = &table->m_props_pointer[i];

		if (!prop)
			continue;

		if (std::isdigit(prop->m_var_name[0]))
			continue;

		if (g_utils.run_time(prop->m_var_name) == g_utils.compile_time("baseclass"))
			continue;

		if (prop->m_recv_type == send_prop_type_t::DATATABLE &&
			prop->m_data_table &&
			prop->m_data_table->m_net_table_name[0] == 'D')
			dump(base, prop->m_data_table, offset + prop->m_offset);

		m_database[g_utils.run_time(std::format("{}->{}", base, prop->m_var_name).c_str())] = offset + prop->m_offset;
	}
}
