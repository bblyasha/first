#include "database.h"

Database::Database(string file)
{   // ����������� � ����������� 
    fileName = file;
}

//get-����� 
vector<User> Database::getUsers()
{
    return users;
}
//set-�����
void Database::setUsers(vector<User> users)
{
    this->users = users;
}

bool Database::addUser(User user)
{ // ���������� ������������
    for (int i = 0; i < users.size(); i++)
        if (users.getByIndex(i).getLogin() == user.getLogin())
            return false;
    users.pushBack(user);
    return true;
}

bool Database::deleteUser(string login)
{      //�������� ������������
    bool check = false;
    for (int i = 0; i < users.size(); i++) {
        check = (users.getByIndex(i).getLogin() == login); //���������� ������� ������� � ���������
        if (check) { //���� ������ ������������ � �������
            if (i == users.size() - 1) //���� ��� ��������� �������, �������
                break;
            User temp = users.getByIndex(i + 1);
            users.pushIn(users.getByIndex(i), i + 1);
            users.pushIn(temp, i);
        }
    }
    if (check) {    //������� ��������� ������� �������
        users.popBack();
        return true;
    }
    return false;

}

void Database::downloadFrom()
{ // ��������� ������ � ������������� �� �����
    ifstream fin(fileName); // ��������� ����
    while (!fin.eof()) //�������� ����� �� �������
    {
        User user;
        string buff, str;
        int start = 0, end;
        getline(fin, buff, '\n'); //��������� ������
        if (buff != "\n" && buff != "")
        {
            end = buff.find('/');
            str = buff.substr(start, end - start); //�������� �� ��� �����
            user.setLogin(str);
            start = end + 1; //������ ������ ��������� ����� ��� ����� ':'
            end = buff.find(';', start);
            str = buff.substr(start, end - start);//�������� �� ��� ������
            user.setPassword(str);

            users.pushBack(user);; //��������� ������������
        }
    }
    fin.close(); //��������� ����
}
void Database::uploadIn()
{ //�������� � ����
    ofstream fout(fileName); // ��������� ��� ����
    for (int i = 0; i < users.size(); i++) { //���������� ���� ��� ������ �� �������
        fout << users.getByIndex(i).getLogin() << '/';
        fout << users.getByIndex(i).getPassword() << ';';
        fout << '\n';
    }
    fout.close(); // ��������� ����
}

bool Database::checkLog(string login, string password)
{//�������� ����� � �������
    for (int i = 0; i < users.size(); i++)
    {
        if (users.getByIndex(i).getLogin() == login)
        {
            if (users.getByIndex(i).getPassword() != password)
            {
                cout << endl << "�������� ������!" << endl;
                return false;
            }
            else
                return true;
        }
    }
    return false;
}
