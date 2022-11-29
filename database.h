#pragma once
#include "User.h"
#include "vector.h"
#include <fstream>

class Database {
    vector<User> users;       // ������ �������������
    string fileName;          //��� ����� � �������� ������� � ���

public:
    Database(string); // ����������� � �����������
    //get-����� 
    vector<User> getUsers();
    //set-�����
    void setUsers(vector<User>);

    bool addUser(User); //���������� ������������
    bool deleteUser(string); //�������� ������������

    void downloadFrom(); //�������� ������ �� �����
    void uploadIn(); //�������� ������ � ����

    bool checkLog(string, string); //�������� ����� � �������
};
