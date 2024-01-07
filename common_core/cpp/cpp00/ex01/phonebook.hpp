#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>
# include <iomanip> //parameterized stream manipulators
# include <string>

#include "contact.hpp"

class Phonebook
{
	private:
		Contact contacts[8];
		int index;
	public:
		Phonebook();
		~Phonebook();
		void add_contact();
		void search_contact();
};

#endif