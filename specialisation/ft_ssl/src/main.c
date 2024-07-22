#include <ft_ssl.h>

// Function to parse command-line flags

#include <ft_ssl.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define ERROR -1
#define SUCCESS 0


int main(int argc, char *argv[]) {
    ft_flags flags = {false, false, false, false};
	int is_file_or_string = 0;

	if (check_number_of_arguments(argc) == ERROR)
		return ERROR;

	if (check_command(argv[1]) == ERROR)
		return ERROR;

	if (get_flags(argc, argv, &flags, &is_file_or_string) == ERROR)
		return ERROR;

	char *algo = argv[1];

	process_algo(argc, argv, algo, flags, is_file_or_string);

    return SUCCESS;
}
