#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;


int main() {
	//���Դ���
	/*Worker* w = new Employee(1, "����", 1);
	w->showInfo();
	delete w;*/


	WorkerManager wm;
	int choice = 0;
	while (true) {
		wm.showMenu();
		cout << "���������ѡ��" << endl;
		cin >> choice;

		switch (choice) {
		default: 
			system("cls");    //��������
			break;
		case 0:   //�˳�ϵͳ
			wm.exitSystem();
		case 1:   //1. ����ְ����Ϣ
			wm.addEmp();
			break;
		case 2:   //2. ��ʾְ����Ϣ
			wm.showEmp();
			break;
		case 3:   //3. ɾ����ְְ��
			wm.delEmp();
			break;
		case 4:   //4. �޸�ְ����Ϣ
			wm.modEmp();
			break;
		case 5:   //5. ����ְ����Ϣ
			wm.findEmp();
			break;
		case 6:   //6. ���ձ������
			wm.sortEmp();
			break;
		case 7:   //7. ��������ĵ�
			wm.cleanFile();
			break;
		}
	}
	


	return 0;
}

