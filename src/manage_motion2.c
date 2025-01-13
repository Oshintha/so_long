/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_motion2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:21:53 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/13 11:47:19 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Replaces collectibles (Pac-Men) with the background image
// when they are collected ("killed").
static void	check_collectibles(t_game *game, int new_y, int new_x)
{
	if (game->map->full[new_y][new_x] == COLLECTIBLE)
	{
		keep_score(game);
		game->map->full[new_y][new_x] = EMPTY_SPACE;
		if (render_background(game, new_y, new_x) == -1)
			handle_error("Unable to render background.", game);
	}
}

// Updates player to a new position.
// This function also handles the case of winning the game.
void	update_player_position(t_game *game, int new_x, int new_y)
{
	int	old_x;
	int	old_y;

	old_x = game->map->player_start.x;
	old_y = game->map->player_start.y;
	if (old_x != new_x || old_y != new_y)
	{
		clear_old_position(game, old_y, old_x);
		game->map->player_start.x = new_x;
		game->map->player_start.y = new_y;
		check_collectibles(game, new_y, new_x);
		if (game->map->full[new_y][new_x] == EXIT_OPEN)
			win_game(game);
		else
		{
			set_new_position(game, new_y, new_x);
			if (render_player(game) == -1)
				handle_error("Unable to render the player image.", game);
			count_moves(game);
		}
	}
}

// Updates the exit image to "open" when all collectibles are collected
// (all Pac-Men are killed)
void	open_exit(t_game *game)
{
	int	exit_x;
	int	exit_y;

	exit_x = game->map->exit.x;
	exit_y = game->map->exit.y;
	game->map->full[exit_y][exit_x] = EXIT_OPEN;
	if (render_exit(game, exit_y, exit_x) == -1)
		handle_error("Unable to render exit image.", game);
}

void	clear_old_position(t_game *game, int old_y, int old_x)
{
	char	old_tile;

	old_tile = game->map->full[old_y][old_x];
	if (old_tile == EMPTY_SPACE || old_tile == COLLECTIBLE)
	{		
		if (render_background(game, old_y, old_x) == -1)
			handle_error("Unable to render background image.", game);
	}
	else if (old_tile == EXIT || old_tile == EXIT_OPEN)
	{
		if (render_exit(game, old_y, old_x) == -1)
			handle_error("Unable to render exit image.", game);
	}
}

void	set_new_position(t_game *game, int new_y, int new_x)
{
	game->map->player_start.standing_on = game->map->full[new_y][new_x];
	game->map->player_start.x = new_x;
	game->map->player_start.y = new_y;
}