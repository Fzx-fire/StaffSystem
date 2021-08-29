#pragma once   //��ֹͷ�ļ��ظ�����
#include<iostream>
#include<fstream>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

#define FILENAME "empFile.txt"

using namespace std;

class WorkManager{
public:

    int m_EmpNum; //��¼�ļ��е�����
    Worker ** m_EmpArray;

    //��־�ļ��Ƿ�Ϊ��
    bool m_FileIsEmpty;

    WorkManager();

    //��ʾ�˵�
    void ShowMenu();
    //�˳�����
    void exitSystem();
    //���ְ��
    void Add_Emp();
    //�����ļ�
    void save();
    //ͳ������
    int get_EmpNum();
    //��ʼ������
    void init_Emp();
    //��ʾְ��
    void show_Emp();
    //ɾ��ְ��
    void Del_Emp();
    //�ж�ְ���Ƿ����
    int isExist(int id);
    //�޸�ְ��
    void Mod_Emp();
    //����ְ��
    void Find_Emp();
    //����ְ��
    void Sort_Emp();
    //����ļ�
    void Clean_File();

    ~WorkManager();
};
