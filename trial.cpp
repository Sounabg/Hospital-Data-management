#include <conio.h>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <sstream>  
#include <windows.h>
using namespace std;

int ID;
char devider=254;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //SetConsoleTextAttribute for colour
ios_base::fmtflags flags = cout.flags();

struct Node
{
    int Id;
    string Name, BGrp;
    Node *next;
    Node *prev;
    
    Node() { }

    Node(int ix)
    {
        Id=ix;
        cout<<"Id : "<<Id;
        cout<<endl<<"Name : "; getline( cin.ignore(1,'\n'),Name);
        cout<<"Blood Group : "; cin>>BGrp;
        
    }

    show()
    {
        cout << left<<endl<< setw(10) <<Id<< setw(30) <<Name << setw(5) <<BGrp;
        cout.flags(flags);
    }
};

Node *ptr, *head, *tail;

void writePatient(){
    Node *temp;
    ofstream file("patient.csv");
	for(temp=head; temp!=NULL; temp=temp->next)
	{
        file<<temp->Id<<","<<temp->Name<<","<<temp->BGrp<<endl;
	}
}

void readPatient(){

    string name,bg,id;
    ifstream file("patient.csv");
        if (file.fail()){
            cout << "File is not open:" << endl;
        }
        else{
            file.is_open();
            while (!file.eof()){
                Node *temp=new Node();

                getline(file, id, ',');
                getline(file, name, ',');
                getline(file, bg, '\n');

                stringstream geek(id);
                geek >> temp->Id;

                temp->Name=name;
                temp->BGrp=bg;
                temp->next=NULL;
                if (temp->Id==1)
                {   
                    temp->prev=NULL;
                    head=temp;
                    tail=temp;
                }
                else{
                    temp->prev=tail;
                    tail->next=temp;
                    tail=temp;
                }
                
            }
        }
            
    file.close();
} 

void insert() {
    if (head==NULL)
    {   ID=1;
        ptr= new Node(ID);
        ptr->next=NULL;
        ptr->prev=NULL;
        head=ptr;
        tail=ptr;
    }
    else{
        ID=((tail->Id)+1);
        ptr=new Node(ID);   
        ptr->next=NULL;
        ptr->prev=tail;
        tail->next=ptr;
        tail=ptr;
    }
}

void show(){
    SetConsoleTextAttribute(console, 10);
    cout<<"Available Data :\n"<<"---------------------------------------------------------"<<endl;
    cout << left
        << setw(10) <<"Id"
        << setw(30) <<"Name"
        << setw(5) <<"Blood Group"<<endl<<"---------------------------------------------------------";
        cout.flags(flags);

    SetConsoleTextAttribute(console, 15);
    Node *temp;
	for(temp=head; temp!=NULL; temp=temp->next)
	{
		temp->show();
	}
    SetConsoleTextAttribute(console, 10);
    cout<<endl<<"---------------------------------------------------------"<<endl;
}

int main()
{

    int choice, access=1, password;
    string name,bg,id;
    readPatient();
    insert();
    show();
    writePatient();


    return 0;
}
