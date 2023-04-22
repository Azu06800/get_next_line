/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihamdan <nihamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 12:34:04 by nihamdan          #+#    #+#             */
/*   Updated: 2023/04/22 13:50:57 by nihamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	if (!(s))
		return (0);
	while (s && *s != 0)
	{
		s++;
		len++;
	}
	return (len);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	res;

	res = 0;
	if (size > 0)
	{
		while (size > 0 && src[res])
		{
			dest[res] = src[res];
			res++;
			size--;
		}
		dest[res] = 0;
	}
	while (src[res] != 0)
	{
		res++;
	}
	return (res);
}

char	*ft_strdup(char *s)
{
	char			*dest;
	int				dest_len;

	if (!s)
		return (NULL);
	dest_len = ft_strlen(s);
	dest = malloc(sizeof(char) * (dest_len + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s, dest_len + 1);
	free(s);
	s = NULL;
	return (dest);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*dst;
	char	*str;
	size_t	i;

	i = 0;
	dst = malloc(count * size);
	if (!dst)
		return (NULL);
	str = dst;
	while (i < count * size)
		str[i++] = '\0';
	dst = str;
	return (dst);
}

char	*ft_strcat(char *dest, char *src)
{
	size_t	i;
	size_t	j;

	if (!dest)
		return (NULL);
	if (!src)
		return (dest);
	i = ft_strlen(dest);
	j = 0;
	while (src[j] != 0)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = 0;
	return (dest);
}
