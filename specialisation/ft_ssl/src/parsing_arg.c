#include <parsing.h>

int check_number_of_arguments(int argc) {
	if (argc < 2) {
		write(STDERR, "usage: ft_ssl command [flags] [file/string]", 42);
		return ERROR;
	}
	return SUCCESS;
}

int check_command(const char *cmd) {
    if (strcmp(cmd, "md5") != 0 && strcmp(cmd, "sha256") != 0) {
        write(STDERR, "ft_ssl: Error: '", 16);
		write(STDERR, cmd, strlen(cmd));
		write(STDERR, "' is an invalid command.\n\nCommands:\nmd5\nsha256\n", 47);
        return ERROR;
    }
    return SUCCESS;
}

int get_flags(int argc, char *argv[], ft_flags *flags, int *is_file_or_string) {
	if (argc == 2) {
		return SUCCESS;
	}

	int i = 2;
	for (; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
				case 'p': flags->p = true; break;
				case 'q': flags->q = true; break;
				case 'r': flags->r = true; break;
				case 's': break;
				default:
					write(STDERR, "ft_ssl: Error: '", 16);
					write(STDERR, argv[i], strlen(argv[i]));
					write(STDERR, "' is an invalid flag.\n", 22);
					return ERROR;
			}
		}
		else
			*is_file_or_string = 1;
	}
	return SUCCESS;
}

int parse_flags(int argc, char *argv[], ft_flags *flags, char **file_names, int *file_count) {
    int i = 2; // Start parsing after the command
    bool last_was_s = false; // Track if the last flag was -s to expect a string next

    for (; i < argc; i++) {
        if (argv[i][0] == '-' && !last_was_s) { // Flag expected
            if (strlen(argv[i]) != 2) {
                write(STDERR, "ft_ssl: Error: '", 16);
				write(STDERR, argv[i], strlen(argv[i]));
				write(STDERR, "' is an invalid flag.\n", 22);
                return ERROR;
            }

            switch (argv[i][1]) {
                case 'p': flags->p = true; break;
                case 'q': flags->q = true; break;
                case 'r': flags->r = true; break;
                case 's': flags->s = true; last_was_s = true; break;
                default:
                    write(STDERR, "ft_ssl: Error: '", 16);
					write(STDERR, argv[i], strlen(argv[i]));
					write(STDERR, "' is an invalid flag.\n", 22);
                    return ERROR;
            }
		} else if (last_was_s) {
			file_names[*file_count] = argv[i];
			(*file_count)++;
			last_was_s = false; // Reset for next flags
        } else {
            // It's not a flag or part of -s, must be a file name
            file_names[*file_count] = argv[i];
            (*file_count)++;
        }
    }
    return SUCCESS;
}