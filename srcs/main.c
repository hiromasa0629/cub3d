/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:05:51 by hyap              #+#    #+#             */
/*   Updated: 2022/11/14 15:20:26 by yang             ###   ########.fr       */
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
	game->paused_img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	save_img_addr(&(game->paused_img));
	draw_floor_n_ceiling(&(game->img_3d), game->c_color, 0, WIN_HEIGHT / 2);
	draw_floor_n_ceiling(&(game->img_3d), game->f_color, \
							WIN_HEIGHT / 2, WIN_HEIGHT);
}

int	render_frame(t_game *game)
{
	if (game->paused)
		return (0);
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
	handle_mouse(game);
	draw_minimap(game);
	if (game->door_status == DOOR_OPEN || game->door_status == DOOR_CLOSE)
		handle_door(game);
	else
		draw_3d(game);
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
	game->door_status = DOOR_CLOSED;
	init_weapon(game, &(game->weapons));
	game->paused = 0;
	game->frame_door_close.img = mlx_new_image(game->mlx, WIN_WIDTH, \
												WIN_HEIGHT);
	save_img_addr(&(game->frame_door_close));
	game->frame_door_open.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	save_img_addr(&(game->frame_door_open));
	mlx_mouse_move(game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	game->prev_mouse_x = WIN_WIDTH / 2;
	mlx_mouse_hide();
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, 17, 0L, exit_hook, game);
	mlx_loop_hook(game->mlx, render_frame, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf("./cub3D <path_to_map>\n");
		return (0);
	}
	init_game(&game, av[1]);
	free_splits(game.map);
	free(game.weapons.images);
	return (0);
}
