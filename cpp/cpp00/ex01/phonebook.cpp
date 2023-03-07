#include "phonebook.hpp"

Phonebook::Phonebook()
{
    this->index = 0;
    std::cout << "PhoneBook constructor called!" << std::endl;
}

Phonebook::~Phonebook()
{
	std::cout << "PhoneBook destructor called!" << std::endl;
}


void	Phonebook::add_contact()
{
	std::string first_name;
	std::string last_name;
	std::string nickname;
	std::string login;
	std::string phone_number;
	std::string darkest_secret;
	int valid;

	valid = 0;

	while(!valid)
	{
		std::cout << "Enter first name: ";
		std::getline(std::cin, first_name);
		if (first_name.length())
		{
			contacts[index].set_first_name(first_name);
			valid = 1;
		}
		else
			std::cout << "Invalid first name" << std::endl;
	}
	valid = 0;
	while(!valid)
	{
		std::cout << "Enter last name: ";
		std::getline(std::cin, last_name);
		if (last_name.length())
		{
			contacts[index].set_last_name(last_name);
			valid = 1;
		}
		else
			std::cout << "Invalid last name" << std::endl;
	}
	valid = 0;
	while(!valid)
	{
		std::cout << "Enter nickname: ";
		std::getline(std::cin, nickname);
		if (nickname.length())
		{
			contacts[index].set_nickname(nickname);
			valid = 1;
		}
		else
			std::cout << "Invalid nickname" << std::endl;
	}
	valid = 0;
	while(!valid)
	{
		std::cout << "Enter login: ";
		std::getline(std::cin, login);
		if (login.length())
		{
			contacts[index].set_login(login);
			valid = 1;
		}
		else
			std::cout << "Invalid login" << std::endl;
	}
	valid = 0;
	while(!valid)
	{
		std::cout << "Enter phone number: ";
		std::getline(std::cin, phone_number);
		if (phone_number.length())
		{
			contacts[index].set_phone_number(phone_number);
			valid = 1;
		}
		else
			std::cout << "Invalid phone number" << std::endl;
	}
	valid = 0;
	while (!valid)
	{
		std::cout << "Enter darkest secret: ";
		std::getline(std::cin, darkest_secret);
		if (darkest_secret.length())
		{
			contacts[index].set_darkest_secret(darkest_secret);
			valid = 1;
		}
		else
			std::cout << "Invalid darkest secret" << std::endl;
	}
	this->index++;
}

int main()
{
	Phonebook phonebook;
	std::string command;

	while (1)
	{
		std::cout << "Enter command: ";
		std::getline(std::cin, command);
		if (command == "EXIT")
			break ;
		else if (command == "ADD")
			phonebook.add_contact();
		else if (command == "SEARCH")
			phonebook.search_contact();
		else if (command == "EXIT")
			break ;
		else
			std::cout << "Invalid command" << std::endl;

	}
	return (0);
}