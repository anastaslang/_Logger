#include "Chat.h"

Chat::Chat() = default;
Chat::~Chat() = default;

void Chat::connectMySQL()
{
	_data.openDataBase();
	_data.createDataTable();
}

void Chat::disconnectMySQL()
{
	_data.closeDataBase();
}

std::string Chat::registration(int connection)
{
	std::string name;
	std::string login;
	std::string password;

	Network netConnect;

	name = netConnect.reseiveMessage(connection);
	login = netConnect.reseiveMessage(connection);
	password = netConnect.reseiveMessage(connection);

	if (_data.addDataUser(name, login, password))
	{
		netConnect.sendMessage(connection, "Поздравляем, вы успешно зарегистрированы.");
		Logger logger;		
		std::thread l1 ([&logger, &login, &name] () {		
		logger.loggerWrite("Регистрация:  ");  //пишем в log.txt
		logger.loggerWrite(name);
		logger.loggerWrite(login);
		}); 
		if (l1.joinable())
			l1.join();
		return login;
	}
	else
	{
		netConnect.sendMessage(connection, "error");
		return "error";
	}
}

std::string Chat::signUp(int connection)
{
	Network netConnect;
	auto count = 0;
	std::string login = netConnect.reseiveMessage(connection);
	std::string password = netConnect.reseiveMessage(connection);

	if (_data.enterDataUser(login, password))
	{
		netConnect.sendMessage(connection, "Вход выполнен успешно.");
		Logger logger;			
		std::thread l ([&logger, &login] () {		
		logger.loggerWrite("Вход:  ");  //пишем в log.txt
		logger.loggerWrite(login);
		}); 
		if(l.joinable())
			l.join();
		return login;
	}
	else
	{
		netConnect.sendMessage(connection, "Такого логина/пароля не существует");
		return "error";
	}
}

void Chat::personList(int connection, const std::string &login_from)
{
	Network netConnect;
	std::string str;

	str = _data.showDataUsersLogin(login_from);
	netConnect.sendMessage(connection, str);
}

bool Chat::correctEnterPerson(int connection, const std::string &login_to)
{
	Network netConnect;
	if (_data.correctDataEnterPerson(login_to))
	{
		netConnect.sendMessage(connection, "true");
		return true;
	}
	else
	{
		netConnect.sendMessage(connection, "false");
		return false;
	}
}

void Chat::addMessageAll(int connection, const std::string &login_from)
{
	Network netConnect;
	std::string text = netConnect.reseiveMessage(connection);
	_data.addDataMessageAll(login_from, text);	
}

void Chat::addMessage(int connection, const std::string &login_from)
{
	std::string text;
	std::string login_to;
	Network netConnect;

	personList(connection, login_from);
	login_to = netConnect.reseiveMessage(connection);
	if (login_to == "всем")
	{
		addMessageAll(connection, login_from);
	}
	else
	{
		if (correctEnterPerson(connection, login_to))
		{
			text = netConnect.reseiveMessage(connection);
			_data.addDataMessage(login_from, login_to, text);
		}
	}
}

void Chat::showMessagePersonal(int connection, const std::string &login_from)
{
	auto count = 0;
	std::string str;
	Network netConnect;
	str = _data.showDataMessage(login_from);

	if (!str.empty())
	{
		netConnect.sendMessage(connection, str);
	}
	else
	{
		netConnect.sendMessage(connection, "error");
	}
}

void Chat::showMessageAll(int connection)
{
	std::string str;
	Network netConnect;

	str = _data.showDataMessageAll();
	if (!str.empty())
	{
		netConnect.sendMessage(connection, str);
	}
	else
	{
		netConnect.sendMessage(connection, "error");
	}
}

void Chat::showMessageMenu(int connection, const std::string &login_from)
{
	Network netConnect;
	const char *operation;
	std::string str;
	do
	{
		str = netConnect.reseiveMessage(connection);
		operation = str.c_str();
		
		switch (operation[0])
		{
		case '1':
			showMessageAll(connection);
			break;

		case '2':
			showMessagePersonal(connection, login_from);
			break;

		case '3':
			addMessage(connection, login_from);
			break;

		case '4':
			break;

		default:
			break;
		}
	} while (operation[0] != '4');
}
