#include "Link22Variable.h"

std::map<std::string, std::string> CodetoName = {
	{"0_1_0", "电子战 方位字首"}, {"0_1_1", "电子战 定位字首"}, {"0_1_2", "电子战 位置"}, {"0_1_3", "电子战 放大"},
	{"0_2_0", "电子战 概率范围区字首"}, {"0_2_1", "电子战 概率范围区"}, 
	{"0_3_0", "电子战 发射机和电子对抗措施"}, {"0_3_1", "电子战 频率"}, {"0_3_2", "电子战 PD/PRF/扫描"}, {"0_3_3", "电子战 平台"},
	{"0_4_0", "电子战 协调字首"}, {"0_4_1", "电子战 相关"}, {"0_4_2", "电子战 协调 ECM"}, {"0_4_3", "电子战 协调发射控制"},
	{"0_7_0", "频率分配"}, {"0_7_1", "网络媒介参数"}, {"0_7_3", "网络管理命令"}, {"0_7_4", "带参数的网络管理命令"},
	{"0_7_5", "无线电静默命令"}, {"0_7_6", "网络状态"}, {"0_7_7", "任务领域子网的网络状态"}, {"0_7_10", "密钥滚动"}, 
	{"1_0_0", "敌我识别(IFF)"}, {"1_4_0", "声定向/声测距"}, {"1_4_1", "声定向/声测距模糊"}, 
	{"1_5_0", "声定向/声测距放大"}, {"1_5_1", "声定向/声测距传感器"}, {"1_5_2", "声定向/声测距频率"}, {"1_6_0", "基本命令"}, {"1_6_1", "命令拓展"},
	{"1_6_2", "空中协同"}, 
	{"2_0_0", "间接PLI放大"}, {"2_1_0", "PLI敌我识别"}, {"2_2_0", "空中PLI航向和速度"}, {"2_2_1", "空中PLI附加任务相关器"},
	{"2_3_0", "海上PLI航向和速度"}, {"2_3_1", "海上PLI任务相关器"}, {"2_4_0", "水下 PLI航向和速度"}, {"2_4_1", "水下PLI任务相关器"}, {"1_0_0", ""},
	{"2_5_0", "地面上点的PLI连续"}, {"2_5_1", "地面上点的PLI附加任务相关器"}, {"2_6_1", "地面轨迹 PLI任务相关器"}, {"2_7_0", "ANFT TBD"},
	{"3_0_0", "参考点字首"}, {"3_0_1", "参考点位置"},  {"3_0_2", "参考点航向和速度"},  {"3_0_3", "参考点中心线"}, {"3_0_4", "参考点分段"}, {"3_0_5", "参考点反潜"}, {"3_0_6", "参考点友方武器危险区"}, {"3_0_7", "参考点战区弹道导弹防御"},
	{"3_1_0", "紧急地点字首"}, {"3_1_11", "紧急地点位置"}, {"3_4_0", "ASW联系信息"}, {"3_4_1", "ASW 联系证实"},
	{"3_5_0", "地面轨迹/点的字首"}, {"3_5_1", "地面轨迹/点的位置"}, {"3_5_2", "地面非实时轨迹"}, {"3_5_31", "地面轨迹/点的IFF"}, 
	{"1_-1_0", "间接PLI位置"}, {"1_-1_1", "PLI位置"}, 
	{"4_-1_0", "水下航迹位置"}, {"4_-1_1", "水下航迹的航向和速度"},
	{"5_-1_0", "空中航迹的航向和速度"}, {"5_-1_1", "海上航迹的航向和速度"},
	{"2_-1_-1", "空中航迹位置"}, {"3_-1_-1", "海上航迹位置"}, {"6_-1_-1", "EW紧急情况"}, {"7_-1_-1", "备用(可能用于SWUTT)"}
};