#include <iostream>
#include <string>
#include <list>


//інтерфейс компонентів
class Component{
public: 
  virtual void add(Component *component) {}
  virtual void remove(Component *component) {}
  virtual std::string action() const = 0;

};



//клас простого компоненту форми
class Input: public Component{
private:
    std::string m_input = "Component input: ";
    std::string m_inputed_object = "obgect";
    
public:
    Input(std::string inputed_object){
        m_inputed_object = inputed_object;
    }

    std::string action() const override {
        return m_input +"'"+ m_inputed_object+"', ";
  }

};


//клас простого компоненту форми
class Select: public Component{
private:
    std::string m_select = "Component select";
    std::string m_selected_object = "obgect";

public:
    Select(std::string selected_object){
        m_selected_object = selected_object;
    }


    std::string action() const override {
        return m_select +"'"+ m_selected_object+"'";
    }

};

//клас контейнеру
class Fieldset: public Component{
private:
    std::list <Component *> m_childrens;
    std::string m_fieldset = "Component fieldset";

public:
    Fieldset(std::string fieldset){
        m_fieldset = fieldset;
    }
    void add(Component *component) override {
        m_childrens.push_back(component);
    }

    void remove(Component *component) override {
        m_childrens.remove(component);
    }

    std::string getChildren() const{
        std::string component_list = "";
        for (Component * n : m_childrens)
            component_list = component_list + n->action() + "\n\t";
            
    return component_list;
    }

    std::string action() const override {
        return m_fieldset + " which includes: \n\t"  + this->getChildren();
    }


};



//клієнтський код
int main()
{
    Component * form1 = new Fieldset{"Form_1"};
    Component * field1 = new Fieldset{"Field_1"};
    Component * field2 = new Fieldset{"Field_2"};

    Component * imput_text1 = new Input{"textfield1"};
    Component * imput_radio1 = new Input{"radiobutton1"};
    Component * imput_radio2 = new Input{"radiobutton2"};
    Component * imput_radio3 = new Input{"radiobutton3"};
    Component * imput_button1 = new Input{"button1"};

    Component * select_list1 = new Select{"select1"};

    field1->add(imput_text1);
    field1->add(imput_button1);

    field2->add(imput_radio1);
    field2->add(imput_radio2);
    field2->add(imput_radio3);

    form1->add(field1);
    form1->add(field2);
    form1->add(imput_button1);

    std::cout <<form1->action()<< "\n";

    std::cout << "Client removed first field...\n";
    form1->remove(field1);
    std::cout <<form1->action()<< "\n";

    delete form1;
    delete field1;
    delete field2;
    delete imput_text1;
    delete imput_radio1;
    delete imput_radio2;
    delete imput_radio3;
    delete imput_button1;
    delete select_list1;

    return 0;
}
