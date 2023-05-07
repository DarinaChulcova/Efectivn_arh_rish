#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <regex>




//клас PostgreSQL

class PostgreSQLBase{
private: 
    PostgreSQLBase() {}
    PostgreSQLBase( const PostgreSQLBase&);  
    PostgreSQLBase& operator=( PostgreSQLBase& );
    int n = 0;

public:
    static PostgreSQLBase& getInstance() {
        static PostgreSQLBase  m_pinstance;
        return m_pinstance;
    } 

    void someQuery(){
        n= n+1;    
        std::cout<<" Some PostgreSQLBase query. You use it " + std::to_string(n) + " time \n";
    }

}; 

//клас MongoDB 
class MongoDBBase{
private: 
    MongoDBBase() {}
    MongoDBBase( const MongoDBBase&);  
    MongoDBBase& operator=( MongoDBBase& );
    int m = 0;

public:
    static MongoDBBase& getInstance() {
        static MongoDBBase  m_minstance;
        return m_minstance;
    } 

    void someQuery(){
        m= m+1;    
        std::cout<<" Some MongoDBBase query. You use it " + std::to_string(m) + " time \n";
    }


};


//клієнтський код
int main()
{
    PostgreSQLBase& p1 = PostgreSQLBase::getInstance();
    p1.someQuery();
    PostgreSQLBase& p2 = PostgreSQLBase::getInstance();
    PostgreSQLBase::getInstance().someQuery();

    MongoDBBase& m1 = MongoDBBase::getInstance();
    MongoDBBase::getInstance().someQuery();
    MongoDBBase& m2 = MongoDBBase::getInstance();
    MongoDBBase::getInstance().someQuery();
    return 0;
}



