/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:22:43 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/17 16:07:00 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	win_game(t_game *game)
{
	if (game->score == 0)
	{
		count_moves(game);
		ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
		ft_printf("      🌟 🌟 🌟 CONGRATULATIONS! YOU WIN! 🌟 🌟 🌟\n");
		ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
		ft_printf("         🎯 Your total number of moves: %d 🎯\n",
			game->move_count);
		ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
		ft_printf("  🤔 Think you can do it in fewer moves next time? 🤔\n");
		ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
		cleanup_game(game);
		exit(EXIT_SUCCESS);
	}
}
