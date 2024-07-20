#include <parsing.h>

void handle_input_md5(char *input, bool is_string, ft_flags flags) {
    MD5_CTX context;
    MD5Init(&context);
    unsigned char digest[16];
    char buffer[BUFFER_SIZE];
    int bytes_read;

    if (is_string) {
        MD5Update(&context, (unsigned char*)input, ft_strlen(input));
    } else {
        int fd = open(input, O_RDONLY);
		if (fd < 0) {
			write(STDERR, "ft_ssl: ", 8);
			write(STDERR, "md5", 3);
			write(STDERR, ": ", 2);
			write(STDERR, input, strlen(input));
			write(STDERR, ": No such file or directory\n", 29);
			return;
		}
        while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
            MD5Update(&context, (unsigned char*)buffer, bytes_read);
        }
        close(fd);
    }
    MD5Final(digest, &context);
	char hex_output[33];
	for (int i = 0; i < 16; i++) {
		hex_output[i*2] = "0123456789abcdef"[digest[i] / 16];
		hex_output[i*2 + 1] = "0123456789abcdef"[digest[i] % 16];
	}
	hex_output[32] = '\0';

    if (is_string) {
		print_algo(hex_output, input, "md5", flags, false, false);
	} else {
		print_algo(hex_output, input, "md5", flags, false, true);
	}
}

void process_md5(int argc, char *argv[], ft_flags flags, int is_file_or_string) {
    // If flag p, read stdin
	if (flags.p || (is_file_or_string == 0)) {
		char buffer[BUFFER_SIZE];
		int bytes_read;
		MD5_CTX context;
		MD5Init(&context);

		while ((bytes_read = read(STDIN, buffer, BUFFER_SIZE)) > 0) {
			buffer[bytes_read] = '\0';
			MD5Update(&context, (unsigned char*) buffer, bytes_read);
		}
		unsigned char digest[16];
		MD5Final(digest, &context);
		char hex_output[33];
		for (int i = 0; i < 16; i++) {
			hex_output[i*2] = "0123456789abcdef"[digest[i] / 16];
			hex_output[i*2 + 1] = "0123456789abcdef"[digest[i] % 16];
		}
		hex_output[32] = '\0';
		print_algo(hex_output, buffer, "md5", flags, true, false);
	}

	int i = 2;
	for (; i < argc; i++) {
		if (argv[i][0] == '-' && argv[i][1] == 's' && argv[i][2] == '\0' && i + 1 < argc && flags.s == false) {
			flags.s = true;
			// Handle the string
			i++;
			handle_input_md5(argv[i], true, flags);
			continue;
		}
		if (argv[i][0] == '-' && argv[i][1] == 's' && argv[i][2] == '\0' && flags.s == true) {
				write(STDERR, "ft_ssl: ", 8);
				write(STDERR, argv[1], ft_strlen(argv[1]));
				write(STDERR, ": ", 2);
				write(STDERR, argv[i], ft_strlen(argv[i]));
				write(STDERR, ": No such file or directory\n", 29);
				continue;
		}
		if (argv[i][0] != '-')
			handle_input_md5(argv[i], false, flags);
	}
}