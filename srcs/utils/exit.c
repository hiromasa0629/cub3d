/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:57:16 by hyap              #+#    #+#             */
/*   Updated: 2022/11/14 14:04:36 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	exit_error(const char *s)
{
	printf("Error\n%s", s);
	exit(1);
}

int	exit_hook(t_game *game)
{
	destroy_all_images(game);
	mlx_destroy_window(game->mlx, game->win);
	free_splits(game->map);
	// system("leaks cub3d");
	exit(0);
}
