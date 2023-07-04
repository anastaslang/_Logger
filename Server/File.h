#pragma once
#include <string>
#include <iostream>

char mainMenu();
char userMenu();
std::string enterName();
std::string enterLogin();
std::string enterPass();
std::string enterTo();
std::string textMessage();
void discorrectUserMenu();
void discorrectMainMenu(char operation_menu);
void noMessages();

