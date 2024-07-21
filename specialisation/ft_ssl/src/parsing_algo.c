#include <parsing.h>


void process_algo(int argc, char *argv[], char *algo, ft_flags flags, int is_file_or_string) {
    // If flag p, read stdin
	if (flags.p || (is_file_or_string == 0)) {
		if (ft_strcmp(algo, "md5") == 0)
			process_md5_stdin(flags);
		else if (ft_strcmp(algo, "sha256") == 0)
			process_sha256_stdin(flags);
	}

	int i = 2;
	for (; i < argc; i++) {
		if (argv[i][0] == '-' && argv[i][1] == 's' && argv[i][2] == '\0' && i + 1 < argc && flags.s == false) {
			flags.s = true;
			// Handle the string
			i++;
			if (ft_strcmp(algo, "md5") == 0)
				process_md5_input(argv[i], true, flags);
			else if (ft_strcmp(algo, "sha256") == 0)
				process_sha256_input(argv[i], true, flags);
			continue;
		}
		if (argv[i][0] == '-' && argv[i][1] == 's' && argv[i][2] == '\0' && flags.s == true) {
				write_file_or_directory_error(algo, argv[i]);
				continue;
		}
		if (argv[i][0] != '-')
		{
		    if (ft_strcmp(algo, "md5") == 0)
				process_md5_input(argv[i], false, flags);
			else if (ft_strcmp(algo, "sha256") == 0)
				process_sha256_input(argv[i], false, flags);
		}
	}
}