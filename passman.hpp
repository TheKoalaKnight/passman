#ifndef PASSMAN_H
#define PASSMAN_H

#include <sqlite_modern_cpp.h>
#include <vector>


namespace Passman
{

  class Account
  {
    std::string service;
    std::string email;
    std::string username;
    std::string password;

    bool        saveEncrypt(std::string, std::string&);

  
    static sqlite::database *database;

  public:
    
    void        generatePassword();
    bool        setPassword(std::string);
    bool        setEmail(std::string);
    bool        setUsername(std::string);
    bool        setService(std::string);

    std::string getService();
    std::string getEmail();
    std::string getUsername();
    std::string getPassword();

    Account();

    void        saveToDatabase();
    void        updateDatabase();
    
    Account(std::string, std::string, std::string, std::string);
    static void setDatabase(sqlite::database&);
    static std::vector<Account> searchDatabase(std::string);
  };

}

#endif
