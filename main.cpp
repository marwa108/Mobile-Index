#include <iostream>
#include <conio.h>
#include <string.h>
#include<strings.h>
#include <string>
#include <windows.h>
#include<fstream>

#define null -32
#define up 72
#define down 80
#define home 71
#define end 79
#define enter 13
#define esc 27

using namespace std;






void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);

}

void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        coord
    );
}




struct Telephone_Node
{
public:
    Telephone_Node* next;
    Telephone_Node* prev;
    string phone;
};



class Telephone_linked_list
{

    Telephone_Node *head,*tail;
public:
    Telephone_linked_list()
    {
        head=tail=NULL;
    }

    void append(string phone)
    {
        Telephone_Node *temp= new Telephone_Node;
        temp->phone=phone;
        if(head==NULL)
        {
            head=tail=temp;
            temp->prev=NULL;
            temp->next=NULL;
        }
        else
        {
            temp->prev=tail;
            temp->next=NULL;
            tail->next=temp;
            tail=temp;
        }

    }
    void display()
    {
        Telephone_Node *temp=head;
        while(temp!=NULL)
        {
            cout<<temp->phone<<"\n";
            temp=temp->next;
        }
    }
    int count()
    {
        int count=0;
        Telephone_Node *temp=head;
        while(temp!=NULL)
        {
            temp=temp->next;
            count++;
        }
        return count;
    }
    void modify_phone(string old, string newp)
    {
        Telephone_Node* temp=search_by_phone(old);
        temp->phone=newp;
    }
    Telephone_Node* save()
    {
        return head;
    }


    void delete_by_phone(string phone)
    {
        Telephone_Node* temp=search_by_phone(phone);
        if(temp==NULL)
            cout<<"error";
        if(head==tail)
        {
            delete temp;
            head=tail=NULL;
        }
        else if (temp==head)
        {
            head=temp->next;
            head->prev=NULL;
            delete temp;
        }
        else if (temp==tail)
        {
            tail=temp->prev;
            tail->next=NULL;
            delete temp;
        }
        else
        {
            temp->next->prev=temp->prev;
            temp->prev->next=temp->next;
            delete temp;
        }
    }

    Telephone_Node* search_by_phone( string phone)
    {
        Telephone_Node *temp=head;
        while(temp!=NULL)
        {
            if(temp->phone==phone)
                return temp;
            temp=temp->next;

        }
        cout<<"\ndata not found\n";
        return NULL;

    }


    void deleteall()
    {
        Telephone_Node* temp=head;
        while(temp!=NULL)
        {
            head=head->next;
            delete temp;
            temp=head;
        }
    }


    Telephone_linked_list (const Telephone_linked_list &olds)
    {
        Telephone_Node *temp=olds.head;

        deleteall();
        while(temp !=NULL)
        {
            append(temp->phone);
            temp=temp->next;

        }

    }

    Telephone_Node* operator[](int i)
    {
        int counter =0;
        Telephone_Node* temp =head;
        while(temp!=NULL)
        {
            if(counter==i)
                return temp;
            temp=temp->next;
            counter ++;

        }
        return NULL;
    }


    ~Telephone_linked_list()
    {
        deleteall();


    }
};

struct node
{
    string myName;
    Telephone_linked_list myPhone;
    node* next;
    node* prev;
};

struct Data
{
    string myName ;
    Telephone_linked_list  myPhone;
};


class LL
{
    node *head, *tail;
public:
      std::ofstream write;
      std::ifstream read;
    LL()
    {
        head=tail=NULL;
    }
    void savetofile()
        {
                node *temp=head;


            write.open("text.txt");
            remove("text.txt");

            while(temp!=NULL)
            {
                write<<endl;
                write<<temp->myName;

                Telephone_Node *num=temp->myPhone.save();
                while(num)
                {
                    write<<","<<num->phone;
                    num=num->next;
                }

                temp=temp->next;
            }


            write.close();
        }


    void displaydata()
    {
        string line;
         read.open("text.txt");
        if(read.is_open())
        {
            while(getline(read,line))
            {
                cout<<line<<endl;
            }
            read.close();

        }
    }

    void append(string myName,string myPhone)
    {
        node* temp=new node;
        temp->myName=myName;
        temp->myPhone.append(myPhone);
        if(head==NULL)
        {
            head=tail=temp;
            temp->prev=NULL;
            temp->next=NULL;
        }
        else
        {
            temp->prev=tail;
            temp->next=NULL;
            tail->next=temp;
            tail=temp;
        }
    }
    void display()
    {
        node* temp=head;
        while(temp!=NULL)
        {
            cout<<"Name: "<<temp->myName<<endl;
            cout<<"phones :"<<endl;
            temp->myPhone.display();
            temp=temp->next;
        }
    }
    void modifyName(string oldname,string newname)
    {
        node* temp=searchByName(oldname);
        temp->myName=newname;

    }
    void modifyPhone(string old,string newp)
    {
        node* temp=searchByphone(old);
        temp->myPhone.modify_phone(old,newp);

    }

    int counter()
    {
        int count=0;
        node*temp=head;
        while(temp!=NULL)
        {
            count++;
            temp=temp->next;
        }
        return count;
    }
    node* searchByName(string myName)
    {
        node* temp=head;
        while(temp)
        {
            if(temp->myName==myName)
                return temp;
            temp=temp->next;
        }
        return NULL;
    }
    node* searchByphone(string myPhone)
    {
        node* temp=head;
        while(temp!=NULL)
        {
            if(temp->myPhone.search_by_phone(myPhone))
                return temp;

            temp=temp->next;
        }
        return NULL;
    }
    void deleteByName(string myName)
    {
        node* temp=searchByName(myName);
        if(temp==NULL)
            return  ;
        if(head==tail)
        {
            delete temp;
            head=tail=NULL;
        }
        else if(temp==head)
        {
            head=temp->next;
            head->prev=NULL;
            delete temp;
        }
        else if(temp==tail)
        {
            tail=temp->prev;
            tail->next=NULL;
            delete temp;
        }
        else
        {
            temp->next->prev=temp->prev;
            temp->prev->next=temp->next;
            delete temp;
        }


    }

    void deleteByPhone(string myPhone)
    {
        node* temp=searchByphone(myPhone);
        if(temp==NULL)
            return ;
        if(head==tail)
        {
            delete temp;
            head=tail=NULL;
        }
        else if(temp==head)
        {
            head=temp->next;
            head->prev=NULL;
            delete temp;
        }
        else if(temp==tail)
        {
            tail=temp->prev;
            tail->next=NULL;
            delete temp;
        }
        else
        {
            temp->next->prev=temp->prev;
            temp->prev->next=temp->next;
            delete temp;
        }


    }

    void insertAfter(string nName,string nPhone,string oldName)
    {
        node* temp=searchByName(oldName);
        if(temp==NULL||temp==tail)
        {
            append(nName,nPhone);
        }
        else
        {
            node* t=new node;
            t->myName=nName;
            t->myPhone.append(nPhone);
            t->prev=temp;
            t->next=temp->next;
            temp->next=t;
            t->next->prev=t;
        }
    }
    void insertBefore(string nName,string nPhone,string oldName)
    {
        node* temp=searchByName(oldName);
        if(temp==NULL)
        {
            append(nName,nPhone);
        }
        else if(temp==head)
        {
            node* t=new node;
            t->myPhone.append(nPhone);
            t->myName=nName;
            temp->prev=t->next;
            t->next=temp->prev;
            head=t;
        }
        else
        {
            node* t=new node;
            t->myPhone.append(nPhone);
            t->myName=nName;
            t->next=temp;
            t->prev=temp->prev;
            temp->prev=t;
            t->prev->next=t;
        }

    }
    void append_another_phone(string phone, string name)
    {
        node* temp=searchByName(name);
        temp->myPhone.append(phone);
        if(temp==NULL)
            return;
    }
    void deleteAll()
    {
        node* temp=head;
        while(temp!=NULL)
        {
            head=head->next;
            delete temp;
            temp=head;
        }
    }
    ~LL()
    {
        deleteAll();
    }

    node * operator[](int i)
    {
        int counter=0;
        node * temp=head;
        while(temp!=NULL)
        {
            if(counter==i)
                return temp;
            else
            {
                temp=temp->next;
                counter++;
            }
        }

        return NULL;
    }
    /*LL (LL &l1)
    {
        head=tail=NULL;
        node*temp=l1.head;
        while(temp)
        {
            append(temp->myName,temp->myPhone);
            temp=temp->next;
        }
    }*/

    LL & operator=(LL &l)
    {
        deleteAll();
        head=l.head;

        return *this;



    }


};

class stackNode
{
    node* tail ;
    node* head ;
public :
    stackNode()
    {
        tail=head=NULL;
    }
    int isEmpty()
    {
        return tail==NULL ;
    }
    int isFull()
    {
        node* ptr =new node;
        if(ptr!=NULL)
        {
            delete ptr ;
            return 0 ;
        }
        else
            return 1 ;
    }
    void push(string name,string phone)
    {
        node* ptr=new node ;
        if(ptr!=NULL)
        {
            ptr->myName=name;
            ptr->myPhone.append(phone);
            if(tail==NULL)
            {
                tail=head=ptr;
                ptr->prev=NULL;
            }
            else
            {
                ptr->prev=tail;
                tail=ptr;
            }
        }
    }

    Data pop()
    {
        if(tail !=NULL)
        {
            Data d1 ;
            d1.myName=tail->myName;
            d1.myPhone=tail->myPhone;
            node* temp =tail ;
            tail =tail->prev ;
            delete temp ;
            return d1 ;
        }
    }
    void p()
    {
        if(tail !=NULL)
        {

            cout<<tail->myName;

            tail->myPhone.display();
        }
    }

};
int itsName(string n)
{
    int flag=1 ;
    if(n.length()<=10||n.length()>=20)
    {
        return 0 ;

    }
    for(int i=0; i<n.length(); i++)
    {

        if(!(isalpha(n[i])||(isspace(n[i]))))
        {
            return 0 ;
        }

    }

    return flag ;
}

int itsPhone(string n)
{
    int flag=1 ;
    if(n.length()!=11)
    {
        return 0 ;

    }
    for(int i=0; i<n.length(); i++)
    {

        if(!isdigit(n[i]))
        {
            return 0 ;
        }

    }
    return flag ;
}
int main()
{

  char menu [15][20]= {"New","Display","Add Number","modify name","modify number","save to file","load from file","Search by Name","Search by Phone","Delete by Name",
                         "Delete by Phone","Call","dailyNumbers","Delete All","Exit"
                        };
    int i, current=0, exitflag=0;
    char ch;
    string Name,Phone,pos,oldname ,Nname;
    LL l;
    stackNode s;


    do
    {
        system("cls");
        for(i=0; i<11; i++)
        {
            if(i==current)
                textattr(295);
            gotoxy(10,5+i*3);
            _cprintf("%s",menu[i]);
            textattr(0x07);

        }
        ch=getche();
        switch(ch)
        {
        case -32:
        case 0:
            ch=getche();
            switch(ch)
            {
            case up:
                --current;
                if(current<0)
                    current=10;
                break;

            case down:
                ++current;
                if(current>10)
                    current=0;
                break;
            case home:
                current=0;
                break;
            case end:
                current=10;
                break;

            }
            break;
        case enter:
            system("cls");
            switch(current)
            {
            case 0:
                cout<<"**Enter New Data**"<<endl;
                cout<<"Enter Name: "<<endl;
                getline(cin,Name);
                if(!itsName(Name))
                {
                    cout<<"this is invalid name";
                    getche();
                    break ;
                }

                cout<<"Enter Phone: "<<endl;
                cin>>Phone;
                if(!itsPhone(Phone))
                {
                    cout<<"this is invalid phone";
                    getche();
                    break ;
                }

                l.append(Name,Phone);
                break;
            case 1:
                cout<<"**Display**"<<endl;
                l.display();
                getche();
                break;
            case 2:

                cout<<"Enter Name: "<<endl;
                getline(cin,Name);
                if(itsName(Name)) //validate Name
                {
                    if(l.searchByName(Name)!=NULL)//check name is found
                    {
                        cout<<"Enter Phone: "<<endl;
                        cin>>Phone;
                        if((l.searchByphone(Phone)==NULL)&&itsPhone(Phone))
                        {
                            l.append_another_phone(Phone,Name);
                            break;
                        }
                        else
                        {
                            cout<<"phone is found or not correct"<<endl;
                            getche();
                            break ;
                        }

                    }
                    else
                    {
                        cout<<"name is not found or number is repeated"<<endl;
                        getche();
                        break ;
                    }

                }
                else
                {
                    cout<<"name is not valid"<<endl;
                    getche();
                    break ;
                }
            case 3:
                cout<<"Enter Name: "<<endl;
                getline(cin,oldname);
                if(itsName(oldname)) //validate Name
                {
                    if(l.searchByName(oldname)!=NULL)//check name is found
                    {
                        cout<<"Enter new name: "<<endl;
                        getline(cin,Name);
                        if((l.searchByName(Name)==NULL)&&itsName(Name))
                        {
                            l.modifyName(oldname,Name);
                            break;
                        }
                        else
                        {
                            cout<<"name not correct"<<endl;
                            getche();
                            break ;
                        }

                    }
                    else
                    {
                        cout<<"name is not found or number is repeated"<<endl;
                        getche();
                        break ;
                    }

                }
                else
                {
                    cout<<"name is not valid"<<endl;
                    getche();
                    break ;
                }

            case 4:

                cout<<"Enter phone: "<<endl;
                cin>>Name;
                if(itsPhone(Name)) //validate Name
                {
                    if(l.searchByphone(Name)!=NULL)//check name is found
                    {
                        cout<<"Enter Phone: "<<endl;
                        cin>>Phone;
                        if((l.searchByphone(Phone)==NULL)&&itsPhone(Phone))
                        {
                            l.modifyPhone(Name,Phone);
                            break;
                        }
                        else
                        {
                            cout<<"phone is found or not correct"<<endl;
                            getche();
                            break ;
                        }

                    }
                    else
                    {
                        cout<<"phone is not found or number is repeated"<<endl;
                        getche();
                        break ;
                    }
                    break;

                }

                else
                {
                    cout<<"phone is not valid"<<endl;
                    getche();
                    break ;
                }


                break;
            case 5:
                l.savetofile();
                cout<<"done "<<endl;
                getche();
                break;
            case 6:
                l.displaydata();
                getche();
                break;
            case 7:
                  cout<<"Enter Name To Search: "<<endl;
                getline(cin,Name);
                if((!itsName(Name))||(l.searchByName(Name)==NULL))
                {
                    cout<<"this is invalid name or name is not found";
                    getche();
                    break ;
                }
                else
                {
                    cout<<"the Name is exist in our note" ;
                    getche();
                    break;
                }
            case 8:
                cout<<"Enter Phone: "<<endl;
                cin>>Phone;
                if(!itsPhone(Phone)||(l.searchByphone(Phone)==NULL))
                {
                    cout<<"this is invalid phone or phone is not found ";
                    getche();
                    break ;
                }
                else
                {
                    cout<<"the phone is exist in our Note";
                    getche();
                    break;
                }




            case 9:
                cout<<"enter Name to delete"<<endl;
                cin>>Name;
                if((!itsName(Name))||(l.searchByName(Name)==NULL))
                {
                    cout<<"this is invalid name or name is not found";
                    getche();
                    break ;
                }
                else
                {
                    l.deleteByName(Name);
                    cout<<"deleted"<<endl;
                    getche();
                    break;
                }


            case 10:
                cout<<"enter phone to delete"<<endl;
                cin>>Phone;
                if(!itsPhone(Phone)||(l.searchByphone(Phone)==NULL))
                {
                    cout<<"this is invalid phone or phone is not found ";
                    getche();
                    break ;
                }
                else
                {
                    l.searchByphone(Phone)->myPhone.delete_by_phone(Phone);
                    cout<<"deleted"<<endl;
                    getche();
                    break;
                }


            case 11:
                cout<<"enter phone to call"<<endl;
                cin>>Phone;
                if(l.searchByphone(Phone)!=NULL)
                {
                    s.push(l.searchByphone(Phone)->myName,Phone);
                    getche();
                    break;
                }
                else
                {
                    s.push("un Known",Phone);
                    getche();
                    break;
                }
            case 12:
                s.p();
                getche();
                break;
            case 13:
                l.deleteAll();
                cout<<"**Data Deleted**"<<endl;
                getche();
                break;



            case 14:
                exitflag=1;
                break;

            case esc:
                exitflag=1;
                break;

            }
        }

    }
    while(exitflag==0);



    return 0;
}
