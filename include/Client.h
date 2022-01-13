#include <string>
#include "Date.h"

#ifndef CLIENT_H
#define CLIENT_H

class Client
{
    public:
        Client();
        virtual ~Client();

        void creatAccount(std::string,std::string,int=0);     //This function creates a new account.

        void set_username(std::string);
        std::string get_username()const;   //This function check and set username

        void set_ip(std::string);
        std::string get_ip()const;     //This function check and set IP

        void set_cardNumber(std::string,std::string);        //This function sets the card number.
        unsigned int get_cardNumber()const;           //This function returns card number

        void set_inventory(char,int);       //This function sets the inventory.
        int get_inventory() const;     //This function returns the inventory.
        void deposit(int);              //This function deposits the inventory.
        void withdraw(int);             //This function withdraws the inventory.

        void set_creatAccountDate(int,int,int);        //This function sets the account opening date.
        void set_acounExpirationAuto();         //This function sets the account expiration date.
        void set_acounExpirationManual();       //This function sets the account expiration date.

        void print() const;     //This function displays information.
    private:
        std::string userName;       //Variable to store customer name.
        std::string IP;         //Variable to store client ip.

        unsigned int cardNumber;    //Variable to store card number.
        int Inventory;              //Variable to save account balance.

        Date creatAccountDate;      //Variable to save account opening date.
        Date acounExpiration;       //Variable to save account expiration date.

};
#endif // CLIENT_H
