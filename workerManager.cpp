#include"workerManager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

//类外实现
WorkManager::WorkManager(){
    ifstream ifs;
    ifs.open(FILENAME,ios::in);

    if(!ifs.is_open()){
        cout<<"文件不存在"<<endl;
        this->m_EmpNum=0;
        this->m_EmpArray=NULL;
        this->m_FileIsEmpty=true;

        ifs.close();
        return ;
    }

    //文件存在，数据为空
    char ch;
    ifs>>ch;
    if(ifs.eof()){
        cout<<"文件为空"<<endl;
        this->m_EmpNum=0;
        this->m_EmpArray=NULL;
        this->m_FileIsEmpty=true;

        ifs.close();
        return ;
    }

    //文件存在并且有数据
    int num=this->get_EmpNum();
    cout<<"职工人数为："<<num<<endl;
    this->m_EmpNum=num;
    this->m_EmpArray=new Worker*[this->m_EmpNum];
    init_Emp();
    this->m_FileIsEmpty=false;
    for(int i=0;i<this->m_EmpNum;i++){
        cout<<"职工编号："<<this->m_EmpArray[i]->m_Id
            <<"\t职工姓名："<<this->m_EmpArray[i]->m_Name
            <<"\t部门编号："<<this->m_EmpArray[i]->m_DeptId<<endl;
    }

}

WorkManager::~WorkManager(){
    if(this->m_EmpArray!=NULL){
        for(int i=0;i<this->m_EmpNum;i++){
                if(this->m_EmpArray[i]!=NULL){
                    delete this->m_EmpArray[i];
                }
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray=NULL;

    }
}

void WorkManager::ShowMenu(){
    cout<<"***************************************"<<endl;
    cout<<"-------- 欢迎使用职工管理系统 --------"<<endl;
    cout<<"----------- 0.退出管理程序 -----------"<<endl;
    cout<<"----------- 1.增加职工信息 -----------"<<endl;
    cout<<"----------- 2.显示职工信息 -----------"<<endl;
    cout<<"----------- 3.删除离职职工 -----------"<<endl;
    cout<<"----------- 4.修改职工信息 -----------"<<endl;
    cout<<"----------- 5.查找职工信息 -----------"<<endl;
    cout<<"----------- 6.按照编号排序 -----------"<<endl;
    cout<<"----------- 7.清空所有文档 -----------"<<endl;
    cout<<"***************************************"<<endl;
    cout<<endl;
}


void WorkManager::exitSystem(){
    cout<<"欢迎下次使用"<<endl;
    exit(0);
}

void WorkManager::Add_Emp(){
    cout<<"请输入添加职工的数量"<<endl;
    int addNum=0;
    cin>>addNum;
    if(addNum>0){

        //计算新空间的大小=原来的+添加的
        int newsize=this->m_EmpNum+addNum;

        //堆区开辟新空间
        Worker ** newSpace=new Worker*[newsize];

        //将原来的内容存放在新的空间下
        if(this->m_EmpArray!=NULL){
            for(int i=0;i<this->m_EmpNum;i++){
                newSpace[i]=this->m_EmpArray[i];
            }
        }

        //输入新的数据
        for(int i=0;i<addNum;i++){
            int id;
            string name;
            int deptid;

            cout<<"请输入第 "<<i+1<<" 个新职工编号： "<<endl;
            cin>>id;

            cout<<"请输入第 "<<i+1<<" 个新职工姓名： "<<endl;
            cin>>name;

            cout<<"请选择该职工的岗位： "<<endl;
            cout<<"1、普通职工"<<endl;
            cout<<"2、经理"<<endl;
            cout<<"3、老板"<<endl;
            cin>>deptid;

            Worker *worker=NULL;
            switch(deptid){
            case 1:
                worker = new Employee(id,name,1);
                break;
            case 2:
                worker=new Manager(id,name,2);
                break;
            case 3:
                worker = new Boss(id,name,3);
                break;
            default:
                break;

            }

            newSpace[this->m_EmpNum+i]=worker;

        }
        //释放原有空间
        delete[] this->m_EmpArray;

        //更改空间指向
        this->m_EmpArray=newSpace;

        //更新新的个数
        this->m_EmpNum=newsize;

        //提示信息
        cout<<"成功添加 "<<addNum<<" 名新职工！"<<endl;

        this->m_FileIsEmpty=false;

        this->save();
    }
    else{

        cout<<"输入有误！"<<endl;
    }

    system("pause");
    system("cls");
}

void WorkManager::save(){
    ofstream ofs;
    ofs.open(FILENAME,ios::out);

    for(int i=0;i<this->m_EmpNum;i++){

        ofs<<this->m_EmpArray[i]->m_Id<<" "
            <<this->m_EmpArray[i]->m_Name<<" "
            <<this->m_EmpArray[i]->m_DeptId<<endl;
    }

    ofs.close();
}

int WorkManager::get_EmpNum(){
    ifstream ifs;
    ifs.open(FILENAME,ios::in);

    int id;
    string name;
    int deptid;

    int num=0;
    //一行一行的
    while(ifs>>id && ifs>>name &&ifs>>deptid){
        num++;
    }
    ifs.close();

    return num;
}

void WorkManager::init_Emp(){
    ifstream ifs;
    ifs.open(FILENAME,ios::in);

    int id;
    string name;
    int deptid;

    int index=0;
    while(ifs>>id && ifs>>name &&ifs>>deptid){

        Worker *worker=NULL;
        //根据不同的部门创建不同的对象
        if(deptid==1){
            worker=new Employee(id,name,1);
        }
        else if(deptid==2){
            worker=new Manager(id,name,2);
        }
        else{
            worker=new Boss(id,name,3);
        }

        this->m_EmpArray[index]=worker;
        index++;
    }

}

void WorkManager::show_Emp(){
    if(this->m_FileIsEmpty){
        cout<<"文件不存在或记录为空"<<endl;
    }
    else{
        for(int i=0;i<this->m_EmpNum;i++){
            //多态调用程序接口
            this->m_EmpArray[i]->showInfo();
        }

    }
    system("pause");
    system("cls");
}

void WorkManager::Del_Emp(){
    if(this->m_FileIsEmpty){
        cout<<"文件不存在或记录为空"<<endl;
    }
    else{
        cout<<"请输入删除的职工编号： "<<endl;

        int id=0;
        cin>>id;

        int index=this->isExist(id);

        if(index!=-1){
            for(int i=index;i<this->m_EmpNum-1;i++){
                this->m_EmpArray[i]=this->m_EmpArray[i+1];
            }
            this->m_EmpNum--;
            //并且同步更新到文件
            this->save();
            cout<<"删除成功！"<<endl;
        }
        else{
            cout<<"职工不存在，删除失败！"<<endl;
        }

    }
    system("pause");
    system("cls");
}

int WorkManager::isExist(int id){
    int index=-1;
    for(int i=0;i<this->m_EmpNum;i++){

        if(this->m_EmpArray[i]->m_Id==id){
            index=i;
            break;
        }
    }
    return index;
}

void WorkManager::Mod_Emp(){
    if(this->m_FileIsEmpty){
        cout<<"文件不存在或者为空"<<endl;
    }
    else{
        cout<<"请输入修改的职工编号："<<endl;

        int id;
        cin>>id;

        int ret=this->isExist(id);
        if(ret!=-1){
            //查到编号职工
            delete this->m_EmpArray[ret];

            int newid=0;
            string newname="";
            int newsel=0;

            cout<<"查到："<<id<<" 号职工，请输入新的工号："<<endl;
            cin>>newid;

            cout<<"请输入新的姓名："<<endl;
            cin>>newname;

            cout<<"请输入岗位："<<endl;
            cout<<"1、普通职工"<<endl;
            cout<<"2、经理"<<endl;
            cout<<"3、老板"<<endl;
            cin>>newsel;

            Worker *worker=NULL;
            switch(newsel){
            case 1:
                worker = new Employee(newid,newname,1);
                break;
            case 2:
                worker=new Manager(newid,newname,2);
                break;
            case 3:
                worker = new Boss(newid,newname,3);
                break;
            default:
                break;
            }

            //更新到数组中
            this->m_EmpArray[ret]=worker;
            cout<<"修改成功！"<<endl;

            this->save();
        }
        else{
            cout<<"修改失败，查无此人！"<<endl;
        }

    }
    system("pause");
    system("cls");
}

void WorkManager::Find_Emp(){
    if(this->m_FileIsEmpty){
        cout<<"文件不存在或者为空"<<endl;
    }
    else{
        cout<<"请输入查找方式："<<endl;
        cout<<"1、按职工编号查找"<<endl;
        cout<<"2、按职工姓名查找"<<endl;

        int select=0;
        cin>>select;

        if(select==1){
            cout<<"请输入查找的职工编号："<<endl;
            int id;
            cin>>id;

            int ret=this->isExist(id);
            if(ret!=-1){
                cout<<"查找成功！该职工信息如下："<<endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else{
                cout<<"查找失败！查无此人"<<endl;
            }
        }
        else if(select==2){
            cout<<"请输入查找的职工姓名："<<endl;
            string name;
            cin>>name;

            //查找到的标志
            bool flag=false;
            for(int i=0;i<this->m_EmpNum;i++){
                if(this->m_EmpArray[i]->m_Name==name){
                    cout<<"查找成功，职工编号为："
                        <<this->m_EmpArray[i]->m_Id
                        <<" 的信息如下："<<endl;

                    flag=true;
                    this->m_EmpArray[i]->showInfo();
                }
            }
            if(flag==false){
                cout<<"查找失败！查无此人"<<endl;
            }
        }
        else{
            cout<<"输入选项有误！"<<endl;

        }
    }

    system("pause");
    system("cls");
}

void WorkManager::Sort_Emp(){
    if(this->m_FileIsEmpty){
        cout<<"文件不存在或者为空"<<endl;
    }
    else{
        cout<<"请选择排序方式："<<endl;
        cout<<"1、升序"<<endl;
        cout<<"2、降序"<<endl;

        int select=0;
        cin>>select;

        if(select==1){
            for(int i=0;i<this->m_EmpNum-1;i++){
                for(int j=i+1;j<this->m_EmpNum;j++){

                    if(this->m_EmpArray[i]->m_Id > this->m_EmpArray[j]->m_Id){
                       Worker *work=this->m_EmpArray[i];
                        this->m_EmpArray[i]=this->m_EmpArray[j];
                        this->m_EmpArray[j]=work;
                    }
                }
            }

            cout<<"排序成功，排序后结果为："<<endl;
            this->save();
            this->show_Emp();

        }
        else if(select==2){
            for(int i=0;i<this->m_EmpNum-1;i++){
                for(int j=i+1;j<this->m_EmpNum;j++){
                    if(this->m_EmpArray[i]->m_Id<this->m_EmpArray[j]->m_Id){
                       Worker *work=this->m_EmpArray[i];
                        this->m_EmpArray[i]=this->m_EmpArray[j];
                        this->m_EmpArray[j]=work;
                    }
                }
            }

            cout<<"排序成功，排序后结果为："<<endl;
            this->save();
            this->show_Emp();
        }
        else{
            cout<<"排序失败"<<endl;
        }
    }
}

void WorkManager::Clean_File(){
    if(this->m_FileIsEmpty){
        cout<<"文件不存在或者为空"<<endl;
    }
    else{
        cout<<"确认清空?"<<endl;
        cout<<"1、确认"<<endl;
        cout<<"2、返回"<<endl;

        int select=0;
        cin>>select;

        if(select==1){
            ofstream ofs;
            //如果存在删除文件并重新创建
            ofs.open(FILENAME,ios::trunc);
            ofs.close();

            for(int i=0;i<this->m_EmpNum;i++){
                if(this->m_EmpArray[i]!=NULL){
                    delete this->m_EmpArray[i];
                }
            }
            this->m_EmpNum=0;
            delete[] this->m_EmpArray;
            this->m_EmpArray=NULL;
            this->m_FileIsEmpty=true;

            cout<<"清空成功！"<<endl;
        }

    }
    system("pause");
    system("cls");

}




