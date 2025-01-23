/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:01:32 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/17 14:53:59 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	restore_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map->full[y][x])
		{
			if (game->map->full[y][x] == 'e')
				game->map->full[y][x] = EXIT;
			else if (game->map->full[y][x] == 'c')
				game->map->full[y][x] = COLLECTIBLE;
			else if (game->map->full[y][x] == 'o')
				game->map->full[y][x] = EMPTY_SPACE;
			x++;
		}
		y++;
	}
}

static bool	update_tile(t_game *game, int y, int x, int *c_count)
{
	if (game->map->full[y][x] == 'E')
	{
		game->exit_flag = 1;
		game->map->full[y][x] = 'e';
		if (*c_count == 0)
			return (false);
	}
	else if (game->map->full[y][x] == 'C')
	{
		(*c_count)--;
		game->map->full[y][x] = 'c';
		if (*c_count == 0 && game->exit_flag)
			return (false);
	}
	else if (game->map->full[y][x] == '0')
		game->map->full[y][x] = 'o';
	return (true);
}

static bool	ft_floodfill(t_game *game, int y, int x, int *c_count)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (true);
	if (game->map->full[y][x] == '1' || game->map->full[y][x] == 'c'
		|| game->map->full[y][x] == 'o' || game->map->full[y][x] == 'e')
		return (true);
	if (!update_tile(game, y, x, c_count))
		return (false);
	if (ft_floodfill(game, (y - 1), x, c_count)
		&& ft_floodfill(game, (y + 1), x, c_count)
		&& ft_floodfill(game, y, (x - 1), c_count)
		&& ft_floodfill(game, y, (x + 1), c_count))
		return (true);
	return (false);
}

void	validate_path(t_game *game)
{
	int	x;
	int	y;
	int	c_count;

	y = 0;
	c_count = game->collectible_count;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map->full[y][x])
		{
			if (game->map->full[y][x] == PLAYER)
			{
				ft_floodfill(game, y, x, &c_count);
				if (c_count != 0)
					handle_error("One or more collectibles are inaccessible.",
						game);
				if (game->exit_flag == 0)
					handle_error("The Exit is not accessible!", game);
				restore_map(game);
			}
			x++;
		}
		y++;
	}
}
