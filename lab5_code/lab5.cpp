#include <iostream>
#include <string>
#include <regex>


//інтерфейс для сутностей
class Objects{
public:
    virtual void setNewStatus(bool status, std::string code, std::string name = "L", std::string email = "em") = 0;
    virtual std::string getCode() const = 0;
    virtual bool getStatus() const = 0;
    virtual std::string getName() const {return " ";} 
    virtual std::string getEmail() const{return " ";}

};

//клас продукту
class Product : public Objects{
 private:
    std::string m_product_code = "00000001";
    std::string m_product_name = "00000000";
    bool m_product_status = false;

 public:
    Product(std::string product_code, std::string product_name, bool product_status){
        m_product_code = product_code;
        m_product_name = product_name;
        m_product_status = product_status;
    }

    void setNewStatus(bool product_status, std::string p_code, std::string name = "L", std::string email = "em") {
      m_product_status = product_status;
      m_product_code = p_code;
      m_product_name = name;
      std::cout << "Saved product info: "<<m_product_status<<", "<<m_product_code<<", "<<m_product_name <<"\n";
    }
    

    std::string getCode() const override{
        return m_product_code ;
    }

    std::string getName() const override {
        return m_product_name ;
    }

    bool getStatus() const override {
        return m_product_status ;
    }



};

//клас користувача
class User  : public Objects{
 private:
    std::string m_user_name = "Joker";
    std::string m_user_email = "";
    std::string m_user_code = "00000002";
    // true якщо покупець надійний, false якщо ні
    bool m_user_status = false;

 public:
    User(std::string user_name, std::string user_email, std::string user_code){
        m_user_name = user_name;
        m_user_email = user_email;
        m_user_code = user_code;
    }

    void setNewStatus(bool user_status, std::string u_code, std::string name = "L", std::string email = "em") {
        m_user_status = user_status;
        m_user_code = u_code;
        m_user_name = name; 
        m_user_email = email;
        std::cout << "Saved user info: "<<m_user_status<<", "<<m_user_code<<", "<<m_user_name <<", "<<m_user_email<<"\n";
    }
 

    std::string getEmail() const override{
        return m_user_email;
    }

    std::string getName() const override{
        return m_user_name ;
    }

    std::string getCode() const override{
        return m_user_code ;
    }

    bool getStatus() const override{
        return m_user_status;
    }


};

//клас замовлення
class Order  : public Objects{
 private:
    std::string m_order_code = "00000003";
    bool m_order_status = false;

 public:
    Order(std::string order_code, bool order_status){
        m_order_code = order_code;
        m_order_status = order_status;
    }

    void setNewStatus(bool order_status, std::string o_code, std::string name = "L", std::string email = "em") {
        m_order_status = order_status;
        m_order_code = o_code;
        std::cout << "Saved order info: "<<m_order_status<<", "<<m_order_code<<"\n";
    }

    std::string getCode() const override{
        return m_order_code ;
    }

    bool getStatus() const override{
        return m_order_status ;
    }


};

//клас, шаблоного методу, де можна зберегти та замінити данні, якщо вони валідні, 
//отримати відповідь по данним, використати хуки для майбутніх змін у конкретних класах
class RestApiSimulator {

 public:
  void setObgect(Objects *object) const {
    std::cout << "You work with object # ";
    std::cout << object->getCode()<<"\n";
    if(this->validation(object->getCode(), object->getStatus(), object->getName(), object->getEmail())){
      this->saveInfo(object, object->getCode(), object->getStatus(), object->getName(), object->getEmail());
    }
  }
  void makeObjectChandges(Objects *object, std::string code, std::string name = "L", std::string email = "em", bool status = false) const{
    std::cout << "You want to change object # ";
    std::cout << object->getCode()<<"\n";
    if(this->validation(code, status, name, email )){
      this->saveInfo(object, code, status, name, email );
      }
  }

 protected:


  void getAnsver(bool status, std::string code) const {
    std::cout << "Code: "<<code<< " Status: "<<status<<"\n";
  }

  virtual bool validation(std::string code, bool status = false, std::string name = "L", std::string email = "em") const = 0;
  virtual void saveInfo(Objects *object, std::string code, bool status = false, std::string name = "L", std::string email = "em") const = 0;
  

  virtual std::string someHook1(bool status, std::string code) const {return " ";}
  virtual void someHook2() const {}
};

//валідація та збереження валідного продукту
class RequestProduct : public RestApiSimulator {
protected:
  bool validation(std::string code, bool status = false, std::string name = "L", std::string email = "em") const override {
    bool validation_status = false;
    std::string m_code = code;
    std::string m_name = name;
    std::cout<<"Name: "<<m_name<<"\n";
    bool m_status = status;
    std::regex code_reg("[0-9]{8}");
    std::regex name_reg("(\\w)*");

    std::cout << "Product validation result: ";
    if(std::regex_match(m_code , code_reg)){
      if(std::regex_match(m_name , name_reg)){
        if (m_status)
        {
          std::cout<<"All is ok\n";
          validation_status = true;
        }
        else{
          std::cout<<"Product had run out\n";
        }
      }
      else{
        std::cout<<"Wrong name\n";
      }
    }
    else
    {
      std::cout<<"Wrong code\n";
    }
    
    return validation_status;
  }

  void saveInfo(Objects *object, std::string code, bool status = false, std::string name = "L", std::string email = "em") const override {
    
    std::cout << "Saving good product info\n";
    object->setNewStatus(true, code, name); 
    this->getAnsver(object->getStatus(), object->getCode());
    
  }
};

//валідація та збереження надійного користувача
class RequestUser : public RestApiSimulator {
protected:
  bool validation(std::string code, bool status = false, std::string name = "L", std::string email = "em") const override {
    bool validation_status = false;
    std::regex email_reg("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    std::regex code_reg("[0-9]{8}");
    std::regex name_reg("(\\w)*");
    std::string m_email = email;
    std::string m_name = name;
    std::string m_code = code;
    
    std::cout << "User validation result: ";
    
    if(std::regex_match(m_code , code_reg)){
      if(std::regex_match(m_name , name_reg)){
        if (std::regex_match(m_email, email_reg))
        {
          std::cout<<"All is ok\n";
          validation_status = true;
        }
        else{
          std::cout<<"Wrong email\n";
        }
      }
      else{
        std::cout<<"Wrong name\n";
      }
    }
    else
    {
      std::cout<<"Wrong code\n";
    }    
    return validation_status; 
  }

  void saveInfo(Objects *object, std::string code, bool status = false, std::string name = "L", std::string email = "em") const override {
    std::cout << "Saving good user info\n";
    object->setNewStatus(true, code, name, object->getEmail()); 
    this->getAnsver(object->getStatus(), object->getCode());
  }
};

//валідація та збереження валідного замовлення
class RequestOrder : public RestApiSimulator {
 protected:
  bool validation(std::string code, bool status = false, std::string name = "L", std::string email = "em") const override {
    bool validation_status = false;
    std::regex code_reg("[0-9]{8}");
    std::string m_code = code;
    bool m_status = status;

    std::cout << "Order validation result: ";
    if(std::regex_match(m_code , code_reg)){
      if(m_status){
          std::cout<<"All is ok\n";
          validation_status = true;
      }
      else{
        std::cout<<"Order status error\n";
      }
    }
    else
    {
      std::cout<<"Wrong code\n";
    }    
    return validation_status;
  }

  void saveInfo(Objects *object, std::string code, bool status = false, std::string name = "L", std::string email = "em") const override {
    std::cout << "Saving good order info\n";
    object->setNewStatus(true, code); 
    this->getAnsver(object->getStatus(), object->getCode());
    this->someHook1(object->getStatus(), object->getCode());
  }

  std::string someHook1(bool status, std::string code) const override {
    std::cout << "Pseudo Json as Hook1: \n";
    std::cout<<"{ code: "<<code<<", status: "<<status<<" } \n";
    return "{ code: "+code +", status: " + std::to_string(status) + " } ";
  }
};


//клієнтський код
int main() {
    std::cout << "Product:\n";
    Product *product1 = new Product{"10000001", "Lamp", true};
    product1->getCode();

    RequestProduct *recquest_product1 = new RequestProduct;
    recquest_product1->setObgect(product1);
    std::cout << "\n";


    std::cout << "User:\n";
    //name, email, code
    User *user1 = new User{"Parry", "perry1@gmail.com", "20000001"};
    RequestUser *recquest_user1 = new RequestUser;
    recquest_user1->setObgect(user1);
    std::cout << "\n";

    recquest_user1->makeObjectChandges(user1, "20000001", "Parry", "perryNo@gmail.com");
    std::cout << "\n";

    recquest_user1->makeObjectChandges(user1, "20000001", "Parry", "permail.com");
    std::cout << "\n";

    std::cout << "Order:\n";
    //code, status
    Objects *order1 = new Order{"30000001", true};
    RequestOrder *recquest_order1 = new RequestOrder;
    recquest_order1->setObgect(order1);


    delete product1;
    delete user1;
    delete order1;
    delete recquest_product1;
    delete recquest_user1;
    delete recquest_order1;
    return 0;
}