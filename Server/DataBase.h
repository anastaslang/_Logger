#pragma once
#include "File.h"
#include <mysql/mysql.h>

class DataBase
{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;

public:
    DataBase();
    ~DataBase();

    void openDataBase();
    void createDataTable();
    bool addDataUser(const std::string &name, const std::string &login, const std::string &password);
    bool enterDataUser(const std::string &login, const std::string &password);
    bool addDataMessage(const std::string &from, const std::string &to, const std::string &text);
    bool addDataMessageAll(const std::string &from, const std::string &text);
    std::string showDataUsersLogin(const std::string &login);
    bool correctDataEnterPerson(const std::string& login_to);
    std::string showDataMessage(const std::string &login);
    std::string showDataMessageAll();
    void closeDataBase();
};
