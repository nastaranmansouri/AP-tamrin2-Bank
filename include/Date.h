#ifndef DATE_H
#define DATE_H


class Date
{
    public:
        static const unsigned int month_per_year=12;    //number of month per year
        explicit Date(int=1,int=1,int=2020);
        void set_year(int);         //set year
        unsigned int get_year()const;   //return year

        void print() const;     //print Date
        virtual ~Date();

    private:
        unsigned int month; //save month
        unsigned int day;   //save day
        unsigned int year;  //save year

        unsigned int checkDay(int)const;    //Checks 31-day and 30-day months.
};

#endif // DATE_H
