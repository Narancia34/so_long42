/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamraou <mgamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:10:22 by mgamraou          #+#    #+#             */
/*   Updated: 2024/11/26 10:04:59 by mgamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*get_strchr(const char *str, int ch)
{
	while (*str != '\0')
	{
		if (*str == (char)ch)
			return ((char *)str);
		str++;
	}
	if ((char)ch == '\0')
		return ((char *)str);
	return (0);
}

char	*get_strjoin(char *s1, char *s2)
{
	int		total_len;
	char	*str;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	total_len = get_strlen(s1) + get_strlen(s2) + 1;
	str = (char *)malloc(total_len * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[i - get_strlen(s1)])
	{
		str[i] = s2[i - get_strlen(s1)];
		i++;
	}
	str[i] = '\0';
	free (s1);
	return (str);
}

void	*get_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst != src)
	{
		while (i < n)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

char	*get_strdup(const char *s1)
{
	char	*str;
	size_t	len;

	len = get_strlen(s1);
	str = (char *)malloc((len + 1) * (sizeof(char)));
	if (!str)
		return (NULL);
	get_memcpy(str, s1, len);
	str[len] = '\0';
	return (str);
}
