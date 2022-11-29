#pragma once
#include "vector.h"
#include "ticket.h"
class Station
{
    string fileName;                  //��� ����� � ����� ������
    vector<Ticket> tickets;           //������� ����� �������
    vector<Ticket> copyOfTickets;     //����� �������� ������ �������
    int numberOfTickets = 0;          //���������� ������� � ���� ������

    string deleteFreePlaces(string);    //�������� ��������� ���� ������
    string addFreePlaces(string);       //���������� ��������� ���� ������

public:
    Station(string fileName);                // ����������� � �����������

    //get-������
    int getNumberOfTickets();
    int getNumberOfFreePlaces(int);
    vector<Ticket> getTickets();
    //set-������
    void setTickets(vector<Ticket>);

    bool addTicket(Ticket);                  //���������� ������ 
    void deleteTicketByNumber(int);          //�������� ������ �� ������
    bool deleteTicket(Ticket);               //�������� ������ ��� ���������� ��������� ����
    void downloadFrom();                     //��������� ������ ������� �� �����
    void uploadTo();                         //�������� � ����
    void showTickets();                      //����� �������


    //����������
    void dateSort();             //�� ����
    void timeSort();             //�� �������
    void priceSort();            //�� ����
    void destinationSort();      //�� ������ ����������
    void departureSort();        //�� ������ �����������
    void placesSort();           //�� ���������� ��������� ����

    //������(�����)
    vector<int> filterDate(string);          //�� ����
    vector<int> filterTime(string);          //�� �������
    vector<int> filterPlaces(int);           //�� ��������� ������
    vector<int> filterDestination(string);   //�� ������ ����������    
    vector<int> filterDeparture(string);     //�� ������ �����������
    vector<int> filterPrice(double);         //�� ����


    void createNewTicket();              //�������� ������
    void editTicket(int);                //��������� ������
    void buyTicket(int);                 //������� ������

    //��� ������ ���������� ��������
    void deny(); //������ ���������� ��������
    void clone(); // ����� ������� ������

};

