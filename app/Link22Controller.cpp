#include <app/Link22Controller.h>

using namespace yazi::app;

REGISTER_CLASS(Link22Controller);
REGISTER_CLASS_METHOD(Link22Controller, encode, void, const Request &, Response &);
REGISTER_CLASS_METHOD(Link22Controller, decode, void, const Request &, Response &);

void Link22Controller::encode(const Request & req, Response & resp){
    string msg = "!!!This is a warning message.";
    Json json = link22Center.encoder_Link22("Hello, world! My name is Michael, I'm 22 years old.", 0 ,1, 0);
    std::cout << json << std::endl;
    resp.json(json.str());
};

void Link22Controller::decode(const Request & req, Response & resp){
    resp.json("decode");
}