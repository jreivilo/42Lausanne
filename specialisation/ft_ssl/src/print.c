#include <print.h>

void print_algo(char *hash, char *input, char *algo, ft_flags flags, bool is_stdin, bool is_file) {
    if (flags.q) {
		if (is_stdin) {
			write(STDOUT, input, ft_strlen(input) - 1);
			write(STDOUT, "\n", 1);
		}
        write(STDOUT, hash, ft_strlen(hash));
        write(STDOUT, "\n", 1);
        return;
    }

    // STDIN ONLY
    if (is_stdin) {
        if (flags.p) {
            write(STDOUT, "(\"", 2);
            write(STDOUT, input, ft_strlen(input) - 1);
            write(STDOUT, "\")= ", 4);
            write(STDOUT, hash, ft_strlen(hash));
            write(STDOUT, "\n", 1);
        } else {
            write(STDOUT,"(stdin)= ", 9);
            write(STDOUT, hash, ft_strlen(hash));
            write(STDOUT, "\n", 1);
        }
    } else { // STRING + FILE
        if (input) {
            if (flags.r) {
				if (is_file) {
					write(STDOUT, hash, ft_strlen(hash));
					write(STDOUT, " ", 1);
					write(STDOUT, input, ft_strlen(input));
					write(STDOUT, "\n", 1);
				}
                else {
					write(STDOUT, hash, ft_strlen(hash));
					write(STDOUT, " \"", 2);
					write(STDOUT, input, ft_strlen(input));
					write(STDOUT, "\"\n", 2);
                }
            } else {
				if (is_file) {
					write(STDOUT, algo, ft_strlen(algo));
					write(STDOUT, " (", 2);
					write(STDOUT, input, ft_strlen(input));
					write(STDOUT, ") = ", 4);
					write(STDOUT, hash, ft_strlen(hash));
					write(STDOUT, "\n", 1);
				}
                else {
					write(STDOUT, algo, ft_strlen(algo));
					write(STDOUT, " (\"", 3);
					write(STDOUT, input, ft_strlen(input));
					write(STDOUT, "\") = ", 5);
					write(STDOUT, hash, ft_strlen(hash));
					write(STDOUT, "\n", 1);
                }
            }
		} else {
			if (flags.r) {
			write(STDOUT, hash, ft_strlen(hash));
			write(STDOUT, "\n", 1);
			} else {
			write(STDOUT, algo, ft_strlen(algo));
			write(STDOUT, " (\"", 3);
			write(STDOUT, input, ft_strlen(input));
			write(STDOUT, "\") = ", 5);
			write(STDOUT, hash, ft_strlen(hash));
			write(STDOUT, "\n", 1);
			}
		}
    }
}