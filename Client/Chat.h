#pragma once
#include "File.h"
#include <cassert>
#include "Network.h"

class Chat
{	
public:
	Chat();
	~Chat();

	void ReadFiles();
	void WriteFiles();
	std::string registration(int connection);
	std::string signUp(int connection);
	void personList(int connection, const std::string &login_from);
	bool correctEnterPerson(int connection, const std::string& login_to);
	void addMessageAll(int connection);
	void addMessage(int connection, const std::string& login_from);
	void showMessagePersonal(int connection, const std::string& login_from);
	void showMessageAll(int connection);
	void showUserMenu(int connection, const std::string& login_from);
	
};
