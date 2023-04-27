#pragma once

#include <web/Controller.h>

#include "Link22/Link22Center.h"
#include "Link16/Link16Center.h"
#include "Link11/Link11Center.h"

using namespace yazi::web;

namespace yazi
{
    namespace app
    {

        // link数据链
        class LinkController : public Controller
        {
        public:
            void link11_encode(const Request &req, Response &resp);
            void link11_decode(const Request &req, Response &resp);

            void link16_encode(const Request &req, Response &resp);
            void link16_decode(const Request &req, Response &resp);

            void link22_encode(const Request &req, Response &resp);
            void link22_decode(const Request &req, Response &resp);

            void from11to16(const Request &req, Response &resp);
            void from16to11(const Request &req, Response &resp);
            void from11to22(const Request &req, Response &resp);
            void from22to11(const Request &req, Response &resp);
            void from16to22(const Request &req, Response &resp);
            void from22to16(const Request &req, Response &resp);

        private:
            Link11Center link11Center;
            Link16Center link16Center;
            Link22Center link22Center;
        };

    }
}
