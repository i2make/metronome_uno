#include "define.h"

M_State stateMap[6][2] = {
        {M_State::STOP, M_State::START},
        {M_State::STOP, M_State::CHANGE_CLICK},
        {M_State::START, M_State::STOP},
        {M_State::START, M_State::CHANGE_CLICK},
        {M_State::CHANGE_CLICK, M_State::STOP},
        {M_State::CHANGE_CLICK, M_State::START},
};
