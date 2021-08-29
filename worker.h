#pragma once
#include<iostream>
#include<string>

using namespace std;

class Worker{
public:
    int m_Id;
    string m_Name;
    int m_DeptId;   //部门编号

    //显示个人信息
    virtual void showInfo()=0;
    //获取岗位名称
    virtual string getDeptName()=0;
};
