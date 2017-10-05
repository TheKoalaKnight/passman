#include <sqlite_modern_cpp.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "passman.hpp"

std::string encrypt(std::string str, char key)
{
  int i = 0;
  std::string result = str;
  for(char c : result)
    {
      result[i] = (str[i] ^ key);
      i++;
    }
  return result;
}

using namespace Passman;

bool Account::saveEncrypt(std::string str, std::string& result)
{
  char key = '^';

  for(char c : str)
    {
      if(c == key)
	return false;
    }
    
  result = encrypt(str, key);
    
    
  return true;
}

void Account::generatePassword()
{
  int length = 16;
  std::srand (time(NULL));
 
  char result[length];
  char chars[] = "qwertyuiopasdfghjklzxcvbnm@(){[]}!1234567890";
  for(int i = 0 ; i < length-1 ; i++)
    {
      result[i] = chars[rand() % 44];
    }
  result[length - 1] = '\0';
  //avsluta alltid string med NULL!!!!!!!!!!

  std::string resultString = result;
  setPassword(resultString);
}

bool Account::setPassword(std::string str)
{        
  return saveEncrypt(str, password);
}

bool Account::setEmail(std::string str)
{        
  return saveEncrypt(str, email);
}

bool Account::setUsername(std::string str)
{        
  return saveEncrypt(str, username);
}

bool Account::setService(std::string str)
{        
  return saveEncrypt(str, service);
}

std::string Account::getService()
{
  return encrypt(service, '^');
}
std::string Account::getEmail()
{
  return encrypt(email, '^');
}
std::string Account::getUsername()
{
  return encrypt(username, '^');
}
std::string Account::getPassword()
{
  return encrypt(password, '^');
}

Account::Account(std::string Service, std::string Email, std::string Username, std::string Password)
{
  setService(Service);
  setEmail(Email);
  setUsername(Username);
  setPassword(Password);
  
}

Account::Account()
{
  
}

void Account::saveToDatabase()
{
  *Account::database << "INSERT INTO accounts (service, email, username, password)"
    " VALUES(?, ?, ?, ?);"
	   << service << email << username << password;
}

sqlite::database *Account::database = NULL;

void Account::updateDatabase()
{
  *Account::database
    << "UPDATE accounts SET service = ?, email = ?, username = ?, "
    "password = ? WHERE service = ?;"
    << service << email
    << username << password
    << service;
}

void Account::setDatabase(sqlite::database& Database)
{
  Account::database = &Database;
  *Account::database <<
  "CREATE TABLE IF NOT EXISTS accounts(service TEXT"
    ", email TEXT, username TEXT, password TEXT);";
}

std::vector<Account> Account::searchDatabase(std::string searchTerm)
{
  char key = '^';
  
  std::vector<Account> returns;
  searchTerm = '%' + encrypt(searchTerm, key) + '%';
  *Account::database << "SELECT * FROM accounts WHERE service LIKE ?;" << searchTerm
	   >> [&](std::string s, std::string e, std::string u, std::string p)
    {
      returns.push_back(Account(encrypt(s, key), encrypt(e, key), encrypt(u, key), encrypt(p, key)));
    };
  return returns;
}


