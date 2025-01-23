/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:44:31 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/17 14:53:36 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	validate_tile(t_game *game, char tile)
{
	if (!(tile == 'P' || tile == 'E' || tile == 'C'
			|| tile == '1' || tile == '0' || tile == '\r'))
		handle_error("Invalid character detected.", game);
	if (tile == 'P')
		(game->player_count)++;
	if (tile == 'E')
		(game->exit_count)++;
	if (tile == 'C')
		(game->collectible_count)++;
}

static void	validate_wall(t_game *game, char tile, int x, int y)
{
	if ((y == 0 || x == 0 || y == game->map_height - 1
			|| x == game->map_width - 1) && tile != '1')
		handle_error("The map is not totally enclosed by walls.", game);
}

static void	validate_tiles(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map->full[y][x])
		{
			validate_tile(game, game->map->full[y][x]);
			validate_wall(game, game->map->full[y][x], x, y);
			x++;
		}
		y++;
	}
}

static void	validate_counts(t_game *game)
{
	if (game->player_count != 1)
		handle_error("The map must contain one player.", game);
	if (game->exit_count != 1)
		handle_error("The map must contain one exit.", game);
	if (game->collectible_count < 1)
		handle_error("The map must contain at least one collectible.", game);
}

void	validate_map(t_game *game)
{
	if (!game || !game->map || !game->map->full)
		handle_error("Null pointer detected in map validation.", game);
	validate_tiles(game);
	validate_counts(game);
}
