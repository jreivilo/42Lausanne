#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>

class Brain
{
	private:
		std::string ideas[100];
	public:
		Brain();
		Brain(Brain const & src);
		~Brain();
		Brain & operator=(Brain const & rhs);

		std::string getIdea(int i) const;
		void setIdea(int i, std::string idea);
};

#endif