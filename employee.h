#pragma once
#include<iostream>
#include"worker.h"

using namespace std;

class Employee : public Worker{
public:
    Employee(int id,string name,int deptid);

     void showInfo();

     string getDeptName();
};
