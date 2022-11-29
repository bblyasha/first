#pragma once
#include "station.h"
#include <fstream>


string Station::deleteFreePlaces(string msg)//удаление свободных мест билета
{
    for (int i = 0; i < msg.size(); i++)
        if (msg.at(i) == ' ')
            msg.at(i) = '~';
    return msg;
}
string Station::addFreePlaces(string msg)//добавление свободных мест билета
{
    for (int i = 0; i < msg.size(); i++)
        if (msg.at(i) == '~')
            msg.at(i) = ' ';
    return msg;
}

Station::Station(string fileName) { // конструктор с параметрами
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
// добавление билета в текущий набор билетов
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
//удаление билета из набора по его номеру
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

bool Station::deleteTicket(Ticket ticket) //удаление билета при отсутствии свободных мест
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

void Station::downloadFrom() // загрузка билетов из файла
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
void Station::uploadTo() //загрузка в файл
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

void Station::showTickets() //печать билетов
{
    int count = 0;
    for (int i = 0; i < tickets.size(); i++)
    {
        cout << ++count << "/ " << tickets.getByIndex(i) << endl;
    }
}

// сортировки
void Station::dateSort() // сортировка по дате
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
void Station::timeSort() // сортировка по времени
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
void Station::priceSort() // сортировка по цене
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
void Station::destinationSort() // сортировка по пункту назначения
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
void Station::departureSort() // сортировка по пункту отправления
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
void Station::placesSort() // сортировка по свободным местам
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
//фильтр(поиск)
vector<int> Station::filterDate(string data) //поиск по дате
{
    vector<int> result;
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets.getByIndex(i).getDate() == data)
            result.pushBack(i);
    }
    return result;
}
vector<int> Station::filterTime(string data) //поиск по времени
{
    vector<int> result;
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets.getByIndex(i).getTime() == data)
            result.pushBack(i);
    }
    return result;
}
vector<int> Station::filterPlaces(int data)  //поиск по свободным местам
{
    vector<int> result;
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets.getByIndex(i).getFreePlaces() == data)
            result.pushBack(i);
    }
    return result;
}
vector<int> Station::filterDestination(string data)  //поиск по пункту назначения
{
    vector<int> result;
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets.getByIndex(i).getDestination() == data)
            result.pushBack(i);
    }
    return result;
}
vector<int> Station::filterPrice(double data)  //поиск по цене
{
    vector<int> result;
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets.getByIndex(i).getPrice() == data)
            result.pushBack(i);
    }
    return result;
}
vector<int> Station::filterDeparture(string data)  //поиск по пункту отправления
{
    vector<int> result;
    for (int i = 0; i < tickets.size(); i++)
    {
        if (tickets.getByIndex(i).getDeparture() == data)
            result.pushBack(i);
    }
    return result;
}

void Station::createNewTicket() //создание билета
{
    clone();
    Ticket temp;
    while (1)
    {
        string s;
        cout << "Введите пункт отправления" << endl;
        cin >> s;
        if (s.empty())
            cout << "Нужно ввести данные" << endl;
        else
        {
            temp.setDeparture(s);
            break;
        }
    }

    while (1)
    {
        string s;
        cout << "Введите пункт назначения" << endl;
        cin >> s;
        if (s.empty())
            cout << "Нужно ввести данные" << endl;
        else
        {
            temp.setDestination(s);
            break;
        }
    }

    while (1)
    {
        string s;
        cout << "Введите время поездки в формате дд.чч.мм" << endl;
        cin >> s;
        if (s.size() != 8)
            cout << "Неверный формат ввода" << endl;
        else
        {
            temp.setTime(s);
            break;
        }

    }
    while (1) {
        string s;
        cout << "Введите дату отправления в формате дд.мм.гггг" << endl;
        cin >> s;
        if (s.size() != 10)
            cout << "Неверный формат ввода" << endl;
        else {
            temp.setDate(s);
            break;
        }

    }
    while (1)
    {
        string s;
        cout << "Введите цену поездки" << endl;
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
            cout << "Неверный формат ввода" << endl;
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
        cout << "Введите количество свободных мест" << endl;
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
            cout << "Неверный формат ввода" << endl;
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

void Station::editTicket(int ticketNumber) //изменение данных билета
{
    clone();
    char number = '0';
    while (1) {
        cout << "Выберите поле для изменения:" << endl;
        cout << "1) Пункт отправлнеия" << endl;
        cout << "2) Пункт назначения" << endl;
        cout << "3) Время поездки" << endl;
        cout << "4) Дата поездки" << endl;
        cout << "5) Цена поездки" << endl;
        cout << "6) Количество вободных мест" << endl;

        cin >> number;
        if (number < '1' || number>'6')
            cout << "Неверный формат ввода" << endl;
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
            cout << "Введите пункт отправления" << endl;
            cin >> s;
            if (s.empty())
                cout << "Нужно ввести данные" << endl;
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
            cout << "Введите пункт назначения" << endl;
            cin >> s;
            if (s.empty())
                cout << "Нужно ввести данные" << endl;
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
            cout << "Введите время поездки в формате дд.чч.мм" << endl;
            cin >> s;
            if (s.size() != 8)
                cout << "Неверный формат ввода" << endl;
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
            cout << "Введите дату отправления  в формате дд.мм.гггг" << endl;
            cin >> s;
            if (s.size() != 10)
                cout << "Неверный формат ввода" << endl;
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
            cout << "Введите цену поездки" << endl;
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
                cout << "неправильный формат ввода" << endl;
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
            cout << "Введите количество свободных мест" << endl;
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
                cout << "Неверный формат ввода" << endl;
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

void Station::buyTicket(int number) //покупка билета
{
    clone();
    Ticket tmp = tickets.getByIndex(number);
    tmp.setFreePlaces(tmp.getFreePlaces() - 1);
    tickets.pushIn(tmp, number);
}

//для отмены последнего действия
void Station::deny() //отменв последнего действия
{
    tickets = copyOfTickets;
}
void Station::clone() // сохранение текущего состояния 
{
    copyOfTickets = tickets;
}

