#pragma once
#include<cassert>
#include"Network.h"
#include"DataBase.h"

class Chat
{
	DataBase _data;
		
public:
	Chat();
	~Chat();
	void connectMySQL();
	void disconnectMySQL();
	std::string registration(int connection);
	std::string signUp(int connection);
	void personList(int connection, const std::string &login_from);
	bool correctEnterPerson(int connection, const std::string& login_to);
	void addMessageAll(int connection, const std::string& login_from);
	void addMessage(int connection, const std::string& login_from);
	void showMessagePersonal(int connection, const std::string& login_from);
	void showMessageAll(int connection);
	void showMessageMenu(int connection, const std::string& login_from);
	
};


