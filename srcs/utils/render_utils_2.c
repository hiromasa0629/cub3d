/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:41:18 by hyap              #+#    #+#             */
/*   Updated: 2022/11/12 17:58:31 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	better_angle(double *angle)
{
	if (*angle < 0.0)
		*angle += 360.0;
	else if (*angle >= 360.0)
		*angle -= 360.0;
}

uint32_t	get_tex_color(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->size + x * (data->bpp / 8));
	return (*(uint32_t *)dst);
}

void	destroy_all_images(t_game *game)
{
	mlx_destroy_image(game->mlx, game->wall_ea.img);
	mlx_destroy_image(game->mlx, game->wall_no.img);
	mlx_destroy_image(game->mlx, game->wall_so.img);
	mlx_destroy_image(game->mlx, game->wall_we.img);
	mlx_destroy_image(game->mlx, game->img_3d.img);
	mlx_destroy_image(game->mlx, game->minimap.img.img);
	mlx_destroy_image(game->mlx, game->paused_img.img);
}

void	save_new_paused_screen(t_game *game)
{
	t_int_pos	px;
	t_color		rgb;
	
	px.y = -1;
	while (++px.y < WIN_HEIGHT)
	{
		px.x = -1;
		while (++px.x < WIN_WIDTH)
		{
			rgb = int_to_rgb(get_tex_color(&(game->img_3d), px.x, px.y));
			rgb = darker_rgb(rgb);
			my_mlx_pixel_put(&(game->paused_img), px.x, px.y, rgb_to_int(rgb));
		}
	}
}
