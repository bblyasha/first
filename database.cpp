#include "database.h"

Database::Database(string file)
{   // конструктор с параметрами 
    fileName = file;
}

//get-метод 
vector<User> Database::getUsers()
{
    return users;
}
//set-метод
void Database::setUsers(vector<User> users)
{
    this->users = users;
}

bool Database::addUser(User user)
{ // добавление пользовател€
    for (int i = 0; i < users.size(); i++)
        if (users.getByIndex(i).getLogin() == user.getLogin())
            return false;
    users.pushBack(user);
    return true;
}

bool Database::deleteUser(string login)
{      //удаление пользовател€
    bool check = false;
    for (int i = 0; i < users.size(); i++) {
        check = (users.getByIndex(i).getLogin() == login); //сравниваем текущий элемент с удал€емым
        if (check) { //если объект присутствует в векторе
            if (i == users.size() - 1) //если это последний элемент, выходим
                break;
            User temp = users.getByIndex(i + 1);
            users.pushIn(users.getByIndex(i), i + 1);
            users.pushIn(temp, i);
        }
    }
    if (check) {    //удал€ем последний элемент вектора
        users.popBack();
        return true;
    }
    return false;

}

void Database::downloadFrom()
{ // получение данных о пользовател€х из файла
    ifstream fin(fileName); // открываем файл
    while (!fin.eof()) //проверка файла на пустоту
    {
        User user;
        string buff, str;
        int start = 0, end;
        getline(fin, buff, '\n'); //считываем строку
        if (buff != "\n" && buff != "")
        {
            end = buff.find('/');
            str = buff.substr(start, end - start); //вырезаем из нее логин
            user.setLogin(str);
            start = end + 1; //начало нового параметра будет уже после ':'
            end = buff.find(';', start);
            str = buff.substr(start, end - start);//вырезаем из нее пароль
            user.setPassword(str);

            users.pushBack(user);; //добавл€ем пользовател€
        }
    }
    fin.close(); //закрываем файл
}
void Database::uploadIn()
{ //загрузка в файл
    ofstream fout(fileName); // открываем наш файл
    for (int i = 0; i < users.size(); i++) { //записываем туда все данные из вектора
        fout << users.getByIndex(i).getLogin() << '/';
        fout << users.getByIndex(i).getPassword() << ';';
        fout << '\n';
    }
    fout.close(); // закрываем файл
}

bool Database::checkLog(string login, string password)
{//проверка входа в систему
    for (int i = 0; i < users.size(); i++)
    {
        if (users.getByIndex(i).getLogin() == login)
        {
            if (users.getByIndex(i).getPassword() != password)
            {
                cout << endl << "Ќеверный пароль!" << endl;
                return false;
            }
            else
                return true;
        }
    }
    return false;
}
