#include "Chat.h"

Chat::Chat() = default;
Chat::~Chat() = default;

std::string Chat::registration(int connection)
{ 
	std::string name ;
	std::string login ;
	std::string password ;
	
	Network netConnect;
	name = enterName();
	netConnect.sendMessage(connection, name);
	login = enterLogin();
	netConnect.sendMessage(connection, login);
	password = enterPass();			
	netConnect.sendMessage(connection, password);		

	std::string str = netConnect.reseiveMessage(connection);			

	if(strncmp("error", str.c_str(), 5) == 0) 
	{
		std::cout << "Такие имя/логин/пароль уже заняты.\n Попробуйте еще раз. ";
		std::cout << std::endl;	
		return "error";	
	}
	else 
	{
		std::cout << str;		
		std::cout << std::endl;	
		return login;
	}	
}

std::string Chat::signUp(int connection)
{
	std::string login;
	std::string password;
	
	Network netConnect;		
	login = enterLogin();
	netConnect.sendMessage(connection, login);
	password = enterPass();
	netConnect.sendMessage(connection, password);
	
	std::string str = netConnect.reseiveMessage(connection);
			
	if(strncmp("Вход", str.c_str(), 4) == 0) 
	{	
		std::cout << str;
		std::cout << std::endl;		
		return login;
	}	
	else
	{
		std::cout << str << std::endl;
		return "error";
	}
}

void Chat::personList(int connection, const std::string& login_from)
{
	Network netConnect;

	std::cout << "Пользователи чата:   всем  / ";	
	std::string str = netConnect.reseiveMessage(connection);				
	std::cout << str << '\n';		
}

bool Chat::correctEnterPerson(int connection, const std::string& login_to)
{
	Network netConnect;
	
	std::string str = netConnect.reseiveMessage(connection);
		if(strncmp("true", str.c_str(), 4) == 0) 
		{			
			return true;
		}	
	return false;
}

void Chat::addMessageAll(int connection)
{
	std::string text = textMessage();
	Network netConnect;
	netConnect.sendMessage(connection, text);	
}

void Chat::addMessage(int connection, const std::string& login_from) {
	std::string text;
	std::string login_to;
	Network netConnect;

	personList(connection, login_from);
	login_to = enterTo();
	
	netConnect.sendMessage(connection, login_to);

	if (login_to == "всем")
	{
		addMessageAll(connection);
	}
	else
	{
		if (correctEnterPerson(connection, login_to))
		{
			text = textMessage();
			netConnect.sendMessage(connection, text);
		}	
		else
		{
			discorrectUserMenu();
		}
	}
}

void Chat::showMessagePersonal(int connection, const std::string& login_from) 
{
	Network netConnect;	
	
	std::string str1 = netConnect.reseiveMessage(connection);
	if(strncmp("error", str1.c_str(), 2) == 0)	
	{
		std::cout << "Личных сообщений нет." << std::endl;	
		return;		
	}				
	std::cout << "Личные сообщения:     " << std::endl;
	std::cout << str1 << std::endl;		
}

void Chat::showMessageAll(int connection)
{	
	Network netConnect;	
	std::string str1  = netConnect.reseiveMessage(connection);
		
	if(strncmp("error", str1.c_str(), 2) == 0)	
	{
		std::cout << "Сообщений из общего чата нет. " << std::endl;	
		return;		
	}

	std::cout << "Сообщения из общего чата:     " << std::endl;
	std::cout << str1 << std:: endl;
}

void Chat::showUserMenu(int connection, const std::string& login_from)
{
	Network netConnect;
	std::string str;
	char operation;
	do
	{
		operation = userMenu();
		str = operation;
		netConnect.sendMessage(connection, str);
		switch (operation)
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
			discorrectUserMenu();
			break;
		}
	} 
	while (operation != '4');
}

