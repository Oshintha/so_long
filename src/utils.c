/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:16:13 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/17 16:05:18 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "so_long.h"

void	keep_score(t_game *game)
{
	game->score--;
	if (game->score == 0)
	{
		open_exit(game);
		ft_printf("*******************************************************\n");
		ft_printf("*              ★★★★ CONGRATULATIONS! ★★★★             *\n");
		ft_printf("*                                                     *\n");
		ft_printf("*   You’ve collected everything! The exit is open! 🎉 *\n");
		ft_printf("*                                                     *\n");
		ft_printf("*     Make your escape now to complete the game!      *\n");
		ft_printf("*******************************************************\n");
	}
	else if (game->score == 1)
	{
		ft_printf("*******************************************************\n");
		ft_printf("*             🔥 ONE MORE ITEM REMAINING! 🔥          *\n");
		ft_printf("*                                                     *\n");
		ft_printf("*   Just one collectible left to unlock the exit!     *\n");
		ft_printf("*                                                     *\n");
		ft_printf("*           🔥 Go for it and claim victory! 🔥        *\n");
		ft_printf("*******************************************************\n");
	}
}

void	count_moves(t_game *game)
{
	ft_printf("Moves: %d\n", game->move_count++);
}

void	handle_error(const char *message, t_game *game)
{
	if (message)
		ft_printf("Error\n%s\n", message);
	if (game)
		cleanup_game(game);
	exit(EXIT_FAILURE);
}
