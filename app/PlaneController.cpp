#include <app/PlaneController.h>
#include <fstream>
#include <iomanip>
#include <json/Parser.h>
#include "Variable.h"

using namespace yazi::app;

REGISTER_CLASS(PlaneController);
REGISTER_CLASS_METHOD(PlaneController, getPlaneData, void, const Request &, Response &);
REGISTER_CLASS_METHOD(PlaneController, getData, void, const Request &, Response &);

extern UAV uav_data[4];
extern const std::string UAV_DATA_JSON_PATH;
extern Json planeJson;

void PlaneController::getPlaneData(const Request &req, Response &resp)
{   
    std::cout << "--------------------getPlaneData--------------------" << std::endl;
    std::cout << planeJson.str() << std::endl;
    resp.json(planeJson.str());
}


// 从ROS源中接收json数据
void yazi::app::PlaneController::getData(const Request &req, Response &resp){
    
    std::cout << "-------------------getData--------------------" << std::endl;
	std::cout <<"path:  " << req.path() << std::endl;
	std::cout <<"header:  " << req.header("Host") << std::endl;
	std::cout <<"get: " << req.is_get() << " post: " << req.is_post() <<std::endl;

    // 将json存入本地
    Json j = req.post();

    // 解析json错误
    if (j.isNull()) {
        resp.code(500);
        resp.html("null json");
        return;
    }

    std::cout << "size: " << j.size() << std::endl;
    std::cout <<"body: " << j.str() << std::endl;
    std::ofstream ofs(UAV_DATA_JSON_PATH);
    ofs << std::setw(4) << j << std::endl;
    planeJson = j;
    std::cout << "-------------------getData--------------------" << std::endl << std::endl << std::endl;
    
	resp.html("hello, I have reveived");
};