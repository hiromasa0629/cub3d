/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:55:27 by hyap              #+#    #+#             */
/*   Updated: 2022/11/14 14:01:22 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	pre_draw_texture(t_game *game, t_raycast *rc)
{
	double	ca;

	rc->perpwalldist = (rc->sidedist.y - rc->deltadist.y);
	if (rc->side == 0)
		rc->perpwalldist = (rc->sidedist.x - rc->deltadist.x);
	ca = game->player_pos.angle - rc->angle;
	better_angle(&ca);
	rc->line_height = WIN_HEIGHT / (rc->perpwalldist * cos(deg_to_rad(ca)));
	rc->draw_start = -rc->line_height / 2 + WIN_HEIGHT / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + WIN_HEIGHT / 2;
	if (rc->draw_end >= WIN_HEIGHT)
		rc->draw_end = WIN_HEIGHT;
}

t_img get_texture_img(t_game *game, t_raycast *rc, int elem)
{
    if (elem == 2 || elem == 3)
        return (game->door);
    if (rc->side == 0 && rc->raydir.x < 0)
        return (game->wall_ea);
    if (rc->side == 0)
        return (game->wall_we);
    if (rc->side == 1 && rc->raydir.y < 0)
        return (game->wall_no);
    if (rc->side == 1)
        return (game->wall_so);
    return (game->wall_we);
}

void	dda_3d(t_game *game, t_raycast *rc, int x)
{
	uint32_t	color;
	int			y;

	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		rc->texture.tex_pos.y = (int)rc->texture.tex_start & (TEXSIZE - 1);
		rc->texture.tex_start += rc->texture.step;
		color = get_tex_color(&(rc->texture.img), rc->texture.tex_pos.x, \
								rc->texture.tex_pos.y);
		my_mlx_pixel_put(&(game->img_3d), x, y, color);
		y++;
	}
}

void	draw_texture(t_game *game, t_raycast *rc, int elem)
{
	pre_draw_texture(game, rc);
	rc->texture.img = get_texture_img(game, rc, elem);
	rc->texture.step = 1.0 * TEXSIZE / rc->line_height;
	if (rc->side == 0)
		rc->wall.x = rc->draw_ray.y1;
	else
		rc->wall.x = rc->draw_ray.x1;
	rc->wall.x -= (int)rc->wall.x;
	rc->texture.tex_pos.x = (int)(rc->wall.x * (double)TEXSIZE);
	if (rc->side == 0 && rc->raydir.x > 0.0)
		rc->texture.tex_pos.x = TEXSIZE - rc->texture.tex_pos.x - 1;
	if (rc->side == 1 && rc->raydir.y < 0.0)
		rc->texture.tex_pos.x = TEXSIZE - rc->texture.tex_pos.x - 1;
	rc->texture.tex_start = rc->texture.step * \
		(rc->draw_start - WIN_HEIGHT / 2 + rc->line_height / 2);
}
