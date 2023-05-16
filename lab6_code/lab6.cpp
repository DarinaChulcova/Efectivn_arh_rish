#include <iostream>
#include <string>
#include <vector>


class Department;
class Company;

//інтерфейси візиторів та сутностей(департменту та компанії)
class Visitor {
public:
    virtual void visit(Department& ref) = 0;
    
    virtual void visit(Company& ref) = 0;
    
    virtual ~Visitor() = default;
};

class Essence{
public:
    virtual void accept(Visitor& visitor) = 0;
    
    virtual ~Essence() = default;
};

//класс співробітника
class Employee{
public: 
    std::string name_empl;
    int salary_empl;
    
    Employee(std::string n_empl, int s_empl)
    {
        name_empl = n_empl;
        salary_empl = s_empl;
        std::cout <<"Employee " + name_empl + " " << salary_empl << "\n";
    };
    
};

//клас департменту(відділу)
class Department: public Essence {
public:
    std::vector<Employee> employees;
    
    void add_employee(Employee empl)
    {
        employees.push_back(empl);
    };
    
    void accept(Visitor& v) override{
        v.visit(*this);
    };
};

//клас компанії
class Company: public Essence {
  
public:
    std::vector<Department> departments;
    
    void add_department(Department dep)
    {
        departments.push_back(dep);
    };
    
    void accept(Visitor& v) override{
        v.visit(*this);
    };
};

// в залежності від класу визивається свій метод visit
class VisitorHuman: public Visitor{
public:
    void visit(Department& ref) override{
        std::cout << "Department report: \n";
        for (size_t i = 0; i < ref.employees.size(); i++)
        {
            std::cout << ref.employees[i].name_empl << " with salary " << ref.employees[i].salary_empl << "\n";
        }
    };
    
    void visit(Company& ref) override{
        std::cout << "Company report: \n";
        for (size_t i = 0; i < ref.departments.size(); i++){
            for (size_t j = 0; j < ref.departments[i].employees.size(); j++){
                std::cout << ref.departments[i].employees[j].name_empl << " with salary " << ref.departments[i].employees[j].salary_empl<<"\n";
            }
        }
        
    };
};

//клієнтський код
int main()
{
    Employee emp1("Employ_1", 700);
    Employee emp2("Employ_2", 700);
    Employee emp3("Employ_3", 800);
    Employee emp4("Employ_4", 800);
    
    Department dep1;
    dep1.add_employee(emp1);
    dep1.add_employee(emp2);
    
    Department dep2;
    dep2.add_employee(emp3);
    dep2.add_employee(emp4);
    
    Company comp1;
    comp1.add_department(dep1);
    comp1.add_department(dep2);
    
    VisitorHuman vis;
    dep1.accept(vis);
    dep2.accept(vis);
    comp1.accept(vis);
    
    return 0;
}
