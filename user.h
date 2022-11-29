#pragma once
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

class User {
	string login;
	string password;
public:
	//������������
	User()
	{
		this->login = "user";
		this->password = "user";
	}
	User(const User& user)
	{
		this->login = user.login;
		this->password = user.password;
	}
	User(string login, string password)
	{
		this->login = login;
		this->password = password;
	}

	//get-������
	string getLogin()
	{
		return login;
	}
	string getPassword()
	{
		return password;
	}

	//set-������
	void setLogin(string login)
	{
		this->login = login;
	}
	void setPassword(string password)
	{
		this->password = password;
	}

	User& operator= (const User& user)
	{	// ���������� ��������� ������������
		if (&user == this) //�������� �� ����������������
			return *this;
		login = user.login;
		password = user.password;
		return *this;
	}
	bool operator== (const User& user) const
	{ // ���������� ��������� ���������
		return (this->login == user.login) &&
			(this->password == user.password);
	}
};
