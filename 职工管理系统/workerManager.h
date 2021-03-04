#pragma once
#include <iostream>
#include "worker.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"
#include <fstream>
#define FILENAME "empFile.txt"

using namespace std;

class WorkerManager {
public:
	WorkerManager();

	~WorkerManager();

	//显示菜单
	void showMenu();

	//添加职工
	void addEmp();

	//保存文件
	void save();

	//统计人数
	int getNum();

	//根据文件初始化
	void initEmp();

	//显示职工
	void showEmp();

	//查询职工是否存在，存在返回数组下标，不存在返回-1
	int isExist(int id);

	//修改员工
	void modEmp();

	//查找职工
	void findEmp();

	//排序
	void sortEmp();

	//删除职工
	void delEmp();

	//退出系统
	void exitSystem();

	//记录职工人数
	int m_EmpNum;

	//判断文件是否为空标志位
	bool m_FileIsEmpty;

	//清空文件
	void cleanFile();

	//职工数组指针
	Worker** m_EmpArray;

	
};
