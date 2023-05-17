#pragma once

#include <web/Controller.h>
using namespace yazi::web;

namespace yazi
{
    namespace app
    {

        class PlaneController : public Controller
        {
        public:
            void getPlaneData(const Request &req, Response &resp);
            void getData(const Request &req, Response &resp);
        };
    }
}