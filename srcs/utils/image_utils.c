/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:34:08 by yang              #+#    #+#             */
/*   Updated: 2022/11/14 15:18:22 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_img	copy_image(t_game *game, t_img img)
{
	t_img		new;
	t_int_pos	pos;
	uint32_t	color;

	new.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	save_img_addr(&(new));
	pos.y = -1;
	while (++pos.y < WIN_HEIGHT)
	{
		pos.x = -1;
		while (++pos.x < WIN_WIDTH)
		{
			color = get_tex_color(&img, pos.x, pos.y);
			my_mlx_pixel_put(&(new), pos.x, pos.y, color);
		}
	}
	return (new);
}

int	get_img_transparent(t_color *first, t_color *second, double percent)
{
	t_color	new;

	new.r = (second->r * percent) + (first->r * (1.0 - percent));
	new.g = (second->g * percent) + (first->g * (1.0 - percent));
	new.b = (second->b * percent) + (first->b * (1.0 - percent));
	return (rgb_to_int(new));
}

void	reset_img(t_game *game)
{
	mlx_destroy_image(game->mlx, game->minimap.img.img);
	mlx_destroy_image(game->mlx, game->img_3d.img);
	game->minimap.img.img = mlx_new_image(game->mlx, game->minimap.pxsize.x, \
							game->minimap.pxsize.y);
	save_img_addr(&(game->minimap.img));
	game->img_3d.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	save_img_addr(&(game->img_3d));
	draw_floor_n_ceiling(&(game->img_3d), game->c_color, 0, WIN_HEIGHT / 2);
	draw_floor_n_ceiling(&(game->img_3d), game->f_color, \
						WIN_HEIGHT / 2, WIN_HEIGHT);
	draw_minimap(game);
}
