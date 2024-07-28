#include <parsing.h>

typedef struct {
    char *name;
    void (*process_input)(char *input, bool is_string, ft_flags flags);
    void (*process_stdin)(ft_flags flags);
} Algorithm;

Algorithm algorithms[] = {
    {"md5", process_md5_input, process_md5_stdin},
    {"sha256", process_sha256_input, process_sha256_stdin}
};

int get_algorithm_index(char *algo) {
	int i = 0;
	for (; i < 2; i++) {
		if (ft_strcmp(algo, algorithms[i].name) == 0)
			return i;
	}
	return -1;
}


void process_algo(int argc, char *argv[], char *algo, ft_flags flags, int is_file_or_string) {
    // If flag p, read stdin
	if (flags.p || (is_file_or_string == 0)) {
		int j = get_algorithm_index(algo);
		if (j != -1)
			algorithms[j].process_stdin(flags);
	}

	int i = 2;
	for (; i < argc; i++) {
		if (argv[i][0] == '-' && argv[i][1] == 's' && argv[i][2] == '\0' && i + 1 < argc && flags.s == false) {
			flags.s = true;
			// Handle the string
			i++;
			int j = get_algorithm_index(algo);
			if (j != -1)
				algorithms[j].process_input(argv[i], true, flags);
			continue;
		}
		if (argv[i][0] == '-' && argv[i][1] == 's' && argv[i][2] == '\0' && flags.s == true) {
				write_file_or_directory_error(algo, argv[i]);
				continue;
		}
		if (argv[i][0] != '-')
		{
			int j = get_algorithm_index(algo);
			if (j != -1)
				algorithms[j].process_input(argv[i], false, flags);
		}
	}
}