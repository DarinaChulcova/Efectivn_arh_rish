#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <regex>


//клас спогадів
class Memories{
public: 
    virtual std::string getDate() const = 0;
    virtual std::string getState() const = 0;
    virtual std::string getName() const = 0;
};

//клас конкретного спогаду
class ConcreteMemory : public Memories{
private:
    std::string m_state;
    std::string m_date;


public:
    ConcreteMemory(std::string state) : m_state(state) {
    m_state = state;
    std::time_t now = std::time(0);
    m_date = std::ctime(&now);
    }
    //отримати стан
    std::string getState() const override {
    return m_state+ "\n";
    }
    //отримати дату
    std::string getDate() const override {
        return m_date+ "\n";
    }
    //отмиати стан і дату
    std::string getName() const override {
        return m_state + " /Date of saving: " + m_date + "\n";
    }

};



//клас творця
class Creator{
private:
    std::string m_creator_state;
    Memories *m_creator_memory;

public:
    Creator(){
        m_creator_state = "Not choosed";
    }
    
    //збереження нового стану
    void setNewState(std::string creator_state){
        m_creator_state = creator_state;
    }

    void saveNewState(){
        //копіювання нового стану до спогаду
        m_creator_memory = new ConcreteMemory{m_creator_state};
    }

    std::string getCurrentName(){
        //отримання поточного стану зі спогаду
        return m_creator_memory->getName();
    }
        std::string getCurrentState(){
        //отримання поточного стану зі спогаду
        return m_creator_memory->getState();
    }

};


//клас де зберігаються спогади
class Keeper{

private:
    std::vector<std::string> m_memories;
    std::vector<std::string> m_state_memories;
    std::string m_setting_name = "Oh no";
    std::string m_setting_state = "Oh no";

    Creator *m_creator = new Creator();
    
    

public:
Keeper(Creator* new_creator) : m_creator(new_creator) {}

//додавання поточного стану до вектору історії
void addBackup(){

    m_setting_name = m_creator ->getCurrentName();
    m_memories.push_back(m_setting_name);

    m_setting_state = m_creator ->getCurrentState();
    m_state_memories.push_back(m_setting_state);
}

//поки є, що вилучати - вилучаємо та змінюємо поточний стан
void undo(){
    if (m_memories.size()<=1){
        std::cout <<"No memories \n";
        m_creator -> setNewState("No state");
        m_creator -> saveNewState();
    }
    else{
        m_memories.pop_back();
        m_state_memories.pop_back();

        m_creator -> setNewState(m_state_memories[m_state_memories.size()-1] );
        m_creator -> saveNewState();
    }
    
}

//вивід усіх елементів вектору
void showHistory(){
    std:: cout <<"History: \n";
    for(std::string n : m_memories)
        std::cout << n ;
    std:: cout <<"End\n";
}

};

//клієнтський код
int main()
{
    
    Creator *user1 = new Creator();
    Keeper pusher{user1};

    user1->setNewState("Accept all notifications");
    user1->saveNewState();
    pusher.addBackup();

    user1->setNewState("Accept notifications about technical changes to the site");
    user1->saveNewState();
    pusher.addBackup();

    user1->setNewState("Accept news alerts");
    user1->saveNewState();
    pusher.addBackup();

    user1->setNewState("Do not accept notifications");
    user1->saveNewState();
    pusher.addBackup();
    
    std:: cout <<"Current state 1: " <<user1->getCurrentState();
    pusher.showHistory();
    
    std:: cout <<"Current state 2: " <<user1->getCurrentState();
    pusher.undo();
    pusher.showHistory();
    std:: cout <<"Current state 3: " <<user1->getCurrentState();
    pusher.undo();
    pusher.showHistory();
    std:: cout <<"Current state 4: " <<user1->getCurrentState();
    pusher.undo();
    pusher.showHistory();
    std:: cout <<"Current state 5: " <<user1->getCurrentState();
    pusher.undo();
    std:: cout <<"Current state 6: " <<user1->getCurrentState();
    

    return 0;
}
