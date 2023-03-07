#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <iostream>
# include <iomanip> //parameterized stream manipulators
# include <string>

class Contact
{
	private:
		std::string first_name;
		std::string last_name;
		std::string nickname;
		std::string login;
		std::string phone_number;
		std::string darkest_secret;
	public:
		Contact();
		~Contact();
		void set_first_name(std::string first_name);
		void set_last_name(std::string last_name);
		void set_nickname(std::string nickname);
		void set_login(std::string login);
		void set_phone_number(std::string phone_number);
		void set_darkest_secret(std::string darkest_secret);
};

#endif