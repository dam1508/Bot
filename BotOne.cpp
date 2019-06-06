#include "BotOne.h"

void BotOne::st_attack(BotData* p_data)
{
    BotData* _data = new BotData();
    _data->distance_from_player = p_data->distance_from_player;

    cout<<"Haha!"<<endl;
    loose_hp(20);

    if(health_points <= 0)
    internal_event(DEAD_STATE);

    else if(health_points > 40 && _data->distance_from_player <= attack_range)
    internal_event(ATTACK_STATE, _data);

    else
    internal_event(IDLE_STATE);
}