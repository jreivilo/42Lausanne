#include "phonebook.hpp"
# include <string>

Phonebook::Phonebook()
{
    this->index = 0;
    // std::cout << "PhoneBook constructor called!" << std::endl;
}

Phonebook::~Phonebook()
{
	// std::cout << "PhoneBook destructor called!" << std::endl;
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
		if (first_name.length() && first_name.find_first_not_of("0123456789") != std::string::npos)
		{
			contacts[index % 8].set_first_name(first_name);
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
			contacts[index % 8].set_last_name(last_name);
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
			contacts[index % 8].set_nickname(nickname);
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
			contacts[index % 8].set_login(login);
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
		//check is a number
		if (phone_number.length() && phone_number.find_first_not_of("0123456789") == std::string::npos)
		{
			contacts[index % 8].set_phone_number(phone_number);
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
			contacts[index % 8].set_darkest_secret(darkest_secret);
			valid = 1;
		}
		else
			std::cout << "Invalid darkest secret" << std::endl;
	}
	this->index++;
}

void	Phonebook::search_contact()
{
	int i;
	int index;
	std::string index_str;

	i = 0;
	index = 0;
	if (this->index == 0)
	{
		std::cout << "No contacts to display" << std::endl;
		return ;
	}
	while (i < this->index && i < 8)
	{
		std::cout << std::setw(10) << i << "|";
		if (contacts[i].get_first_name().length() > 10)
			std::cout << std::setw(10) << contacts[i].get_first_name().substr(0, 9) << "." << "|";
		else
			std::cout << std::setw(10) << contacts[i].get_first_name() << "|";
		if (contacts[i].get_last_name().length() > 10)
			std::cout << std::setw(10) << contacts[i].get_last_name().substr(0, 9) << "." << "|";
		else
			std::cout << std::setw(10) << contacts[i].get_last_name() << "|";
		if (contacts[i].get_nickname().length() > 10)
			std::cout << std::setw(10) << contacts[i].get_nickname().substr(0, 9) << "." << "|";
		else
			std::cout << std::setw(10) << contacts[i].get_nickname() << "|";
		std::cout << std::endl;
		i++;
	}
	std::cout << "Enter index: ";
	std::getline(std::cin, index_str);
	index = index_str[0] - '0';
	
	if (index < 0 || index > 7)
	{
		std::cout << "Invalid index" << std::endl;
		return ;
	}
	if (index >= this->index)
	{
		std::cout << "No contact at this index" << std::endl;
		return ;
	}
	std::cout << std::endl;
	std::cout << "Index: " << index << std::endl;
	std::cout << "First name: " << contacts[index].get_first_name() << std::endl;
	std::cout << "Last name: " << contacts[index].get_last_name() << std::endl;
	std::cout << "Nickname: " << contacts[index].get_nickname() << std::endl;
	std::cout << "Login: " << contacts[index].get_login() << std::endl;
	std::cout << "Phone number: " << contacts[index].get_phone_number() << std::endl;
	std::cout << std::endl;
}

int main()
{
	Phonebook phonebook;
	std::string command;

	std::cout << "Welcome to the Phonebook!" << std::endl;

	while (1)
	{
		if (std::cin.eof())
			break ;
		std::cout << "Available commands: ADD, SEARCH, EXIT" << std::endl;
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