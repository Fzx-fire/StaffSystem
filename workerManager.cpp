#include"workerManager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

//����ʵ��
WorkManager::WorkManager(){
    ifstream ifs;
    ifs.open(FILENAME,ios::in);

    if(!ifs.is_open()){
        cout<<"�ļ�������"<<endl;
        this->m_EmpNum=0;
        this->m_EmpArray=NULL;
        this->m_FileIsEmpty=true;

        ifs.close();
        return ;
    }

    //�ļ����ڣ�����Ϊ��
    char ch;
    ifs>>ch;
    if(ifs.eof()){
        cout<<"�ļ�Ϊ��"<<endl;
        this->m_EmpNum=0;
        this->m_EmpArray=NULL;
        this->m_FileIsEmpty=true;

        ifs.close();
        return ;
    }

    //�ļ����ڲ���������
    int num=this->get_EmpNum();
    cout<<"ְ������Ϊ��"<<num<<endl;
    this->m_EmpNum=num;
    this->m_EmpArray=new Worker*[this->m_EmpNum];
    init_Emp();
    this->m_FileIsEmpty=false;
    for(int i=0;i<this->m_EmpNum;i++){
        cout<<"ְ����ţ�"<<this->m_EmpArray[i]->m_Id
            <<"\tְ��������"<<this->m_EmpArray[i]->m_Name
            <<"\t���ű�ţ�"<<this->m_EmpArray[i]->m_DeptId<<endl;
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
    cout<<"-------- ��ӭʹ��ְ������ϵͳ --------"<<endl;
    cout<<"----------- 0.�˳�������� -----------"<<endl;
    cout<<"----------- 1.����ְ����Ϣ -----------"<<endl;
    cout<<"----------- 2.��ʾְ����Ϣ -----------"<<endl;
    cout<<"----------- 3.ɾ����ְְ�� -----------"<<endl;
    cout<<"----------- 4.�޸�ְ����Ϣ -----------"<<endl;
    cout<<"----------- 5.����ְ����Ϣ -----------"<<endl;
    cout<<"----------- 6.���ձ������ -----------"<<endl;
    cout<<"----------- 7.��������ĵ� -----------"<<endl;
    cout<<"***************************************"<<endl;
    cout<<endl;
}


void WorkManager::exitSystem(){
    cout<<"��ӭ�´�ʹ��"<<endl;
    exit(0);
}

void WorkManager::Add_Emp(){
    cout<<"���������ְ��������"<<endl;
    int addNum=0;
    cin>>addNum;
    if(addNum>0){

        //�����¿ռ�Ĵ�С=ԭ����+��ӵ�
        int newsize=this->m_EmpNum+addNum;

        //���������¿ռ�
        Worker ** newSpace=new Worker*[newsize];

        //��ԭ�������ݴ�����µĿռ���
        if(this->m_EmpArray!=NULL){
            for(int i=0;i<this->m_EmpNum;i++){
                newSpace[i]=this->m_EmpArray[i];
            }
        }

        //�����µ�����
        for(int i=0;i<addNum;i++){
            int id;
            string name;
            int deptid;

            cout<<"������� "<<i+1<<" ����ְ����ţ� "<<endl;
            cin>>id;

            cout<<"������� "<<i+1<<" ����ְ�������� "<<endl;
            cin>>name;

            cout<<"��ѡ���ְ���ĸ�λ�� "<<endl;
            cout<<"1����ְͨ��"<<endl;
            cout<<"2������"<<endl;
            cout<<"3���ϰ�"<<endl;
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
        //�ͷ�ԭ�пռ�
        delete[] this->m_EmpArray;

        //���Ŀռ�ָ��
        this->m_EmpArray=newSpace;

        //�����µĸ���
        this->m_EmpNum=newsize;

        //��ʾ��Ϣ
        cout<<"�ɹ���� "<<addNum<<" ����ְ����"<<endl;

        this->m_FileIsEmpty=false;

        this->save();
    }
    else{

        cout<<"��������"<<endl;
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
    //һ��һ�е�
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
        //���ݲ�ͬ�Ĳ��Ŵ�����ͬ�Ķ���
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
        cout<<"�ļ������ڻ��¼Ϊ��"<<endl;
    }
    else{
        for(int i=0;i<this->m_EmpNum;i++){
            //��̬���ó���ӿ�
            this->m_EmpArray[i]->showInfo();
        }

    }
    system("pause");
    system("cls");
}

void WorkManager::Del_Emp(){
    if(this->m_FileIsEmpty){
        cout<<"�ļ������ڻ��¼Ϊ��"<<endl;
    }
    else{
        cout<<"������ɾ����ְ����ţ� "<<endl;

        int id=0;
        cin>>id;

        int index=this->isExist(id);

        if(index!=-1){
            for(int i=index;i<this->m_EmpNum-1;i++){
                this->m_EmpArray[i]=this->m_EmpArray[i+1];
            }
            this->m_EmpNum--;
            //����ͬ�����µ��ļ�
            this->save();
            cout<<"ɾ���ɹ���"<<endl;
        }
        else{
            cout<<"ְ�������ڣ�ɾ��ʧ�ܣ�"<<endl;
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
        cout<<"�ļ������ڻ���Ϊ��"<<endl;
    }
    else{
        cout<<"�������޸ĵ�ְ����ţ�"<<endl;

        int id;
        cin>>id;

        int ret=this->isExist(id);
        if(ret!=-1){
            //�鵽���ְ��
            delete this->m_EmpArray[ret];

            int newid=0;
            string newname="";
            int newsel=0;

            cout<<"�鵽��"<<id<<" ��ְ�����������µĹ��ţ�"<<endl;
            cin>>newid;

            cout<<"�������µ�������"<<endl;
            cin>>newname;

            cout<<"�������λ��"<<endl;
            cout<<"1����ְͨ��"<<endl;
            cout<<"2������"<<endl;
            cout<<"3���ϰ�"<<endl;
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

            //���µ�������
            this->m_EmpArray[ret]=worker;
            cout<<"�޸ĳɹ���"<<endl;

            this->save();
        }
        else{
            cout<<"�޸�ʧ�ܣ����޴��ˣ�"<<endl;
        }

    }
    system("pause");
    system("cls");
}

void WorkManager::Find_Emp(){
    if(this->m_FileIsEmpty){
        cout<<"�ļ������ڻ���Ϊ��"<<endl;
    }
    else{
        cout<<"��������ҷ�ʽ��"<<endl;
        cout<<"1����ְ����Ų���"<<endl;
        cout<<"2����ְ����������"<<endl;

        int select=0;
        cin>>select;

        if(select==1){
            cout<<"��������ҵ�ְ����ţ�"<<endl;
            int id;
            cin>>id;

            int ret=this->isExist(id);
            if(ret!=-1){
                cout<<"���ҳɹ�����ְ����Ϣ���£�"<<endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else{
                cout<<"����ʧ�ܣ����޴���"<<endl;
            }
        }
        else if(select==2){
            cout<<"��������ҵ�ְ��������"<<endl;
            string name;
            cin>>name;

            //���ҵ��ı�־
            bool flag=false;
            for(int i=0;i<this->m_EmpNum;i++){
                if(this->m_EmpArray[i]->m_Name==name){
                    cout<<"���ҳɹ���ְ�����Ϊ��"
                        <<this->m_EmpArray[i]->m_Id
                        <<" ����Ϣ���£�"<<endl;

                    flag=true;
                    this->m_EmpArray[i]->showInfo();
                }
            }
            if(flag==false){
                cout<<"����ʧ�ܣ����޴���"<<endl;
            }
        }
        else{
            cout<<"����ѡ������"<<endl;

        }
    }

    system("pause");
    system("cls");
}

void WorkManager::Sort_Emp(){
    if(this->m_FileIsEmpty){
        cout<<"�ļ������ڻ���Ϊ��"<<endl;
    }
    else{
        cout<<"��ѡ������ʽ��"<<endl;
        cout<<"1������"<<endl;
        cout<<"2������"<<endl;

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

            cout<<"����ɹ����������Ϊ��"<<endl;
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

            cout<<"����ɹ����������Ϊ��"<<endl;
            this->save();
            this->show_Emp();
        }
        else{
            cout<<"����ʧ��"<<endl;
        }
    }
}

void WorkManager::Clean_File(){
    if(this->m_FileIsEmpty){
        cout<<"�ļ������ڻ���Ϊ��"<<endl;
    }
    else{
        cout<<"ȷ�����?"<<endl;
        cout<<"1��ȷ��"<<endl;
        cout<<"2������"<<endl;

        int select=0;
        cin>>select;

        if(select==1){
            ofstream ofs;
            //�������ɾ���ļ������´���
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

            cout<<"��ճɹ���"<<endl;
        }

    }
    system("pause");
    system("cls");

}




