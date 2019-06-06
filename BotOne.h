#ifndef BOTONE_H
#define BOTONE_H

#include "BotBody.h"

//!Przyklad jak mozna wykorzystac cialo bota do zrobienia roznych wersji przeciwnika
class BotOne: public BotBody
{
    void st_attack(BotData*);

    public:

    BotOne(): BotBody() {}
};

#endif