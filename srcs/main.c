/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:05:51 by hyap              #+#    #+#             */
/*   Updated: 2022/11/09 19:44:06 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_minimap(t_game *game)
{
	game->minimap.size.x = MI_WIDTH;
	if (game->map_size.x < MI_WIDTH)
		game->minimap.size.x = game->map_size.x;
	game->minimap.size.y = MI_HEIGHT;
	if (game->map_size.y < MI_HEIGHT)
		game->minimap.size.y = game->map_size.y;
	game->minimap.pxsize.x = game->minimap.size.x * SCALE;
	game->minimap.pxsize.y = game->minimap.size.y * SCALE;
	game->minimap.img.img = mlx_new_image(game->mlx, game->minimap.pxsize.x, \
											game->minimap.pxsize.y);
	save_img_addr(&(game->minimap.img));
	game->img_3d.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	save_img_addr(&(game->img_3d));
	draw_floor_n_ceiling(&(game->img_3d), game->c_color, 0, WIN_HEIGHT / 2);
	draw_floor_n_ceiling(&(game->img_3d), game->f_color, \
							WIN_HEIGHT / 2, WIN_HEIGHT);
}

int	render_frame(t_game *game)
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
	draw_3D(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img_3d.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img.img, 0, 0);
	draw_weapon(game);
	return (0);
}

void	init_game(t_game *game, char *map_path)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	parse(game, map_path);
	init_minimap(game);
	init_weapon(game, &(game->weapons));
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_loop_hook(game->mlx, render_frame, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf("./cub3d <path_to_map>\n");
		return (0);
	}
	init_game(&game, av[1]);
	free_splits(game.map);
	free(game.weapons.images);
	return (0);
}
