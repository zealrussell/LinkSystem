#pragma once

#include <web/Controller.h>
using namespace yazi::web;

namespace yazi
{
    namespace app
    {

        class Link16Controller : public Controller
        {
        public:
            void encode(const Request &req, Response &resp);
            void decode(const Request &req, Response &resp);
        };

    }
}