#pragma once
#include <iostream>
#include "worker.h"
#include <string>
using namespace std;

class Boss : public Worker {
public:
	Boss(int id, string name, int did);
	//��ʾ������Ϣ
	virtual void showInfo();
	//��ȡ��λ����
	virtual string getDeptName();
};