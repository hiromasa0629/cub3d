/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:57:16 by hyap              #+#    #+#             */
/*   Updated: 2022/11/14 14:35:28 by yang             ###   ########.fr       */
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
	exit(0);
}
