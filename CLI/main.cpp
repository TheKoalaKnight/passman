#include <iostream>
#include <sqlite_modern_cpp.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "passman.hpp"

using namespace Passman;

void addAccount()
{
  Account account;
  std::string string;

  std::cout << std::endl << "Please enter all required details. "
	    << std::endl << "Service: ";
  
  std::getline(std::cin, string);
  account.setService(string);


  std::cout << std::endl << "Email: ";
  std::getline(std::cin, string);
  account.setEmail(string);

  std::cout << std::endl << "Username: ";
  std::getline(std::cin, string);
  account.setUsername(string);

  std::cout << std::endl << "Do you want to use a generated password? [Y/n]";
  char answer;
  std::cin >> answer; 
  std::cin.clear();
  std::cin.ignore(1000, '\n');
  if(answer == 'y' || answer == 'Y'){
    account.generatePassword();
  }
  else
    {
      std::cout << std::endl << "Password: ";
      std::getline(std::cin, string);
      account.setPassword(string);
    }



  std::cout << std::endl << "Do you want to save these details? [Y/n]"
	    << std::endl << "Service: " << account.getService()
	    << std::endl << "Email: " << account.getEmail()
	    << std::endl << "Username: " << account.getUsername() << std::endl;

  char response;
  std::cin >> response;
  std::cin.clear();
  std::cin.ignore(1000, '\n');

  if(response == 'y' || response == 'Y')
    {
      account.saveToDatabase();
    }

}

void edit(Account account)
  {
    std::string string;
    while(1)
      {
	std::cout << std::endl
		  << "Service: " << account.getService() << "\nEmail: " << account.getEmail()
		  << "\nUsername: " << account.getUsername() << std::endl
		  << "What do you wish to do? \n1. View password. \n2. Edit email."
		  << "\n3. Edit Username. \n4. Edit password. \n5. Nothing. \n: ";
	char input;
	std::cin.ignore(1000, '\n');
	std::cin >> input;
	switch (input)
	  {
	  case '1':
	    std::cout << std::endl << "Password: " << account.getPassword(); break;
	  case '2':
	    std::cout << std::endl << "Enter new email: ";
	    std::cin >> string; account.setEmail(string); break;
	  case '3':
	    std::cout << std::endl << "Enter new username: ";
	    std::cin >> string; account.setUsername(string); break;
	  case '4':
	    std::cout << std::endl << "Enter new password: ";
	    std::cin >> string; account.setPassword(string); break;
	  default: account.updateDatabase(); return;
	  }
      }

  }

void browseAccounts()
{
  std::cout << std::endl << "Please enter the service you wish to find and press 'Enter'.";
  std::string searchString;
  
  std::getline(std::cin, searchString);

  
  
  std::vector <Account>returns = Account::searchDatabase(searchString);

  for(auto a : returns)
    {
      std::cout << std::endl << a.getService();
    }


  char response;
  std::cout << std::endl << "Please choose how to proceed. \n1. Choose one of" " these. \n2. Search again. \n3. Exit. ";

  std::cin >> response;
  std::cin.clear();
  std::cin.ignore(1000, '\n');
  switch (response)
    {
    case '1': break;
    case '2': browseAccounts(); return; break;
    default: return;
    }

  int count = 0;

  for(auto a : returns)
    {
      std::cout << std::endl << count << ": " << a.getService();
      count++;
    }

  int answer;
  std::cout << std::endl << "Choose ẃhich to view: ";
  std::cin >> answer;
  if (answer <=  count)
    {
      edit(returns[answer]);
    }
  else
    return;

}

void mainMenu()
{

  char response;
  while(1)
    {
      std::cout << std::endl;

      std::cout << std::endl << "What do you want to do?"
		<< std::endl << "1. Add new account. "
		<<  std::endl << "2. Browse existing accounts. "
		<< std::endl << "3. Exit. " << std::endl;



      std::cin >> response;
      std::cin.clear();
      std::cin.ignore(1000, '\n');

      if (response == '1')
	addAccount();
      else if (response == '2')
	browseAccounts();
      else if (response == '3')
	break;

    }
}


int main()
{
  std::cout << "\nWelcome back to Jakob Alwall's official password manager!";
  sqlite::database database ("/usr/share/passman/accounts.db");
  Account::setDatabase(database);
  mainMenu();

  return 0;
}
