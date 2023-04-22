/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihamdan <nihamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 12:34:36 by nihamdan          #+#    #+#             */
/*   Updated: 2023/04/22 12:35:14 by nihamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <limits.h>

size_t	ft_strlen(char *s);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(char *s);
char	*ft_strcat(char *dest, char *src);
char	*get_next_line(int fd);

#endif
