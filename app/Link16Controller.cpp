#include <app/Link16Controller.h>
#include <Link16/interface.h>
using namespace yazi::app;

REGISTER_CLASS(Link16Controller);
REGISTER_CLASS_METHOD(Link16Controller, encode, void, const Request &, Response &);
REGISTER_CLASS_METHOD(Link16Controller, decode, void, const Request &, Response &);

void Link16Controller::encode(const Request &req, Response &resp)
{
    
    string msg = req.post("message");
    Json json = interface::encoder_Link16(15, 0, msg);
    std::cout << json << std::endl;
    resp.json(json.str());
}

void Link16Controller::decode(const Request &req, Response &resp)
{
    resp.html("decode");
}