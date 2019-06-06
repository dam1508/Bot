#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "BotOne.h"

TEST_CASE("Simple Event", "Checking hp and states")
{
    BotOne test_subject;
    BotBody body_subject;
    BotData* simple_event = new BotData();

    simple_event->distance_from_player = 10;
    simple_event->player_appeard = true;

    body_subject.charge(simple_event);
    test_subject.charge(simple_event);

    CHECK(body_subject.get_hp() == 40);			//Test ma po prostu pokazac ze dwa boty po tym samym wydarzeniu
    REQUIRE(test_subject.get_hp() == 40);		//skonczyly z rozna iloscia hp (nadpisanie funkcji ataku w klasie
}							//BotOne dziala)
