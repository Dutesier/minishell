#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 420
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 420
# endif

char *get_next_line(int fd);
char *ft_substr(char *str, int start, int ammount);
char *store_buffer(char *holder, char *buff);
char *store_line(char **line, char *holder, int ret);

#endif
