#ifndef COMM_JY_H
#define COMM_JY_H
#include "SerialPort.h"
#include <iostream>
#include <conio.h>
using namespace std;
class Comm_jy {

private:
	int flag; // 각 시리얼포트의 이름을 설정해준다(현재 플레그가 몇인지에 따라 1,2,3,4,5 (5는 전체명령)등등
	int throttle;
	int aileron;
	int elevator;
	int rudder;

	char *portname;

	int tg;
	int ag;
	int eg;
	int rg;
	SerialPort arduino;

public:
	Comm_jy();
	~Comm_jy();
	void Comm_set_jy(char *portname, int name);
	void connet();
	void comst_write(char orderst);
	void Comst_write_void();
};

#endif
#pragma once
