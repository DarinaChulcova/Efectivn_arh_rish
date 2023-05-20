#include <iostream>
#include <string>

//клас підсистеми
class WorkWithYoutube{
private:
    std::string api_key = " ";
    char symbols[27]  = "abcdefghijklmnopqrstuvwxyz";
    char api[11] = {0};
    int random;

public:
    void uploadVideo(std::string video_name){
        std::cout<<"You are uploading new video: '"<<video_name<<"'\n";
        std::cout<<"Video '"<<video_name<<"' had been converted into YouTube format\n";
    }
    void proccesingVideo(std::string video_name){
        std::cout<<"Video '"<<video_name<<"' is being processed...\n";
    }
    void postingVideo(std::string video_name){
        std::cout<<"Video '"<<video_name<<"' had been posted\n";
    }    
    std::string getApiKey(){

        for (int i = 0; i<8; i++) {
            random = rand()%(26);
            api[i] = symbols[random];
        }
        api_key = api;
        std::cout<<"Use api key: '"<<api_key<<"\n";
        return api_key;
    } 
    void proccesingVideoWithApi(std::string video_name){
        this->getApiKey();
        std::cout<<"Video '"<<video_name<<"' is being processed with API\n";
    }

};

//клас фасаду, з яким працює клієнтський код
class Facade{
private:
    WorkWithYoutube new_task;

public:
    void uploadNewVideo(std::string video_name){
        new_task.uploadVideo(video_name);
        new_task.proccesingVideo(video_name);
        new_task.postingVideo(video_name);
    }

    void uploadNewVideoWhithAPI(std::string video_name){
        new_task.uploadVideo(video_name);
        new_task.proccesingVideoWithApi(video_name);
        new_task.postingVideo(video_name);
    }


};


//клієнтський код
int main()
{
    Facade work1;

    std::cout<<"Native uploading:\n";
    work1.uploadNewVideo("Simple Video 1");
    std::cout<<"\n";
    std::cout<<"API uploading:\n";
    work1.uploadNewVideoWhithAPI("Simple Video 2");

    return 0;
}
