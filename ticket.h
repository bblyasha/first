#pragma once
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

class Ticket {
    string departure;       //����� �����������
    string destination;     //����� ����������
    string date;            //���� �����������
    string time;            //����� �����������
    double price;           //����
    int freePlaces;         //��������� �����

public:
    //get-������ ��� ���� �����
    string getDeparture();
    string getDestination();
    string getDate();
    string getTime();
    double getPrice();
    int getFreePlaces();

    //set-������ ��� ���� �����
    void setDeparture(string);
    void setDestination(string);
    void setDate(string);
    void setTime(string);
    void setPrice(double);
    void setFreePlaces(int);

    bool buyTicket(); // ������� ������

    friend ostream& operator << (ostream&, const Ticket&);     //���������� ��������� <<
    friend bool operator == (const Ticket&, const Ticket&); //���������� ��������� ==
};

