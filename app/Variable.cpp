#include "Variable.h"
#include <json/Json.h>

// 非const变量默认为extern

UAV uav_data[4];
extern const std::string UAV_DATA_JSON_PATH = "./data/origin_data.json";
yazi::json::Json planeJson;