/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhamdan <nhamdan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 13:33:41 by nhamdan           #+#    #+#             */
/*   Updated: 2022/04/28 13:37:30 by nhamdan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_only_line(char *buf)
{
	char	*only_line;
	int		sbuf;
	int		sal;

	if (buf == NULL)
		return (NULL);
	sbuf = ft_strlen(buf);
	sal = ft_strlen(ft_strchr(buf, '\n')) - 1;
	only_line = (char *) malloc(sbuf - sal + 1);
	ft_strlcpy(only_line, buf, sbuf - sal + 1);
	return (only_line);
}

char	*buf_line(char	*buf, char	*only_line)
{
	char	*rbuf;
	int		sline;
	int		stot;

	if (buf == NULL || only_line == NULL)
		return (NULL);
	stot = ft_strlen(buf);
	sline = ft_strlen(only_line);
	if (sline <= 0)
	{
		free(buf);
		return (NULL);
	}
	rbuf = malloc(stot - sline + 1);
	ft_strlcpy(rbuf, buf + sline, stot - sline + 1);
	free(buf);
	return (rbuf);
}

static	char	*gnl_cat(char	*buf, char	*mbufsize)
{
	char	*rbuf;
	int		sbuf;
	int		smbuf;

	if (buf == NULL || mbufsize == NULL)
		return (NULL);
	sbuf = ft_strlen(buf) + 1;
	smbuf = ft_strlen(mbufsize);
	rbuf = malloc(sbuf + smbuf);
	ft_strlcpy(rbuf, buf, sbuf);
	ft_strcat(rbuf, mbufsize);
	free(buf);
	return (rbuf);
}

static char	*get_line(int fd, char	*buf)
{
	char	*mbufsize;
	int		ret;

	mbufsize = (char *) malloc(BUFFER_SIZE + 1);
	if (!mbufsize)
	{
		free(mbufsize);
		free(buf);
		return (NULL);
	}
	ret = 42;
	while (ret && !ft_strchr(buf, '\n'))
	{
		ret = read(fd, mbufsize, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buf);
			free(mbufsize);
			return (NULL);
		}
		mbufsize[ret] = 0;
		buf = gnl_cat(buf, mbufsize);
	}
	free(mbufsize);
	return (buf);
}

char	*get_next_line(int fd)
{
	char static	*buf[OPEN_MAX];
	char		*only_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buf[fd])
		buf[fd] = ft_calloc(1, 1);
	buf[fd] = get_line(fd, buf[fd]);
	if (buf[fd] == NULL)
		return (NULL);
	only_line = get_only_line(buf[fd]);
	buf[fd] = buf_line(buf[fd], only_line);
	if (only_line[0] == '\0')
	{
		free(buf[fd]);
		free(only_line);
		return (NULL);
	}
	return (only_line);
}
