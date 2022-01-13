#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <iomanip>

#include "Client.h"
#include "Date.h"

using namespace std;

void commands();
void add_acount(string,string);     //Function to create a new account
void renew(string,string);      //Function for account renewal
void invent(string,string,int);     //Function to reduce and increase inventory
void transfer(string,string,string,int);        //Function for transferring money


int main()
{
    cout << "--------Welcome to the bank--------"<<endl;
    cout<<"Please use the guide below to enter commands." << endl;
    cout<<"_____________________________________________________________"<<endl<<endl;
    commands();
    cout<<"_____________________________________________________________"<<endl;
    do
    {
        string str1="",us="",ipAccount="";
        int money=0;
        cout<<">>> ";
        getline(cin,str1);
        cout<<str1<<endl;

        if(str1.substr(0,6)=="create")      //In this condition, if the input value is "create"
        {                                   // by the user, the "add" function will be called
            str1.erase(0,7);                //after separating the components.
            auto pos=str1.find(":");
            us=str1.substr(0,pos);
            ipAccount=str1.substr(pos+1);
            add_acount(us,ipAccount);

        }

        if(str1.substr(0,7)=="renewal")     //In this condition, if the input value is "renewal"
        {                                   //by the user, the "renew" function will be called
           str1.erase(0,8);                 //after separating the components.
           auto pos=str1.find(":");
           us=str1.substr(0,pos);
           ipAccount=str1.substr(pos+1);
           renew(us,ipAccount);

        }

        if(str1.substr(0,7)=="deposit")     //In this condition, if the input value is "deposit"
        {                                   //by the user, the "invent" function will be called
           str1.erase(0,8);                 //after separating the components.
           auto pos=str1.find(":");
           us=str1.substr(0,pos);
           str1.erase(0,pos+1);
           auto pos2=str1.find(":");
           ipAccount=str1.substr(0,pos2);
           str1.erase(0,pos2+1);
           money=stoi(str1);
          invent(us,ipAccount,money);
        }

        if(str1.substr(0,8)=="withdraw")    //In this condition, if the input value is "withdraw"
        {                                   //by the user, the "invent" function is called after
           str1.erase(0,9);                 //separating the components.
           auto pos=str1.find(":");
           us=str1.substr(0,pos);
           str1.erase(0,pos+1);
           auto pos2=str1.find(":");
           ipAccount=str1.substr(0,pos2);
           str1.erase(0,pos2+1);
           money=stoi(str1);
          invent(us,ipAccount,money);
        }

        if(str1.substr(0,8)=="transfer")    //In this condition, if the input value is "transfer"
        {                                   //by the user, the "transfer" function will be called
           string us2="";                   //after separating the components.
           str1.erase(0,9);
           auto pos=str1.find(":");
           us=str1.substr(0,pos);
           str1.erase(0,pos+1);
           auto pos2=str1.find(":");
           ipAccount=str1.substr(0,pos2);
           str1.erase(0,pos2+1);
           auto pos3=str1.find(":");
           us2=str1.substr(0,pos3);
           str1.erase(0,pos3+1);
           money=stoi(str1);
           transfer(us,ipAccount,us2,money);
        }

   }while(1);

    return 0;
}
//end of main
////////////////////////////////////////////////////////////
void commands()
{
   cout<<"------------COMMANDS:------------"<<endl;
   cout<<"Enter the following command to CREATE A NEW ACCOUNT:"<<endl;
   cout<<"\tcreate username:uaserIP"<<endl<<endl;
   cout<<"Enter the following command to RENEW YOUR ACCOUNT:"<<endl;
   cout<<"\trenew username:uaserIP"<<endl<<endl;
   cout<<"Enter the following command to WITHDARW FROME THE ACCOUNT:"<<endl;
   cout<<"\twithdraw username:uaserIP:money"<<endl<<endl;
   cout<<"Enter the following command to DEPOSIT:"<<endl;
   cout<<"\tdeposit username:uaserIP:money"<<endl<<endl;
   cout<<"Enter the following command to TRANSFER:"<<endl;
   cout<<"\tcreate senderUsername:senderUserIP:receiver:money"<<endl<<endl;

}
////////////////////////////////////////////////////////////
void add_acount(string a,string b)
{
    Client cl;  //Creates an object
    ofstream outFile;   //Opens a file to write account information in.
	outFile.open("Clients.dat",ios::binary|ios::app);
	try
	{
	    cl.creatAccount(a,b);   //call createAccount from class Client
	}
	catch (invalid_argument &e)
	{
	    cout<<endl<<"Exception occurred: " << e.what() << endl;
	}
	outFile.write(reinterpret_cast<char *> (&cl), sizeof(Client)); //Close file
	outFile.close();
}

////////////////////////////////////////////////////////////
void renew(string us,string ip)
{
    Client c2;  ///Creates an object
    //char ch;
    fstream File;
    bool found=false;
    File.open("Clients.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)  //Checks the username and IP in the file.
	{
	    File.read(reinterpret_cast<char *> (&c2), sizeof(Client));
	    if(c2.get_username()==us || c2.get_ip()==ip)
        {
           try
           {
               c2.set_acounExpirationManual();  //call set_acounExpirationManual from class Client
           }
           catch (invalid_argument &e)
           {
               cout<<endl<<"Exception occurred: " << e.what() << endl;
           }
        }
        int pos=(-1)*static_cast<int>(sizeof(c2));
        File.seekp(pos,ios::cur);
        File.write(reinterpret_cast<char *> (&c2), sizeof(Client));
        cout<<endl<<"\t\t Record Updated"<<endl;
        found=true;
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

////////////////////////////////////////////////////////////
void invent(string us,string ip,int mny)
{
    Client c3;  /////Creates an object
    char ch;
    cout<<"DEPOSIT OR WITHDRAW:(d,w)\t";    //Asks the user to select withdrawal or deposit.
    cin>>ch;
    cout<<endl;
    fstream File;
    bool found=false;
    File.open("Clients.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)  //Checks the username and IP in the file.
	{
	    File.read(reinterpret_cast<char *> (&c3), sizeof(Client));
	    if(c3.get_username()==us || c3.get_ip()==ip)
        {
             try
           {
                c3.set_inventory(ch,mny);  //call set_inventory from class Client
           }
           catch (invalid_argument &e)
           {
               cout<<endl<<"Exception occurred: " << e.what() << endl;
           }

        }
        int pos=(-1)*static_cast<int>(sizeof(c3));
        File.seekp(pos,ios::cur);
        File.write(reinterpret_cast<char *> (&c3), sizeof(Client));
        cout<<endl<<"\t\t Record Updated"<<endl;
        found=true;
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

////////////////////////////////////////////////////////////
void transfer(string us,string us2,string ip,int mny)
{
    Client c4;  /////Creates an object
    Client c5;  /////Creates an object

    fstream File;
    bool found=false;
    File.open("Clients.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
	    File.read(reinterpret_cast<char *> (&c4), sizeof(Client));
	    if((c4.get_username()==us || c4.get_ip()==ip)&&(c5.get_username()==us2))    //Checks the username and IP in the file.
        {
              try
           {
               c4.set_inventory('w',mny);   //call set_inventory from class Client for withdraw
               c5.set_inventory('d',mny);  //call set_inventory from class Client for deposit
           }
           catch (invalid_argument &e)
           {
               cout<<endl<<"Exception occurred: " << e.what() << endl;
           }


        }
        int pos=(-1)*static_cast<int>(sizeof(c4));
        File.seekp(pos,ios::cur);
        File.write(reinterpret_cast<char *> (&c4), sizeof(Client));
        cout<<endl<<"\t\t Record Updated"<<endl;
        found=true;
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}
////////////////////////////////////////////////////////////
