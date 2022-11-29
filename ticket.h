#pragma once
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

class Ticket {
    string departure;       //пункт отправления
    string destination;     //пункт назначения
    string date;            //дата отправление
    string time;            //время отправления
    double price;           //цена
    int freePlaces;         //свободные места

public:
    //get-методы для всех полей
    string getDeparture();
    string getDestination();
    string getDate();
    string getTime();
    double getPrice();
    int getFreePlaces();

    //set-методы для всех полей
    void setDeparture(string);
    void setDestination(string);
    void setDate(string);
    void setTime(string);
    void setPrice(double);
    void setFreePlaces(int);

    bool buyTicket(); // покупка билета

    friend ostream& operator << (ostream&, const Ticket&);     //перегрузка оператора <<
    friend bool operator == (const Ticket&, const Ticket&); //перегрузка оператора ==
};

