#ifndef BOTBODY_H
#define BOTBODY_H

#include <iostream>
#include "BotBrain.h"

using namespace std;

//!Informacje o wydarzeniu ktore przechowuje BOT 
struct BotData: public EventData
{
    public:

    bool player_appeard;

    int distance_from_player;
};

//!Klasa modelu bazowego danego typu bota
class BotBody: public BotBrain
{
    protected:

    int health_points;
    int attention;
    int speed;
    int player_distance;
    int attack_range;

    //!Funkcje stanow (oznaczone st_<nazwa funkcji>)
    /*!
      Każda z nich jest wywolywana w momencie przejscia do danego stanu.
      To wlasnie one determinuja jak bedzie zachowywal sie bot.
      Kazda z nich moze wywolywac rozne funkcje wplywajace na statystyki bota
      lub dane zdarzenia. To w nich znajduja sie internal_event powodujace 
      przejscia z jednego stanu do drugiego w sposob nie wymuszony "z zewnatrz"
    */
    virtual void st_idle();
    virtual void st_event(BotData*);
    virtual void st_persue(BotData*);
    virtual void st_attack(BotData*);
    virtual void st_run(BotData*);
    virtual void st_dead();

    //!Sa to wszystkie stany tego "ciala" bota
    enum states
    {
        IDLE_STATE,
        EVENT_STATE,
        PERSUE_STATE,
        ATTACK_STATE,
        RUN_STATE,
        DEAD_STATE,
        MAX_STATES
    };

    //!Mapa stanow
    /*!
      Przyporzadkowywuje ona funkcje stanow, do
      odpowiadajacym im stanow
    */
    BEGIN_STATE_MAP
        STATE_MAP_ENTRY(&BotBody::st_idle)
        STATE_MAP_ENTRY(&BotBody::st_event)
        STATE_MAP_ENTRY(&BotBody::st_persue)
        STATE_MAP_ENTRY(&BotBody::st_attack)
        STATE_MAP_ENTRY(&BotBody::st_run)
        STATE_MAP_ENTRY(&BotBody::st_dead)
    END_STATE_MAP

    public:

    int get_hp() {return health_points;}

    /*!
      Jest to pewne zdarzenie powodujace agresje bota.
      Polega ono na zmianie stanu w momencie wywolania
      na stan ktory zostal przypisany w transition map.
    */
    void charge(BotData*);
    void go_idle();

    virtual void take_dmg(int damage);
    void info();

    void loose_hp(int amount) {health_points-=amount;}

    BotBody(int hp=100, int at=10, int spd=2, int att_r=2); 
};

#endif