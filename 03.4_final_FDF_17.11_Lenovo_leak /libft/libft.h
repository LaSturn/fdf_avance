/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturny <csturny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:23:37 by csturny           #+#    #+#             */
/*   Updated: 2025/01/22 10:08:00 by csturny          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *ptr1, const void *ptr2, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t len);
void	*ft_memset(void *ptr, int value, size_t count);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *str, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr( const char *str, int searchedChar);
char	*ft_strdup(const char *src);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strnstr(const char *str, const char *to_f, size_t len);
char	*ft_strrchr(const char *str, int searchLastChar);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_substr(const char *src, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);

/* --- ajout apres rendu cercle 0 --------*/
char	*get_next_line(int fd);
int	ft_atoi_base(const char *str, int str_base);

#endif
