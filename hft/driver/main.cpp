#include <iostream>
#include "../Exchange/exchange_engine.h"
#include "../Replay/replay_engine.h"

int main(){
    std::cout<<"-------HFT SYSTEM-------"<<std::endl;
    runReplayEngine();
    return 0;
}