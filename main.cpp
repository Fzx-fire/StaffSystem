#include <iostream>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

using namespace std;


int main()
{

    WorkManager wm;
    int choice=0;

    while(1){

        wm.ShowMenu();
        cout<<"����������ѡ��"<<endl;
        cin>>choice;

        switch(choice){
        case 0: //�˳�ϵͳ
            wm.exitSystem();
            break;
        case 1: //����ְ��
            wm.Add_Emp();
            break;
        case 2: //��ʾְ��
            wm.show_Emp();
            break;
        case 3: //ɾ��ְ��
            wm.Del_Emp();
            break;
        case 4: //�޸�ְ��
            wm.Mod_Emp();
            break;
        case 5: //����ְ��
            wm.Find_Emp();
            break;
        case 6: //����ְ��
            wm.Sort_Emp();
            break;
        case 7: //����ļ�
            wm.Clean_File();
            break;
        default:
            break;
        }

    }

    return 0;
}