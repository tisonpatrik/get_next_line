
#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10

#endif
typedef struct s_list {
  char *str_buf;
  struct s_list *next;
} t_list;

char *get_next_line(int fd);

#endif
