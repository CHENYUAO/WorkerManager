#include "workerManager.h"

WorkerManager::WorkerManager() {


	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//�ļ�������
	if (!ifs.is_open()) {
		//cout << "�ļ������ڣ�" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}


	//�ļ����ڵ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "�ļ�Ϊ�գ�" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	
	//�ļ�������������
	this->m_EmpNum = this->getNum();
	this->m_FileIsEmpty = false;
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->initEmp();
	
}

void WorkerManager::showMenu() {


	cout << "************************************************" << endl;
	cout << "************** ��ӭʹ��ְ������ϵͳ ************" << endl;
	cout << "**************** 0. �˳�������� ***************" << endl;
	cout << "**************** 1. ����ְ����Ϣ ***************" << endl;
	cout << "**************** 2. ��ʾְ����Ϣ ***************" << endl;
	cout << "**************** 3. ɾ����ְְ�� ***************" << endl;
	cout << "**************** 4. �޸�ְ����Ϣ ***************" << endl;
	cout << "**************** 5. ����ְ����Ϣ ***************" << endl;
	cout << "**************** 6. ���ձ������ ***************" << endl;
	cout << "**************** 7. ��������ĵ� ***************" << endl;
	cout << "************************************************" << endl;
	cout << endl;


}

void WorkerManager::showEmp() {


	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��ļ�Ϊ�գ�" << endl;
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


	cout << "��ѡ��Ҫɾ����ְ����ţ�" << endl;
	int id;
	cin >> id;


	int index = this->isExist(id);
	if (index == -1) {
		cout << "��Ա�������ڣ�" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		cout << "������Ҫ�޸ĵ�Ա���ı��" << endl;
		int id;
		cin >> id;
		int index = this->isExist(id);
		if (index == -1) {
			cout << "��Ա�������ڣ�" << endl;
			return;
		}
		else {
			delete this->m_EmpArray[index];

			int newId;
			string newName;
			int newDid;
			cout << "�������޸ĺ��Ա����ţ�" << endl;
			cin >> newId;
			cout << "�������޸ĺ��Ա��������" << endl;
			cin >> newName;
			cout << "��ѡ���ְ���ĸ�λ" << endl;
			cout << "1. ��ְͨ��" << endl;
			cout << "2. ����" << endl;
			cout << "3. �ϰ�" << endl;
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
			

			cout << "�޸ĳɹ���" << endl;
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
	cout << "���������ְ����������" << endl;
	int inNum = 0;
	cin >> inNum;


	if (inNum > 0 && inNum < 100) {
		//���
		//������ӿռ�Ĵ�С
		int newSize = this->m_EmpNum + inNum; //�����¿ռ��С
		Worker** newSpace = new Worker* [newSize];
		//����ԭ���ݵ��¿ռ�
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//���������
		for (int i = 0; i < inNum; i++) {
			int id;
			string name;
			int dSelect;

			cout << "�������" << i + 1 << "����ְ���ı��" << endl;
			cin >> id;
			if (this->isExist(id) != -1) {
				cout << "�ñ���Ѵ��ڣ�" << endl;
				i--;
				continue;
			}

			cout << "�������" << i + 1 << "����ְ��������" << endl;
			cin >> name;
			cout << "��ѡ�����ְ���ĸ�λ" << endl;
			cout << "1. ��ְͨ��" << endl;
			cout << "2. ����" << endl;
			cout << "3. �ϰ�" << endl;
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
			//ָ�뱣�浽������
			newSpace[this->m_EmpNum + i] = worker;
		}

		//�ͷ�ԭ�пռ䣬ָ���¿ռ�
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		
		//��������
		this->m_EmpNum = newSize;
		cout << "�ɹ����" << inNum << "����ְ��" << endl;
		this->m_FileIsEmpty = false;
		//���浽�ļ���
		this->save();

	}
	else {
		cout << "������������" << endl;
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
		cout << "�ļ������ڻ�������Ϊ�գ�" << endl;
	}
	else {


		int fSelect;
		cout << "1. ����Ų���" << endl;
		cout << "2. ����������" << endl;
		cin >> fSelect;

		if (fSelect == 1) {
			int id;
			cout <<"������Ҫ���ҵ�Ա����ţ�" << endl;
			cin >> id;
			int index = this->isExist(id);
			if (index != -1) {
				cout << "���ҳɹ�" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else {
				cout << "���޴��ˣ�" << endl;
			}
		}
		else if (fSelect == 2) {

			string name;
			cout <<"������Ҫ���ҵ�Ա��������" <<endl;
			cin >> name;


			bool found = false;
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray[i]->m_Name == name) {
					found = true;
					cout << "���ҳɹ�" << endl;
					this->m_EmpArray[i]->showInfo();
				}
			}


			if (!found) {
				cout << "���޴��ˣ�" <<endl;
			}

		}
		else {
			cout << "�������" << endl;
		}
	}

	system("pause");
	system("cls");

}

void WorkerManager::sortEmp() {


	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�������Ϊ�գ�" << endl;
	}
	else {
		int mod;
		cout << "1. ��ְ������������" << endl;
		cout << "2. ��ְ���Ž�������" << endl;
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
		
		cout << "����ɹ���" << endl;
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


	cout << "ȷ����գ�[y/n] (Ĭ��Ϊn)" <<endl;
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

	cout << "��ճɹ���" << endl;

	system("pause");
	system("cls");
}

void WorkerManager::exitSystem() {
	cout << "��ӭ�´�ʹ�ã�" << endl;
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
