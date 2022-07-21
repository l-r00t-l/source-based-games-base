#pragma once
#include "../../../ext/singleton/singleton.h"
#include "../../../sdk/other/cmd.h"


class c_misc : public c_singleton<c_misc>
{
	int32_t m_flags_backup{};
private:
	void bunnyhop(c_user_cmd* cmd);
	void edge_jump_pre_prediction(c_user_cmd* cmd);
public:
	void edge_jump(c_user_cmd* cmd);
	void run(c_user_cmd* cmd);
};