#pragma once
#include "../../ext/singleton/singleton.h"
#include "../interfaces/classes/i_event_manager.h"

class i_game_event;


/*

	#Ref: https://wiki.alliedmods.net/Counter-Strike:_Global_Offensive_Events

*/
class c_events : public c_singleton<c_events>, public i_game_event_listener
{
	void player_hurt(i_game_event* event, const char* event_name) const;
	void player_death(i_game_event* event, const char* event_name) const;
public:
	void fire_game_event(i_game_event* event);
	void init();
	void destroy();
};

