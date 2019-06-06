#include "BotOne.h"

int main()
{
    BotOne A;
    BotData* data = new BotData();
    data->player_appeard=true;
    data->distance_from_player=8;
    A.charge(data);
    A.info();
}