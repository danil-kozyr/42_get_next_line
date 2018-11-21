/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkozyr <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:07:33 by dkozyr            #+#    #+#             */
/*   Updated: 2018/11/07 19:08:11 by dkozyr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_new_line(char **str, char **line, int fd)
{
	char			*tmp;
	int				i;

	i = 0;
	while (str[fd][i] != '\0' && str[fd][i] != '\n')
		i++;
	if (str[fd][i] == '\n')
	{
		*line = ft_strsub(str[fd], 0, i);
		tmp = ft_strdup(str[fd] + i + 1);
		ft_strdel(&str[fd]);
		str[fd] = tmp;
	}
	else if (str[fd][i] == '\0')
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
	}
}

int		get_next_line(const int fd, char **line)
{
	static char		**str;
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	int				ret;

	PRE_ERRORS();
	if (!str && !(str = (char **)ft_memalloc(sizeof(char *) * 4096)))
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!str[fd] && !(str[fd] = ft_strnew(1)))
			return (-1);
		tmp = ft_strjoin(str[fd], buf);
		free(str[fd]);
		str[fd] = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	ERR_CHECKER();
	ft_new_line(str, line, fd);
	return (1);
}
