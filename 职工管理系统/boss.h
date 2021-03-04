#pragma once
#include <iostream>
#include "worker.h"
#include <string>
using namespace std;

class Boss : public Worker {
public:
	Boss(int id, string name, int did);
	//显示个人信息
	virtual void showInfo();
	//获取岗位名称
	virtual string getDeptName();
};