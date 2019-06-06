#include <assert.h>
#include "BotBrain.h"

BotBrain::BotBrain(unsigned char maxs)
:max_states(maxs), current_state(0), event_generated(false), p_event_data(NULL)
{}

void BotBrain::external_event(unsigned char new_state, EventData *p_data)
{
    if(new_state == EVENT_IGNORED)
    {
        if(p_data)
            delete p_data;
    }
    else{

        internal_event(new_state, p_data);
        state_engine();
    }
}

void BotBrain::internal_event(unsigned char new_state, EventData* p_data)
{
    if(p_data == NULL)
        p_data = new EventData();

    p_event_data = p_data;
    event_generated = true;
    current_state = new_state;
}

void BotBrain::state_engine()
{
    EventData* p_data_temp = NULL;

    while(event_generated)
    {
        p_data_temp = p_event_data;
        p_event_data = NULL;
        event_generated = false;

        assert(current_state < max_states);

        const StateStruct* p_state_map = get_state_map();

        (this->*p_state_map[current_state].p_state_func)(p_data_temp);

        if(p_data_temp)
        {
            delete p_data_temp;
            p_data_temp = NULL;
        }
    }
}