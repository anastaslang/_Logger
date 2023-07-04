#include "File.h"
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

char mainMenu()
{	
	char operation;
	std::cout << "***********************" << std::endl;
	std::cout << " (1) Регистрация" << std::endl;
	std::cout << " (2) Вход в аккаунт" << std::endl;
	std::cout << " (3) Выход из чата" << std::endl;
	std::cout << "***********************" << std::endl;
	
	std::cout << "Выбор операции -  ";
	std::cin >> operation;
	std::cin.ignore(1, '\n');
	return operation;
}

char userMenu()
{	
	std::cout << "******************************" << std::endl;
	std::cout << " (1) Показать сообщения из общего чата." << std::endl;
	std::cout << " (2) Показать личные сообщения." << std::endl;
	std::cout << " (3) Написать сообщение." << std::endl;
	std::cout << " (4) Выйти из аккаунта." << std::endl;
	std::cout << "******************************" << std::endl;
	
	std::cout << " Выбор операции -  ";
	char operation;
	std::cin >> operation;
	std::cin.ignore(100, '\n');
	return operation;
}

std::string enterName()
{
	std::string str;
	std::cout << "Имя - ";
	std::cin >> str;
	return str;
}

std::string enterLogin()
{
	std::string str;
	std::cout << "Логин - ";
	std::cin >> str;
	return str;
}

std::string enterPass()
{
	std::string str;
	std::cout << "Пароль - ";
	std::cin >> str;
	return str;
}

std::string enterTo()
{
	std::string str;
	std::cout << std::endl;
	std::cout << "Кому - ";
	std::cin >> str;
	return str;
}

std::string textMessage()
{
	std::string text;
	std::cout << ">>  ";
	std::cin.ignore();
	std::getline(std::cin, text);

	return text;
}

void discorrectUserMenu()
{
	std::cout << "Некорректный ввод. Попробуйте ещё раз." << std::endl;

}

bool discorrectMainMenu(char operation_menu)
{
	if (operation_menu < 49 || operation_menu > 52)
	{
		std::cout << std::endl;
		std::cout << "Некорректный ввод. Попробуйте ещё раз." << std::endl;
		return false;
	}
	return true;
}



