/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:42:43 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/17 14:34:59 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	validate_args(argc, argv[1]);
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		handle_error("Memory allocation failure for the game struct.", NULL);
	if (!initialise_game(game, argv[1]))
		handle_error("Failed to initialise game.", game);
	manage_motion(game);
	cleanup_game(game);
	exit(EXIT_SUCCESS);
}
