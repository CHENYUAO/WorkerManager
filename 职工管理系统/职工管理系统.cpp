#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;


int main() {
	//测试代码
	/*Worker* w = new Employee(1, "张三", 1);
	w->showInfo();
	delete w;*/


	WorkerManager wm;
	int choice = 0;
	while (true) {
		wm.showMenu();
		cout << "请输入你的选择" << endl;
		cin >> choice;

		switch (choice) {
		default: 
			system("cls");    //清屏操作
			break;
		case 0:   //退出系统
			wm.exitSystem();
		case 1:   //1. 增加职工信息
			wm.addEmp();
			break;
		case 2:   //2. 显示职工信息
			wm.showEmp();
			break;
		case 3:   //3. 删除离职职工
			wm.delEmp();
			break;
		case 4:   //4. 修改职工信息
			wm.modEmp();
			break;
		case 5:   //5. 查找职工信息
			wm.findEmp();
			break;
		case 6:   //6. 按照编号排序
			wm.sortEmp();
			break;
		case 7:   //7. 清空所有文档
			wm.cleanFile();
			break;
		}
	}
	


	return 0;
}

