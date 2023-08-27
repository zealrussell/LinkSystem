#include "Variable.h"
#include <json/Json.h>

// 非const变量默认为extern

// 无人机数据: 敌军、友军、自身
UAV uav_data[4] = {
    {"enemy", -0.020000, -0.030000, 0.070000, 0, 0.007550, 0.044475, 1.869000},
    {"allies", -0.040000, 0, 0.070000, 0, 0.037748, 6.982605, 1.903000},
    {"self", -0.010000, 0, 0.06, 0, -0.015099, -6.960367, 1.865000}
};  
extern const std::string UAV_DATA_JSON_PATH = "./data/origin_data.json";
yazi::json::Json planeJson;