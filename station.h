#pragma once
#include "vector.h"
#include "ticket.h"
class Station
{
    string fileName;                  //имя файла с базой данных
    vector<Ticket> tickets;           //текущий набор билетов
    vector<Ticket> copyOfTickets;     //копия текущего набора билетов
    int numberOfTickets = 0;          //количество билетов в базе данных

    string deleteFreePlaces(string);    //удаление свободных мест билета
    string addFreePlaces(string);       //добавление свободных мест билета

public:
    Station(string fileName);                // конструктор с параметрами

    //get-методы
    int getNumberOfTickets();
    int getNumberOfFreePlaces(int);
    vector<Ticket> getTickets();
    //set-методы
    void setTickets(vector<Ticket>);

    bool addTicket(Ticket);                  //добавление билета 
    void deleteTicketByNumber(int);          //удаление билета по номеру
    bool deleteTicket(Ticket);               //удаление билета при отсутствии свободных мест
    void downloadFrom();                     //получение набора билетов их файла
    void uploadTo();                         //загрузка в файл
    void showTickets();                      //вывод билетов


    //сортировки
    void dateSort();             //по дате
    void timeSort();             //по времени
    void priceSort();            //по цене
    void destinationSort();      //по пункту назначения
    void departureSort();        //по пункту отправления
    void placesSort();           //по количеству свободных мест

    //фильтр(поиск)
    vector<int> filterDate(string);          //по дате
    vector<int> filterTime(string);          //по времени
    vector<int> filterPlaces(int);           //по свободным местам
    vector<int> filterDestination(string);   //по пункту назначения    
    vector<int> filterDeparture(string);     //по пункту отправления
    vector<int> filterPrice(double);         //по цене


    void createNewTicket();              //создание билета
    void editTicket(int);                //изменение билета
    void buyTicket(int);                 //покупка билета

    //для отмены последнего действия
    void deny(); //отмена последнего действия
    void clone(); // копия текущих данных

};

