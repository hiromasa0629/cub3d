/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:38:22 by yang              #+#    #+#             */
/*   Updated: 2022/11/14 15:16:57 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_player_facing_door(t_game *game, t_raycast *rc)
{
	double		dist;
	t_matrix	*draw_ray;
	int			elem;

	rc->angle = game->player_pos.angle;
	draw_ray = &rc->draw_ray;
	init_raycast(game, rc);
	set_side_dist(game, rc);
	elem = determine_hit(game, rc, true);
	if (elem == 2 || elem == 3)
	{
		draw_rays(game, rc);
		dist = sqrt((fabs(ft_sqr(draw_ray->x1 - draw_ray->x0)) \
				+ fabs(ft_sqr(draw_ray->y1 - draw_ray->y0))));
		if (dist <= 3.0)
			return (1);
	}
	return (0);
}

void	dda_door_3d(t_game *game, t_raycast *rc, int x, double percent)
{
	t_color		bg_color;
	t_color		door_color;
	uint32_t	color;
	int			y;

	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		bg_color = int_to_rgb(get_tex_color(&(game->frame_door_open), x, y));
		door_color = int_to_rgb(get_tex_color(&(game->frame_door_close), x, y));
		color = get_img_transparent(&door_color, &bg_color, percent);
		my_mlx_pixel_put(&(game->img_3d), x, y, color);
		y++;
	}
}
