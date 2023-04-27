#include <iostream>
#include <string>

//клас посередника
class BaseMediator{
public:
    virtual void getOrder(std::string client_order_name, 
                            std::string client_tel,
                            std::string product_name, 
                            bool order_self_pickup, 
                            int order_date, 
                            bool order_pickup_anozer, 
                            std::string pickuper_order_name, 
                            std::string pickuper_tel ) = 0;
};

//конкретний клас, що викликається через посередника, в якому обробляється замовлення
class OrderMediator : public BaseMediator{
private:
std::string order_time = " Delivery time: 00:00 - 02:00";

public:
    OrderMediator(){}
    void getOrder(std::string client_order_name , 
                    std::string client_tel, 
                    std::string product_name, 
                    bool order_self_pickup, 
                    int order_date, 
                    bool order_pickup_anozer, 
                    std::string pickuper_order_name, 
                    std::string pickuper_tel){

                        std::cout<<"Client "<< client_order_name<<" order: \n";
                        std::cout<<" Order: "<< product_name <<"\n";
                        if (order_self_pickup){
                            std::cout<<" The client chosed self-pickap. We wait you in our store from 9 a.m to 6 p.m ! \n";
                        }
                        else{
                            std::cout<<" Day for delivery: "<<order_date<<"th of this month\n";
                            if(order_date%2==0){
                                order_time = " Delivery time: 08:00 - 13:00";
                                std::cout<<order_time<<"\n";
                            }
                            else{
                                order_time = " Delivery time: 14:00 - 19:00";
                                std::cout<<order_time<<"\n";
                            }

                            if(order_pickup_anozer){
                                std::cout<<" Order will receive another person: "<<pickuper_order_name<<". Phone number: "<<pickuper_tel<<"\n";
                            }
                            else{
                                std::cout<<" Order will receive the client. Phone number: "<<client_tel<<"\n";
                            }                           
                        }
                                              
    }

};

//клас клієнтів служби, в якому передаються дані до посередника
class Client{
private:
    std::string m_client_name = "Petrovich";
    BaseMediator *m_med_order;
public:
    Client(BaseMediator *med_order, 
            std::string client_name, 
            std::string client_tel,
            std::string product_name,  
            bool order_self_pickup, 
            int order_date = 0, 
            bool order_pickup_anozer = false, 
            std::string pickuper_order_name = "Nobody", 
            std::string pickuper_tel = "0000000000"){

                m_client_name = client_name;
                m_med_order = med_order;
                med_order-> getOrder(m_client_name, client_tel, product_name, order_self_pickup, order_date, order_pickup_anozer, pickuper_order_name, pickuper_tel);//order metod
    }

};

//клієнтський код
int main()
{
    
    std::cout<<"Order list: \n";

    //Параметри: ім'я, телефон, назва замовлення, самовивіз, дата, забере інша людина, ім'я забирача, телефон забирача
    Client *cl1 = new Client(new OrderMediator(), "Oleksa","097276484", "Rose basket", true);
    Client *cl2 = new Client(new OrderMediator(), "Toreodor","044377928", "Bouquet of sunflowers and dahlias", false, 13, false);
    Client *cl3 = new Client(new OrderMediator(), "Alba","0630709554", "Wild flower wreath", false, 10, true, "Nahida", "0670643788");

    delete cl1;
    delete cl2;
    delete cl2;
    return 0;
}
