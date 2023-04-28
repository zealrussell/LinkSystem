#include <iostream>
using namespace std;

#include <web/Server.h>
using namespace yazi::web;

#include <app/controllers.h>

int main()
{
    Server *server = Singleton<Server>::instance();
    server->listen("", 9023);
    server->start();
    return 0;
}
