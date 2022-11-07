/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:10:18 by hyap              #+#    #+#             */
/*   Updated: 2022/11/07 13:18:32 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	handle_movements(int key, t_game *game)
{
	double	angle;

	angle = game->player_pos.angle;
	if (key == A_BTN)
		angle = (int)(game->player_pos.angle + 90) % 360;
	else if (key == D_BTN)
		angle = (int)(game->player_pos.angle - 90) % 360;
	game->player_pos.pos.x0 += cos(deg_to_rad(angle)) * PLAYER_STEP;
	game->player_pos.pos.y0 -= sin(deg_to_rad(angle)) * PLAYER_STEP;
	if (key == S_BTN)
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

void	recreate_img(t_game *game)
{
	mlx_destroy_image(game->mlx, game->minimap.img.img);
	mlx_destroy_image(game->mlx, game->img_3d.img);
	game->minimap.img.img = mlx_new_image(game->mlx, MI_PX_WIDTH, MI_PX_HEIGHT);
	save_img_addr(&(game->minimap.img));
	game->img_3d.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	save_img_addr(&(game->img_3d));
}

void	handle_keypress(int key, t_game *game)
{
	handle_movements(key, game);
	handle_angle(key, game);
	set_player_direction(game);
	get_start_pt(game);
}