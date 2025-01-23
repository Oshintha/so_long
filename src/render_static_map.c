/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_static_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:11:25 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/17 14:44:27 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_tile(t_game *game, char tile, int y, int x)
{
	if (tile == WALL)
	{
		if (render_walls(game, y, x) == -1)
			handle_error("Unable to render  walls.", game);
	}
	else if (tile == COLLECTIBLE)
	{
		if (render_collectibles(game, y, x) == -1)
			handle_error("Unable to render Gift", game);
	}
	else if (tile == EXIT || tile == EXIT_OPEN)
	{
		if (render_exit(game, y, x) == -1)
			handle_error("Unable to render the exit", game);
	}
}

static void	cover_empty_space(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (render_empty_space(game, y, x) == -1)
				handle_error("Unable to render empty_space.", game);
			x++;
		}
		y++;
	}
}

void	render_static_map(t_game *game)
{
	int		x;
	int		y;
	char	tile;

	cover_empty_space(game);
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			tile = game->map->full[y][x];
			render_tile(game, tile, y, x);
			x++;
		}
		y++;
	}
}
