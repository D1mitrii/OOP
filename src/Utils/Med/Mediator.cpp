#include "Mediator.h"

Mediator::Mediator(Game *pGame, IOCommander *pCommander)  : game(pGame), commander(pCommander), log(nullptr), control(
        nullptr) {
    game->set_mediator(this);
    commander->set_mediator(this);
}

void Mediator::notify(MediatorObject* who, IMediator::MEVENTS event) {
    if(auto temp = dynamic_cast<Game*>(who)){
        game_handler(event);
        return;
    }
    if(auto temp = dynamic_cast<IOCommander*>(who)){
        commander_handler(event);
        return;
    }
    game->set_step(control->get_step());
}

void Mediator::game_handler(IMediator::MEVENTS cmd) {
    switch (cmd) {
        case IMediator::GAME_STATUS:{
            if(game->get_status() == Game::START){
                g_start();
                return;
            }
            if(game->get_status() == Game::INPROGRESS)
                return;
            if(game->get_status() == Game::DEFEAT){
                commander->Defeat();
            }
            else if(game->get_status() == Game::WIN){
                commander->Victory();
            }
            game->set_status(Game::END);
            break;
        }
        case IMediator::STEP:{
            control->next_step();
            return;
        }
        default:
            break;
    }
}

void Mediator::g_start() {
    commander->create_logger();
    ConfigReader rcfg;
    control = new ControlBridge(rcfg.read_cfg(), new ConsoleControler());
    control->set_mediator(this);
    commander->map_standard();
}

void Mediator::commander_handler(IMediator::MEVENTS cmd) {
    switch (cmd) {
        case IMediator::CONFIRM:{
            game->initialize_field(commander->read_size());
            break;
        }
        case IMediator::CANCEL:{
            game->initialize_field();
            break;
        }
        case IMediator::STEP:{
            game->set_step(control->get_step());
            break;
        }
        default:
            break;
    }
}

void Mediator::set_log(LogPool * logger) {
    log = logger;
}

Mediator::~Mediator() {
    delete game;
    delete commander;
    delete log;
    delete control;
}

