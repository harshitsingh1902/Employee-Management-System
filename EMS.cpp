#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
using namespace std;

class Employee
{
private:
    int code;
    char name[20];
    float salary;
    int no_of_emp;
public:
    void read();
    void display();
    void setEmp(int no_of_emp)
    {
        this->no_of_emp=no_of_emp;
    }

    int getEmp()
    {
        return no_of_emp;
    }

    int getEmpCode()
    {
        return code;
    }
    int getSalary()
    {
        return salary;
    }
    char* getEmpname()
    {
        return name;
    }
};

class Department
{
    int no_of_dept;
    Employee *e;
public:
    void setDept(int no_of_dept)
    {
        this->no_of_dept=no_of_dept;
    }
    int getDept()
    {
        return no_of_dept;
    }
    void setEmp(Employee *e1)
    {
        int no_of_emp;
        e=e1;
        e=new Employee;
        cout<<"\nEnter no. of Employees: ";
        cin>>no_of_emp;
        if(no_of_emp>100)
        {
            cout<<"\n Can't have more than 100 employees";
            return;
        }
        else
            e1->setEmp(no_of_emp);
    }
    void display(Employee *e1)
    {
        e=e1;
        cout<<"\nNo. of Employees: "<<e->getEmp()<<endl;
    }
};

class Company
{
    string name;
    Department dept;
public:
    void setname(string name)
    {
        this->name=name;
    }
    string getName()
    {
        return name;
    }
    void setDept()
    {
        int no_of_dept;
        cout<<"\nEnter no. of departments: ";
        cin>>no_of_dept;
        dept.setDept(no_of_dept);
    }
    void display()
    {
        cout<<"Company Name: "<<getName();
        cout<<"\nNo. of departments: "<<dept.getDept();
    }
};

void Employee::read()
{
    cout<<"Enter employee code: ";
    cin>>code;
    cout<<"Enter name: ";
    cin.ignore();
    cin.getline(name,20);
    cout<<"Enter salary: ";
    cin>>salary;
}

void Employee::display()
{
    cout<<"Employee code is "<<code<<'\n'
        <<"Employee name is "<<name<<'\n'
        <<"Employee salary is "<<salary<<'\n';
}

void deleteExistingFile()
{
    remove("EMPLOYEE.DAT");
}

void appendtofile()
{
    Employee e;
    e.read();
    ofstream fout;
    fout.open("EMPLOYEE.DAT",ios::binary|ios::app);
    if(!fout)
	{
        cout<<"ERROR IN CREATING FILE\n";
        exit(0);
    }
    fout.write((char*)&e,sizeof(e));
    fout.close();
    cout<<"Record added successfully!\n";
}

void displayAll()
{
    Employee e;
    ifstream fin;
    fin.open("EMPLOYEE.DAT",ios::binary);
    if(!fin)
	{
        cout<<"ERROR IN OPENING FILE!\n";
        exit(0);
    }
    while(fin.read((char*)&e,sizeof(e)))
	{
         e.display();
    }
    fin.close();
}

void searchbycode()
{
    Employee e;
    int c;
    int l=0;
    cout<<"Enter employee code: ";
    cin>>c;
    ifstream fin;
    fin.open("EMPLOYEE.DAT",ios::binary|ios::in);
    if(!fin)
	{
        cout<<"ERROR IN OPENING FILE!\n";
        exit(0);
    }
    while(fin.read((char*)&e,sizeof(e)))
	{
        {
            if(e.getEmpCode()==c)
			{
                cout<<"RECORD FOUND\n";
                e.display();
                l=1;
                break;
            }
        }
    }
    if(l==0)
	{
        cout<<"Record not found!\n";
    }
    fin.close();
}

void searchbyname()
{
    Employee e;
    char ch[20];
    int l=0;
    cout<<"Enter employee name: ";
    cin.ignore();
    cin.getline(ch,20);
    ifstream fin;
    fin.open("EMPLOYEE.DAT",ios::binary|ios::in);
    if(!fin)
	{
        cout<<"ERROR IN OPENING FILE!\n";
        exit(0);
    }
    while(fin.read((char*)&e,sizeof(e)))
	{
	    {
            if(strcmp(e.getEmpname(),ch)==0)
			{
                cout<<"RECORD FOUND\n";
                e.display();
                l=1;
                break;
            }
        }
    }
    if(l==0)
	{
        cout<<"Record not found!\n";
    }
    fin.close();
}

void deleterecord()
{
    ifstream fin;
    ofstream fout;
    fin.open("Employee.dat",ios::binary);
    fout.open("Temp.dat",ios::binary|ios::app);
    if(!fin)
    {
        cout<<"ERROR IN OPENING FILE!";
        exit(0);
	}

    int eno;
    cout<<"ENTER EMPLOYEE CODE : ";
    cin>>eno;

    Employee e;
    while(fin.read((char*)&e,sizeof(e)))
    {
        if(e.getEmpCode()!=eno)
        {
            fout.write((char*)&e,sizeof(e));
        }
        cout<<"RECORD DELETED SUCCESSFULLY!\n";

        fin.close();
        fout.close();
        remove("Employee.dat");
        rename("Temp.dat","Employee.dat");
    }
}

void updaterecord()
{
    fstream fin;
    fin.open("Employee.dat",ios::in|ios::out|ios::binary);
    if(!fin)
    {
        cout<<"ERROR IN OPENING FILE!";
        exit(0);
	}

	int sno; int l=0;
	cout<<"ENTER EMPLOYEE CODE : ";
	cin>>sno;

	Employee e;
	while(fin.read((char*)&e,sizeof(e)))
	{
	    if(e.getEmpCode()==sno)
        {
            l++;
            cout<<"ENTER NEW ENTRIES\n";
            e.read();
        }
        else if(l==0)
        {
            cout<<"RECORD NOT FOUND!";
        }
        fin.seekp(-1*sizeof(e),ios::cur);
        fin.write((char*)&e,sizeof(e));
	}
	cout<<"record updated successfully!"<<endl;

	fin.close();
}

void login()
{
    string userName;
    string userPassword;
    int loginAttempt=0;

    while(loginAttempt<3)
    {
        cout<<"Enter Userid: ";
        cin>>userName;
        cout<<"Enter password: ";
        cin>>userPassword;

        if(userName=="admin" && userPassword=="admin123")
        {
            break;
        }
        else
        {
            cout<<"Invalid login attempt. Please try again.\n"<<"\n";
            loginAttempt++;
        }
    }
    if(loginAttempt==3)
    {
        cout<<"Too many login attempts! Please try after sometime.\n";
        exit(0);
    }

    return;
}

int main()
{
    char compName[20],choice;
    Company *comp=new Company;
    cout<<"Enter company name: ";
    cin.getline(compName,20);
    comp->setname(compName);
    comp->setDept();
    Department dept1;
    Employee *e=new Employee;
    dept1.setEmp(e);

    system("cls");
    comp->display();
    dept1.display(e);

    cout<<"\nDo you want to continue to employee management system(Y/y): ";
    cin>>choice;

    if(choice=='Y'||choice=='y')
    {
        system("cls");
        login();
        system("cls");

        cout<<"\nEMPLOYEE MANAGEMENT SYSTEM\n";

        char ch;
//        deleteExistingFile();
        do
        {
            int n;
            cout<<"\nENTER CHOICE\n"
                <<"1.ADD AN EMPLOYEE\n"
                <<"2.DISPLAY ALL RECORDS\n"
                <<"3.SEARCH RECORD BY CODE\n"
                <<"4.SEARCH RECORD BY NAME\n"
                <<"5.DELETE RECORD OF AN EMPLOYEE\n"
                <<"6.UPDATE RECORD OF AN EMPLOYEE\n"
                <<"Make a choice: ";
            cin>>n;

            switch(n)
            {
                case 1:
                    appendtofile();
                    break;
                case 2 :
                    displayAll();
                    break;
                case 3:
                    searchbycode();
                    break;
                case 4:
                    searchbyname();
                    break;
                case 5:
                    deleterecord();
                    break;
                case 6:
                    updaterecord();
                    break;

                default :
                    cout<<"Invalid Choice\n";
            }
            cout<<"Do you want to continue(y/n): ";
            cin>>ch;

        }while(ch=='Y'||ch=='y');
    }
    else
    {
        exit(0);
    }

    return 0;
}

