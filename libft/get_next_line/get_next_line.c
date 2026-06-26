/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 19:49:38 by mstepnic          #+#    #+#             */
/*   Updated: 2025/05/13 18:21:09 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

char	*get_next(char *line)
{
	char	*next_line;
	size_t	nl_index;
	size_t	line_len;

	nl_index = ft_strlen_to_char(line, '\n');
	line_len = ft_strlen_to_char(line, 0);
	if (nl_index == line_len)
	{
		free(line);
		return (NULL);
	}
	next_line = ft_substr(line, nl_index + 1, line_len - nl_index);
	if (!next_line)
		return (NULL);
	free(line);
	return (next_line);
}

char	*get_line(char *line)
{
	char	*temp_line;
	size_t	nl_index;
	int		is_nl;

	if (!*line)
		return (NULL);
	is_nl = 0;
	nl_index = ft_strlen_to_char(line, '\n');
	if (nl_index != ft_strlen_to_char(line, 0))
		is_nl = 1;
	temp_line = ft_substr(line, 0, nl_index + is_nl);
	if (!temp_line)
		return (NULL);
	temp_line[nl_index + is_nl] = 0;
	return (temp_line);
}

char	*read_line(int fd, char	*line)
{
	char	*temp_line;
	int		bytes_read;

	temp_line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line || !temp_line)
		return (NULL);
	bytes_read = BUFFER_SIZE;
	while (bytes_read > 0 && bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, temp_line, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(line);
			free(temp_line);
			return (NULL);
		}
		temp_line[bytes_read] = 0;
		line = ft_join_and_free(line, temp_line);
		if (ft_strchr(line, '\n'))
			break ;
	}
	free(temp_line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*next_line[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!next_line[fd])
		next_line[fd] = ft_calloc(1, sizeof(char));
	next_line[fd] = read_line(fd, next_line[fd]);
	if (!next_line[fd])
		return (NULL);
	line = get_line(next_line[fd]);
	next_line[fd] = get_next(next_line[fd]);
	if (next_line[fd] && !next_line[fd][0])
	{
		free(next_line[fd]);
		next_line[fd] = NULL;
	}
	return (line);
}
