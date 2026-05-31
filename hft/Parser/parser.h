#pragma once 
#include <iostream>
#include <string>
struct OrderEvent{
    std::string recordType;
    std::string orderNumber;
    char buyAndSellIncidicator;
    char activityType ;
    std::string symbol ;
    std::string volumeDisclosed ;
    std::string volumeOriginal ;
    std::string limitPrice ;
    char marketOrderFlag ;

   static OrderEvent parseOrderEvent(std::string& Event );

    void PrintOrderEvent();
};