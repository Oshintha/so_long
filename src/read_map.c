/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:06:40 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/13 11:25:37 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	open_map_file(char *map_file_name)
{
	int	fd;

	fd = open(map_file_name, O_RDONLY);
	if (fd <= 0)
		handle_error("Error: Could not open map file.", NULL);
	return (fd);
}

static void	init_map_structure(t_game *game, size_t height)
{
	size_t	i;

	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		handle_error("Memory allocation failed for game->map.", game);
	game->map->full = ft_calloc(height, sizeof(char *));
	if (!game->map->full)
		handle_error("Memory allocation failed for game->map->full.", game);
	i = 0;
	while (i < height)
	{
		game->map->full[i] = NULL;
		i++;
	}
}

// Helper function to handle map_line allocation error
// related to one edge case in get_next_line
// where if reading one line failed, the entire map should be
// read to the end before freeing allocated memory.
static void	handle_allocation_error(int fd, t_game *game, char *map_line)
{
	free(map_line);
	while (1)
	{
		map_line = get_next_line(fd);
		if (!map_line)
			break ;
		free(map_line);
	}
	close(fd);
	handle_error("Memory allocation failed for line.", game);
}

// Read map line one by one using get_next_line()
// Check if the first line is empty.
// Inside the loop: Process the first line and continue reading remaining lines
// Handle case where file ends prematurely
static void	read_map_lines(int fd, t_game *game)
{
	char	*map_line;
	int		i;

	i = 0;
	while (i < game->map_height)
	{
		map_line = get_next_line(fd);
		if (!map_line)
		{
			if(i< game->map_height)
            	handle_error("Invalid line length in map file.", game);
			else
            handle_error("Unexpected end of file in map.", game);
		}
		game->map->full[i] = ft_calloc(game->map_width + 1, sizeof(char));
		if (!game->map->full[i])
			handle_allocation_error(fd, game, map_line);
		ft_strlcpy(game->map->full[i], map_line, game->map_width + 1);
		free(map_line);
		i++;
	}
}

// Get's map dimensions and copies the file map
// into a 2d array for use in the game.
// Closes the file descriptor (fd) if valid.
// Handles error and exits the game if file is too big:
// Map size limit width: 60, height: 32.
// (This limit is based on my current computer screen size).
void	read_map(char *map_file_name, t_game *game)
{
	int		fd;
	size_t	height;
	size_t	width;

	width = 0;
	fd = open_map_file(map_file_name);
	height = get_map_dimensions(fd, &width);
	init_map_structure(game, height);
	game->map_width = width;
	game->map_height = height;
	if (fd >= 0)
		close(fd);
	fd = open_map_file(map_file_name);
	read_map_lines(fd, game);
	if (fd >= 0)
		close(fd);
	if (width > 60 || height > 32)
		handle_error("The map is too big.", game);
}