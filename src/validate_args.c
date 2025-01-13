/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:02:30 by aoshinth          #+#    #+#             */
/*   Updated: 2025/01/10 10:54:30 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	validate_file_name(char *map_file_name)
{
	size_t	len;
    
    if (!map_file_name)
		handle_error("Map file name is NULL.", NULL);
	len = ft_strlen(map_file_name);
	if (len < 4 || ft_strncmp(map_file_name + len - 4, ".ber", 4) != 0)
		handle_error("Wrong file extension. Expected '.ber'.", NULL);
}

void	validate_args(int argc, char *map_file_name)
{
	if (argc < 2)
		handle_error("Add a map file.\nUsage: ./so_long <map_file.ber>", NULL);
	if (argc > 2)
		handle_error("Too many arguments.\nUsage: ./so_long <map_file.ber>", NULL);
	validate_file_name(map_file_name);
}