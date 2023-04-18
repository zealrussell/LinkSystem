#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <time.h>
#include <list>
#include <algorithm>
#include <json/Json.h>

using namespace yazi::json;

// michael@phonon:~/C++Space/yazi-web$ g++ -g -Wall -ldl -std=c++11 -I. -c Test/test.cpp -o Test/test.o
// g++ -o Test/test Test/test.o json/Json.o json/Parser.o -g -Wall -ldl -fPIC -std=c++11 -I.
int main()
{
    // ofstream out(R"(./LinkSystem/data.txt)", ios_base::app);
    // if (out.is_open()) {
    //    cout << "file open" << endl;
    // }
    // string str = "file write......";
    // out << "hello zeal";
    // out.write(str.c_str(), str.length());
    // out.close();
    // return 0;

    // Format Json
    Json json;
    std::list<Json> array;
    json["linkType"] = "link16";
    json["headerWord"] = 0;
    json["initialWord"] = Json("json_array");
    json["extendWord"] = Json("json_array");
    json["continueWord"] = Json("json_array");
    json["encryptedMsg"] = 0;
    json["dataTime"] = 0;

    time_t timep;

    Json json0;
    json0["header1"] = "111";
    json0["header2"] = "222";
    json0["header3"] = "333";
    json["headerWord"] = json0;

    Json json1;
    json1["param1"] = 0;
    json1["param2"] = "222";
    json1["param3"] = "333";
    json["initialWord"].append(json1);

    Json json2;
    json2["param4"] = "111";
    json2["param5"] = 0;
    json2["param6"] = "333";
    json["extendWord"].append(json2);

    Json json3;

    json3["param7"] = "111";
    json3["param8"] = "222";
    json3["param9"] = 0;
    json["continueWord"].append(json3);

    time(&timep);
    json["dataTime"] = ctime(&timep);
    json["encryptedMsg"] = "010110101010110001001001011010111010101";
    std::cout << json << std::endl;

    Json linkType = json.get("linkType");
    std::cout << "linkType = " << linkType << std::endl;
    Json headerWord = json.get("headerWord");
    std::cout << "headerWord = " << headerWord << std::endl;
    Json initialWord = json.get("initialWord");
    std::cout << "initialWord = " << initialWord << std::endl;
    Json extendWord = json.get("extendWord");
    std::cout << "extendWord = " << extendWord << std::endl;
    Json continueWord = json.get("continueWord");
    std::cout << "continueWord = " << continueWord << std::endl;
    Json encryptedMsg = json.get("encryptedMsg");
    std::cout << "encryptedMsg = " << encryptedMsg << std::endl;
    Json dataTime = json.get("dataTime");
    std::cout << "dataTime = " << dataTime << std::endl;
}