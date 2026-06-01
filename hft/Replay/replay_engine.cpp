#include <iostream>
#include <fstream>
#include "../Parser/parser.h"
#include "../Orderbook/orderbook.h"
#include <unordered_map>
#include <map>
#include <list>



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
    int kotak_c = 0; 

    std::unordered_map<std::uint64_t, OrderEvent > orderbookMap;

    std::map<int32_t, std::list<uint64_t> , std::greater<uint64_t>> buySide;

    std::map<int32_t, std::list<uint64_t> > sellSide;


    while( std::getline(InputFile, entry) ){
         
        order_event = OrderEvent::parseOrderEvent(entry);
        if(order_event.recordType != "PO"){
            break;
        }else{
            if(order_event.symbol == "KOTAKBANK") {
                orderbookMap[order_event.orderNumber] = order_event;
                //check by side or sell side
                if(order_event.buyAndSellIncidicator == 'B'){
                    buySide[order_event.limitPrice].push_back(order_event.orderNumber);
                }else{
                    sellSide[order_event.limitPrice].push_back(order_event.orderNumber);
                }
                kotak_c++;
            }
            count++;
        }
    }
   for (const auto& [orderNumber, event] : orderbookMap) {
    std::cout << "Order Number: " << orderNumber <<"  "<< event.buyAndSellIncidicator << "\n";
    }
    std::cout<<kotak_c<<std::endl;

    InputFile.close();
    return 1;
}