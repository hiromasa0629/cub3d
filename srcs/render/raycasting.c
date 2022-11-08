/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:44:33 by yang              #+#    #+#             */
/*   Updated: 2022/11/08 12:02:01 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "main.h"

#define FOV 66.0
// #define STRIPE 1000.0
// #define h 1000
// #define MAP_WIDTH 15.0
// #define MAP_HEIGHT 15.0
#define TEXSIZE 64

// void dda_ver(t_matrix matrix, t_minimap *minimap, t_texture texture)
// {
// 	int y = (int)matrix.y0;
// 	uint32_t	color;
// 	while (y < (int)matrix.y1)
// 	{
// 		texture.tex_pos.y = (int)texture.tex_start & (TEXSIZE - 1);
// 		texture.tex_start += texture.step;
// 		color = get_tex_color(&(texture.img), texture.tex_pos.x, texture.tex_pos.y);
// 		my_mlx_pixel_put(&mini, (int)matrix.x0, y, color);
// 		y++;
// 	}
// }

void	init_raycast(t_game *game, t_raycast *rc, int x)
{
	rc->angle = (double)(game->player_pos.angle + (FOV / 2)) - \
				((double)x * (FOV / WIN_WIDTH));
	if (rc->angle < 0.0)
		rc->angle += 360.0;
	else if (rc->angle > 360.0)
		rc->angle -= 360.0;
	rc->rayDir.x = cos(deg_to_rad(rc->angle));
	rc->rayDir.y = sin(deg_to_rad(rc->angle));
	rc->map_pos.x = (int)game->player_pos.pos.x0;
	rc->map_pos.y = (int)game->player_pos.pos.y0;
	rc->deltaDist.x = sqrt(1 + (rc->rayDir.y * rc->rayDir.y) / \
		(rc->rayDir.x * rc->rayDir.x));
	if (rc->rayDir.x == 0)
		rc->deltaDist.x = 1e30;
	rc->deltaDist.y = sqrt(1 + (rc->rayDir.x * rc->rayDir.x) / \
		(rc->rayDir.y * rc->rayDir.y));
	if (rc->rayDir.y == 0)
		rc->deltaDist.y = 1e30;
}

void	set_side_dist_x(t_game *game, t_raycast *rc)
{
	if (rc->rayDir.x < 0)
	{
		rc->step.x = -1;
		rc->sideDist.x = (game->player_pos.pos.x0 - rc->map_pos.x) * \
			rc->deltaDist.x;
		rc->ray_deduct.x = 1;
	}
	else
	{
		rc->step.x = 1;
		rc->sideDist.x = (rc->map_pos.x + 1.0 - game->player_pos.pos.x0) * \
			rc->deltaDist.x;
	}
}

void	set_side_dist_y(t_game *game, t_raycast *rc)
{
	if (rc->rayDir.y < 0)
	{
		rc->step.y = 1;
		rc->sideDist.y = (rc->map_pos.y + 1.0 - game->player_pos.pos.y0) * \
			rc->deltaDist.y;
	}
	else
	{
		rc->step.y = -1;
		rc->sideDist.y = (game->player_pos.pos.y0 - rc->map_pos.y) * \
			rc->deltaDist.y;
		rc->ray_deduct.y = 1;
	}
}

void	determine_hit(t_game *game, t_raycast *rc)
{
	int	hit;
	
	hit = 0;
	while (hit == 0)
	{
		if (rc->sideDist.x < rc->sideDist.y)
		{
			rc->sideDist.x += rc->deltaDist.x;
			rc->map_pos.x += rc->step.x;
			rc->side = 0;
		}
		else
		{
			rc->sideDist.y += rc->deltaDist.y;
			rc->map_pos.y += rc->step.y;
			rc->side = 1;
		}
		if ((game->map)[rc->map_pos.y][rc->map_pos.x] == '1')
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
		draw_ray.x1 = draw_ray.x0 + (rc->rayDir.x * \
			fabs(rc->map_pos.x - draw_ray.x0 + rc->ray_deduct.x) * \
			rc->deltaDist.x);
		draw_ray.y1 = draw_ray.y0 - (rc->rayDir.y * \
			fabs(rc->map_pos.x - draw_ray.x0 + rc->ray_deduct.x) * \
			rc->deltaDist.x);
	}
	else
	{
		draw_ray.x1 = draw_ray.x0 + (rc->rayDir.x * \
			fabs(rc->map_pos.y - draw_ray.y0 + rc->ray_deduct.y) * \
			rc->deltaDist.y);
		draw_ray.y1 = draw_ray.y0 - (rc->rayDir.y * \
			fabs(rc->map_pos.y - draw_ray.y0 + rc->ray_deduct.y) * \
			rc->deltaDist.y);
	}
	dda_line(draw_ray, game);
}

void	pre_draw_texture(t_game *game, t_raycast *rc)
{
	double	ca;
	
	rc->perpWallDist = (rc->sideDist.y - rc->deltaDist.y);
	if (rc->side == 0)
		rc->perpWallDist = (rc->sideDist.x - rc->deltaDist.x);
	ca = game->player_pos.angle - rc->angle;
	better_angle(&ca);
	rc->line_height = WIN_HEIGHT / (rc->perpWallDist * cos(deg_to_rad(ca)));
	rc->draw_start = -rc->line_height / 2 + WIN_HEIGHT / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + WIN_HEIGHT / 2;
	if (rc->draw_end >= WIN_HEIGHT)
		rc->draw_end = WIN_HEIGHT - 1;
}


void dda_3D(t_game *game, t_raycast *rc, int x)
{
	uint32_t	color;
	int y;
	
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

void	draw_texture(t_game *game, t_raycast *rc, int x)
{
	pre_draw_texture(game, rc);
	rc->texture.step = 1.0 * TEXSIZE / rc->line_height;
	rc->wall.x = game->player_pos.pos.x0 + rc->perpWallDist * rc->rayDir.x;
	if (rc->side == 0) 
		rc->wall.x = game->player_pos.pos.y0 + rc->perpWallDist * rc->rayDir.y;
	rc->wall.x -= (int)rc->wall.x;
	rc->texture.tex_pos.x = (int)(rc->wall.x * (double)TEXSIZE);
	if (rc->side == 0 && rc->rayDir.x > 0.0) 
		rc->texture.tex_pos.x = TEXSIZE - rc->texture.tex_pos.x - 1;
	if (rc->side == 1 && rc->rayDir.y < 0.0) 
		rc->texture.tex_pos.x = TEXSIZE - rc->texture.tex_pos.x - 1;
	rc->texture.tex_start = rc->texture.step * \
		(rc->draw_start - WIN_HEIGHT / 2 + rc->line_height / 2);
	rc->texture.img = game->wall_EA;
	dda_3D(game, rc, x);
}

void	draw_3D(t_game *game)
{
	int			x;
	t_raycast	rc;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		init_raycast(game, &rc, x);
		set_side_dist_x(game, &rc);
		set_side_dist_y(game, &rc);
		determine_hit(game, &rc);
		draw_rays(game, &rc);
		draw_texture(game, &rc, x);
	}
	// mlx_put_image_to_window(game->mlx, game->win, game->img_3d.img, 0, 0);
}

// void draw_3D(t_game *game, t_minimap *minimap)
// {
// 	int x = -1;
// 	t_matrix draw_ray;
// 	while (++x < STRIPE)
// 	{
// 		double angle;
// 		angle = (double)(minimap->player_angle + (FOV / 2)) - ((double)x * (FOV / STRIPE));
// 		if (angle < 0.0)
// 			angle += 360.0;
// 		else if (angle > 360.0)
// 			angle -= 360.0;
// 		double rayDirX = cos(deg_to_rad(angle));
// 		double rayDirY = sin(deg_to_rad(angle));
// 		int mapX = (int)minimap->player_pos.x0; // need to know the exact player pos (0.x? and facing direction to get exact starting point)
// 		int mapY = (int)minimap->player_pos.y0;
// 		double sideDistX;
// 		double sideDistY;
// 		double deltaDistX = (rayDirX == 0) ? 1e30 : sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
// 		double deltaDistY = (rayDirY == 0) ? 1e30 : sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
// 		double perpWallDist;
// 		int stepX;
// 		int stepY;

// 		int hit = 0;
// 		int side;
// 		int ray_deduct_x = 0;
// 		int ray_deduct_y = 0;
// 		if (rayDirX < 0)
// 		{
// 			stepX = -1;
// 			sideDistX = (minimap->player_pos.x0 - mapX) * deltaDistX;
// 			ray_deduct_x = 1;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - minimap->player_pos.x0) * deltaDistX;
// 		}
// 		if (rayDirY < 0)
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - minimap->player_pos.y0) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = -1;
// 			sideDistY = (minimap->player_pos.y0 - mapY) * deltaDistY;
// 			ray_deduct_y = 1;
// 		}
// 		while (hit == 0)
// 		{
// 			if (sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 			if ((game->map)[mapY][mapX] == '1')
// 				hit = 1;
// 		}
		
// 		if (side == 0)
// 			perpWallDist = (sideDistX - deltaDistX);
// 		else
// 			perpWallDist = (sideDistY - deltaDistY);
// 		double ca = minimap->player_angle - angle;
// 		if (ca < 0.0)
// 			ca += 360.0;
// 		else if (ca >= 360.0)
// 			ca -= 360.0;
// 		int lineHeight = (int)(h / (perpWallDist * cos(deg_to_rad(ca))));

// 		int drawStart = -lineHeight / 2 + h / 2;
// 		if (drawStart < 0)
// 			drawStart = 0;
// 		int drawEnd = lineHeight / 2 + h / 2;
// 		if (drawEnd >= h)
// 			drawEnd = h - 1;
// 		// int color = 0x0000FF;
// 		// if (side == 1)
// 		// 	color /= 2;
		
		
// 		t_texture	texture;
// 		texture.step = 1.0 * TEXSIZE / lineHeight;
// 		double wallX;
		
// 		if (side == 0) wallX = minimap->player_pos.y0 + perpWallDist * rayDirY;
// 		else wallX = minimap->player_pos.x0 + perpWallDist * rayDirX;
// 		wallX -= (int)wallX;
// 		texture.tex_pos.x = (int)(wallX * (double)TEXSIZE);
// 		if (side == 0 && rayDirX > 0.0) 
// 			texture.tex_pos.x = TEXSIZE - texture.tex_pos.x - 1;
// 		if (side == 1 && rayDirY < 0.0) 
// 			texture.tex_pos.x = TEXSIZE - texture.tex_pos.x - 1;
// 		texture.tex_start = (drawStart - h / 2 + lineHeight / 2) * texture.step;
// 		texture.img = game->wall_EA;
// 		t_matrix draw;
// 		draw.x0 = x;
// 		draw.y0 = drawStart;
// 		draw.y1 = drawEnd;
// 		dda_ver(draw, minimap, texture);
// 	}
// 	mlx_put_image_to_window(game->mlx, game->win, minimap->map_3d.img, 0, 0);
// }


