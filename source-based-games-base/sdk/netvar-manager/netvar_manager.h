#pragma once
#include "../utils/utils.h"
#include <vector>
#include <unordered_map>

#include "../../ext/singleton/singleton.h"


//struct recv_prop_t;
struct recv_table_t;

// struct netvar_table {
// 	std::string					name{};
// 	recv_prop_t*				prop{};
// 	uint32_t					offset{};
// 	std::vector<recv_prop_t*>	child_props{};
// 	std::vector<netvar_table>	child_tables{};
// };





class c_netvars : public c_singleton<c_netvars>
{
public:
	std::unordered_map<uint32_t, uint32_t> m_database = {};
	void init();
	void dump(const std::string_view base, recv_table_t* table, const uint32_t offset = 0);
};



#define GET_NETVAR(name, var, ...) \
std::add_lvalue_reference_t<__VA_ARGS__> name() \
{ \
	static const uint32_t offset = c_netvars::get()->m_database[g_utils.compile_time(var)]; \
	return *reinterpret_cast<std::add_pointer_t<__VA_ARGS__>>(uint32_t(this) + offset); \
}

#define GET_NETVAR_OFFSET(name, var, o, ...) \
std::add_lvalue_reference_t<__VA_ARGS__> name() \
{ \
	static const uint32_t offset = c_netvars::get()->m_database[g_utils.compile_time(var)]; \
	return *reinterpret_cast<std::add_pointer_t<__VA_ARGS__>>(uint32_t(this) + offset + o); \
}