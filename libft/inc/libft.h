/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:58:53 by ebayat            #+#    #+#             */
/*   Updated: 2024/07/20 14:11:22 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define HEX_BASE "012346789ABCDEF"
# define EXIT_ERROR -1

# define MALLOC_FAIL 9223372036854775807

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* IO */
int			ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(char *s, int fd);
int			ft_putendl_fd(char *s, int fd);
int			ft_putnbr_fd(int n, int fd);

/* Nums */
uint64_t	ft_abs(int64_t val);
char		*ft_itoa(int n);
int			ft_atoi(const char *str);
int64_t		ft_atol(const char *str);
uint32_t	ft_hex_to_uint(const char *str);

/* Chars */
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
uint32_t	ft_get_hex_value(int c);
uint32_t	ft_ishex(int c);

uint32_t	ft_isnl(int c);
uint32_t	ft_isspace(int c);
uint32_t	ft_istab(int c);
uint32_t	ft_iswhitespace(int c);

/* Strs */
char		*ft_strdup(const char *s1);
char		*ft_strndup(const char *src, size_t n);

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);

char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);

int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

char		*ft_strnstr(const char *big, const char *small, size_t len);

void		ft_striteri(char *s, void (*f)(uint32_t, char*));
char		*ft_strmapi(const char *s, char (*f)(uint32_t, char));
char		*ft_strtrim(const char *s1, const char *set);

char		*ft_strjoin(const char *s1, const char *s2);
char		**ft_split(const char *s, char c);
char		*ft_substr(const char *s, uint32_t start, size_t len);

size_t		ft_strlen(const char *s);
size_t		ft_array_len(const char **array);
size_t		ft_count_words(const char *str, char delimiter);

/* Memory */
char		*ft_alloc(char *str);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);

void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
void		*ft_memset(void *b, int c, size_t len);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

void		ft_free_and_null(char **ptr);
void		ft_free_strs(char ***array);
void		ft_free_n_strs( size_t i, char ***array);

/* Printf */
int			ft_printf(const char *format, ...);
int			ft_put_address(void *ptr);
int			ft_puthex(uint64_t num, const char *upper_or_lower);
int			ft_put_unum(uint64_t n);
size_t		ft_hex_len(uint64_t num);

/* get_next_line*/
char		*get_next_line(int fd);
void		update_buffer(char **line, char **buffer);
void		extract_line_from_buffer(char **line, char **buffer);
void		read_to_buffer(int fd, char **buffer);

size_t		gnl_strlen(char *s);
char		*gnl_strchr(char *s, int c);
void		gnl_strjoin(char **buffer, char *recently_read);

/* List */
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
