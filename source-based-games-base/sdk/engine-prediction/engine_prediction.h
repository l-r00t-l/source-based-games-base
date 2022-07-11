#pragma once
#include "../../ext/singleton/singleton.h"

class c_engine_prediction : public c_singleton<c_engine_prediction>
{
public:
	void init();
};
