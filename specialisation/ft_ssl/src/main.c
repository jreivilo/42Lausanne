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
    uint32_t state[8];
    struct BUFFER_STATE buffstate;
    const uint8_t text[] = "42 is nice";
    uint8_t hash[32];
    size_t len = strlen((char *)text);

    sha256_init(state, &buffstate);
    sha256_update(state, &buffstate, text, len);
    sha256_final(state, &buffstate, hash);

    printf("SHA-256 of '%s':\n", text);
    for (int i = 0; i < 32; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

	(void) argc;
	(void) argv;

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
