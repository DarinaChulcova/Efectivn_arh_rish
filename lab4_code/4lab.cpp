#include <iostream>


class OrderStrategy{
public:
    virtual void getCost() = 0;
};

class SelfPickup : public OrderStrategy{

private:
    double m_producr_sprice = 0;
    double m_self_pickup_sprice = 0;
    double final_sprice = 0;

public:
    SelfPickup(double producr_price){
        m_producr_sprice = producr_price;
    }
    void getCost(){
        final_sprice = m_producr_sprice+m_self_pickup_sprice;
        std::cout<<"Self pickup \n";
        std::cout<<"You have to pay "<<final_sprice<<" uan.\n";
        std::cout<<"Self pickup cost "<<m_self_pickup_sprice<<" uan.\n";
    }

};

class ExternalDeliveryService : public OrderStrategy{

private:
    double m_producr_eprice = 0;
    double m_delivery_eprice = 90;
    double final_eprice = 0;

public:
    ExternalDeliveryService(double producr_price){
        m_producr_eprice = producr_price;
    }
    void getCost(){
        final_eprice = m_producr_eprice+m_delivery_eprice;
        std::cout<<"External delivery service \n";
        std::cout<<"You have to pay "<<final_eprice<<" uan.\n";
        std::cout<<"External delivery service cost "<<m_delivery_eprice<<" uan.\n";
    }

};

class OwnDeliveryService : public OrderStrategy{

private:
    double m_producr_oprice = 0;
    double m_delivery_oprice = 40;
    double final_oprice = 0;

public:
    OwnDeliveryService(double producr_price){
        m_producr_oprice = producr_price;
    }
    void getCost(){
        final_oprice = m_producr_oprice+m_delivery_oprice;
        std::cout<<"Own delivery service \n";
        std::cout<<"You have to pay "<<final_oprice<<" uan.\n";
        std::cout<<"Own delivery service cost "<<m_delivery_oprice<<" uan.\n";
    }
};

class getProductCost{

private:
     OrderStrategy *m_strat; 

public:

    void setStrategy(OrderStrategy *s){
        m_strat=s;
        s -> getCost();
    }

};


int main()
{
    double milk_price = 25.5;
    std::cout<<"You want to bye milk. Milk cost: "<<milk_price<<" uan.\n";

    getProductCost *milk = new getProductCost();
    milk->setStrategy(new SelfPickup(milk_price));
    milk->setStrategy(new ExternalDeliveryService(milk_price));
    milk->setStrategy(new OwnDeliveryService(milk_price));

    delete milk;
    return 0;
}
