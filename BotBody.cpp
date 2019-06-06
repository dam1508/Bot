#include "BotBody.h"

void BotBody::take_dmg(int damage)
{
    loose_hp(damage);
}

void BotBody::info()
{
    cout<<health_points<<endl;
}

//<<<<<<<<FUNKCJA STANU st_idle>>>>>>>>>>

void BotBody::st_idle()
{
    cout<<"Does nothing"<<endl;
}

//<<<<<<<<FUNKCJA STANU st_event>>>>>>>>>>

void BotBody::st_event(BotData* p_data)
{
    BotData* _data = new BotData();
    _data->distance_from_player = p_data->distance_from_player;

    if(p_data->distance_from_player > attention)
    internal_event(IDLE_STATE);

    else if(p_data->distance_from_player >= attack_range)
    internal_event(PERSUE_STATE, _data);

    else internal_event(ATTACK_STATE, _data);
}

//<<<<<<<<FUNKCJA STANU PERSUE>>>>>>>>>>

void BotBody::st_persue(BotData* p_data)
{
    cout<<"I'll get u!"<<endl;

    BotData* _data = new BotData();
    _data->distance_from_player = p_data->distance_from_player;

    _data->distance_from_player -= speed;

    if(_data->distance_from_player <= attack_range)
    internal_event(ATTACK_STATE, _data);

    else if(_data->distance_from_player < attention)
    internal_event(PERSUE_STATE, _data);

    else 
    internal_event(IDLE_STATE);
}

//<<<<<<<<FUNKCJA STANU ATTACK>>>>>>>>>>

void BotBody::st_attack(BotData* p_data)
{
    BotData* _data = new BotData();
    _data->distance_from_player = p_data->distance_from_player;

    cout<<"Attack!"<<endl;
    loose_hp(35);

    if(health_points <= 0)
    internal_event(DEAD_STATE);

    else if(health_points > 20 && _data->distance_from_player <= attack_range)
    internal_event(ATTACK_STATE, _data);

    else
    internal_event(IDLE_STATE);
}

//<<<<<<<<FUNKCJA STANU RUN>>>>>>>>>>

void BotBody::st_run(BotData*)
{
cout<<"AAA!"<<endl;
}

//<<<<<<<<FUNKCJA STANU DEAD>>>>>>>>>>

void BotBody::st_dead()
{
    cout<<"Dead :("<<endl;
}

void BotBody::charge(BotData* p_data)
{
    /*!
      Transition map mowi nam do jakiego stanu powinnismy przejsc
      gdy wywolany zostanieexternal st_event. Do kazdego stanu przypisujemy
      ten na ktory ma sie zmienic.
    */
    BEGIN_TRANSITION_MAP                          
        TRANSITION_MAP_ENTRY(EVENT_STATE)              
        TRANSITION_MAP_ENTRY(EVENT_STATE)
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)
        TRANSITION_MAP_ENTRY(ATTACK_STATE)
        TRANSITION_MAP_ENTRY(PERSUE_STATE)
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)             
    END_TRANSITION_MAP(p_data)
}

void BotBody::go_idle()
{
    BEGIN_TRANSITION_MAP
        TRANSITION_MAP_ENTRY(EVENT_IGNORED)
        TRANSITION_MAP_ENTRY(IDLE_STATE)
        TRANSITION_MAP_ENTRY(IDLE_STATE)
        TRANSITION_MAP_ENTRY(IDLE_STATE)
        TRANSITION_MAP_ENTRY(IDLE_STATE)
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)
    END_TRANSITION_MAP(NULL)
}

BotBody::BotBody(int hp, int at, int spd, int att_r)
:BotBrain(MAX_STATES), health_points(hp), attention(at),speed(spd),attack_range(att_r)
{}