#include "LinkCenter.h"

// 1. 从文本中读取数据
// 2. 进行转换
// 3. 写入到文本中

void LinkCenter::From22to16()
{
	// link22 消息数据
	std::string msg;
	int m, n, p;
	// 1. 从link22 数据中解码出 msg, m, n, p
	link22Center.decoder_Link22(msg, n, m, p);

	// 2. 判断 进行那种转换

	// case 1: 直译 
	// 选择 F00.7-10 密钥滚动消息作为
	if (m == 0 && n == 7 && p == 10) {

	}
	// case 2：转译
	else if (m == 2 && n == 2) {

	}
	// case 3：删译
	// F5-0 空中航迹的航向和速度
	else if (m == 4 && n == 1) {
		int m_16 = 3, n_16 = 2;
		std::string msg_16 = msg.substr(0, msg.find_first_of(":"));
		msg  = "sudu:10";
		// link16Center.encoder_Link16(m_16, n_16, msg_16);
	}

}

void LinkCenter::From16to22() {
	
	link16Center.encoder_Link16("hellozeal",1, 2);
	string msg;
	int n, m, p;
	link16Center.decoder_Link16(msg,n,m);
	cout << "11111111111111:  " << msg << endl << endl;
	//link22Center.encoder_Link22("hellozeal",0,1,2);
}
