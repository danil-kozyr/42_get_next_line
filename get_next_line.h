/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkozyr <dkozyr@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:07:30 by dkozyr            #+#    #+#             */
/*   Updated: 2018/11/07 19:07:30 by dkozyr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft/includes/libft.h"
# include <fcntl.h>

# define BUFF_SIZE 20

# define PRE_ERRORS() if (fd < 0 || fd > 4096 || !line) return (-1);
# define ERR_CHECKER() POST_ERRORS() ENDFILE();
# define POST_ERRORS() if (ret < 0) return (-1);
# define ENDFILE() if (ret == 0 && (!str[fd] || str[fd][0] == '\0')) return (0);

int		get_next_line(const int fd, char **line);

#endif
