#include <iostream>
#include <fstream>
#include "../Parser/parser.h"
int runReplayEngine(){

    std::cout<<"Replay Engine is Initiated "<<std::endl;
    std::cout<<"------------------------- "<<std::endl;


    std::fstream InputFile("inputs/CASH_SELECTED_28072025.DAT");

    if( !InputFile.is_open()){
        std::cout<<"Error Opening The File";
        return 0; 
    }

    int count =0; 
    
    std::string entry;
    OrderEvent order_event;

    while( std::getline(InputFile, entry)  ){
        std::string recordType = entry.substr(0,2);
       
        if(recordType == "PO"){
            order_event = OrderEvent::parseOrderEvent(entry);
            count++;
        }else{
            std::cout<<"Regular Order "<<std::endl;
            break;
        }
    }
     std::cout<<count<<std::endl;

    InputFile.close();
    return 1;
}