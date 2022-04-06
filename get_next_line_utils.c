/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzima <lzima@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:31:45 by lzima             #+#    #+#             */
/*   Updated: 2022/01/10 22:35:04 by lzima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief 
 * Calling your function get_next_line in a loop will then allow you to read 
 * the text available on the file descriptor one line at a time until the end 
 * of it.
 * 
 * @param
 * File descriptor to read from
 * example : test.txt 
 * 
 * @return
 * Read line: correct behavior
 * (null): nothing else to read or an error occurred
 * 
 * @fn
 * char	*ft_strjoin(char const *s1, char const *s2)
 * 
 * @fn
 * size_t	ft_strlen(const char *str)
 * 
 * @fn
 * void	*ft_bzero(void *s, size_t n)
 * 
 * @fn
 * char	*ft_strdup(char *s1)
 * 
 * @fn
 * char	*ft_substr(char const *s, unsigned int start, size_t len)
 * 
 * @see
 * 
 */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char const	*s2)
{
	int		len;
	char	*res;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != (char)c)
		i++;
	if (str[i] == (char)c)
		return (&((char *)str)[i]);
	if (str[i] == '\0' && (char)c == '\0')
		return (&((char *)str)[i]);
	return (NULL);
}

int	ft_strlen(const char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	int		slen;
	int		i;
	char	*str;

	slen = ft_strlen((char *)s1);
	i = -1;
	str = (char *)malloc(slen + 1);
	if (!str)
		return (NULL);
	while (++i < slen)
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && start < (unsigned int)ft_strlen(s))
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
