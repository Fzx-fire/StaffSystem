#pragma once   //防止头文件重复包含
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

    int m_EmpNum; //记录文件中的人数
    Worker ** m_EmpArray;

    //标志文件是否为空
    bool m_FileIsEmpty;

    WorkManager();

    //显示菜单
    void ShowMenu();
    //退出程序
    void exitSystem();
    //添加职工
    void Add_Emp();
    //保存文件
    void save();
    //统计人数
    int get_EmpNum();
    //初始化数组
    void init_Emp();
    //显示职工
    void show_Emp();
    //删除职工
    void Del_Emp();
    //判断职工是否存在
    int isExist(int id);
    //修改职工
    void Mod_Emp();
    //查找职工
    void Find_Emp();
    //排序职工
    void Sort_Emp();
    //清空文件
    void Clean_File();

    ~WorkManager();
};
