/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_dimensions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:22:14 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/17 14:29:25 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static size_t	get_trimmed_length(char *line)
{
	size_t	line_len;

	line_len = ft_strlen(line);
	while (line_len > 0 && (line[line_len - 1] == '\n'
			|| line[line_len - 1] == '\r'))
		line_len--;
	return (line_len);
}

static size_t	find_height(int fd, char *line, size_t height, size_t *width)
{
	size_t	line_len;

	line = get_next_line(fd);
	if (!line)
		exit(1);
	while (line != NULL)
	{
		line_len = get_trimmed_length(line);
		if (line_len != *width)
		{
			free(line);
			handle_error("Inconsistent map line widths.", NULL);
		}
		height++;
		free(line);
		line = get_next_line(fd);
	}
	return (height);
}

size_t	get_map_dimensions(int fd, size_t *width)
{
	char	*line;
	size_t	height;

	line = get_next_line(fd);
	if (!line)
		return (0);
	*width = get_trimmed_length(line);
	free(line);
	height = 1;
	height = find_height(fd, line, height, width);
	return (height);
}
