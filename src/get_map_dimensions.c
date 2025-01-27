/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_dimensions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:22:14 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/27 11:50:56 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_gnl(char *line, int fd)
{
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

static size_t	get_trimmed_length(char *line)
{
	char	*start;
	char	*end;

	start = line;
	while (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r')
		start++;
	if (*start == '\0')
		return (0);
	end = start + strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'
			|| *end == '\r'))
		end--;
	*(end + 1) = '\0';
	return (strlen(start));
}

static void	validate_line(char *line, size_t height, t_map_data *map_data)
{
	size_t	line_len;

	line_len = get_trimmed_length(line);
	if (line_len == 0 && height > 0)
	{
		free_gnl(line, map_data->fd);
		handle_error("Empty or whitespace-only line detected in the map."
				, map_data->game);
	}
	if (line_len != *(map_data->width))
	{
		free_gnl(line, map_data->fd);
		handle_error("Inconsistent map line widths detected.", map_data->game);
	}
}

static size_t	find_height(t_map_data *map_data)
{
	char	*line;
	size_t	height;

	line = get_next_line(map_data->fd);
	height = 1;
	if (!line)
	{
		free_gnl(line, map_data->fd);
		handle_error("Incorrect map, essential requirements not met.", map_data->game);
	}
	while (line != NULL)
	{
		validate_line(line, height, map_data);
		height++;
		free(line);
		line = get_next_line(map_data->fd);
	}
	return (height);
}

size_t get_map_dimensions(int fd, size_t *width, t_game *game)
{
    char        *line;
    size_t      height;
    t_map_data  map_data;

    map_data.fd = fd;
    map_data.width = width;
    map_data.game = game;

    line = get_next_line(fd);
    if (!line)
        return (0);
    *width = get_trimmed_length(line);
    if (*width == 0)
    {
        free_gnl(line, fd);
        handle_error("Empty or whitespace-only first line in the map detected.", game);
    }
    free(line);
    height = find_height(&map_data);
    return (height);
}

