#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "SerialPort.h"
#include <conio.h>
//#include <thread>
#include "windows.h"
#include "Comm_jy.h"
#include "FindColor_jy.h"
class Arduino_jy {
private:
	char *port_name;

	//String for incoming data
	char incomingData[MAX_DATA_LENGTH];
	int input;
	char tmp[3];
	int flag;
	char tmpport[13];
	
	string color;
public:
	FindColor_jy MyColor;
	Arduino_jy(int inputport);
	Arduino_jy(int inputport, string inputcolor);
	~Arduino_jy();
	void Arduino_jy_st();
	char getch_jy;
	void Arduino_connet();
	Comm_jy drone_flag;
	//void for_datination(FindColor_jy myObj, cv::Point Dastination);
	//thread t1() {
	//return thread([=] {
	//do_comm();
	//});
	//}
};