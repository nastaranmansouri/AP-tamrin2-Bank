//Client.cpp definition

#include <iostream>
#include <string>
#include <cstdlib>      //for rand & srand
#include <ctime>        //for time

#include "Client.h"

using namespace std;


Client::Client()
{
    //ctor
}

Client::~Client()
{
    //dtor
}

///////////////////////////////////////////////////
void Client::creatAccount(string u,string ip,int a)
{
    set_username(u);        //call set_username
    set_ip(ip);             //call set_ip
    set_cardNumber(u,ip);   //call set_cardNumber
    int m,d,y;
    cout<<"Enter the day, month and year of account opening, respectively."<<endl;
    cin>>d>>m>>y;
    set_creatAccountDate(d,m,y);        //call set_createAccountDate
}
///////////////////////////////////////////////////
void Client::set_username(string name)
{

        if(name.size()<=25)     //check size of username an substr the username if it's longer than 25 carachture
        {
            userName=name;
        }
        else
        {
            userName = name.substr( 0, 25 );
            cerr << "Name :" << name << "\" exceeds maximum length (25).\n"<< "Limiting username to first 25 characters.\n" << endl;

        }

}
///////////////////////////////////////////////////
string Client::get_username()const
{
    return userName;
}

///////////////////////////////////////////////////
void Client::set_ip(string ip)
{
    string st,ipp;
    ipp=ip;
    bool temp=true;

    for(int i=0;i<4;i++)        //In this loop, it is checked that the different
     {                          //parts of the ip are greater than 0 and smaller
                                 //than 255, otherwise it will throw an exception.
        auto pos=ipp.find(".");
        st=ipp.substr(0,pos);
        if(!(stoi(st)>=0 && stoi(st)<=255))
        {
            temp=false;
            throw invalid_argument("The IP entered is incorrect.");
        }

        ipp.erase(0,pos+1);

    }
    if (temp==true)
        IP=ip;
    else
        cout<<"We have incorrect IP"<<endl;
}
///////////////////////////////////////////////////
string Client::get_ip()const
{
    return IP;
}
///////////////////////////////////////////////////
void Client::set_cardNumber(string us,string ip)
{
    srand( static_cast<unsigned int>( time( 0 ) ) );        //Here random 4-digit numbers are
    while(1)                                                //created for the card number.
    {
        unsigned int number = 1000 + rand() %10000 ;
        if(number>=1000)
        {
            cardNumber=number;
            break;
        }
        else
            continue;

    }

}
///////////////////////////////////////////////////
unsigned int Client::get_cardNumber()const
{
    return cardNumber;
}
///////////////////////////////////////////////////
void Client::set_inventory(char ch,int m)
{
    //Is it checked here that it should be withdrawn from the account or added to it?
    switch (ch)
    {
    case 'w':
        withdraw(m);        //call withdraw func
        break;
    case 'd':
        deposit(m);         //call deposit func
        break;
    default:
        throw invalid_argument("The input value must be p or d.");
    }
    cout<<endl;

}
///////////////////////////////////////////////////
int Client::get_inventory()const
{
    return Inventory;
}
///////////////////////////////////////////////////
void Client::deposit(int mon)
{
    Inventory+=mon;
}
///////////////////////////////////////////////////
void Client::withdraw(int mon)
{
    int balance=get_inventory()- mon;
    if(balance<0)           //Here it is checked that if an exception is made
       {                    //by withdrawing from the account, an exception will be thrown
          throw invalid_argument("The input amount is more than the inventory.");
       }
       else
       {
           Inventory-=mon;
       }

}
///////////////////////////////////////////////////
void Client::set_creatAccountDate(int dy,int mn, int yr)
{
    Date d(dy,mn,yr);           //Input values ​​taken from the user were stored in
    creatAccountDate=d;         //the variable. The automatic expiration function
                                //is then selected to set the expiration date.
    set_acounExpirationAuto();
    cout<<endl;

}
///////////////////////////////////////////////////
void Client::set_acounExpirationAuto()
{
                                                //In this function, by placing the available values ​​
    acounExpiration=creatAccountDate;           //of the opening variable in the expiration variable,
    acounExpiration.set_year(creatAccountDate.get_year()+2);// the year value of the expiration variable increases by 2 years.
    cout<<"Account expiration date:";
    acounExpiration.print();
    cout<<endl;
}
///////////////////////////////////////////////////
void Client::set_acounExpirationManual()
{
    int y=acounExpiration.get_year();       //This function is to extend the expiration.
    acounExpiration.set_year(y+2);
    set_inventory('w',5000);
    cout<<"Account expiration new date:";
    acounExpiration.print();
    cout<<endl;
}
///////////////////////////////////////////////////
void Client::print() const
{
    cout<<"Account No. : "<<IP<<endl;       //By calling this function, customer information is displayed.
	cout<<"Account Holder Name : "<<userName<<endl;
	cout<<"Balance amount : "<<Inventory<<endl;
}
///////////////////////////////////////////////////
