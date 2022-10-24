/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaptmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 20:27:15 by hyap              #+#    #+#             */
/*   Updated: 2022/10/24 21:39:22 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
# define GREEN 0x7FFF00
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define WALL '1'
# define FLOOR '0'

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
	"100000000000001",
	"100100000000001",
	"100000000000001",
	"100000000000001",
	"111111111111111",
};

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	
	dst = img->addr + (y * img->size + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
	
}

void	draw_block(t_game *game, t_int_pos pos, char c)
{
	int	color;
	
	if (c == WALL)
		color = GREEN;
	else if (c == FLOOR)
		color = WHITE;
	
	
}

void	save_block_img_addr(t_img *img)
{
	img->addr = mlx_get_data_addr(img, &(img->bpp), &(img->size), \
		&(img->endian));
}

void	create_block_img(t_game *game)
{
	game->minimap.wall05.img = mlx_new_image(game->mlx, 5, 5);
	game->minimap.floor05.img = mlx_new_image(game->mlx, 5, 5);
	save_block_img_addr(&(game->minimap.wall05.img));
	save_block_img_addr(&(game->minimap.floor05.img));
}

void	put_pixel_to_block(t_game *game)
{
	int	pxmove;
	int	x;
	int y;
	
	pxmove = game->minimap.pxmove;
	y = 0;
	while (y < 5)
	{
		while (x < 5)
		{
			my_mlx_pixel_put(&(game->minimap.wall05), x, y, GREEN);
			my_mlx_pixel_put(&(game->minimap.floor05), x++, y, WHITE);
		}
		y++;
	}
}

void	init_minimap(t_game *game)
{
	t_int_pos	pos;
	
	game->minimap.height = 200;
	game->minimap.width = 200;
	game->minimap.block_size = 20;
	game->minimap.pxmove = 5;
	game->map_width = 15;
	game->map_height = 15;
	game->map = map;
	
	pos.y = 0;
	while ((game->map)[pos.y])
	{
		pos.x = 0;
		while ((game->map)[pos.y][pos.x])
			draw_block(game, pos, (game->map)[pos.y][pos.x++]);
		pos.y++;
	}
	
}

int	main(void)
{
	t_game	game;
	
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1024, 720, "cub3D");
	init_minimap(&game);
	printf("height: %d, wdith: %d\n", game.minimap.height, game.minimap.width);
}