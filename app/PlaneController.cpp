#include <app/PlaneController.h>
#include "Variable.h"
#include <fstream>
#include <iomanip>
#include <Link16/tools.h>
using namespace yazi::app;

REGISTER_CLASS(PlaneController);
REGISTER_CLASS_METHOD(PlaneController, planes, void, const Request &, Response &);
REGISTER_CLASS_METHOD(PlaneController, getData, void, const Request &, Response &);

extern UAV uav_data[4];

void PlaneController::planes(const Request &req, Response &resp)
{
    Plane *planes = Tools::assemble_plane();
    Plane plane0 = planes[0];
    std::cout << "plane0.label = " << plane0.label << std::endl;
    std::cout << "plane0.vx = " << plane0.vx << std::endl;
    std::cout << "plane0.vy = " << plane0.vy << std::endl;
    std::cout << "plane0.vz = " << plane0.vz << std::endl;
    std::cout << "plane0.x = " << plane0.x << std::endl;
    std::cout << "plane0.y = " << plane0.y << std::endl;
    std::cout << "plane0.z = " << plane0.z << std::endl;
    delete[] planes;
    resp.html("planes");
}


// 从ROS源中接收json数据
void yazi::app::PlaneController::getData(const Request &req, Response &resp){
    const std::string JSONPATH = "./data/origin_data.json";
    std::cout << "-------------------getData--------------------" << std::endl;
	std::cout <<"path:  " << req.path() << std::endl;
	std::cout <<"header:  " << req.header("Host") << std::endl;
	std::cout <<"get: " << req.is_get() << " post: " << req.is_post() <<std::endl;

	Json j = req.post();
	std::cout <<"body: " << j.str() << std::endl;
    std::ofstream o(JSONPATH);
    o << std::setw(4) << j << std::endl;
    std::cout << "-------------------getData--------------------" << std::endl;
	return resp.html("hello, I have reveived");
};