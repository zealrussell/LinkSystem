#include <app/PlaneController.h>
#include <Link16/tools.h>
using namespace yazi::app;

REGISTER_CLASS(PlaneController);
REGISTER_CLASS_METHOD(PlaneController, planes, void, const Request &, Response &);

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