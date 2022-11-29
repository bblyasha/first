#pragma once
#include "station.h"
#include <fstream>


string Station::deleteFreePlaces(string msg)//�������� ��������� ���� ������
{
    for (int i = 0; i < msg.size(); i++)
        if (msg.at(i) == ' ')
            msg.at(i) = '~';
    return msg;
}
string Station::addFreePlaces(string msg)//���������� ��������� ���� ������
{
    for (int i = 0; i < msg.size(); i++)
        if (msg.at(i) == '~')
            msg.at(i) = ' ';
    return msg;
}

Station::Station(string fileName) { // ����������� � �����������
    this->fileName = fileName;
}

int Station::getNumberOfTickets()
{
    return numberOfTickets;
}
int Station::getNumberOfFreePlaces(int number)
{
    return tickets.getByIndex(number).getFreePlaces();
}
vector<Ticket> Station::getTickets()
{
    return tickets;
}

void Station::setTickets(vector<Ticket> tickets)
{
    this->tickets = tickets;
}
// ���������� ������ � ������� ����� �������
bool Station::addTicket(Ticket ticket)
{
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets.getByIndex(i) == ticket)
            return false;
    }
    tickets.pushBack(ticket);
    numberOfTickets++;
    return true;
}
//�������� ������ �� ������ �� ��� ������
void Station::deleteTicketByNumber(int number)
{
    clone();
    bool deleted = false;
    for (int i = 0; i < tickets.size(); i++)
    {
        if (i == number)
        {
            deleted = true;
        }
        if (deleted == true)
        {
            if (i == tickets.size() - 1)
                break;
            Ticket temp = tickets.getByIndex(i + 1);
            tickets.pushIn(tickets.getByIndex(i), i + 1);
            tickets.pushIn(temp, i);
        }
    }
    if (deleted)
    {
        tickets.popBack();
        numberOfTickets--;
    }
}

bool Station::deleteTicket(Ticket ticket) //�������� ������ ��� ���������� ��������� ����
{
    bool deleted = false;
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets.getByIndex(i) == ticket)
        {
            deleted = true;
        }
        if (deleted == true)
        {
            if (i == tickets.size() - 1)
                break;
            Ticket temp = tickets.getByIndex(i + 1);
            tickets.pushIn(tickets.getByIndex(i), i + 1);
            tickets.pushIn(temp, i);
        }
    }
    if (deleted)
    {
        tickets.popBack();
        numberOfTickets--;
        return true;
    }
    return false;
}

void Station::downloadFrom() // �������� ������� �� �����
{
    ifstream fin(fileName);
    while (1) {
        Ticket temp;
        for (int i = 0; i < 6; i++)
        {
            string s;
            fin >> s;
            if (fin.eof())
                break;
            switch (i)
            {
            case 0:
                temp.setDeparture(addFreePlaces(s));
                break;
            case 1:
                temp.setDestination(addFreePlaces(s));
                break;
            case 2:
                temp.setTime(s);
                break;
            case 3:
                temp.setDate(s);
                break;
            case 4:
                temp.setPrice(stod(s));
                break;
            case 5:
                temp.setFreePlaces(stoi(s));
                break;
            default:
                break;
            }
        }
        if (fin.eof())
            break;
        addTicket(temp);
        numberOfTickets++;
    }
    fin.close();
}
void Station::uploadTo() //�������� � ����
{
    ofstream fin(fileName);
    for (int i = 0; i < tickets.size(); i++)
    {
        fin << deleteFreePlaces(tickets.getByIndex(i).getDeparture()) << ' ';
        fin << deleteFreePlaces(tickets.getByIndex(i).getDestination()) << ' ';
        fin << tickets.getByIndex(i).getTime() << ' ';
        fin << tickets.getByIndex(i).getDate() << ' ';
        fin << to_string(tickets.getByIndex(i).getPrice()) << ' ';
        fin << to_string(tickets.getByIndex(i).getFreePlaces()) << ' ';
        fin << '\n';
    }
    fin.close();
}

void Station::showTickets() //������ �������
{
    int count = 0;
    for (int i = 0; i < tickets.size(); i++)
    {
        cout << ++count << "/ " << tickets.getByIndex(i) << endl;
    }
}

// ����������
void Station::dateSort() // ���������� �� ����
{
    int size = tickets.size();
    bool done;
    for (int i = 1; i < size; i++)
    {
        done = true;
        for (int j = 0; j < size - i; j++)
        {
            if (tickets.getByIndex(j).getDate() > tickets.getByIndex(j + 1).getDate())
            {
                Ticket temp = tickets.getByIndex(j);
                tickets.pushIn(tickets.getByIndex(j + 1), j);
                tickets.pushIn(temp, j + 1);
                done = false;
            }
        }
        if (done)
            return;
    }
}
void Station::timeSort() // ���������� �� �������
{
    int size = tickets.size();
    bool done;
    for (int i = 1; i < size; i++)
    {
        done = true;
        for (int j = 0; j < size - i; j++)
        {
            if (tickets.getByIndex(j).getTime() > tickets.getByIndex(j + 1).getTime())
            {
                Ticket temp = tickets.getByIndex(j);
                tickets.pushIn(tickets.getByIndex(j + 1), j);
                tickets.pushIn(temp, j + 1);
                done = false;
            }
        }
        if (done)
            return;
    }
}
void Station::priceSort() // ���������� �� ����
{
    int size = tickets.size();
    bool done;
    for (int i = 1; i < size; i++)
    {
        done = true;
        for (int j = 0; j < size - i; j++)
        {
            if (tickets.getByIndex(j).getPrice() > tickets.getByIndex(j + 1).getPrice())
            {
                Ticket temp = tickets.getByIndex(j);
                tickets.pushIn(tickets.getByIndex(j + 1), j);
                tickets.pushIn(temp, j + 1);
                done = false;
            }
        }
        if (done)
            return;
    }
}
void Station::destinationSort() // ���������� �� ������ ����������
{
    int size = tickets.size();
    bool done;
    for (int i = 1; i < size; i++)
    {
        done = true;
        for (int j = 0; j < size - i; j++)
        {
            if (tickets.getByIndex(j).getDestination() > tickets.getByIndex(j + 1).getDestination())
            {
                Ticket temp = tickets.getByIndex(j);
                tickets.pushIn(tickets.getByIndex(j + 1), j);
                tickets.pushIn(temp, j + 1);
                done = false;
            }
        }
        if (done)
            return;
    }
}
void Station::departureSort() // ���������� �� ������ �����������
{
    int size = tickets.size();
    bool done;
    for (int i = 1; i < size; i++)
    {
        done = true;
        for (int j = 0; j < size - i; j++)
        {
            if (tickets.getByIndex(j).getDeparture() > tickets.getByIndex(j + 1).getDeparture())
            {
                Ticket temp = tickets.getByIndex(j);
                tickets.pushIn(tickets.getByIndex(j + 1), j);
                tickets.pushIn(temp, j + 1);
                done = false;
            }
        }
        if (done)
            return;
    }
}
void Station::placesSort() // ���������� �� ��������� ������
{
    int size = tickets.size();
    bool done;
    for (int i = 1; i < size; i++)
    {
        done = true;
        for (int j = 0; j < size - i; j++)
        {
            if (tickets.getByIndex(j).getFreePlaces() > tickets.getByIndex(j + 1).getFreePlaces())
            {
                Ticket temp = tickets.getByIndex(j);
                tickets.pushIn(tickets.getByIndex(j + 1), j);
                tickets.pushIn(temp, j + 1);
                done = false;
            }
        }
        if (done)
            return;
    }
}
//������(�����)
vector<int> Station::filterDate(string data) //����� �� ����
{
    vector<int> result;
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets.getByIndex(i).getDate() == data)
            result.pushBack(i);
    }
    return result;
}
vector<int> Station::filterTime(string data) //����� �� �������
{
    vector<int> result;
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets.getByIndex(i).getTime() == data)
            result.pushBack(i);
    }
    return result;
}
vector<int> Station::filterPlaces(int data)  //����� �� ��������� ������
{
    vector<int> result;
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets.getByIndex(i).getFreePlaces() == data)
            result.pushBack(i);
    }
    return result;
}
vector<int> Station::filterDestination(string data)  //����� �� ������ ����������
{
    vector<int> result;
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets.getByIndex(i).getDestination() == data)
            result.pushBack(i);
    }
    return result;
}
vector<int> Station::filterPrice(double data)  //����� �� ����
{
    vector<int> result;
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets.getByIndex(i).getPrice() == data)
            result.pushBack(i);
    }
    return result;
}
vector<int> Station::filterDeparture(string data)  //����� �� ������ �����������
{
    vector<int> result;
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets.getByIndex(i).getDeparture() == data)
            result.pushBack(i);
    }
    return result;
}

void Station::createNewTicket() //�������� ������
{
    clone();
    Ticket temp;
    while (1)
    {
        string s;
        cout << "������� ����� �����������" << endl;
        cin >> s;
        if (s.empty())
            cout << "����� ������ ������" << endl;
        else
        {
            temp.setDeparture(s);
            break;
        }
    }

    while (1)
    {
        string s;
        cout << "������� ����� ����������" << endl;
        cin >> s;
        if (s.empty())
            cout << "����� ������ ������" << endl;
        else
        {
            temp.setDestination(s);
            break;
        }
    }

    while (1)
    {
        string s;
        cout << "������� ����� ������� � ������� ��.��.��" << endl;
        cin >> s;
        if (s.size() != 8)
            cout << "�������� ������ �����" << endl;
        else
        {
            temp.setTime(s);
            break;
        }

    }
    while (1) {
        string s;
        cout << "������� ���� ����������� � ������� ��.��.����" << endl;
        cin >> s;
        if (s.size() != 10)
            cout << "�������� ������ �����" << endl;
        else {
            temp.setDate(s);
            break;
        }

    }
    while (1)
    {
        string s;
        cout << "������� ���� �������" << endl;
        cin >> s;
        bool check = true;
        for (int i = 0; i < s.size(); i++) {
            if ((s.at(i) < '0' || s.at(i) > '9') && s.at(i) != '.') {
                check = false;
                break;
            }
        }
        if (!check)
        {
            cout << "�������� ������ �����" << endl;
            check = true;
        }
        else
        {
            temp.setPrice(stod(s));
            break;
        }

    }
    while (1)
    {
        string s;
        cout << "������� ���������� ��������� ����" << endl;
        cin >> s;
        bool check = true;
        for (int i = 0; i < s.size(); i++) {
            if ((s.at(i) < '0' || s.at(i) > '9')) {
                check = false;
                break;
            }
        }
        if (!check)
        {
            cout << "�������� ������ �����" << endl;
            check = true;
        }
        else
        {
            temp.setFreePlaces(stoi(s));
            break;
        }
    }
    addTicket(temp);
}

void Station::editTicket(int ticketNumber) //��������� ������ ������
{
    clone();
    char number = '0';
    while (1) {
        cout << "�������� ���� ��� ���������:" << endl;
        cout << "1) ����� �����������" << endl;
        cout << "2) ����� ����������" << endl;
        cout << "3) ����� �������" << endl;
        cout << "4) ���� �������" << endl;
        cout << "5) ���� �������" << endl;
        cout << "6) ���������� �������� ����" << endl;

        cin >> number;
        if (number < '1' || number>'6')
            cout << "�������� ������ �����" << endl;
        else
            break;
    }

    Ticket tmp(tickets.getByIndex(ticketNumber));

    switch (number)
    {
    case '1':
        while (1)
        {
            string s;
            cout << "������� ����� �����������" << endl;
            cin >> s;
            if (s.empty())
                cout << "����� ������ ������" << endl;
            else
            {
                tmp.setDeparture(s);
                tickets.pushIn(tmp, ticketNumber);
                break;
            }
        }
        break;
    case '2':
        while (1)
        {
            string s;
            cout << "������� ����� ����������" << endl;
            cin >> s;
            if (s.empty())
                cout << "����� ������ ������" << endl;
            else
            {
                tmp.setDestination(s);
                tickets.pushIn(tmp, ticketNumber);
                break;
            }
        }
        break;
    case '3':
        while (1)
        {
            string s;
            cout << "������� ����� ������� � ������� ��.��.��" << endl;
            cin >> s;
            if (s.size() != 8)
                cout << "�������� ������ �����" << endl;
            else
            {
                tmp.setTime(s);
                tickets.pushIn(tmp, ticketNumber);
                break;
            }
        }
        break;
    case '4':
        while (1) {
            string s;
            cout << "������� ���� �����������  � ������� ��.��.����" << endl;
            cin >> s;
            if (s.size() != 10)
                cout << "�������� ������ �����" << endl;
            else
            {
                tmp.setDate(s);
                tickets.pushIn(tmp, ticketNumber);
                break;
            }
        }
        break;
    case '5':
        while (1) {
            string s;
            cout << "������� ���� �������" << endl;
            cin >> s;
            bool check = true;
            for (int i = 0; i < s.size(); i++)
            {
                if ((s.at(i) < '0' || s.at(i) > '9') && s.at(i) != '.')
                {
                    check = false;
                    break;
                }
            }
            if (!check)
            {
                cout << "������������ ������ �����" << endl;
                check = true;
            }
            else
            {
                tmp.setPrice(stod(s));
                tickets.pushIn(tmp, ticketNumber);
                break;
            }
        }
        break;
    case '6':
        while (1) {
            cout << "������� ���������� ��������� ����" << endl;
            string s;
            cin >> s;
            bool check = true;
            for (int i = 0; i < s.size(); i++)
            {
                if ((s.at(i) < '0' || s.at(i) > '9'))
                {
                    check = false;
                    break;
                }
            }
            if (!check)
            {
                cout << "�������� ������ �����" << endl;
                check = true;
            }
            else {
                tmp.setFreePlaces(stoi(s));
                tickets.pushIn(tmp, ticketNumber);
                break;
            }
        }
        break;
    default: break;
    }
}

void Station::buyTicket(int number) //������� ������
{
    clone();
    Ticket tmp = tickets.getByIndex(number);
    tmp.setFreePlaces(tmp.getFreePlaces() - 1);
    tickets.pushIn(tmp, number);
}

//��� ������ ���������� ��������
void Station::deny() //������ ���������� ��������
{
    tickets = copyOfTickets;
}
void Station::clone() // ���������� �������� ��������� 
{
    copyOfTickets = tickets;
}

