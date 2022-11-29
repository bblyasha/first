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
        cout << "АВТОРИЗАЦИЯ" << endl;
        cout << "***********" << endl;

        cout << "Имя пользователя: ";
        cin >> login;
        if (cin.peek() != '\n')
        {
            cin.clear();
            while (cin.get() != '\n');
        }

        cout << "Пароль: ";
        do
        {
            p = _getch(); //возвращаем очередной символ, считанный с консоли, но не выводим его на экран
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
                cout << '*'; // маскируем символы пароля для конфиденциальности
                password.push_back(p); //заносим символ в пароль
            }

        } while (true);

        if ((login == "admin" && password == "admin") || d.checkLog(login, password))
        {
            system("cls");
            return login;
        }
        else {
            cout << endl << "Данные введены неверно!" << endl;
            password.clear();
            login.clear();
            system("pause");
        }
    } while (true);
    return login; //забираем login, чтобы знать, кто вошёл
}

void administratorMenu() // меню выбора администратора
{
    system("cls");
    cout << "*************" << endl;
    cout << "АДМИНИСТРАТОР" << endl;
    cout << "*************" << endl;
    cout << "Меню:" << endl;
    cout << "1/ просмотреть все билеты" << endl;
    cout << "2/ редактировать билет" << endl;
    cout << "3/ сортировать билеты по выбранному параметру" << endl;
    cout << "4/ найти билет по параметру" << endl;
    cout << "5/ удалить билет" << endl;
    cout << "6/ добавить билет" << endl;
    cout << "7/ отмена последнего действия" << endl;
    cout << "8/ выйти из личного кабинета" << endl;
    cout << "0/ выйти из приложения" << endl;
}
void userWithoutBillets() // вход под user при пустой базе данных
{
    while (true) {
        system("cls");
        cout << "************" << endl;
        cout << "ПОЛЬЗОВАТЕЛЬ" << endl;
        cout << "************" << endl;
        cout << "В данный момент билеты отсутствуют" << endl;
        cout << "1/ выйти из личного кабинета" << endl;
        cout << "2/ выйти из приложения" << endl;
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
            cout << "ошибка выбора" << endl;
            system("pause");
        }
    }
}
void userMenu()
{
    system("cls");
    cout << "************" << endl;
    cout << "ПОЛЬЗОВАТЕЛЬ" << endl;
    cout << "************" << endl;
    cout << "Меню:" << endl;
    cout << "1/ просмотреть все билеты" << endl;
    cout << "2/ купить билет" << endl;
    cout << "3/ сортировать билеты по заданному параметру" << endl;
    cout << "4/ найти билет по параметру" << endl;
    cout << "5/ удалить данные о пользователе" << endl;
    cout << "6/ выйти из личного кабинета" << endl;
    cout << "0/ выход из приложения" << endl;
}

void printTickets(Station s) //просмотр всех билетов 
{
    s.downloadFrom();
    system("cls");
    cout << "Список билетов:" << endl;
    s.showTickets();
}

Station editTickets(Station s)//редактирование билета
{
    while (true)
    {
        printTickets(s);
        cout << "Выберите номер билета который вы хотите отредактировать" << endl;
        cout << "(чтобы выйти из редактирования нажмите 0)" << endl;
        cout << "Выбор билета" << endl;
        int numberTicket;
        do {
            cin >> numberTicket;
            if (numberTicket < 0 || numberTicket > s.getNumberOfTickets())
            {
                cout << "Ошибка ввода" << endl;
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

Station sortTickets(Station s) //сортировка билетов по заданному критерию
{
    while (true)
    {
        printTickets(s);
        cout << "************" << endl;
        cout << "Сортировать:" << endl;
        cout << "************" << endl;

        cout << "1/ по длительности поездки" << endl;
        cout << "2/ по дате отправления" << endl;
        cout << "3/ по количеству свободных мест" << endl;
        cout << "4/ по стоимости поездки" << endl;
        cout << "5/ по пункту назначения" << endl;
        cout << "6/ по пункту отправления" << endl;
        cout << "(чтобы выйти из сортировки нажмите 0)" << endl;
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

void filterTickets(Station s) // поиск билетов по параметру
{
    while (true) {

        printTickets(s);

        cout << "******" << endl;
        cout << "Поиск:" << endl;
        cout << "******" << endl;

        cout << "1/ по времени поездки" << endl;
        cout << "2/  по дате поездки" << endl;
        cout << "3/ по количеству свободных мест" << endl;
        cout << "4/ по стоимости поездки" << endl;
        cout << "5/ по станции прибытия" << endl;
        cout << "6/ по станции отправления" << endl;
        cout << "(чтобы выйти из поиска, нажмите 0)" << endl;
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
                cout << "Введите время поездки в формате дд.чч.мм" << endl;
                cin >> str;
                if (str.size() != 8)
                    cout << "Неверный формат ввода" << endl;
                else {
                    break;
                }
            }

            numbersOfTickets = s.filterTime(str);
            break;
        case'2':
            while (1)
            {
                cout << "Введите дату отправления  в формате дд.мм.гггг" << endl;
                cin >> str;
                if (str.size() != 8)
                    cout << "Неверный формат ввода" << endl;
                else {
                    break;
                }
            }

            numbersOfTickets = s.filterDate(str);
            break;
        case'3':
            cout << "Введите количество свободных мест" << endl;
            cin >> intData;
            numbersOfTickets = s.filterPlaces(intData);
            break;
        case'4':
            cout << "Введите цену проезда" << endl;
            cin >> doubleData;
            numbersOfTickets = s.filterPrice(doubleData);
            break;
        case'5':
            while (1) {
                cout << "Введите пункт назначения" << endl;
                cin >> str;
                if (str.empty())
                    cout << "Нужно ввести данные" << endl;
                else
                {
                    break;
                }
            }
            numbersOfTickets = s.filterDestination(str);
            break;
        case'6':
            while (1) {
                cout << "Введите пункт отправления" << endl;
                cin >> str;
                if (str.empty())
                    cout << "Нужно ввести данные" << endl;
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
        cout << "Результаты поиска:" << endl;
        cout << "******************" << endl;
        if (numbersOfTickets.size() != 0) // выводим результат поиска
            for (int i = 0; i < numbersOfTickets.size(); i++) {
                cout << s.getTickets().getByIndex(numbersOfTickets.getByIndex(i)) << endl;
            }
        else
            cout << "Таких билетов нет" << endl;
        numbersOfTickets.clear();
        cout << endl;
        system("pause");
    }
}

Station deleteTicket(Station s)//удаление билета
{
    while (true)
    {
        printTickets(s);

        cout << "*****************************" << endl;
        cout << "Удаление билета по его номеру" << endl;
        cout << "*****************************" << endl;
        cout << "(чтобы выйти из удаления, нажмите 0):" << endl;
        int numberDelete;
        do {
            cin >> numberDelete;
            if (numberDelete < 0 || numberDelete > s.getNumberOfTickets())
            {
                cout << "Ошибка выбора номера билета" << endl;
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
Station addTicket(Station s) // добавление билета 
{
    system("cls");
    printTickets(s);

    cout << "*****************" << endl;
    cout << "Добавление билета" << endl;
    cout << "*****************" << endl;
    s.createNewTicket();
    deny = true;
    s.uploadTo();
    return s;
}

Station buyTicket(Station s) // покупка билета
{
    printTickets(s);
    cout << "Выберите номер билета, который хотите купить" << endl;
    int numberBy;
    do
    {
        cin >> numberBy;
        if (numberBy < 1 || numberBy > s.getNumberOfTickets())
        {
            cout << "Ошибка ввода" << endl;
        }
        else
            break;

    } while (true);
    int countBy;
    cout << "Введите количество билетов, которое вам нужно" << endl;
    cout << "От 1 до " << s.getNumberOfFreePlaces(--numberBy) << endl;

    do
    {
        cin >> countBy;
        if (countBy < 1 || countBy > s.getNumberOfFreePlaces(numberBy))
        {
            cout << "Ошибка выбора количества билета" << endl;
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
    cout << "Аккаунт пользователя удалён" << endl;
    system("pause");
    return d;
}

string launch(Database d) {
    while (true) {
        system("cls");
        cout << "1/ Войти в существующий аккаунт" << endl;
        cout << "2/ Создать новый аккаунт" << endl;
        cout << "3/ Выход" << endl;
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
            cout << "Введите имя пользователя: ";
            cin >> log;
            if (cin.peek() != '\n') {
                cin.clear();
                while (cin.get() != '\n');
            }

            cout << "Введите пароль: ";
            do {
                p = _getch(); //возвращаем очередной символ, считанный с консоли, но не выводим его на экран
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
                    cout << '*'; // маскируем символы пароля для конфиденциальности
                    pass.push_back(p); //заносим символ в пароль
                }

            } while (true);
            if (d.addUser(User(log, pass))) {
                d.uploadIn();
                cout << endl << "Пользователь добавлен" << endl;
            }
            else
                cout << endl << "Пользователь с таким именем уже существует" << endl;
            break;
        }
        case '3':
            exit(0);
        default:
            cout << "Ошибка выбора" << endl;
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
        string logIn = launch(d); //авторизация
        if (logIn == "admin") { //вошёл админ
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