/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:10:18 by hyap              #+#    #+#             */
/*   Updated: 2022/11/10 17:20:38 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_wall_collision(t_game *game, t_player player, double angle, int type)
{
	t_int_pos	pos;

	if (type == 0)
	{
		pos.x = player.pos.x0 + cos(deg_to_rad(angle)) * PLAYER_STEP;
		pos.y = player.pos.y0 - sin(deg_to_rad(angle)) * PLAYER_STEP;
	}
	else
	{
		pos.x = player.pos.x0 - cos(deg_to_rad(angle)) * PLAYER_STEP;
		pos.y = player.pos.y0 + sin(deg_to_rad(angle)) * PLAYER_STEP;
	}
	if (is_wall(game->map, pos))
		return (1);
	return (0);
}

void	handle_movements(int key, t_game *game)
{
	double		angle;

	angle = game->player_pos.angle;
	if (key == A_BTN)
		angle = (int)(game->player_pos.angle + 90) % 360;
	else if (key == D_BTN)
		angle = (int)(game->player_pos.angle - 90) % 360;
	if (key != S_BTN)
	{
		if (!check_wall_collision(game, game->player_pos, angle, 0))
		{
			game->player_pos.pos.x0 += cos(deg_to_rad(angle)) * PLAYER_STEP;
			game->player_pos.pos.y0 -= sin(deg_to_rad(angle)) * PLAYER_STEP;
		}
		return ;
	}
	if (!check_wall_collision(game, game->player_pos, angle, 1))
	{
		game->player_pos.pos.x0 -= cos(deg_to_rad(angle)) * PLAYER_STEP;
		game->player_pos.pos.y0 += sin(deg_to_rad(angle)) * PLAYER_STEP;
	}
}

void	handle_angle(int key, t_game *game)
{
	if (key == LEFT_BTN)
	{
		game->player_pos.angle += 5;
		if (game->player_pos.angle > 360)
			game->player_pos.angle -= 360;
	}
	else if (key == RIGHT_BTN)
	{
		game->player_pos.angle -= 5;
		if (game->player_pos.angle < 0)
			game->player_pos.angle += 360;
	}
}

int	handle_keypress(int key, t_game *game)
{
	if (key == W_BTN || key == S_BTN || key == A_BTN || key == D_BTN)
		handle_movements(key, game);
	handle_angle(key, game);
	if (key == E_BTN && game->weapons.status == CLOSED)
		game->weapons.status = OPENED;
	else if (key == E_BTN && game->weapons.status == OPENED)
		game->weapons.status = CLOSED;
	set_player_direction(game);
	return (0);
}
