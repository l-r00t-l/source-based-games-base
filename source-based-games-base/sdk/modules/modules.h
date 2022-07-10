#pragma once
#include "../sdk.hpp"
#include <cassert>
#ifndef MY_ASSERT
#define MY_ASSERT
#define ASSERT(_EXPR, additional_info)	assert(_EXPR && additional_info); if (!(_EXPR)) c_logger::get()->printf(log_t::critical, additional_info);
#endif
class c_modules : public c_singleton<c_modules>
{
public:
	void init() const;
};