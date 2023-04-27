#include <app/Link16Controller.h>
#include <Link16/Link16Center.h>
using namespace yazi::app;

REGISTER_CLASS(Link16Controller);
REGISTER_CLASS_METHOD(Link16Controller, encode, void, const Request &, Response &);
REGISTER_CLASS_METHOD(Link16Controller, decode, void, const Request &, Response &);

void Link16Controller::encode(const Request &req, Response &resp)
{
    string msg = req.post("message");
    Link16Center link16Center;
    Json json = link16Center.encoder_Link16(msg, 15, 0);
    std::cout << json << std::endl;
    resp.json(json.str());
}

void Link16Controller::decode(const Request &req, Response &resp)
{
    Link16Center link16Center;
    string msg;
    int n = 0, m = 0;
    Json json = link16Center.decoder_Link16(msg, n, m);
    resp.json(json.str());
}