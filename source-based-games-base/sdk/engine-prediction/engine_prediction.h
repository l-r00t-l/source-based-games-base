#pragma once

#include "../../ext/singleton/singleton.h"
#include "../other/move_data.h"

class c_user_cmd;

class c_engine_prediction : public c_singleton<c_engine_prediction>
{
    uintptr_t m_prediction_seed{};

    struct backup_data_t {
        int m_tick_count{};
        int m_frame_count{};

        float m_current_time{};
        float m_frame_time{};

        bool m_in_prediction{};
        bool m_is_first_time_predicted{};
    }m_backup_data{};

    c_move_data m_move_data = c_move_data();
public:
    void init();
    void begin(c_user_cmd* cmd);
    void end();
};
