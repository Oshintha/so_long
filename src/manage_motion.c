/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:21:26 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/13 11:45:22 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	can_move(t_game *game, int new_x, int new_y)
{
	if (new_y < 0 || new_y >= game->map_height || new_x < 0
		|| new_x >= game->map_width)
		return (0);
	else if (game->map->full[new_y][new_x] == WALL)
		return (0);
	return (1);
}

static void	set_movement_direction(t_game *game, int *new_x, int *new_y)
{
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_UP)
		|| mlx_is_key_down(game->mlx_ptr, MLX_KEY_W))
		*new_y -= 1;
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_DOWN)
		|| mlx_is_key_down(game->mlx_ptr, MLX_KEY_S))
		*new_y += 1;
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_LEFT)
		|| mlx_is_key_down(game->mlx_ptr, MLX_KEY_A))
		*new_x -= 1;
	else if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_RIGHT)
		|| mlx_is_key_down(game->mlx_ptr, MLX_KEY_D))
		*new_x += 1;
}

static void	ft_hook(void *param)
{
	t_game	*game;
	int		new_x;
	int		new_y;

	game = (t_game *)param;
	new_x = game->map->player_start.x;
	new_y = game->map->player_start.y;
	if (game->move_cooldown > 0)
	{
		game->move_cooldown--;
		return ;
	}
	if (mlx_is_key_down(game->mlx_ptr, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx_ptr);
		cleanup_game(game);
		exit(EXIT_SUCCESS);
	}
	set_movement_direction(game, &new_x, &new_y);
	if (can_move(game, new_x, new_y)
		&& (new_x != game->map->player_start.x || new_y != game->map->player_start.y))
		update_player_position(game, new_x, new_y);
	game->move_cooldown = MOVE_DELAY;
}

// Manages MLS loops and everything related to movement and changes.
void	manage_motion(t_game *game)
{
	mlx_loop_hook(game->mlx_ptr, ft_hook, game);
	mlx_loop(game->mlx_ptr);
}