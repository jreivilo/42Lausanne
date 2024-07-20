#ifndef PRINT_H
# define PRINT_H

#include <flag.h>
#include <ft_ssl.h>

void print_algo(char *hash, char *input, char *algo, ft_flags flags, bool is_stdin, bool is_file);
#endif