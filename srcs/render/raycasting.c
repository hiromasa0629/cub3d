/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:44:33 by yang              #+#    #+#             */
/*   Updated: 2022/11/14 16:11:09 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_raycast(t_game *game, t_raycast *rc)
{
	rc->raydir.x = cos(deg_to_rad(rc->angle));
	rc->raydir.y = sin(deg_to_rad(rc->angle));
	rc->map_pos.x = (int)game->player_pos.pos.x0;
	rc->map_pos.y = (int)game->player_pos.pos.y0;
	rc->ray_deduct.x = 0;
	rc->ray_deduct.y = 0;
	rc->deltadist.x = sqrt(1 + (rc->raydir.y * rc->raydir.y) \
						/ (rc->raydir.x * rc->raydir.x));
	if (fabs(rc->raydir.x) <= 0.00001)
		rc->deltadist.x = 1e30;
	rc->deltadist.y = sqrt(1 + (rc->raydir.x * rc->raydir.x) \
						/ (rc->raydir.y * rc->raydir.y));
	if (fabs(rc->raydir.y) <= 0.00001)
		rc->deltadist.y = 1e30;
}

void	set_side_dist_x(t_game *game, t_raycast *rc)
{
	if (rc->raydir.x < 0)
	{
		rc->step.x = -1;
		rc->sidedist.x = (game->player_pos.pos.x0 - rc->map_pos.x) \
						* rc->deltadist.x;
		rc->ray_deduct.x = 1;
	}
	else
	{
		rc->step.x = 1;
		rc->sidedist.x = (rc->map_pos.x + 1.0 - game->player_pos.pos.x0) \
						* rc->deltadist.x;
	}	
}

void	set_side_dist_y(t_game *game, t_raycast *rc)
{
	if (rc->raydir.y < 0)
	{
		rc->step.y = 1;
		rc->sidedist.y = (rc->map_pos.y + 1.0 - game->player_pos.pos.y0) \
						* rc->deltadist.y;
	}
	else
	{
		rc->step.y = -1;
		rc->sidedist.y = (game->player_pos.pos.y0 - rc->map_pos.y) \
						* rc->deltadist.y;
		rc->ray_deduct.y = 1;
	}
}

int	determine_hit(t_game *game, t_raycast *rc, bool close_door)
{
	int	hit;
	int	elem;

	hit = 0;
	while (hit == 0)
	{
		if (rc->sidedist.x < rc->sidedist.y)
		{
			rc->sidedist.x += rc->deltadist.x;
			rc->map_pos.x += rc->step.x;
			rc->side = 0;
		}
		else
		{
			rc->sidedist.y += rc->deltadist.y;
			rc->map_pos.y += rc->step.y;
			rc->side = 1;
		}
		elem = is_wall_door(game->map, rc->map_pos);
		if (elem == 1 || elem == 2 || (close_door && elem == 3))
			hit = 1;
	}
	return (elem);
}

void	draw_3d(t_game *game)
{
	int			x;
	t_raycast	rc;
	int			elem;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		rc.angle = (double)(game->player_pos.angle + (FOV / 2)) \
					- ((double)x * (FOV / WIN_WIDTH));
		better_angle(&(rc.angle));
		init_raycast(game, &rc);
		set_side_dist_x(game, &rc);
		set_side_dist_y(game, &rc);
		elem = determine_hit(game, &rc, false);
		draw_rays(game, &rc);
		draw_texture(game, &rc, elem);
		dda_3d(game, &rc, x);
	}
}
