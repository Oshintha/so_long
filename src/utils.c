/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:16:13 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/13 14:29:34 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "so_long.h"

// Counts how many Pac-Men were killed
void	keep_score(t_game *game)
{
	game->score--;
	if (game->score == 0)
	{
		open_exit(game);
		ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
		ft_printf("★ CONGRATULATIONS! ★\n");
		ft_printf("You’ve conquered the challenge and collected everything! 🎉\n");
		ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
		ft_printf("🚪 The exit has been unlocked. Make your escape now! 🚪\n");
		ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	}
	else if (game->score == 1)
	{
		ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
		ft_printf("⚠ ONE MORE ITEM REMAINING! ⚠\n");
		ft_printf("Just one collectible stands between you and the exit! 🏆\n");
		ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
		ft_printf("🔥 Go for it and claim victory! 🔥\n");
		ft_printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	}
}


// Counts every movement from one tile to the next:
// Up, down, left, and right. No diagonal movements.
void	count_moves(t_game *game)
{
	ft_printf("Moves: %d\n", game->move_count++);
}

// Prints error message, calls cleanup_game()
// and exits the programme (failure);
void	handle_error(const char *message, t_game *game)
{
	if(message)
        ft_printf("Error\n%s\n", message);
	if (game)
		cleanup_game(game);
	exit(EXIT_FAILURE);
}