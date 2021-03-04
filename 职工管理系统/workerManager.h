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

	//��ʾ�˵�
	void showMenu();

	//���ְ��
	void addEmp();

	//�����ļ�
	void save();

	//ͳ������
	int getNum();

	//�����ļ���ʼ��
	void initEmp();

	//��ʾְ��
	void showEmp();

	//��ѯְ���Ƿ���ڣ����ڷ��������±꣬�����ڷ���-1
	int isExist(int id);

	//�޸�Ա��
	void modEmp();

	//����ְ��
	void findEmp();

	//����
	void sortEmp();

	//ɾ��ְ��
	void delEmp();

	//�˳�ϵͳ
	void exitSystem();

	//��¼ְ������
	int m_EmpNum;

	//�ж��ļ��Ƿ�Ϊ�ձ�־λ
	bool m_FileIsEmpty;

	//����ļ�
	void cleanFile();

	//ְ������ָ��
	Worker** m_EmpArray;

	
};
