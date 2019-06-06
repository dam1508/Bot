#ifndef BOTBRAIN_H
#define BOTBRAIN_H

#include <stdio.h>

//!Klasa przechowujaca dane o wydarzeniu
class EventData
{
    public:
    virtual ~EventData() {};
};

struct StateStruct;

//!Maszyna stanow odpowiadajaca za zachowanie bota
class BotBrain
{
    const unsigned char max_states;
    bool event_generated;
    EventData* p_event_data;
    void state_engine(void);

    protected:

    enum{ EVENT_IGNORED = 0xFE, CANNOT_HAPPEN };
    unsigned char current_state;
    /*!
      Zdarzenie wywolane z zewnatrz, ma priorytet nad innymi wydarzeniami.
      Daje ono botowi informacje do jakiego stanu powinien sie udac w danym momencie
    */
    void external_event(unsigned char, EventData* = NULL);
    //!Zdarzenie wewnatrz stanu powodujace zmiane stanu
    void internal_event(unsigned char, EventData* = NULL);
    virtual const StateStruct* get_state_map() = 0;

    public:

    BotBrain(unsigned char maxs);
    virtual ~BotBrain() {};
};

typedef void (BotBrain::*state_func)(EventData *);
struct StateStruct
{
    state_func p_state_func;
};

#define BEGIN_STATE_MAP \
public:\
const StateStruct* get_state_map() {\
    static const StateStruct StateMap[] = {

#define STATE_MAP_ENTRY(st_fun)\
    {reinterpret_cast<state_func>(st_fun) },

#define END_STATE_MAP \
    }; \
    return &StateMap[0]; }

#define BEGIN_TRANSITION_MAP \
    static const unsigned char TRANSITIONS[]= {\

#define TRANSITION_MAP_ENTRY(entry)\
    entry,

#define END_TRANSITION_MAP(data)\
    0};\
    external_event(TRANSITIONS[current_state], data);

#endif