/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:45:09 by yang              #+#    #+#             */
/*   Updated: 2022/11/05 22:25:17 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "main.h"

#define PLAYER_STEP 0.25
// Player step and player size are the same
// tile : player  = 1.0 : 0.25
#define MINIMAP_WIDTH 10 // total tiles
#define MINIMAP_HEIGHT 10
#define MI_SCREEN_WIDTH 200
#define MI_SCREEN_HEIGHT 200 // in pixel

// Assumptions
#define MAP_WIDTH 15.0
#define MAP_HEIGHT 15.0

void draw_3D(t_game *game, t_minimap *minimap);
/* display minimap player in center (N, S, E or W)
 ** get map start x and y
 ** start x = player.x - 5
 **			case if player is at the corner
 **			check if (player.x - 5 < 0 || player.x + 5 > map.height)
 **				then start x = 0 || start x = map.height - 10
 */

char *map[15] = {
	"111111111111111", // 0
	"100000000000001", // 1
	"101000000000001", // 2
	"101000000000001", // 3
	"100000000011101", // 4
	"101000000000010", // 5
	"101000000000001", // 6
	"100001000000001", // 7
	"111111000W00001", // 8
	"100100000001111", // 9
	"100010000000001", // 10
	"100100000000001", // 11
	"100000000000001", // 12
	"100000000000001", // 13
	"111111111111111", // 14
};

void my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->size + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void draw_minimap_block(t_minimap *minimap, int color, t_matrix *pixel)
{
	t_int_pos count;

	count.y = 0;
	while ((pixel->y0 + count.y) < pixel->y1)
	{
		count.x = 0;
		while ((pixel->x0 + count.x) < pixel->x1)
		{
			if ((pixel->x0 + count.x) <= minimap->screen_width && (pixel->y0 + count.y) <= minimap->screen_height)
				my_mlx_pixel_put(&minimap->map, pixel->x0 + count.x, pixel->y0 + count.y, color);
			count.x++;
		}
		count.y++;
	}
}

int absolute(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

double get_max(double x_step, double y_step)
{
	if (absolute(x_step) > absolute(y_step))
		return (absolute(x_step));
	else
		return (absolute(y_step));
}

t_matrix scale(t_matrix matrix, t_minimap *minimap)
{
	matrix.x0 = matrix.x0 * minimap->scale;
	matrix.x1 = matrix.x1 * minimap->scale;
	matrix.y0 = matrix.y0 * minimap->scale;
	matrix.y1 = matrix.y1 * minimap->scale;
	return (matrix);
}

t_matrix centralize(t_matrix matrix, t_minimap *minimap)
{
	matrix.x0 -= minimap->start_x;
	matrix.x1 -= minimap->start_x;
	matrix.y0 -= minimap->start_y;
	matrix.y1 -= minimap->start_y;
	return (matrix);
}
void dda(t_matrix matrix, t_minimap *minimap, int color)
{
	double x_step;
	double y_step;
	double max;

	matrix = centralize(matrix, minimap);
	matrix = scale(matrix, minimap);
	x_step = matrix.x1 - matrix.x0;
	y_step = matrix.y1 - matrix.y0;
	max = get_max(x_step, y_step);
	x_step /= max;
	y_step /= max;
	while (((int)(matrix.x0 - matrix.x1) || (int)(matrix.y0 - matrix.y1)) && matrix.x0 < MI_SCREEN_WIDTH && matrix.y0 < MI_SCREEN_HEIGHT && matrix.x0 > 0 && matrix.y0 > 0)
	{
		my_mlx_pixel_put(&minimap->map, matrix.x0, matrix.y0, color);
		matrix.x0 += x_step;
		matrix.y0 += y_step;
	}
}

int	get_color(char **map, t_double_pos dpos)
{
	t_int_pos	pos;
	
	pos.x = dpos.x;
	pos.y = dpos.y;
	if (is_wall(map, pos))
		return (GREEN);
	if (is_floor(map, pos))
		return (WHITE);
	return (0);
}

void	draw_minimap(t_game *game)
{
	t_double_pos	dpos;
	int				color;
	int				x;
	int				y;
	
	color = 0;
	get_start_pt(game);
	dpos.y = game->minimap.start.y;
	y = 0;
	while (y < game->minimap.screen_height)
	{
		x = 0;
		dpos.x = game->minimap.start.x;
		while (x < game->minimap.screen_width)
		{
			color = get_color(game->map, dpos);
			my_mlx_pixel_put(&(game->minimap.img), x, y, color);
			dpos.x += 1.0 / TILE_SIZE;
			x++;
		}
		dpos.y +=  1.0 / TILE_SIZE;
		y++;
	}
	draw_player(game);
	dda(game);
	draw_direction(game);
	draw_line(game);
}


// try using
void draw_minimap(t_minimap *minimap)
{
	t_int_pos pos;
	t_matrix pixel;
	pos.y = minimap->start_y;
	int color;

	pixel.y0 = 0;
	int extra_x = 0;
	int extra_y = 0;
	if (minimap->start_x - (int)minimap->start_x)
		extra_x = 1;
	if (minimap->start_y - (int)minimap->start_y)
		extra_y = 1;
	while (pos.y < (int)(minimap->height + minimap->start_y + extra_y))
	{
		pos.x = minimap->start_x;
		if (pixel.y0 == 0 && (minimap->start_y - (int)minimap->start_y))
			pixel.y1 = ((1.0 - (minimap->start_y - (int)minimap->start_y)) * minimap->scale) - 1;
		else if (pos.y == round(minimap->height + minimap->start_y - 1) + extra_y)
			pixel.y1 = minimap->screen_height;
		else
			pixel.y1 = pixel.y0 + minimap->scale - 1;
		pixel.x0 = 0;
		while (pos.x < minimap->width + minimap->start_x + extra_x)
		{
			if (pixel.x0 == 0 && (minimap->start_x - (int)minimap->start_x))
				pixel.x1 = ((1.0 - (minimap->start_x - (int)minimap->start_x)) * minimap->scale) - 1;
			else if (pos.x == round(minimap->width + minimap->start_x - 1) + extra_x)
				pixel.x1 = minimap->screen_width;
			else
				pixel.x1 = pixel.x0 + minimap->scale - 1;
			if (map[pos.y][pos.x] == '1')
				color = 0x58D68D;
			else if (map[pos.y][pos.x] == ' ')
				color = 0x0000FF;
			else
				color = 0XFFFFFF;
			draw_minimap_block(minimap, color, &pixel);
			pixel.x0 = pixel.x1 + 1;
			pos.x++;
		}
		pixel.y0 = pixel.y1 + 1;
		pos.y++;
	}
	t_matrix draw_player;
	draw_player.x0 = (minimap->player_pos.x0 - minimap->start_x) * minimap->scale;
	draw_player.x1 = draw_player.x0 + minimap->scale * PLAYER_STEP;
	draw_player.y0 = (minimap->player_pos.y0 - minimap->start_y) * minimap->scale;
	draw_player.y1 = draw_player.y0 + minimap->scale * PLAYER_STEP;
	draw_minimap_block(minimap, 0xEC7063, &draw_player);
	dda(minimap->player_pos, minimap, 0xEC7063);
}

void display_minimap(t_game *game, t_minimap *minimap)
{
	minimap->map.img = mlx_new_image(game->mlx, minimap->screen_width, minimap->screen_height);
	minimap->map.addr = mlx_get_data_addr(minimap->map.img, &minimap->map.bpp, &minimap->map.size,
										  &minimap->map.endian);
	minimap->map_3d.img = mlx_new_image(game->mlx, 1000, 1000);
	minimap->map_3d.addr = mlx_get_data_addr(minimap->map_3d.img, &minimap->map_3d.bpp, &minimap->map_3d.size,
											 &minimap->map_3d.endian);
	draw_minimap(minimap);
}

void close_win(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

void player_movement(int key, t_game *game)
{
	t_minimap *minimap = &(game->minimap);
	int angle;

	if (key == 123)
	{
		minimap->player_angle += 5;
		if (minimap->player_angle > 360)
			minimap->player_angle -= 360;
	}
	else if (key == RIGHT_BTN)
	{
		minimap->player_angle -= 5;
		if (minimap->player_angle < 0)
			minimap->player_angle += 360;
	}
	else if (key == 13) // up
	{
		minimap->player_pos.x0 += cos(deg_to_rad(minimap->player_angle)) * PLAYER_STEP;
		minimap->player_pos.y0 -= sin(deg_to_rad(minimap->player_angle)) * PLAYER_STEP;
	}
	else if (key == 1) // down
	{
		minimap->player_pos.x0 -= cos(deg_to_rad(minimap->player_angle)) * PLAYER_STEP;
		minimap->player_pos.y0 += sin(deg_to_rad(minimap->player_angle)) * PLAYER_STEP;
	}
	else if (key == 0 || key == 2) // 0 = left, 2 == right
	{
		if (key == 0)
			angle = (int)(minimap->player_angle + 90) % 360;
		else
			angle = (int)(minimap->player_angle - 90) % 360;
		minimap->player_pos.x0 += cos(deg_to_rad(angle)) * PLAYER_STEP;
		minimap->player_pos.y0 -= sin(deg_to_rad(angle)) * PLAYER_STEP;
	}
	set_player_direction(minimap);
	mlx_clear_window(game->mlx, game->win);
	minimap->map.img = mlx_new_image(game->mlx, 200, 200);
	minimap->map.addr = mlx_get_data_addr(minimap->map.img, &minimap->map.bpp, &minimap->map.size,
										  &minimap->map.endian);
	minimap->map_3d.img = mlx_new_image(game->mlx, 1000, 1000);
	minimap->map_3d.addr = mlx_get_data_addr(minimap->map_3d.img, &minimap->map_3d.bpp, &minimap->map_3d.size,
											 &minimap->map_3d.endian);
	init_minimap(minimap, false);
	draw_minimap(minimap);
	draw_3D(game, minimap);
	mlx_put_image_to_window(game->mlx, game->win, minimap->map.img, 0, 0);
}

int deal_key(int key, t_game *game)
{
	if (key == 53)
		close_win(game);
	else if (key == 123 || key == 124 || (key >= 0 && key <= 2) || key == 13)
		player_movement(key, game);
	return (0);
}

void init_minimap(t_game *game)
{
	// minimap->width = 10.0;
	// minimap->height = 10.0;
	// minimap->screen_width = 200;
	// minimap->screen_height = 200;
	if (game->map_size.x < MI_WIDTH)
		game->minimap.size.x = game->map_size.x;
	else
		game->minimap.size.x = MI_WIDTH;
	if (game->map_size.y < MI_HEIGHT)
		game->minimap.size.y = game->map_size.y;
	else
		game->minimap.size.y = MI_HEIGHT;
	game->minimap.pxsize.x = game->minimap.size.x * SCALE;
	game->minimap.pxsize.y = game->minimap.size.y * SCALE;
	game->minimap.img.img = mlx_new_image(game->mlx, game->minimap.pxsize.x, \
											game->minimap.pxsize.y);
	get_start_pt(game);
}

int main(void)
{
	t_game game;
	int		i;
	int		j;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1000, 1000, "cub3D");
	// game.minimap = (t_minimap *)malloc(sizeof(t_minimap));
	game.wall_EA.img = mlx_xpm_file_to_image(game.mlx, "./assets/wall.xpm", &i, &j);
	game.wall_EA.addr = mlx_get_data_addr(game.wall_EA.img, &(game.wall_EA.bpp), &(game.wall_EA.size), &(game.wall_EA.endian));
	
	printf("bpp: %d, size_len: %d, endian: %d\n", game.wall_EA.bpp, game.wall_EA.size, game.wall_EA.endian);
	init_minimap(&game);
	display_minimap(&game, game.minimap);
	// mlx_put_image_to_window(game.mlx, game.win, game.minimap->map.img, 0, 0);
	draw_3D(&game, game.minimap);
	mlx_put_image_to_window(game.mlx, game.win, game.minimap->map_3d.img, 0, 0);
	mlx_put_image_to_window(game.mlx, game.win, game.minimap->map.img, 0, 0);
	mlx_key_hook(game.win, deal_key, &game);
	mlx_loop(game.mlx);
}