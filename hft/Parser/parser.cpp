#include <iostream>
#include "../Parser/parser.h"

OrderEvent OrderEvent::parseOrderEvent(std::string& Event){
    OrderEvent order_event;
    order_event.recordType =
        Event.substr(0,2);

    order_event.orderNumber =
        std::stoull(Event.substr(6,15));

    order_event.buyAndSellIncidicator =
        Event.at(36);

    order_event.activityType =
        Event.at(37);


    std::string symb =  Event.substr(38,10);
    int i=0; 
    while( symb.at(i) == 'b'){
        i++;
    }

    order_event.symbol = symb.substr(i,symb.size());

    order_event.volumeDisclosed =
    std::stoul(Event.substr(50,10));
     

    order_event.volumeOriginal =
    std::stoul(Event.substr(60,10));

    order_event.limitPrice =
       std::stoi(Event.substr(70,8));

    order_event.marketOrderFlag =
        Event.at(86);

    return order_event;
} 

void OrderEvent::PrintOrderEvent(){
    std::cout <<"Record Type "<< recordType <<'\n';
    std::cout << "Order Number "<<orderNumber <<'\n';
    std::cout <<"Buy and Sell Indicator  "<< buyAndSellIncidicator <<'\n';
    std::cout <<"Activity Type "<< activityType <<'\n';
    std::cout <<"Symbol "<< symbol <<'\n';
    std::cout << "Volume Disclosed "<<volumeDisclosed <<'\n';
    std::cout <<"Volume Original "<< volumeOriginal <<'\n';
    std::cout <<"Limit Price "<< limitPrice <<'\n';
    std::cout <<"Market Order Flag "<< marketOrderFlag <<'\n';
}