#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

void append(t_list **list, char *buf);
void polish_list(t_list **list);
void ft_copy_str(t_list *list, char *str);

int ft_found_newline(t_list *list) {
  int i;

  if (NULL == list)
    return (0);
  while (list) {
    i = 0;
    while (list->str_buf[i] && i < BUFFER_SIZE) {
      if (list->str_buf[i] == '\n')
        return (1);
      ++i;
    }
    list = list->next;
  }
  return (0);
}

void create_list(t_list **list, int fd) {
  int char_read;
  char *buf;

  while (!ft_found_newline(*list)) {
    buf = malloc(BUFFER_SIZE + 1);
    if (NULL == buf)
      return;
    char_read = read(fd, buf, BUFFER_SIZE);
    if (!char_read) {
      free(buf);
      return;
    }
    buf[char_read] = '\0';
    append(list, buf);
  }
}



int len_to_newline(t_list *list) {
  int i;
  int len;

  if (NULL == list)
    return (0);
  len = 0;
  while (list) {
    i = 0;
    while (list->str_buf[i]) {
      if (list->str_buf[i] == '\n') {
        ++len;
        return (len);
      }
      ++i;
      ++len;
    }
    list = list->next;
  }
  return (len);
}
char *get_line(t_list *list) {
  int str_len;
  char *next_str;

  if (NULL == list)
    return (NULL);
  str_len = len_to_newline(list);
  next_str = malloc(str_len + 1);
  if (NULL == next_str)
    return (NULL);
  ft_copy_str(list, next_str);
  return (next_str);
}

char *get_next_line(int fd) {
  static t_list *list = NULL;
  char *next_line;

  if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
    return (NULL);
  create_list(&list, fd);
  if (list == NULL)
    return (NULL);
  next_line = get_line(list);
  polish_list(&list);
  return (next_line);
}
