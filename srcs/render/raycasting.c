/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:44:33 by yang              #+#    #+#             */
/*   Updated: 2022/11/10 17:44:18 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_raycast(t_game *game, t_raycast *rc, int x)
{
	rc->angle = (double)(game->player_pos.angle + (FOV / 2)) - \
				((double)x * (FOV / WIN_WIDTH));
	better_angle(&(rc->angle));
	rc->raydir.x = cos(deg_to_rad(rc->angle));
	rc->raydir.y = sin(deg_to_rad(rc->angle));
	rc->map_pos.x = (int)game->player_pos.pos.x0;
	rc->map_pos.y = (int)game->player_pos.pos.y0;
	rc->ray_deduct.x = 0;
	rc->ray_deduct.y = 0;
	rc->deltadist.x = sqrt(1 + (rc->raydir.y * rc->raydir.y) / \
		(rc->raydir.x * rc->raydir.x));
	if (fabs(rc->raydir.x) <= 0.00001)
		rc->deltadist.x = 1e30;
	rc->deltadist.y = sqrt(1 + (rc->raydir.x * rc->raydir.x) / \
		(rc->raydir.y * rc->raydir.y));
	if (fabs(rc->raydir.y) <= 0.00001)
		rc->deltadist.y = 1e30;
}

void	set_side_dist(t_matrix player, t_raycast *rc)
{
	if (rc->raydir.x < 0)
	{
		rc->step.x = -1;
		rc->sidedist.x = (player.x0 - rc->map_pos.x) * rc->deltadist.x;
		rc->ray_deduct.x = 1;
	}
	else
	{
		rc->step.x = 1;
		rc->sidedist.x = (rc->map_pos.x + 1.0 - player.x0) * rc->deltadist.x;
	}
	if (rc->raydir.y < 0)
	{
		rc->step.y = 1;
		rc->sidedist.y = (rc->map_pos.y + 1.0 - player.y0) * rc->deltadist.y;
	}
	else
	{
		rc->step.y = -1;
		rc->sidedist.y = (player.y0 - rc->map_pos.y) * rc->deltadist.y;
		rc->ray_deduct.y = 1;
	}
}

void	determine_hit(t_game *game, t_raycast *rc)
{
	int	hit;

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
		if (is_wall(game->map, rc->map_pos))
			hit = 1;
	}
}

void	draw_rays(t_game *game, t_raycast *rc)
{
	t_matrix	draw_ray;

	draw_ray.x0 = game->player_pos.pos.x0;
	draw_ray.y0 = game->player_pos.pos.y0;
	if (rc->side == 0)
	{
		draw_ray.x1 = draw_ray.x0 + (rc->raydir.x * \
			fabs(rc->map_pos.x - draw_ray.x0 + rc->ray_deduct.x) * \
			rc->deltadist.x);
		draw_ray.y1 = draw_ray.y0 - (rc->raydir.y * \
			fabs(rc->map_pos.x - draw_ray.x0 + rc->ray_deduct.x) * \
			rc->deltadist.x);
	}
	else
	{
		draw_ray.x1 = draw_ray.x0 + (rc->raydir.x * \
			fabs(rc->map_pos.y - draw_ray.y0 + rc->ray_deduct.y) * \
			rc->deltadist.y);
		draw_ray.y1 = draw_ray.y0 - (rc->raydir.y * \
			fabs(rc->map_pos.y - draw_ray.y0 + rc->ray_deduct.y) * \
			rc->deltadist.y);
	}
	dda_line(draw_ray, game);
	rc->draw_ray = draw_ray;
}

void	draw_3d(t_game *game)
{
	int			x;
	t_raycast	rc;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		init_raycast(game, &rc, x);
		set_side_dist(game->player_pos.pos, &rc);
		determine_hit(game, &rc);
		draw_rays(game, &rc);
		draw_texture(game, &rc, x);
	}
}
