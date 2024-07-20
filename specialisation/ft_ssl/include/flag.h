#ifndef FLAG_H
# define FLAG_H

#include <stdbool.h>

typedef struct {
    bool p;   // echo STDIN to STDOUT and append the checksum to STDOUT
    bool q;   // quiet mode
    bool r;   // reverse the format of the output
    bool s;   // print the sum of the given string
} ft_flags;

#endif