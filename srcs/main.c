/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:05:51 by hyap              #+#    #+#             */
/*   Updated: 2022/11/07 13:28:20 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	key_hook(int keycode, t_game *game)
{
	(void)game;
	printf("key: %d\n", keycode);
	return (0);
}

void	init_game(t_game *game, char *map_path)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	parse(game, map_path);
	printf("game->player.x: %f, game->player.y: %f\n", game->player_pos.pos.x0, game->player_pos.pos.y0);
	init_minimap(game);
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
	// printf("NO addr: %p, x: %d, y: %d, size: %d\n", game.wall_NO.addr, game.wall_NO.x, game.wall_NO.y, game.wall_NO.size);
	// printf("SO addr: %p, x: %d, y: %d, size: %d\n", game.wall_SO.addr, game.wall_SO.x, game.wall_SO.x, game.wall_SO.size);
	// printf("WE addr: %p, x: %d, y: %d, size: %d\n", game.wall_WE.addr, game.wall_WE.x, game.wall_WE.x, game.wall_WE.size);
	// printf("EA addr: %p, x: %d, y: %d, size: %d\n", game.wall_EA.addr, game.wall_EA.x, game.wall_EA.x, game.wall_EA.size);
	// printf("\n");
	// printf("Floor rgb: #%d\n",game.f_color);
	// printf("Ceiling rgb: #%d\n", game.c_color);
	// printf("\n");
	// printf("Player x: %d, y: %d\n", game.player_pos.pos.x0, game.player_pos.pos.y0);
	// printf("\n");
	// printf("Map.x: %d, Map.y: %d\n", game.map_size.x, game.map_size.y);
	// printf("\n");
	// for (int i = 0; (game.map)[i]; i++)
	// 	printf("%s\n", (game.map)[i]);
	// mlx_key_hook(game.mlx, key_hook, &game);
	// mlx_loop(game.mlx);
	free_splits(game.map);
	// system("leaks cub3d");
	return (0);
}