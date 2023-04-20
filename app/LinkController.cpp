#include <app/LinkController.h>

using namespace yazi::app;

REGISTER_CLASS(LinkController);
REGISTER_CLASS_METHOD(LinkController, link11_encode, void, const Request &, Response &);
REGISTER_CLASS_METHOD(LinkController, link11_decode, void, const Request &, Response &);
REGISTER_CLASS_METHOD(LinkController, link16_encode, void, const Request &, Response &);
REGISTER_CLASS_METHOD(LinkController, link16_decode, void, const Request &, Response &);
REGISTER_CLASS_METHOD(LinkController, link22_encode, void, const Request &, Response &);
REGISTER_CLASS_METHOD(LinkController, link22_decode, void, const Request &, Response &);



void yazi::app::LinkController::link11_encode(const Request & req, Response & resp)
{
    Json link11Json;
    return resp.json(link11Json.str());
}

void yazi::app::LinkController::link11_decode(const Request & req, Response & resp)
{
    Json link11Json;
    return resp.json(link11Json.str());
}

void yazi::app::LinkController::link16_encode(const Request & req, Response & resp)
{
    Json link16Json;
    return resp.json(link16Json.str());
}

void yazi::app::LinkController::link16_decode(const Request & req, Response & resp)
{
    Json link16Json;
    return resp.json(link16Json.str());
}


void yazi::app::LinkController::link22_encode(const Request & req, Response & resp)
{
    Json link22Json = link22Center.encoder_Link22("zeal",0 ,2, 3);
    return resp.json(link22Json.str());
}

void yazi::app::LinkController::link22_decode(const Request & req, Response & resp)
{
    Json link22Json;
    return resp.json(link22Json.str());
}
