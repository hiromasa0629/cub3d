/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:50:41 by hyap              #+#    #+#             */
/*   Updated: 2022/11/12 18:11:46 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	handle_mouse(t_game *game)
{
	t_int_pos	mouse_pos;
	int			diff;

	mouse_pos.y = 0;
	mouse_pos.x = 0;
	mlx_mouse_get_pos(game->win, &(mouse_pos.x), &(mouse_pos.y));
	diff = game->prev_mouse_x - mouse_pos.x;
	game->player_pos.angle += (diff / 5);
	better_angle(&(game->player_pos.angle));
	mlx_mouse_move(game->win, game->prev_mouse_x, WIN_HEIGHT / 2);
}
