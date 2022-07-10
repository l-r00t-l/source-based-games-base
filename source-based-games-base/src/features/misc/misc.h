#pragma once
#include "../../../ext/singleton/singleton.h"
#include "../../../sdk/other/cmd.h"


class c_misc : public c_singleton<c_misc>
{
	void bunnyhop(c_user_cmd* cmd);
public:
	void run(c_user_cmd* cmd);
};