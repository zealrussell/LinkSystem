#pragma onece

#include <web/Controller.h>
#include "Link22/Link22Center.h"

using namespace yazi::web;

namespace yazi {
namespace app {

class Link22Controller : public Controller
{
public:
    void encode(const Request & req, Response & resp);
    void decode(const Request & req, Response & resp);
private:
    Link22Center link22Center;
};

}
}