#include <app/LinkController.h>
#include "./Variable.h"

using namespace yazi::app;

extern UAV uav_data[4];
extern Json planeJson;

REGISTER_CLASS(LinkController);

// 编码解码
REGISTER_CLASS_METHOD(LinkController, link11_encode, void, const Request &, Response &);
REGISTER_CLASS_METHOD(LinkController, link11_decode, void, const Request &, Response &);
REGISTER_CLASS_METHOD(LinkController, link16_encode, void, const Request &, Response &);
REGISTER_CLASS_METHOD(LinkController, link16_decode, void, const Request &, Response &);
REGISTER_CLASS_METHOD(LinkController, link22_encode, void, const Request &, Response &);
REGISTER_CLASS_METHOD(LinkController, link22_decode, void, const Request &, Response &);

// 转换
REGISTER_CLASS_METHOD(LinkController, from11to16, void, const Request &, Response &);
REGISTER_CLASS_METHOD(LinkController, from11to22, void, const Request &, Response &);
REGISTER_CLASS_METHOD(LinkController, from16to11, void, const Request &, Response &);
REGISTER_CLASS_METHOD(LinkController, from16to22, void, const Request &, Response &);
REGISTER_CLASS_METHOD(LinkController, from22to11, void, const Request &, Response &);
REGISTER_CLASS_METHOD(LinkController, from22to16, void, const Request &, Response &);

void yazi::app::LinkController::link11_encode(const Request &req, Response &resp)
{
	std::string msg;  // = req.get("msg");
	int n = std::stoi(req.get("n"));
	int type = 0;
	// 文本消息
	if (n == 1223) {
		type = 1;
		msg = "文本消息";
	// 测试消息
	} else if (n == 11) {
		type = 0;
		msg = "link11 test";
	} else if ( n == 12) {
		type = 0;
		msg = "国家";
	} else if (n == 2) {
		// 位置报文
		type = 1;
		msg = "x=" + std::to_string(uav_data[0].x) 
				+ ";y=" + std::to_string(uav_data[0].y) 
				+ ";z=" + std::to_string(uav_data[0].z);
	} else if (n == 82) {
		type = 1;
		msg = "messageType=country";
	} else {
		msg = "";
	}
	Json link11Json = link11Center.encoder_Link11(msg, 1, n);
	resp.json(link11Json.str());
	return;
}

void yazi::app::LinkController::link11_decode(const Request &req, Response &resp)
{
	int n = 0;
	int type = 0;
	std::string msg;
	Json link11Json = link11Center.decoder_Link11(msg, type, n);
	resp.json(link11Json.str());
	return;
}

void yazi::app::LinkController::link16_encode(const Request &req, Response &resp)
{
	std::string msg; // = req.get("msg");
	int n = std::stoi(req.get("n"));
	int m = std::stoi(req.get("m"));
	
	if (n == 28 && m == 20) {
		msg = "This is a text message";
	} else if (n == 1 && m == 1) {
		msg = "link16 test";
	} else if (n == 28 && m == 4) {
		msg = "messageType=country;country=UK1";
	} else if (n == 31 && m == 1) {
		// 秘钥滚动
		msg = "12554343";
	} else if (n == 15 && m == 0) {
		// 威胁告警
		msg = "warning!!!";
	} else if (n == 3 && m == 2) {
		// 空中航迹
		msg = "x=" + std::to_string(uav_data[0].x) 
				+ ";y=" + std::to_string(uav_data[0].y) 
				+ ";z=" + std::to_string(uav_data[0].z);
	}	else {
		msg = "";
	}
	Json link16Json = link16Center.encoder_Link16(msg, n, m);
	resp.json(link16Json.str());
	return;
}

void yazi::app::LinkController::link16_decode(const Request &req, Response &resp)
{
	int n = 0, m = 0;
	std::string msg;
	Json link16Json = link16Center.decoder_Link16(msg, n, m);
	resp.json(link16Json.str());
	return;
}

void yazi::app::LinkController::link22_encode(const Request &req, Response &resp)
{
	std::string msg; // = req.get("msg");
	int n = std::stoi(req.get("n"));
	int m = std::stoi(req.get("m"));
	int p = std::stoi(req.get("p"));
	if (n == 2 && m == -1 && p == -1) {
		// 空中航迹位置
		msg = "x=" + std::to_string(uav_data[0].x) 
				+ ";y=" + std::to_string(uav_data[0].y) 
				+ ";z=" + std::to_string(uav_data[0].z);
	} else if (n == 0 && m == 7 && p == 10) {
		// 秘钥滚动
		msg = "";
	} else if (n == 1 && m == 0 && p == 0) {
		// 敌我识别
		msg = "enemy conming";
	} else if (n == 3 && m == 2 && p == -1) {
		msg = "x=" + std::to_string(uav_data[0].x) 
				+ ";y=" + std::to_string(uav_data[0].y) 
				+ ";z=" + std::to_string(uav_data[0].z)
				+ ";speed=" + std::to_string(uav_data[0].vx);
	}
	Json link22Json = link22Center.encoder_Link22(msg, n, m, p);
	resp.json(link22Json.str());
	return;
}

void yazi::app::LinkController::link22_decode(const Request &req, Response &resp)
{
	int n, m, p;
	std::string msg;

	Json link22Json = link22Center.decoder_Link22(msg, n, m, p);
	resp.json(link22Json.str());
	return;
}

// --------------------------------------- 转换 ---------------------------------------------------------

//
void yazi::app::LinkController::from11to16(const Request &req, Response &resp)
{
	int n_11;
	int type_11;
	std::string msg_11;
	Json decodeJson;

	//TODO:添加默认值
	int n_16 = -1, m_16 = -1;
	std::string msg_16 = "";
	Json encodeJson;

	Json resultJson;

	decodeJson = link11Center.decoder_Link11(msg_11, type_11, n_11);
	if (n_11 == 1223)
	{
		// 1. 直译：m.12.23 文本消息 -> j28.20 文本消息
		n_16 = 28;
		m_16 = 20;
		msg_16 = msg_11;
	}
	else if (n_11 == 0)
	{
		// 2. 转译 M.0测试 -》 J0.1 测试报文
		n_16 = 0;
		m_16 = 1;
		msg_16 = "link16 test";
	}
	else if (n_11 == 12)
	{
		// 3. 增译: M.12国家报文 -》 J28。7 英国1
		n_16 = 28;
		m_16 = 7;
		msg_16 = msg_11 + ";country=uk1";
	}
	encodeJson = link16Center.encoder_Link16(msg_16, n_16, m_16);

	resultJson["encode"] = encodeJson;
	resultJson["decode"] = decodeJson;
	resp.json(resultJson.str());
	return;
}

void yazi::app::LinkController::from16to11(const Request &req, Response &resp)
{
	int n_16, m_16;
	std::string msg_16;
	Json decodeJson;
	
	//TODO:添加默认值
	int n_11 = -1;
	std::string msg_11;
	Json encodeJson;

	Json resultJson;

	decodeJson = link16Center.decoder_Link16(msg_16, n_16, m_16);

	if (n_16 == 28 && m_16 == 20)
	{
		// 1. 直译： j28.20 文本消息 -》 m。12.23
		n_11 = 1223;
		msg_11 = msg_16;
	}
	else if (n_16 == 1 && m_16 == 1)
	{
		// 2. 转译: m.0 测试 -> j0.1 测试
		n_11 = 0;
		msg_11 = "link11 test";
	}
	else if (n_16 == 28 && m_16 == 4)
	{
		// 3. 删译: m28.4 英国1 =》 M.12国家报文
		n_11 = 12;
		msg_11 = msg_16.substr(0, msg_16.find_last_of(";"));
	}

	encodeJson = link11Center.encoder_Link11(msg_11, 1, n_11);

	resultJson["encode"] = encodeJson;
	resultJson["decode"] = decodeJson;
	resp.json(resultJson.str());
	return;
}

void yazi::app::LinkController::from11to22(const Request &req, Response &resp)
{
	int n_11;
	int type_11;
	std::string msg_11;
	Json decodeJson;

	//TODO:添加默认值
	int n_22 = -1, m_22 = -1, p_22 = -1;
	std::string msg_22 = "";
	Json encodeJson;

	Json resultJson;

	decodeJson = link11Center.decoder_Link11(msg_11, type_11, n_11);

	if (n_11 == 2)
	{
		// 1. 直译：M.2空中航迹位置 =》 F2 空中航迹位置
		n_22 = 2;
		m_22 = -1;
		p_22 = -1;
		msg_22 = msg_11;
	}
	else if (n_11 == 82)
	{
		// 2. 转译：M.2空中位置扩展报文 =》 F5.0
		n_22 = 1;
		m_22 = 2;
		p_22 = 3;
		msg_22 = msg_11;
	}
	else if (n_11 == 23)
	{
		n_22 = 1;
		m_22 = 1;
		p_22 = 1;
		msg_22 = "masdg";
	}

	encodeJson = link22Center.encoder_Link22(msg_22, n_22, m_22, p_22);

	resultJson["encode"] = encodeJson;
	resultJson["decode"] = decodeJson;
	resp.json(resultJson.str());
	return;
}

//todo:
void yazi::app::LinkController::from22to11(const Request &req, Response &resp)
{
	// link22 消息数据
	std::string msg_22, msg_11;
	int m_22, n_22, p_22;
	int n_11 = 0;

	Json encodeJson, decodeJson, resultJson;

	// 1. 从link22 数据中解码出 msg, m, n, p
	encodeJson = link22Center.decoder_Link22(msg_22, n_22, m_22, p_22);

	if (n_22 == 2 && m_22 == -1 && p_22 == -1)
	{
		// 1. 直译：F2空中航迹位置 =》 M.2空中航迹位置
		n_11 = 2;
		msg_11 = msg_22;
	}
	else if (n_22 == 3 && m_22 == 1 && p_22 == 1)
	{
		// 2. 转译：
		n_11 = 1;
		msg_11 = msg_22;
	}

	encodeJson = link11Center.encoder_Link11(msg_11, 1, n_11);

	resultJson["encode"] = encodeJson;
	resultJson["decode"] = decodeJson;
	resp.json(resultJson.str());
	return;
}

void yazi::app::LinkController::from16to22(const Request &req, Response &resp)
{
	string msg_16;
	int n_16, m_16;
	Json decodeJson;

	string msg_22;
	int n_22 = 0, m_22 = 0, p_22 = 0;
	Json encodeJson;

	Json resultJson;

	decodeJson = link16Center.decoder_Link16(msg_16, n_16, m_16);
	// 1.直译：J31.11 =》 F00.7-10秘钥滚动
	if (n_16 == 31 && m_16 == 11)
	{
		n_22 = 0;
		m_22 = 7;
		p_22 = 10;
		msg_22 = msg_16;
	}
	// 2.转译：J15.0威胁告警 =》 F01.0-0敌我识别
	else if (n_16 == 15 && m_16 == 0)
	{
		n_22 = 1;
		m_22 = 0;
		p_22 = 0;
		msg_22 = "enemy coming!";
	}
	// 3.增 译 : J3.2空中航迹 =》 F5-0空中航迹的航向与速度
	else if (n_16 == 3 && m_16 == 2)
	{
		n_22 = 5;
		m_22 = 0;
		p_22 = -1;
		msg_22 = msg_16 + ";speed=0";
	}
	encodeJson = link22Center.encoder_Link22(msg_22, n_22, m_22, p_22);

	resultJson["encode"] = encodeJson;
	resultJson["decode"] = decodeJson;
	resp.json(resultJson.str());
	return;
}

void yazi::app::LinkController::from22to16(const Request &req, Response &resp)
{
	// link22 消息数据
	std::string msg_22, msg_16;
	int m_22, n_22, p_22;
	int n_16 = 0, m_16 = 0;
	// 1. 从link22 数据中解码出 msg, m, n, p

	Json encodeJson, decodeJson, resultJson;

	decodeJson = link22Center.decoder_Link22(msg_22, n_22, m_22, p_22);
	// 2. 判断 进行那种转换
	printf("n ---- m ------ p:%d %d %d", n_22, m_22, p_22);
	// case 1: 直译
	// 选择 F00.7-10 密钥滚动消息 -》 J31.1空中更换秘钥
	if (n_22 == 0 && m_22 == 7 && p_22 == 10)
	{
		n_16 = 31;
		m_16 = 1;
		msg_16 = msg_22;
	}
	// case 2：转译：F01.0-0敌我识别 => J15.0威胁告警
	else if (n_22 == 1 && m_22 == 0 && p_22 == 0)
	{
		n_16 = 15;
		m_16 = 0;
		msg_16 = "warning!!!";
	}
	// case 3：删译
	else if (n_22 == 5 && m_22 == 0 && p_22 == -1)
	{
		// F5-0空中航迹的航向和速度 => J3.2空中航迹
		n_16 = 3;
		m_16 = 2;
		msg_16 = msg_22.substr(0, msg_22.find_last_of(";"));
	}

	encodeJson = link16Center.encoder_Link16(msg_16, n_16, m_16);

	resultJson["encode"] = encodeJson;
	resultJson["decode"] = decodeJson;
	resp.json(resultJson.str());
	return;
}

void yazi::app::LinkController::preparePlaneData() {
	if (planeJson.isNull()) return;
	for (int i = 0; i < planeJson.size(); i++) {
		std::string name = "uav" + i;
		Json uavJson = planeJson.get(name);

		uav_data[i].label = uavJson.get("label").asString();

		uav_data[i].x = uavJson.get("x").asDouble();
		uav_data[i].y = uavJson.get("y").asDouble();
		uav_data[i].z = uavJson.get("z").asDouble();

		uav_data[i].vx = uavJson.get("vx").asDouble();
		uav_data[i].vy = uavJson.get("vy").asDouble();
		uav_data[i].vz = uavJson.get("vz").asDouble();
	}
}
