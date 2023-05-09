#include <iostream>
#include <string>

//клас PostgreSQL

class PostgreSQLBase{
public:
    std::string m_pselect = "*";
    std::string m_pwhere = "all";
    std::string m_plimit = "no";

    PostgreSQLBase(){}

}; 

//клас MySQL
class MySQLBase{
public:
    std::string m_mselect = "*";
    std::string m_mwhere = "all";
    std::string m_mlimit = "0";

    MySQLBase(){}

};

// інтерфейс класу будівельника
class BuildDataBase{
public: 
    virtual void querySelect(std::string sel) = 0;
    virtual void queryWhere(std::string whe) = 0;
    virtual void queryLimit(std::string lim) = 0;
    virtual void qetSQL() = 0;
};

//клас побудови запитів  до PostgreSQL

class BuildMyPostgreSQLBase : public BuildDataBase{
private: 
    PostgreSQLBase m_pbase;
    std::string m_database;

public:
    BuildMyPostgreSQLBase(std::string database){
        m_database = database;
    }
    void querySelect(std::string sel) override{
        m_pbase.m_pselect = sel;    
    }

    void queryWhere(std::string whe) override{
        m_pbase.m_pwhere = whe;    
    }

    void queryLimit(std::string lim) override{
        m_pbase.m_plimit = lim;    
    }

    void qetSQL() override{
        std:: cout << "PostgreSQL query: \n";
        std:: cout <<" SELECT " + m_pbase.m_pselect + " FROM " + m_database + " WHERE " + m_pbase.m_pwhere + " LIMIT " + m_pbase.m_plimit + ";\n";
    }

}; 

//клас побудови запитів  до MySQL
class BuildMySQLBase : public BuildDataBase{
private: 
    MySQLBase m_mbase;
    std::string m_database;
public:
    BuildMySQLBase(std::string database){
        m_database = database;
    }
    void querySelect(std::string sel) {
        m_mbase.m_mselect = sel;
        
    }

    void queryWhere(std::string whe) {
        m_mbase.m_mwhere = whe;
        
    }

    void queryLimit(std::string lim) {
        m_mbase.m_mlimit = lim;
        
    }

    void qetSQL() { 
        std:: cout << "MySQL query: \n";
        std:: cout <<" SELECT " + m_mbase.m_mselect + " FROM " + m_database + " WHERE " + m_mbase.m_mwhere + " LIMIT " + m_mbase.m_mlimit + ";\n";
    }

};


//клієнтський код
int main()
{
    BuildMyPostgreSQLBase pbase1{"Base 1"};
    pbase1.querySelect("Name");
    pbase1.queryWhere("Name = 'Mike'");
    pbase1.qetSQL();

    BuildMySQLBase mbase1{"Base 2"};
    mbase1.querySelect("Age");
    mbase1.queryWhere("Age < 10");
    mbase1.queryLimit ("5");
    mbase1.qetSQL();
    return 0;
}



