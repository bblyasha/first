#include "ticket.h"

//get-������
double Ticket::getPrice()
{
    return this->price;
}
string Ticket::getDate()
{
    return this->date;
}
string Ticket::getTime()
{
    return this->time;
}
string Ticket::getDeparture()
{
    return this->departure;
}
string Ticket::getDestination()
{
    return destination;
}
int Ticket::getFreePlaces()
{
    return freePlaces;
}
//set-������
void Ticket::setDeparture(string departure)
{
    this->departure = departure;
}
void Ticket::setDestination(string destination)
{
    this->destination = destination;
}
void Ticket::setPrice(double price)
{
    this->price = price;
}
void Ticket::setDate(string date)
{
    this->date = date;
}
void Ticket::setTime(string time)
{
    this->time = time;
}
void Ticket::setFreePlaces(int places)
{
    this->freePlaces = places;
}
// ������� ������
bool Ticket::buyTicket()
{
    cout << "���������" << endl;

    setFreePlaces(freePlaces - 1);
    return freePlaces > 0;
}
//����������
ostream& operator << (ostream& output, const Ticket& t)
{
    output << "���� ����������� (����.�����.���): " << t.date 
        << "\t����� ������� (���:����:������): " << t.time
        << "\t����� �����������: " << t.departure 
        << "\t����� ����������: " << t.destination 
        << "\t��������� �������: " << t.price 
        << "\t��������� �����: " << t.freePlaces << endl
        << endl;
    return output;
}
bool operator == (const Ticket& tckt1, const Ticket& tckt2)
{
    return tckt1.time == tckt2.time &&
        tckt1.destination == tckt2.destination &&
        tckt1.departure == tckt2.departure &&
        tckt1.date == tckt2.date &&
        tckt1.price == tckt2.price &&
        tckt1.freePlaces == tckt2.freePlaces;
}
