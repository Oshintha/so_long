/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:14:17 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/10 11:23:00 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_2d_array(char **array, int height)
{
    int	i;

    i = 0;
    if (!array)
        return ;
    while (i < height)
    {
        free(array[i]);
        i++;
    }
    free(array);
}

static void	free_map(t_game *game)
{
    if (game->map)
    {
        free_2d_array(game->map->full, game->map_height);
        free(game->map);
    }
}

// Frees all memory that is still allocated up to this point.
void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->textures)
	{
		free_textures(game);
		game->textures = NULL;
	}
	if (game->images)
	{
		free_images(game);
		game->images = NULL;
	}
	if (game->mlx_ptr)
	{
		mlx_terminate(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
	free_map(game);
	free(game);
}