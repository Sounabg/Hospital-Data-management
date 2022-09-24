#include <conio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
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

    Node(){ }

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

Node *ptr, *head, *tail, *temp;

void writePatient(){
    Node *temp;
    ofstream file("patient.csv");
	for(temp=head; temp!=NULL; temp=temp->next)
	{
        if (temp->next!=NULL){
        file<<temp->Id<<","<<temp->Name<<","<<temp->BGrp<<endl; }
        else{
        file<<temp->Id<<","<<temp->Name<<","<<temp->BGrp;
        }
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
                geek>>temp->Id;
                temp->Name=name;
                temp->BGrp=bg;
                temp->next=NULL;
                //temp->show();
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
                if(file.eof()) {
                    cout<<"File ended";
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
void del(int id){
    Node *front, *back;
    if (id==1 && head->next!=NULL)
    {
        temp=head->next;
        temp->prev=NULL;
        head=temp;
    }
    else if(id==1 && head->next== NULL)
    {
        head=NULL;
        cout<<"List Cleared.";
    }
    else{
    for (temp=tail; temp!=NULL; temp=temp->prev)
    {
        if(temp->Id==id)
        {
            if(temp->Id == tail->Id) {
                temp=tail->prev;
                temp->next=NULL;
                tail=temp;
            }
            else {
            front=temp->prev;
            back= temp->next;
            front->next=back;
            back->prev=front;
            break; }
        }
    }
    }
    cout<<"ID deleted";
}
void search(int id) {
    int found=0;
    
    for (temp=tail; temp!=NULL; temp=temp->prev)
    {
        if(temp->Id==id)
        {
            temp->show(); 
            found=1;
        }
    }
    if(found==0){
        cout<<"ID Not Found";
    }
}
void Update(int id) {  
    int found=0;
    for (temp=tail; temp!=NULL; temp=temp->prev)
    {
        if(temp->Id==id)
        {
            cout<<"Id: "<<temp->Id<<endl;
            cout<<"Name: "; getline( cin.ignore(1,'\n'),temp->Name);
            cout<<"Blood Group: "; cin>>temp->BGrp;
            cout<<endl<<"Id Updated to -"<<endl;
            search(id);
            found=1;
            break;
        }
        else { }
    }
    if(found==0){
        cout<<"ID Not Found";
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
void welcome(int tim) {
    int len = 0,x, y=1, timer=tim; // 240 = white background, black foreground 
    
    char text[] = "Welcome to Sounab Dream Hospital Pvt. Ltd.";
    len = sizeof(text);
    SetConsoleTextAttribute(console, 14);
    for ( x=0;x<len;x++)
    {
        cout << text[x];
        Sleep(timer); 
    }
    cout<<endl;
    for ( x=0;x<len-1;x++) //PRINT DASH
    {
        cout<<devider;
        }
    cout<<endl;
}
void loading() {
    SetConsoleTextAttribute(console, 13);
	cout<<"Loading"<<endl;
	for(int i=0;i<20;i++ )
	{
		cout<<devider;
		Sleep(80);
	}
    cout<<endl;
    system("pause");
	system("cls");
}


int main()
{
    system("CLS");

    int choice, access=1, id, password;
	ptr=NULL;
    head=tail=ptr;


    loading(); welcome(40);
    SetConsoleTextAttribute(console, 10);
    cout<<"Admin Login"<<endl<<endl;
    cout<<"Enter Password : ";
    SetConsoleTextAttribute(console, 1); cin>>password; 


    //after login code
    while(access!=0)
    {
        if(password==1234)
        {
            system("CLS");
            readPatient();
            SetConsoleTextAttribute(console, 10);
            cout<<"\nChoose Option :\n-----------------------------------------------------------------------------------\n"<<
                    "1- Insert\t 2- Delete\t 3- Search\t 4- Update\t 5-Show\t  0- Exit"<<
                    "\n-----------------------------------------------------------------------------------\n"<<endl;
            cout<<endl<<"Your Choice Is : ";
            cin>>choice;
            while (choice!=0)
        {
        SetConsoleTextAttribute(console, 15);
        switch(choice)
        {
            case 1:
                system("CLS");
                SetConsoleTextAttribute(console, 10);
                cout<<"Adding Date."<<endl;
                SetConsoleTextAttribute(console, 15);
                insert();
                choice=99;
                break;

            case 2:
                show();
                SetConsoleTextAttribute(console, 10);
                cout<<"Enter Id to Delete : ";
                SetConsoleTextAttribute(console, 15);
                cin>> id;
                del(id);
                choice=99;
                break;

            case 3:
                system("CLS");
                SetConsoleTextAttribute(console, 10);
                cout<<"Enter Id to Search : ";
                SetConsoleTextAttribute(console, 15);
                cin>> id;
                search(id);
                choice=99;
                break;
        
            case 4:
                system("CLS");
                show();
                SetConsoleTextAttribute(console, 10);
                cout<<endl<<"Enter Id to Update : ";
                SetConsoleTextAttribute(console, 15);
                cin>> id;
                Update(id);
                choice=99;
                break;

            case 5:
                system("CLS");
                show();
                choice=99;
                break;

            case 0:
                choice=0;
        }
        SetConsoleTextAttribute(console, 10);
        cout<<endl<<"\nChoose Option :\n-----------------------------------------------------------------------------------\n"<<
                    "1- Insert\t 2- Delete\t 3- Search\t 4- Update\t 5-Show\t  0- Exit"<<
                    "\n-----------------------------------------------------------------------------------\n"<<endl;

        cout<<endl<<"Your Choice Is : ";
        cin>>choice;
        
        
        if(choice==0){
            system("CLS");
            writePatient();
            access=0;
            SetConsoleTextAttribute(console, 206);
            cout<<endl<<"***Signed Out****"<<endl<<endl;
            break;
        }
        }
        }
        else {
            system("CLS");
            system("Color 01");
            welcome(0);
            SetConsoleTextAttribute(console, 200);
            cout<<"Enter ID & Password correctly"<<endl<<endl;
        
            SetConsoleTextAttribute(console, 10);
            cout<<"Admin Login"<<endl<<endl;
            cout<<"Enter Password : ";
            SetConsoleTextAttribute(console, 1); cin>>password;
        }
    }

    return 0;
}
