#include "workerManager.h"

WorkerManager::WorkerManager() {


	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在
	if (!ifs.is_open()) {
		//cout << "文件不存在！" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}


	//文件存在但为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "文件为空！" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	
	//文件存在且有内容
	this->m_EmpNum = this->getNum();
	this->m_FileIsEmpty = false;
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->initEmp();
	
}

void WorkerManager::showMenu() {


	cout << "************************************************" << endl;
	cout << "************** 欢迎使用职工管理系统 ************" << endl;
	cout << "**************** 0. 退出管理程序 ***************" << endl;
	cout << "**************** 1. 增加职工信息 ***************" << endl;
	cout << "**************** 2. 显示职工信息 ***************" << endl;
	cout << "**************** 3. 删除离职职工 ***************" << endl;
	cout << "**************** 4. 修改职工信息 ***************" << endl;
	cout << "**************** 5. 查找职工信息 ***************" << endl;
	cout << "**************** 6. 按照编号排序 ***************" << endl;
	cout << "**************** 7. 清空所有文档 ***************" << endl;
	cout << "************************************************" << endl;
	cout << endl;


}

void WorkerManager::showEmp() {


	if (this->m_FileIsEmpty) {
		cout << "文件不存在或文件为空！" << endl;
	}
	else {
		for (int i = 0; i < this->m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

int WorkerManager::isExist(int id){


	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			return i;
		}
	}
	return -1;


}

void WorkerManager::delEmp() {


	cout << "请选择要删除的职工编号：" << endl;
	int id;
	cin >> id;


	int index = this->isExist(id);
	if (index == -1) {
		cout << "该员工不存在！" << endl;
		return;
	}
	else {
		for (int i = index; i < this->m_EmpNum - 1; i++) {
			this->m_EmpArray[i] = this->m_EmpArray[i + 1];
		}
		this->m_EmpNum--;
	}
	this->save();


	system("pause");
	system("cls");


}

void WorkerManager::modEmp() {


	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		cout << "请输入要修改的员工的编号" << endl;
		int id;
		cin >> id;
		int index = this->isExist(id);
		if (index == -1) {
			cout << "该员工不存在！" << endl;
			return;
		}
		else {
			delete this->m_EmpArray[index];

			int newId;
			string newName;
			int newDid;
			cout << "请输入修改后的员工编号：" << endl;
			cin >> newId;
			cout << "请输入修改后的员工姓名：" << endl;
			cin >> newName;
			cout << "请选择该职工的岗位" << endl;
			cout << "1. 普通职工" << endl;
			cout << "2. 经理" << endl;
			cout << "3. 老板" << endl;
			cin >> newDid;


			Worker* worker = NULL;
			switch (newDid) {
			case 1:
				worker = new Employee(newId, newName, 1);
			case 2:
				worker = new Manager(newId, newName, 2);
			case 3:
				worker = new Boss(newId, newName, 3);
			default:
				break;
			}
			this->m_EmpArray[index] = worker;
			

			cout << "修改成功！" << endl;
			this->save();
		}
	}

	system("pause");
	system("cls");


}

void WorkerManager::initEmp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		Worker* worker = NULL;
		if (did == 1) {
			worker = new Employee(id, name, 1);
		}
		else if (did == 2) {
			worker = new Manager(id, name, 2);
		}
		else
			worker = new Boss(id, name, 3);
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
	
}

void WorkerManager::addEmp() {
	cout << "请输入添加职工的数量：" << endl;
	int inNum = 0;
	cin >> inNum;


	if (inNum > 0 && inNum < 100) {
		//添加
		//计算添加空间的大小
		int newSize = this->m_EmpNum + inNum; //计算新空间大小
		Worker** newSpace = new Worker* [newSize];
		//拷贝原数据到新空间
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//添加新数据
		for (int i = 0; i < inNum; i++) {
			int id;
			string name;
			int dSelect;

			cout << "请输入第" << i + 1 << "个新职工的编号" << endl;
			cin >> id;
			if (this->isExist(id) != -1) {
				cout << "该编号已存在！" << endl;
				i--;
				continue;
			}

			cout << "请输入第" << i + 1 << "个新职工的姓名" << endl;
			cin >> name;
			cout << "请选择该新职工的岗位" << endl;
			cout << "1. 普通职工" << endl;
			cout << "2. 经理" << endl;
			cout << "3. 老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//指针保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有空间，指向新空间
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		
		//更新人数
		this->m_EmpNum = newSize;
		cout << "成功添加" << inNum << "名新职工" << endl;
		this->m_FileIsEmpty = false;
		//保存到文件中
		this->save();

	}
	else {
		cout << "输入数量错误！" << endl;
	}
	system("pause");
	system("cls");
}

int WorkerManager::getNum() {


	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int num = 0;
	int id;
	string name;
	int did;


	while (ifs >> id && ifs >> name && ifs >> did) {
		num++;
	}
	ifs.close();

	return num;
}

void WorkerManager::findEmp() {


	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者内容为空！" << endl;
	}
	else {


		int fSelect;
		cout << "1. 按编号查找" << endl;
		cout << "2. 按姓名查找" << endl;
		cin >> fSelect;

		if (fSelect == 1) {
			int id;
			cout <<"请输入要查找的员工编号：" << endl;
			cin >> id;
			int index = this->isExist(id);
			if (index != -1) {
				cout << "查找成功" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else {
				cout << "查无此人！" << endl;
			}
		}
		else if (fSelect == 2) {

			string name;
			cout <<"请输入要查找的员工姓名：" <<endl;
			cin >> name;


			bool found = false;
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray[i]->m_Name == name) {
					found = true;
					cout << "查找成功" << endl;
					this->m_EmpArray[i]->showInfo();
				}
			}


			if (!found) {
				cout << "查无此人！" <<endl;
			}

		}
		else {
			cout << "输入错误！" << endl;
		}
	}

	system("pause");
	system("cls");

}

void WorkerManager::sortEmp() {


	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者内容为空！" << endl;
	}
	else {
		int mod;
		cout << "1. 按职工号升序排序" << endl;
		cout << "2. 按职工号降序排序" << endl;
		cin >> mod;
		

		for (int i = 0; i < this->m_EmpNum; i++) {
			int m = i;
			for (int j = i + 1; j < this->m_EmpNum; j++) {
				if (mod == 1) {
					if (this->m_EmpArray[i]->m_Id > this->m_EmpArray[j]->m_Id) {
						m = j;
					}
				}
				else {
					if (this->m_EmpArray[i]->m_Id < this->m_EmpArray[j]->m_Id) {
						m = j;
					}
				}
			}

			if (i != m) {
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[m];
				this->m_EmpArray[m] = temp;
			}

		}
		
		cout << "排序成功！" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::save() {

	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << "  "
			<< this->m_EmpArray[i]->m_Name << "  "
			<< this->m_EmpArray[i]->m_DeptId << endl;

	}

	ofs.close();
}

void WorkerManager::cleanFile() {


	cout << "确认清空？[y/n] (默认为n)" <<endl;
	char confirm;
	cin >> confirm;
	if (confirm == 'y') {
		ofstream ofs(FILENAME,ios::trunc);
		ofs.close();


		if(this->m_EmpArray != NULL){
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray[i] != NULL) {
					delete this->m_EmpArray[i];
				}
			}

			delete[] this->m_EmpArray;
			this->m_EmpNum = 0;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
	}

	cout << "清空成功！" << endl;

	system("pause");
	system("cls");
}

void WorkerManager::exitSystem() {
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

WorkerManager::~WorkerManager() {
	if (this->m_EmpArray != NULL) {
		this->m_EmpNum = 0;
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
	}
}
