/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:40:28 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/17 14:34:16 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_textures(t_game *game)
{
	if (!game || !game->textures)
		return ;
	if (game->textures->empty_space)
		mlx_delete_texture(game->textures->empty_space);
	if (game->textures->wall)
		mlx_delete_texture(game->textures->wall);
	if (game->textures->collectible)
		mlx_delete_texture(game->textures->collectible);
	if (game->textures->player)
		mlx_delete_texture(game->textures->player);
	if (game->textures->exit)
		mlx_delete_texture(game->textures->exit);
	if (game->textures->exit_open)
		mlx_delete_texture(game->textures->exit_open);
	free(game->textures);
	game->textures = NULL;
}

void	free_images(t_game *game)
{
	if (!game || !game->images)
		return ;
	if (game->images->empty_space)
		mlx_delete_image(game->mlx_ptr, game->images->empty_space);
	if (game->images->wall)
		mlx_delete_image(game->mlx_ptr, game->images->wall);
	if (game->images->collectible)
		mlx_delete_image(game->mlx_ptr, game->images->collectible);
	if (game->images->player)
		mlx_delete_image(game->mlx_ptr, game->images->player);
	if (game->images->exit)
		mlx_delete_image(game->mlx_ptr, game->images->exit);
	if (game->images->exit_open)
		mlx_delete_image(game->mlx_ptr, game->images->exit_open);
	free(game->images);
	game->images = NULL;
}

static int	load_textures(t_game *game)
{
	game->textures = ft_calloc(1, sizeof(t_textures));
	if (!game->textures)
		return (0);
	game->textures->empty_space = mlx_load_png("images/empty_space.png");
	game->textures->wall = mlx_load_png("images/wall.png");
	game->textures->collectible = mlx_load_png("images/collectible.png");
	game->textures->player = mlx_load_png("images/player.png");
	game->textures->exit = mlx_load_png("images/exit.png");
	game->textures->exit_open = mlx_load_png("images/exit_open.png");
	if (!game->textures->empty_space || !game->textures->wall
		|| !game->textures->collectible || !game->textures->player
		|| !game->textures->exit || !game->textures->exit_open)
	{
		ft_printf("Failed to load textures\n");
		free_textures(game);
		return (0);
	}
	return (1);
}

static int	textures_to_image(t_game *game)
{
	game->images = ft_calloc(1, sizeof(t_images));
	if (!game->images)
		handle_error("Failed to allocate memory for images.", game);
	game->images->empty_space = mlx_texture_to_image(game->mlx_ptr,
			game->textures->empty_space);
	game->images->wall = mlx_texture_to_image(game->mlx_ptr,
			game->textures->wall);
	game->images->collectible = mlx_texture_to_image(game->mlx_ptr,
			game->textures->collectible);
	game->images->player = mlx_texture_to_image(game->mlx_ptr,
			game->textures->player);
	game->images->exit = mlx_texture_to_image(game->mlx_ptr,
			game->textures->exit);
	game->images->exit_open = mlx_texture_to_image(game->mlx_ptr,
			game->textures->exit_open);
	if (!game->images->empty_space || !game->images->wall
		|| !game->images->collectible || !game->images->player
		|| !game->images->exit || !game->images->exit_open)
	{
		ft_printf("Failed to turn textures into images\n");
		free_images(game);
		return (0);
	}
	return (1);
}

void	load_images(t_game *game)
{
	if (!load_textures(game) || !textures_to_image(game))
		handle_error("Failed to load textures or images.", game);
	free_textures(game);
}
