/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihamdan <nihamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 12:25:28 by nihamdan          #+#    #+#             */
/*   Updated: 2023/04/22 13:50:49 by nihamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	read_and_stash(int fd, char **stash)
{
	char	*buf;
	char	*tmp;
	size_t	read_size;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size <= 0)
	{
		free(buf);
		return (read_size);
	}
	tmp = ft_strdup(*stash);
	*stash = ft_calloc(ft_strlen(tmp) + ft_strlen(buf) + 1, sizeof(char));
	*stash = ft_strcat(*stash, tmp);
	*stash = ft_strcat(*stash, buf);
	free(tmp);
	free(buf);
	tmp = NULL;
	buf = NULL;
	return (read_size);
}

char	*copy_and_clean(char **stash, size_t i, long read_size)
{
	char	*line;
	char	*tmp;

	tmp = NULL;
	line = ft_calloc(i + 1, sizeof(char));
	if (ft_strlen(*stash) > i)
	{
		tmp = ft_calloc(ft_strlen(*stash) - (i - 1), sizeof(char));
		tmp = ft_strcat(tmp, *stash + (i));
	}
	ft_strlcpy(line, *stash, i);
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	*stash = ft_strdup(tmp);
	if (!read_size && !(line))
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	return (line);
}

int	extract_line_2(char **stash, int fd, long *read_size, long *read_max)
{
	long	i;

	i = 0;
	while ((*stash)[i] != '\n' && *read_size != 0)
	{
		if (i < *read_max)
			i++;
		else if (i == *read_max)
		{
			*read_size = read_and_stash(fd, stash);
			if (*read_size == -1)
			{
				free(*stash);
				*stash = NULL;
				return (-2);
			}
			*read_max += *read_size;
		}
	}
	if ((*stash)[i] == '\n')
		i++;
	return (i);
}

char	*extract_line(int fd, char **stash)
{
	long	i;
	long	read_size;
	long	read_max;
	char	*line;

	read_max = 0;
	read_size = 1;
	if (*stash)
		read_max = ft_strlen(*stash);
	i = extract_line_2(stash, fd, &read_size, &read_max);
	if (i == -2)
		return (NULL);
	line = copy_and_clean(stash, i, read_size);
	if (read_size == 0 && *stash != NULL)
	{
		free(*stash);
		*stash = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*stash[OPEN_MAX];
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, line, 0) < 0)
	{
		if (stash[fd])
			free(stash[fd]);
			stash[fd] = NULL;
		return (NULL);
	}
	if (!stash[fd])
		stash[fd] = ft_calloc(1, 1);
	line = extract_line(fd, &(stash[fd]));
	if (line == NULL || line[0] == '\0')
	{
		free(stash[fd]);
		free(line);
		stash[fd] = NULL;
		return (NULL);
	}
	return (line);
}
