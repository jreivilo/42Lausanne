#ifndef FT_SSL_H
# define FT_SSL_H

# define SUCCESS 0
# define ERROR -1

# define STDIN 0
# define STDOUT 1
# define STDERR 2

#define BUFFER_SIZE 1024

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>

#include <flag.h>
#include <parsing.h>
#include <print.h>
#include <error.h>

#include <md5.h>
#include <sha256.h>

#include "../libft/libft.h"

#endif