//
// Created by Dmitriy on 10/12/2022.
//

#ifndef OOP_MEDIATOR_H
#define OOP_MEDIATOR_H

class Game;
class IOCommander;

#include "src/Game.h"
#include "src/Utils/IOCommander.h"
#include "IMediator.h"
#include "MediatorObject.h"

class Mediator : public IMediator {
private:
    Game* game;
    IOCommander* commander;
    LogPool* log;
    void game_handler(IMediator::MEVENTS cmd);
    void commander_handler(IMediator::MEVENTS cmd);
public:
    Mediator(Game *pGame, IOCommander *pCommander);
    void set_log(LogPool*);
    void notify(MediatorObject *who, IMediator::MEVENTS event) final;
    void print();
    ~Mediator() override;
};


#endif
