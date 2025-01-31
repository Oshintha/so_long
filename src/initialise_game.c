/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:00:13 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/24 18:18:01 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	initialise_vars(t_game *game)
{
	game->mlx_ptr = NULL;
	game->map = NULL;
	game->textures = NULL;
	game->images = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->score = 0;
	game->collectible_count = 0;
	game->move_count = 0;
	game->move_cooldown = 0;
	game->exit_flag = 0;
	game->player_count = 0;
	game->exit_count = 0;
}

static void	init_mlx_window(t_game *game)
{
	int	screen_width;
	int	screen_height;

	if (game->map_width <= 0 || game->map_height <= 0)
		handle_error("Invalid map dimensions. Cannot create game window.",
			game);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	game->mlx_ptr = mlx_init((game->map_width) * TILESIZE, game->map_height
			* TILESIZE, "so_long", true);
	mlx_get_monitor_size(0, &screen_width, &screen_height);
	if (game->map_width * TILESIZE > screen_width || game->map_height
		* TILESIZE > screen_height)
		handle_error("The map is too big to fit on the screen.", game);
	if (!game->mlx_ptr)
		handle_error("Unable to create game window. Check MLX initialization.",
			game);
}

static int	find_player_position(t_game *game)
{
	int	i;
	int	j;

	if (!game->map || !game->map->full)
		handle_error("Map data is missing or invalid.", game);
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map->full[i][j] == PLAYER)
			{
				game->map->player.x = j;
				game->map->player.y = i;
				game->map->full[i][j] = EMPTY_SPACE;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	initialise_game(t_game *game, char *map_name)
{
	initialise_vars(game);
	read_map(map_name, game);
	validate_map(game);
	validate_path(game);
	if (!find_player_position(game))
		handle_error("Player position not found.", game);
	init_mlx_window(game);
	load_images(game);
	render_static_map(game);
	if (render_player(game) == -1)
		return (0);
	game->score = game->collectible_count;
	game->move_count = 1;
	return (1);
}
