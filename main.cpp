#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list> 
#include <map> 
#include <unordered_map> 
#include <iterator> 


struct OrderRecord{
    std::int64_t order_id;
    char activity_type;
    char side;
    long long price; 
    long long quantity; 
    std::int64_t new_order_id;

};
struct OrderRecordPosition{
    char side;
    long long price ; 
    std::list <OrderRecord>::iterator position;
};
 
static std::map<long long , std::list <OrderRecord> , std::greater<long long>> buySide;
static std::map<long long , std::list <OrderRecord>> sellSide;
static std::unordered_map<int64_t , OrderRecordPosition > orderIDLookUp;

static void printOrderRecord(OrderRecord order){
        std::cout << ' '<< order.order_id << ' '<< order.activity_type << ' '<< order.side <<' '<< order.price << ' '<< order.quantity <<'\n' ;
}

static void ADD_ORDER( OrderRecord order ){
        if( order.side == 'B' ){
        if( !buySide.count(order.price) ){
            std::list<OrderRecord> recordList;
            recordList.push_back(order);
            buySide[order.price] = recordList;
        }else{
            buySide[order.price].push_back(order);
        }
        orderIDLookUp[order.order_id] = {
            order.side,
            order.price,
            std::prev(buySide[order.price].end())
        };
        } else if(order.side == 'S') {
         if( !sellSide.count(order.price) ){
            std::list<OrderRecord> recordList;
            recordList.push_back(order);
            sellSide[order.price] = recordList;
         }else{
            sellSide[order.price].push_back(order);
         }
         orderIDLookUp[order.order_id] = {
            order.side,
            order.price,
            std::prev(sellSide[order.price].end())
        };
        }

}
static void DELETE_ORDER(OrderRecord order ){

    if( orderIDLookUp.count( order.order_id ) ){

    char side = orderIDLookUp[order.order_id].side;
    long long price = orderIDLookUp[order.order_id].price;
    auto& position = orderIDLookUp[order.order_id].position;

    if(side == 'B') {
        //remove from the buy side 
        if( buySide.count(price) ){
            auto& order_record = buySide[price];
            //remove
            order_record.erase(position);
            //if the price level is empty
            if(order_record.empty()){
                buySide.erase(price);
            }

        }else{
            std::cout<<"The price level doesn't exists for REMOVAL";
            return;
        }
    }
    
    else if(side == 'S'){
        if( sellSide.count(price) ){

            auto& order_record = sellSide[price];
            //remove
            order_record.erase(position);
            //if the price level is empty
            if(order_record.empty()){
                sellSide.erase(price);
            }
        }else{
            std::cout<<"The price level doesn't exists for REMOVAL";
            return;

        }
    }
    orderIDLookUp.erase(order.order_id);
    }
    else{
        std::cout<<"NO ORDER ID FOUND FOR REMOVAL OF THE ORDER";
    }
}

static void CANCEL_ORDER(OrderRecord order){
    // order cancel -> partial reduction in the quantity -> order id -> cancelled shared -> we will get if from the feed 
    long long cancelQuanity = order.quantity  ;
    //check if the order id is in the order book if yes cancel straight away
    if( orderIDLookUp.count( order.order_id ) ){
        //get the side 
        char side = orderIDLookUp[order.order_id].side;
        long long price = orderIDLookUp[order.order_id].price;
        auto& position = orderIDLookUp[order.order_id].position;
        if(side == 'B') {
            //remove from the buy side 
            if( buySide.count(price) ){
                position->quantity -= cancelQuanity;
                // if quanity is 0 we can remove it from the book 
                if(position->quantity == 0){
                    DELETE_ORDER(order);
                }
            }else{
                std::cout<<"The price level doesn't exists for PARTIAL CANCELLATION";
            }
        }
        else if(side == 'S'){
            if( sellSide.count(price) ){
                auto& order_record = sellSide[price];
                position->quantity -= cancelQuanity;
                // if quanity is 0 we can remove it from the book 
                if(position->quantity == 0){
                    DELETE_ORDER(order);
                }
            }else{
                std::cout<<"The price level doesn't exists for PARTIAL CANCELLATION";
            }
        }
    }
    else{
        std::cout<<"NO ORDER ID FOUND FOR PARTIAL CANCELLATION OF THE ORDER";
    }
}

int main(){
    std::string line;
    int count = 0; 
    while (std::getline(std::cin, line)) {
        std::istringstream ss(line);
        // std::cout<<line<<'\n';
        OrderRecord order{};
        ss >> order.order_id >> order.activity_type  >> order.side >> order.price >> order.quantity >> order.new_order_id;
        //add 
        if(order.activity_type == 'A' || order.activity_type == 'F'){
            ADD_ORDER(order);
        }
        else if( order.activity_type == 'D'){
            DELETE_ORDER(order);
        }
        else if( order.activity_type ==  'X' ){
            CANCEL_ORDER(order);
        }
        else if ( order.activity_type == 'U'){
            
            OrderRecord modified_order{};
            if( orderIDLookUp.count(order.order_id) ){
                char modification_side =   orderIDLookUp[order.order_id].side;
                modified_order.activity_type = order.activity_type;
                modified_order.side = modification_side;
                modified_order.price = order.price;
                modified_order.quantity = order.quantity;
                modified_order.order_id = order.new_order_id;

                DELETE_ORDER(order);
                ADD_ORDER(modified_order);

            }else{
                std::cout<<"Cannot modify this order order id was not found"<<'\n';
            }
           
        }
        count++;
    }
    std::cout<<"Processed "<< count <<" Orders";
    return 0; 
}