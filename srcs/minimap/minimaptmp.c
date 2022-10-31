/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaptmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 20:27:15 by hyap              #+#    #+#             */
/*   Updated: 2022/10/31 20:53:59 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#define GREEN 0x7FFF00
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED 0xFF0000
#define MAX_MINIMAP_X 220
#define MAX_MINIMAP_Y 220
#define TILE_SIZE 20
#define WALL '1'
#define FLOOR '0'
#define MOVEPX 5

char *map[15] = {
	"111111111111111",
	"101000000000001",
	"101000000000001",
	"101000000000001",
	"100000000011101",
	"100001000000010",
	"100001000000001",
	"100001000000001",
	"111111000000001",
	"100000000001111",
	"100000S00000001",
	"100100000000001",
	"100000000000001",
	"100000000000001",
	"111111111111111",
};

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->size + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void save_block_img_addr(t_img *img)
{
	img->addr = mlx_get_data_addr(img->img, &(img->bpp), &(img->size),
								&(img->endian));
}

t_int_pos get_player_pos(t_game *game)
{
	t_int_pos pos;

	pos.y = -1;
	while ((game->map)[++pos.y])
	{
		pos.x = -1;
		while ((game->map)[pos.y][++pos.x])
			if (is_player(game->map, pos))
				return (pos);
	}
	return (pos);
}

int get_start_pos_x(t_game *game)
{
	int player_x;

	player_x = game->player.tile_pos.x;
	if (game->minimap.width < MAX_MINIMAP_X)
		return (0);
	if ((player_x - 5) < 0)
		return (0);
	if ((player_x + 5) >= game->map_width)
		return (game->map_width - 11);
	return (player_x - 5);
}

int get_start_pos_y(t_game *game)
{
	int player_y;

	player_y = game->player.tile_pos.y;
	if (game->minimap.height < MAX_MINIMAP_Y)
		return (0);
	if ((player_y - 5) < 0)
		return (0);
	if ((player_y + 5) >= game->map_height)
		return (game->map_width - 11);
	return (player_y - 5);
}

int is_player_pos(t_game *game, t_int_pos pos)
{
	if (game->player.pos.x == pos.x && game->player.pos.y == pos.y)
		return (1);
	return (0);
}

int get_color(t_game game, t_int_pos pos)
{
	if (is_wall(game.map, pos))
		return (GREEN);
	if (is_floor(game.map, pos))
		return (WHITE);
	return (0);
}

t_img draw_minimap(t_game *game)
{
	t_mini mini;
	t_img minimap;
	int color;

	mini.start_pos.x = get_start_pos_x(game);
	mini.start_pos.y = get_start_pos_y(game);
	minimap.img = mlx_new_image(game->mlx, game->minimap.width, game->minimap.height);
	save_block_img_addr(&minimap);
	mini.pos.y = mini.start_pos.y;
	mini.pxpos.y = 0;
	while (mini.pxpos.y < 220)
	{
		mini.pos.x = mini.start_pos.x;
		mini.pxpos.x = 0;
		if (mini.pxpos.y < game->player.moved.y)
		{
			while (mini.pxpos.x < 220)
			{
				if (mini.pxpos.x < game->player.moved.x)
				{
					color = get_color(*game, mini.pos);
					my_mlx_pixel_put(&minimap, mini.pxpos.x, mini.pxpos.y, color);
					mini.pxpos.x++;
					if (mini.pxpos.x > game->player.moved.x)
						mini.pos.x++;
				}
				else if (mini.pxpos.x > (220 - game->player.moved.x))
				{
					mini.pos.x += 1;
					color = get_color(*game, mini.pos);
					my_mlx_pixel_put(&minimap, mini.pxpos.x, mini.pxpos.y, color);
					mini.pxpos.x++;
				}
				else
				{
					color = get_color(*game, mini.pos);
					my_mlx_pixel_put(&minimap, mini.pxpos.x, mini.pxpos.y, color);
					mini.pxpos.x++;
					if (((-1 * ((int)game->player.moved.x - mini.pxpos.x)) % 20) == 0)
						mini.pos.x++;
				}
			}
			mini.pxpos.y++;
			if (mini.pxpos.y > game->player.moved.y)
				mini.pos.y++;
		}
		else if (mini.pxpos.y > (220 - game->player.moved.y))
		{
			mini.pos.y += 1;
			while (mini.pxpos.x < 220)
			{
				if (mini.pxpos.x < game->player.moved.x)
				{
					color = get_color(*game, mini.pos);
					my_mlx_pixel_put(&minimap, mini.pxpos.x, mini.pxpos.y, color);
					mini.pxpos.x++;
					if (mini.pxpos.x > game->player.moved.x)
						mini.pos.x++;
				}
				else if (mini.pxpos.x > (220 - game->player.moved.x))
				{
					mini.pos.x += 1;
					color = get_color(*game, mini.pos);
					my_mlx_pixel_put(&minimap, mini.pxpos.x, mini.pxpos.y, color);
					mini.pxpos.x++;
				}
				else
				{
					color = get_color(*game, mini.pos);
					my_mlx_pixel_put(&minimap, mini.pxpos.x, mini.pxpos.y, color);
					mini.pxpos.x++;
					if (((-1 * ((int)game->player.moved.x - mini.pxpos.x)) % 20) == 0)
						mini.pos.x++;
				}
			}
			mini.pxpos.y++;
		}
		else
		{
			while (mini.pxpos.x < 220)
			{
				if (mini.pxpos.x < game->player.moved.x)
				{
					color = get_color(*game, mini.pos);
					my_mlx_pixel_put(&minimap, mini.pxpos.x, mini.pxpos.y, color);
					mini.pxpos.x++;
					if (mini.pxpos.x > game->player.moved.x)
						mini.pos.x++;
				}
				else if (mini.pxpos.x > (220 - game->player.moved.x))
				{
					mini.pos.x += 1;
					color = get_color(*game, mini.pos);
					my_mlx_pixel_put(&minimap, mini.pxpos.x, mini.pxpos.y, color);
					mini.pxpos.x++;
				}
				else
				{
					color = get_color(*game, mini.pos);
					my_mlx_pixel_put(&minimap, mini.pxpos.x, mini.pxpos.y, color);
					mini.pxpos.x++;
					if (((-1 * ((int)game->player.moved.x - mini.pxpos.x)) % 20) == 0)
						mini.pos.x++;
				}
			}
			mini.pxpos.y++;
			if (((-1 * ((int)game->player.moved.y - mini.pxpos.y)) % 20) == 0)
				mini.pos.y++;
		}
	}
	return (minimap);
}

void init_player(t_game *game)
{
	game->player.tile_pos = get_player_pos(game);
	game->player.moved.x = 0.0;
	game->player.moved.y = 0.0;
	game->player.dir.x = 1;
	game->player.dir.y = 0;
}

void init_minimap(t_game *game)
{
	t_img minimap;

	game->map_width = 15;
	game->map_height = 15;
	if ((game->map_width * TILE_SIZE) > MAX_MINIMAP_X)
		game->minimap.width = MAX_MINIMAP_X;
	else
		game->minimap.width = game->map_width * TILE_SIZE;
	if ((game->map_height * TILE_SIZE) > MAX_MINIMAP_Y)
		game->minimap.height = MAX_MINIMAP_Y;
	else
		game->minimap.height = game->map_height * TILE_SIZE;
	game->map = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	(game->map)[game->map_height] = NULL;
	int	i = 0;
	int	j;
	while (map[i])
	{
		j = 0;
		(game->map)[i] = (char *)malloc(sizeof(char) * (ft_strlen(map[i]) + 1));
		(game->map)[i][ft_strlen(map[i])] = '\0';
		while (map[i][j])
		{
			(game->map)[i][j] = map[i][j];
			j++;
		}
		i++;
	}
	i = 0;
	while ((game->map)[i])
		printf("%s\n", (game->map)[i++]);
	init_player(game);
	minimap = draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, minimap.img, 0, 0);
}

int handle_keypress(int key, t_game *game)
{
	t_img minimap;

	if (key == D_BTN)
	{
		game->player.moved.x += MOVEPX;
		if (game->player.moved.x >= 20)
		{
			(game->map)[(int)game->player.tile_pos.y][(int)game->player.tile_pos.x] = '0';
			(game->map)[(int)game->player.tile_pos.y][(int)game->player.tile_pos.x + 1] = 'S';
			game->player.moved.x -= 20;
			game->player.tile_pos.x += 1;
		}
	}
	else if (key == W_BTN)
	{
		game->player.moved.y -= MOVEPX;
		if (game->player.moved.y < 0)
		{
			(game->map)[(int)game->player.tile_pos.y][(int)game->player.tile_pos.x] = '0';
			(game->map)[(int)game->player.tile_pos.y - 1][(int)game->player.tile_pos.x] = 'S';
			game->player.moved.y += 20;
			game->player.tile_pos.y -= 1;
		}
	}
	else if (key == S_BTN)
	{
		game->player.moved.y += MOVEPX;
		if (game->player.moved.y >= 20)
		{
			(game->map)[(int)game->player.tile_pos.y][(int)game->player.tile_pos.x] = '0';
			(game->map)[(int)game->player.tile_pos.y + 1][(int)game->player.tile_pos.x] = 'S';
			game->player.moved.y -= 20;
			game->player.tile_pos.y += 1;
		}
	}
	else if (key == A_BTN)
	{
		game->player.moved.x -= MOVEPX;
		if (game->player.moved.x < 0)
		{
			(game->map)[(int)game->player.tile_pos.y][(int)game->player.tile_pos.x] = '0';
			(game->map)[(int)game->player.tile_pos.y][(int)game->player.tile_pos.x - 1] = 'S';
			game->player.moved.x += 20;
			game->player.tile_pos.x -= 1;
		}
	}
	int	i = 0;
	while ((game->map)[i])
		printf("%s\n", (game->map)[i++]);
	minimap = draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, minimap.img, 0, 0);
	return (0);
}

int main(void)
{
	t_game game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1280, 720, "cub3D");
	init_minimap(&game);
	printf("height: %d, wdith: %d\n", game.minimap.height, game.minimap.width);
	// mlx_key_hook(game.win, handle_key, &game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_loop(game.mlx);
}