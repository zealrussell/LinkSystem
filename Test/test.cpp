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
#define TEST_WRITE_JSON_FILE
#ifdef TEST_ASSEMBLE_JSON
int main()
{
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
#endif // TEST_ASSEMBLE_JSON

#ifdef TEST_FILE
int main()
{
    std::ofstream out(R"(./LinkSystem/TestData.txt)", std::ios_base::app);
    if (out.is_open())
    {
        std::cout << "file open" << std::endl;
    }
    string str = "file write......";
    out << "hello zeal";
    out.write(str.c_str(), str.length());
    out.close();
    return 0;
}
#endif

#ifdef TEST_WRITE_JSON_FILE
int main()
{
    Json json;
    json["link16"]["encode_str"] = "010110101010110001001001011010111010101";
    json["link16"]["decode_str"] = "101101100101000110000011111010101010110";

    json["link22"]["encode_str"] = "101100100100110100111101010100100101010";
    json["link22"]["decode_str"] = "001010110101101001010101001010100110101";

    // Write json
    std::ofstream out(R"(./TestData.txt)", std::ios_base::app);
    if (out.is_open())
    {
        std::cout << "file open" << std::endl;
    }
    string str = "file write......";
    out.write(json.str().c_str(), json.str().length());
    out.close();

    // Read Json
    std::ifstream fin(R"(./TestData.txt)", std::ios_base::in);
    if (fin.is_open())
    {
        std::cout << "file open" << std::endl;
    }
    string buffer;
    while (fin >> buffer)
    {
        std::cout << buffer << std::endl;
    }
    fin.close();

    Json read_json;
    read_json.parse(buffer);
    std::cout << "read_json = " << read_json << std::endl;

    Json link16 = read_json.get("link16");
    Json link22 = read_json.get("link22");
    std::cout << "link16 = " << link16 << std::endl;
    std::cout << "link22 = " << link22 << std::endl;

    string link16_encode_str = link16.get("encode_str");
    string link16_decode_str = link16.get("decode_str");
    std::cout << "link16_encode_str = " << link16_encode_str << std::endl;
    std::cout << "link16_decode_str = " << link16_decode_str << std::endl;

    string link22_encode_str = link22.get("encode_str");
    string link22_decode_str = link22.get("decode_str");
    std::cout << "link22_encode_str = " << link22_encode_str << std::endl;
    std::cout << "link22_decode_str = " << link22_decode_str << std::endl;
    return 0;
}
#endif