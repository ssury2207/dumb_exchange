#pragma once 
#include <iostream>
#include <string>
struct OrderEvent{
    std::string recordType;
    std::uint64_t orderNumber;
    char buyAndSellIncidicator;
    char activityType ;
    std::string symbol ;
    std::uint32_t volumeDisclosed ;
    std::uint32_t volumeOriginal ;
    std::int32_t limitPrice ;
    char marketOrderFlag ;

   static OrderEvent parseOrderEvent(std::string& Event );

    void PrintOrderEvent();
};