/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:20:35 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/17 14:44:10 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	render_empty_space(t_game *game, int y, int x)
{
	return (mlx_image_to_window(game->mlx_ptr, game->images->empty_space, x
			* TILESIZE, y * TILESIZE));
}

int	render_walls(t_game *game, int y, int x)
{
	return (mlx_image_to_window(game->mlx_ptr, game->images->wall, x
			* TILESIZE, y * TILESIZE));
}

int	render_collectibles(t_game *game, int y, int x)
{
	return (mlx_image_to_window(game->mlx_ptr, game->images->collectible, x
			* TILESIZE, y * TILESIZE));
}

int	render_exit(t_game *game, int y, int x)
{
	if (game->map->full[y][x] == EXIT)
	{
		game->map->exit.x = x;
		game->map->exit.y = y;
		return (mlx_image_to_window(game->mlx_ptr, game->images->exit, x
				* TILESIZE, y * TILESIZE));
	}
	else if (game->map->full[y][x] == EXIT_OPEN)
		return (mlx_image_to_window(game->mlx_ptr, game->images->exit_open, x
				* TILESIZE, y * TILESIZE));
	else
		return (0);
}

int	render_player(t_game *game)
{
	return (mlx_image_to_window(game->mlx_ptr, game->images->player,
			game->map->player.x * TILESIZE, game->map->player.y * TILESIZE));
}
