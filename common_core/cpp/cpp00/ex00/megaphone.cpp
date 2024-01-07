#include	<iostream> // std in and out
#include	<string> //use a variable that has type std::string

int	main(int argc, char **argv)
{
	if (argc == 1) //if there are no arguments (argc = 1) print the following (argc =
	{
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
        return (0);
	}
	else
	{
		for (int i = 1; i < argc; i++) //for loop that starts at 0 and ends at the number of arguments
		{
			std::string str = argv[i]; //create a string variable and set it equal to the first argument
			for (size_t j = 0; j < str.length(); j++) //for loop that starts at 0 and ends at the length of the string
			{
				if (str[j] >= 'a' && str[j] <= 'z') //if the character is lowercase
				{
					str[j] = str[j] - 32; //make it uppercase
				}
			}
			std::cout << str; //print the string
			if (i != argc - 1) //if the argument is not the last one
				std::cout << " "; //print a space

		}
		std::cout << std::endl; //print a new line
	}
}