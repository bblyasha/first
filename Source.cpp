#include <iostream>
#include "vector.h"
#include "database.h"
#include "station.h"
#include <algorithm>
#include <conio.h>
#include <Windows.h>


using namespace std;
bool deny = false;

string authorization(Database d)
{
    string login, password;
    unsigned char p;
    do
    {
        system("cls");
        cout << "***********" << endl;
        cout << "�����������" << endl;
        cout << "***********" << endl;

        cout << "��� ������������: ";
        cin >> login;
        if (cin.peek() != '\n')
        {
            cin.clear();
            while (cin.get() != '\n');
        }

        cout << "������: ";
        do
        {
            p = _getch(); //���������� ��������� ������, ��������� � �������, �� �� ������� ��� �� �����
            if (p == 13)
                break;
            if (p == '\b' && !password.empty())
            {
                cout << '\b';
                cout << ' ';
                cout << '\b';
                password.pop_back();
                continue;
            }
            if (isalnum((unsigned char)p))
            {
                cout << '*'; // ��������� ������� ������ ��� ������������������
                password.push_back(p); //������� ������ � ������
            }

        } while (true);

        if ((login == "admin" && password == "admin") || d.checkLog(login, password))
        {
            system("cls");
            return login;
        }
        else {
            cout << endl << "������ ������� �������!" << endl;
            password.clear();
            login.clear();
            system("pause");
        }
    } while (true);
    return login; //�������� login, ����� �����, ��� �����
}

void administratorMenu() // ���� ������ ��������������
{
    system("cls");
    cout << "*************" << endl;
    cout << "�������������" << endl;
    cout << "*************" << endl;
    cout << "����:" << endl;
    cout << "1/ ����������� ��� ������" << endl;
    cout << "2/ ������������� �����" << endl;
    cout << "3/ ����������� ������ �� ���������� ���������" << endl;
    cout << "4/ ����� ����� �� ���������" << endl;
    cout << "5/ ������� �����" << endl;
    cout << "6/ �������� �����" << endl;
    cout << "7/ ������ ���������� ��������" << endl;
    cout << "8/ ����� �� ������� ��������" << endl;
    cout << "0/ ����� �� ����������" << endl;
}
void userWithoutBillets() // ���� ��� user ��� ������ ���� ������
{
    while (true) {
        system("cls");
        cout << "************" << endl;
        cout << "������������" << endl;
        cout << "************" << endl;
        cout << "� ������ ������ ������ �����������" << endl;
        cout << "1/ ����� �� ������� ��������" << endl;
        cout << "2/ ����� �� ����������" << endl;
        char item;
        item = _getch();
        if (item == '1')
        {
            break;
        }
        else if (item == '2')
        {
            exit(0);
        }
        else {
            cout << "������ ������" << endl;
            system("pause");
        }
    }
}
void userMenu()
{
    system("cls");
    cout << "************" << endl;
    cout << "������������" << endl;
    cout << "************" << endl;
    cout << "����:" << endl;
    cout << "1/ ����������� ��� ������" << endl;
    cout << "2/ ������ �����" << endl;
    cout << "3/ ����������� ������ �� ��������� ���������" << endl;
    cout << "4/ ����� ����� �� ���������" << endl;
    cout << "5/ ������� ������ � ������������" << endl;
    cout << "6/ ����� �� ������� ��������" << endl;
    cout << "0/ ����� �� ����������" << endl;
}

void printTickets(Station s) //�������� ���� ������� 
{
    s.downloadFrom();
    system("cls");
    cout << "������ �������:" << endl;
    s.showTickets();
}

Station editTickets(Station s)//�������������� ������
{
    while (true)
    {
        printTickets(s);
        cout << "�������� ����� ������ ������� �� ������ ���������������" << endl;
        cout << "(����� ����� �� �������������� ������� 0)" << endl;
        cout << "����� ������" << endl;
        int numberTicket;
        do {
            cin >> numberTicket;
            if (numberTicket < 0 || numberTicket > s.getNumberOfTickets())
            {
                cout << "������ �����" << endl;
            }
            else
                break;

        } while (true);
        if (numberTicket == 0)
            break;
        s.editTicket(--numberTicket);
        s.uploadTo();
        deny = true;
        system("cls");
    }
    return s;
}

Station sortTickets(Station s) //���������� ������� �� ��������� ��������
{
    while (true)
    {
        printTickets(s);
        cout << "************" << endl;
        cout << "�����������:" << endl;
        cout << "************" << endl;

        cout << "1/ �� ������������ �������" << endl;
        cout << "2/ �� ���� �����������" << endl;
        cout << "3/ �� ���������� ��������� ����" << endl;
        cout << "4/ �� ��������� �������" << endl;
        cout << "5/ �� ������ ����������" << endl;
        cout << "6/ �� ������ �����������" << endl;
        cout << "(����� ����� �� ���������� ������� 0)" << endl;
        char item;
        item = _getch();
        switch (item)
        {
        case'1':
            s.timeSort();
            break;
        case'2':
            s.dateSort();
            break;
        case'3':
            s.placesSort();
            break;
        case'4':
            s.priceSort();
            break;
        case'5':
            s.destinationSort();
            break;
        case'6':
            s.departureSort();
            break;
        default:
            break;
        }
        if (item < '6' && item > '1')
            deny = true;
        else
            break;
    }
    s.clone();
    return s;
}

void filterTickets(Station s) // ����� ������� �� ���������
{
    while (true) {

        printTickets(s);

        cout << "******" << endl;
        cout << "�����:" << endl;
        cout << "******" << endl;

        cout << "1/ �� ������� �������" << endl;
        cout << "2/  �� ���� �������" << endl;
        cout << "3/ �� ���������� ��������� ����" << endl;
        cout << "4/ �� ��������� �������" << endl;
        cout << "5/ �� ������� ��������" << endl;
        cout << "6/ �� ������� �����������" << endl;
        cout << "(����� ����� �� ������, ������� 0)" << endl;
        char item;

        string str;
        int intData;
        double doubleData;
        item = _getch();
        vector<int> numbersOfTickets;
        switch (item)
        {
        case'1':
            while (1)
            {
                cout << "������� ����� ������� � ������� ��.��.��" << endl;
                cin >> str;
                if (str.size() != 8)
                    cout << "�������� ������ �����" << endl;
                else {
                    break;
                }
            }

            numbersOfTickets = s.filterTime(str);
            break;
        case'2':
            while (1)
            {
                cout << "������� ���� �����������  � ������� ��.��.����" << endl;
                cin >> str;
                if (str.size() != 8)
                    cout << "�������� ������ �����" << endl;
                else {
                    break;
                }
            }

            numbersOfTickets = s.filterDate(str);
            break;
        case'3':
            cout << "������� ���������� ��������� ����" << endl;
            cin >> intData;
            numbersOfTickets = s.filterPlaces(intData);
            break;
        case'4':
            cout << "������� ���� �������" << endl;
            cin >> doubleData;
            numbersOfTickets = s.filterPrice(doubleData);
            break;
        case'5':
            while (1) {
                cout << "������� ����� ����������" << endl;
                cin >> str;
                if (str.empty())
                    cout << "����� ������ ������" << endl;
                else
                {
                    break;
                }
            }
            numbersOfTickets = s.filterDestination(str);
            break;
        case'6':
            while (1) {
                cout << "������� ����� �����������" << endl;
                cin >> str;
                if (str.empty())
                    cout << "����� ������ ������" << endl;
                else
                {
                    break;
                }
            }
            numbersOfTickets = s.filterDeparture(str);
            break;
        default:
            break;
        }
        if (item > '6' || item < '1')
            break;
        cout << "******************" << endl;
        cout << "���������� ������:" << endl;
        cout << "******************" << endl;
        if (numbersOfTickets.size() != 0) // ������� ��������� ������
            for (int i = 0; i < numbersOfTickets.size(); i++) {
                cout << s.getTickets().getByIndex(numbersOfTickets.getByIndex(i)) << endl;
            }
        else
            cout << "����� ������� ���" << endl;
        numbersOfTickets.clear();
        cout << endl;
        system("pause");
    }
}

Station deleteTicket(Station s)//�������� ������
{
    while (true)
    {
        printTickets(s);

        cout << "*****************************" << endl;
        cout << "�������� ������ �� ��� ������" << endl;
        cout << "*****************************" << endl;
        cout << "(����� ����� �� ��������, ������� 0):" << endl;
        int numberDelete;
        do {
            cin >> numberDelete;
            if (numberDelete < 0 || numberDelete > s.getNumberOfTickets())
            {
                cout << "������ ������ ������ ������" << endl;
            }
            else
                break;

        } while (true);
        if (numberDelete != 0) {
            s.deleteTicketByNumber(--numberDelete);
            s.uploadTo();
            deny = true;
        }
        if (numberDelete == 0)
            break;
    }
    return s;
}
Station addTicket(Station s) // ���������� ������ 
{
    system("cls");
    printTickets(s);

    cout << "*****************" << endl;
    cout << "���������� ������" << endl;
    cout << "*****************" << endl;
    s.createNewTicket();
    deny = true;
    s.uploadTo();
    return s;
}

Station buyTicket(Station s) // ������� ������
{
    printTickets(s);
    cout << "�������� ����� ������, ������� ������ ������" << endl;
    int numberBy;
    do
    {
        cin >> numberBy;
        if (numberBy < 1 || numberBy > s.getNumberOfTickets())
        {
            cout << "������ �����" << endl;
        }
        else
            break;

    } while (true);
    int countBy;
    cout << "������� ���������� �������, ������� ��� �����" << endl;
    cout << "�� 1 �� " << s.getNumberOfFreePlaces(--numberBy) << endl;

    do
    {
        cin >> countBy;
        if (countBy < 1 || countBy > s.getNumberOfFreePlaces(numberBy))
        {
            cout << "������ ������ ���������� ������" << endl;
        }
        else
            break;

    } while (true);

    for (int i = 0; i < countBy; i++)
    {
        s.buyTicket(numberBy);
    }
    if (s.getNumberOfFreePlaces(numberBy) == 0)
        s.deleteTicketByNumber(numberBy);
    system("cls");
    s.uploadTo();
    return s;
}

Database deleteUser(Database d, string login) {
    d.deleteUser(login);
    d.uploadIn();
    cout << "������� ������������ �����" << endl;
    system("pause");
    return d;
}

string launch(Database d) {
    while (true) {
        system("cls");
        cout << "1/ ����� � ������������ �������" << endl;
        cout << "2/ ������� ����� �������" << endl;
        cout << "3/ �����" << endl;
        char k;
        k = _getch();
        switch (k) {
        case '1': {
            return authorization(d);
            break;
        }
        case '2': {
            unsigned char p;
            string log, pass;
            cout << "������� ��� ������������: ";
            cin >> log;
            if (cin.peek() != '\n') {
                cin.clear();
                while (cin.get() != '\n');
            }

            cout << "������� ������: ";
            do {
                p = _getch(); //���������� ��������� ������, ��������� � �������, �� �� ������� ��� �� �����
                if (p == 13)
                    break;
                if (p == '\b' && !pass.empty()) {
                    cout << '\b';
                    cout << ' ';
                    cout << '\b';
                    pass.pop_back();
                    continue;
                }
                if (isalnum((unsigned char)p)) {
                    cout << '*'; // ��������� ������� ������ ��� ������������������
                    pass.push_back(p); //������� ������ � ������
                }

            } while (true);
            if (d.addUser(User(log, pass))) {
                d.uploadIn();
                cout << endl << "������������ ��������" << endl;
            }
            else
                cout << endl << "������������ � ����� ������ ��� ����������" << endl;
            break;
        }
        case '3':
            exit(0);
        default:
            cout << "������ ������" << endl;
            break;
        }
    }


}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Station s("station.txt");
    Database d("database.txt");
    s.downloadFrom();
    d.downloadFrom();
    while (true)
    {
        string logIn = launch(d); //�����������
        if (logIn == "admin") { //����� �����
            deny = false;
            bool end = false;
            while (true)
            {
                if (end)
                    break;
                administratorMenu();
                char choise;
                choise = _getch();
                if (choise == '8') {
                    end = true;
                    deny = false;
                    break;
                }
                switch (choise)
                {
                case '0': exit(0);
                case '1':
                    printTickets(s);
                    system("pause");
                    break;
                case '2':
                    s = editTickets(s);
                    break;
                case '3':
                    s = sortTickets(s);
                    break;
                case '4':
                    filterTickets(s);
                    break;
                case '5':
                    s.clone();
                    s = deleteTicket(s);
                    break;
                case'6':
                    s.clone();
                    s = addTicket(s);
                    break;
                case'7':
                    if (deny == true)
                    {
                        s.deny();
                        s.uploadTo();
                    }
                    break;

                default:
                    break;
                }

            }
        }
        else if (s.getNumberOfTickets() == 0)
        {
            userWithoutBillets();
        }
        else if (s.getNumberOfTickets() != 0)
        {
            bool end = false;
            while (true) {
                if (end)
                    break;
                userMenu();
                char choise;
                choise = _getch();
                if (choise == '6')
                    break;

                switch (choise)
                {
                case '0': exit(0);
                case '1':
                    printTickets(s);
                    system("pause");
                    break;
                case '2':
                    s = buyTicket(s);
                    break;
                case '3':
                    s = sortTickets(s);
                    break;
                case '4':
                    filterTickets(s);
                    break;
                case '5':
                    d = deleteUser(d, logIn);
                    end = true;
                    break;
                default:
                    break;
                }
            }
        }
    }
    return 0;
}