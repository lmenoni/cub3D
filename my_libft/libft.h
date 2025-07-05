/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:14:17 by lmenoni           #+#    #+#             */
/*   Updated: 2025/06/09 19:03:52 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}			t_list;

void		ft_bzero(void *str, size_t len);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
void		*ft_memcpy(void *dst, const void *str, size_t n);
void		*ft_memmove(void *dst, const void *str, size_t n);
void		*ft_memset(void *str, int c, size_t len);
size_t		ft_strlcpy(char *dst, const char *str, size_t n);
size_t		ft_strlen(const char *str);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
void		*ft_memchr(const void *s, int c, size_t n);
size_t		ft_strlcat(char *d, const char *s, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *big, const char *lil, size_t len);
int			ft_atoi(const char *s);
void		*ft_calloc(size_t slot, size_t size);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		**ft_split(char const *str, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putendl_fd(char *s, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *n);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *n);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_putchar_fd(char c, int fd);
int			ft_printunsnbr(unsigned int n, int fd);
int			ft_printhexa(unsigned int n, int fd);
int			ft_printpointer(unsigned long p, int fd);
int			ft_printupphexa(unsigned int n, int fd);
int			ft_printstr(char *s, int fd);
int			ft_printnbr(int n, int fd);
int			ft_printf(const char *in, ...);
int			ft_printf_fd(int fd, const char *in, ...);
char		*get_next_line(int fd);
char		*ft_buffjoin(char *s1, char *s2);
size_t		ft_bufflen(const char *str);
char		*ft_find(const char *s, int c);
void		ft_freemat(void **mat, size_t j);
int			ft_matlen(char **mat);
char		*ft_merge(char *s1, char *s2);
char		*ft_strndup(const char *s, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
long long	ft_atoll(const char *nptr);
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_matdup(char **mat);
void		skip_spaces(char *s, int *i);
int			is_space(char c);
int			is_quoted(char *s, char *to_check);
int			ft_strnncmp(char *s1, char *s2, int n1, int n2);

#endif
