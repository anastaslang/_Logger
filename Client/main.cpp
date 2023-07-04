#include "Chat.h"

int main()
{	
	std::string login;
	char operation_menu;
	Chat chat;
	std::string str;
	
	Network netConnect;
	auto connectNet = netConnect.connectClientOpen();
	std::cout << "Соединение...  "  << std::endl;
	if (connectNet == -1)
	{
		std::cout << "Сбой сети." << std::endl;
		exit(-1);
	}
	
	do
	{
		operation_menu = mainMenu();		
		
		if(discorrectMainMenu(operation_menu))
			{
				str = operation_menu;
				netConnect.sendMessage(connectNet, str);
			}		

		if (operation_menu == '1')
		{
			login = chat.registration(connectNet);
			if (login != "error")
			{
				chat.showUserMenu(connectNet, login);
			}
		}
		if (operation_menu == '2')
		{
			auto loginIn = chat.signUp(connectNet);
			if (loginIn != "error")
			{
				chat.showUserMenu(connectNet, loginIn);
			}
		}
	} while (operation_menu != '3');	
	
	netConnect.connectClose(connectNet);

	return 0;
}
