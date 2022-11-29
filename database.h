#pragma once
#include "User.h"
#include "vector.h"
#include <fstream>

class Database {
    vector<User> users;       // список пользователей
    string fileName;          //имя файла с входными данными о них

public:
    Database(string); // конструктор с параметрами
    //get-метод 
    vector<User> getUsers();
    //set-метод
    void setUsers(vector<User>);

    bool addUser(User); //добавление пользователя
    bool deleteUser(string); //удаление пользователя

    void downloadFrom(); //загрузка данных из файла
    void uploadIn(); //загрузка данных в файл

    bool checkLog(string, string); //проверка входа в систему
};
