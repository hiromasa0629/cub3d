/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:27:17 by yang              #+#    #+#             */
/*   Updated: 2022/11/14 16:16:50 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	frame_door_open_close(t_game *game)
{
	int			x;
	t_raycast	rc;
	int			elem;

	x = -1;
	draw_3d(game);
	game->frame_door_close = copy_image(game, game->img_3d);
	reset_img(game);
	while (++x < WIN_WIDTH)
	{
		rc.angle = (double)(game->player_pos.angle + (FOV / 2)) \
					- ((double)x * (FOV / WIN_WIDTH));
		better_angle(&(rc.angle));
		init_raycast(game, &rc);
		set_side_dist_x(game, &rc);
		set_side_dist_y(game, &rc);
		elem = determine_hit(game, &rc, true);
		if (elem == 2)
			elem = determine_hit(game, &rc, false);
		draw_rays(game, &rc);
		draw_texture(game, &rc, elem);
		dda_3d(game, &rc, x);
	}
	game->frame_door_open = copy_image(game, game->img_3d);
}

static void	single_door_frame(t_game *game, double percent)
{
	t_raycast	rc_door;
	int			x;
	int			elem;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		rc_door.angle = (double)(game->player_pos.angle + (FOV / 2)) \
						- ((double)x * (FOV / WIN_WIDTH));
		better_angle(&(rc_door.angle));
		init_raycast(game, &rc_door);
		set_side_dist_x(game, &rc_door);
		set_side_dist_y(game, &rc_door);
		elem = determine_hit(game, &rc_door, true);
		draw_rays(game, &rc_door);
		draw_texture(game, &rc_door, elem);
		if (elem == 2 || elem == 3)
			dda_door_3d(game, &rc_door, x, percent);
		else
			dda_3d(game, &rc_door, x);
	}
}

static void	opening_closing_door(t_game *game, t_raycast *rc, int handle_door)
{
	static double	frame = 0.1;

	mlx_destroy_image(game->mlx, game->frame_door_close.img);
	mlx_destroy_image(game->mlx, game->frame_door_open.img);
	frame_door_open_close(game);
	if (frame < 1.0)
		single_door_frame(game, frame);
	frame += 0.1;
	if (frame > 1.000000)
	{
		if (handle_door == OPENED)
		{
			game->door_status = DOOR_OPENED;
			game->map[rc->map_pos.y][rc->map_pos.x] = '3';
		}
		else if (handle_door == CLOSED)
		{
			game->door_status = DOOR_CLOSED;
			game->map[rc->map_pos.y][rc->map_pos.x] = '2';
		}
		frame = 0.1;
	}
}

void	handle_door(t_game *game)
{
	t_raycast	rc;
	int			x;
	char		door_char;
	bool		facing_door;

	x = -1;
	facing_door = is_player_facing_door(game, &rc);
	door_char = game->map[rc.map_pos.y][rc.map_pos.x];
	if (facing_door && ((game->door_status == DOOR_OPEN && door_char == '2') \
		|| (game->door_status == DOOR_CLOSE && door_char == '3')))
	{
		if (game->door_status == DOOR_OPEN)
			opening_closing_door(game, &rc, OPENED);
		else if (game->door_status == DOOR_CLOSE)
			opening_closing_door(game, &rc, CLOSED);
	}
	else if (facing_door)
	{
		if (door_char == '2')
			game->door_status = DOOR_CLOSED;
		else if (door_char == '3')
			game->door_status = DOOR_OPENED;
	}
	else
		game->door_status = DOOR_CLOSED;
}
