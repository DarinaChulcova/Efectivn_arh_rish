#include <iostream>
#include <string>
#include <vector>

//клас різних маршрутів
class TourPathIterator{
private:
    std::vector<std::string> m_path_places;
    int variant=0;
    int index=0;

public:
    TourPathIterator(std::vector<std::string> recived_places, int varia){
        m_path_places = recived_places;
        variant=varia;
        
    }

    void getPath(){
        if(variant==1){
            std::cout<<"Self-made path: \n";
        }
        else if(variant==2){
            std::cout<<"Path according to the navigator: \n";           
        }
        else if(variant==3){
            m_path_places.resize(2);
            std::cout<<"Path according to the guide: \n";
            }             
        
    }

    int goNext(int ind){
        index=ind;
        return index+1;
    }

    bool haveEnd(int i){
        index=i;
        return index>=m_path_places.size();
    }


};


//клас колекції елементів
class TourPlaces{

private:
    std::vector<std::string> m_places;
    int my_i=0;

public:
    void setValues(std::vector<std::string> newPlaces){
            m_places=newPlaces;
        }
 
	void printSelfMadePath(){     
        TourPathIterator recomend_spath {m_places, 1};
        recomend_spath.getPath();
        while(!recomend_spath.haveEnd(my_i)){
            std::cout<<m_places[my_i]<<"\n";
            my_i = recomend_spath.goNext(my_i);
        }
        my_i=0;
	}

    void printNavigatorPath(){     
        TourPathIterator recomend_npath {m_places, 2};
        recomend_npath.getPath();
        while(!recomend_npath.haveEnd(my_i)){
            std::cout<<m_places[my_i]<<"\n";
            my_i = recomend_npath.goNext(my_i);
        }       
        my_i=0;
	}

    void printGuidePath(){ 
        TourPathIterator recomend_gpath {m_places, 3};
        recomend_gpath.getPath();
        while(!recomend_gpath.haveEnd(my_i)){
            std::cout<<m_places[my_i]<<"\n";
            my_i = recomend_gpath.goNext(my_i);
        }
        my_i=0;
	}

};

//клієнтський код
int main()
{
    
    TourPlaces placesKh;
    placesKh.setValues({"Gorky Park","Zoo","Freedom Square"});
    placesKh.printGuidePath();
    placesKh.printNavigatorPath();
    placesKh.printSelfMadePath();

    return 0;
}
