#include "Variable.h"
#include <json/Json.h>

// 非const变量默认为extern

UAV uav_data[4];   // 无人机数据: 敌军、友军、自身
extern const std::string UAV_DATA_JSON_PATH = "./data/origin_data.json";
yazi::json::Json planeJson;