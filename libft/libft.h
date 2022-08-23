#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>



size_t	ft_strlen(char *str);
void *ft_memset(void *str, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void *ft_memmove(void *str1, const void *str2, size_t n);
void *ft_memchr(const void *str, int c, size_t n);
int ft_memcmp(const void *str1, const void *str2, size_t n);
char *ft_strdup(const char *s);

int	ft_atoi(char *str);

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size);

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size);
int	ft_strncmp(char *s1, char *s2, unsigned int n);

int ft_isalnum(int c);
int ft_isalpha(int c);
int ft_isascii(int c);
int ft_isdigit(int c);
int ft_isprint(int c);

#endif