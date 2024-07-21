#include <error.h>

void  write_file_or_directory_error(char *algo, char *input) {
	write(STDERR, "ft_ssl: ", 8);
	write(STDERR, algo, ft_strlen(algo));
	write(STDERR, ": ", 2);
	write(STDERR, input, ft_strlen(input));
	write(STDERR, ": No such file or directory\n", 29);
}