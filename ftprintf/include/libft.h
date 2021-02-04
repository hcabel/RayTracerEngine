/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 22:55:37 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 15:02:55 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>

# define FABS(x) ((double)(x > 0.0 ? x : -x))

# define BUFF_SIZE 90
# define GNL_ERROR -1
# define GNL_OK 1
# define GNL_END 0

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_gnl
{
	int				fd;
	char			*line;
	char			*temp;
	struct s_gnl	*next;
}					t_gnl;

/*
**	ft_is...
*/
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
size_t				ft_is_prime(size_t nb);
int					ft_isprint(int c);

void				ft_lstadd(t_list **alst, t_list *new);
t_list				*ft_lstnew(void const *content, size_t content_size);

void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);

int					ft_atoi_base(const char *nbr, unsigned int base);
int					ft_atoi(const char *str);
int					ft_baselen(long long nbr, int base);
void				ft_bzero(void *s, size_t n);
char				*ft_convert_base(char *nbr, char *base_from, char *base_to);
char				*ft_itoa_base(long long nbr, int base);
char				*ft_itoa(long long n);
int					ft_nbrlen(long long nbr);
size_t				ft_sqrt(size_t nb);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					get_next_line(const int fd, char **line);
char				*ft_ftoa(long double n, int precis);
int					ft_ubaselen(unsigned long long nbr, int base);
char				*ft_utoa_base(unsigned long long nbr, int base, char c);

void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(const char *s, int fd);

char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
int					ft_strequ(char const *s1, char const *s2);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strndup(const char *s1, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *haystack, char *needle, size_t len);
char				*ft_strrchr(const char *s, int c);
char				**ft_strsplit(const char *str, char c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtolower(char *str);
char				*ft_strtrim(char const *s);

#endif
