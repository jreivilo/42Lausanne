#ifndef PARSIING_H
# define PARSING_H

#include <flag.h>
#include <ft_ssl.h>

int check_number_of_arguments(int argc);
int check_command(const char *cmd);
int get_flags(int argc, char *argv[], ft_flags *flags, int *is_file_or_string);
int parse_flags(int argc, char *argv[], ft_flags *flags, char **file_names, int *file_count);

void process_md5(int argc, char *argv[], ft_flags flags, int is_file_or_string);

#endif