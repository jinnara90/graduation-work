
#include "Arduino_jy.h"
#pragma warning(disable:4996)


Arduino_jy::Arduino_jy(int inputport)
{
	port_name = "\\\\.\\COM10" ;
	flag = 1;
	input = inputport;
}
Arduino_jy::Arduino_jy(int inputport, string inputcolor) {
	port_name = "\\\\.\\COM10";
	flag = 1;
	input = inputport;
	color = inputcolor;
	MyColor.set_color(inputcolor);
}
Arduino_jy::~Arduino_jy()
{
}


void Arduino_jy::Arduino_connet() {
	//int input;
	strcpy(tmpport, "\\\\.\\COM");
	//puts(tmpport);
	//cout << "input the port number\n";
	//cin >> input;
	//cout << "hmm\n";
	strcat(tmpport, itoa(input, tmp, 10)); //(��Ʈ��ȣ�� 2�ڸ� or 1�ڸ���)
	port_name = tmpport;
	//puts(tmpport);
	//cout << port_name << "����\n";
	drone_flag.Comm_set_jy(port_name, flag);
	drone_flag.connet();
}

//void Arduino_jy::for_datination(FindColor_jy myObj,cv::Point Dastination)
//{
//	myObj.CenterPoint.x;
//}

void Arduino_jy::Arduino_jy_st()
{
	//thread t(drone_flag.comst_read);
	//drone_flag.comst_read();
	//cout << "����\n";
	//while (1) {
	if (_kbhit()) {
		getch_jy = _getch();
		drone_flag.comst_write(getch_jy);
		//cout << getch_jy;
	}
}
//void Do_com::do_thread() {
//	thread t1(&Do_com::do_comm);
//	t1.detach();
//}

