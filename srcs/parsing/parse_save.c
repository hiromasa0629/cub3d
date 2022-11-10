/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:37:44 by hyap              #+#    #+#             */
/*   Updated: 2022/11/10 17:24:52 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	store_color_value(int *color, char *line)
{
	int		i;
	char	**splits;
	int		res;

	i = 1;
	while (line[i] == ' ')
		i++;
	splits = ft_split(&(line[i]), ',');
	res = ft_atoi(splits[0]);
	res = (res << 8) + ft_atoi(splits[1]);
	res = (res << 8) + ft_atoi(splits[2]);
	free_splits(splits);
	*color = res;
	return (1);
}

int	store_wall_value(t_game *game, t_img *img, char *line)
{
	int	i;

	i = 2;
	while (line[i] == ' ')
		i++;
	img->img = mlx_xpm_file_to_image(game->mlx, &(line[i]), &(img->x), \
		&(img->y));
	if (!(img->img))
		return (0);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->size, \
		&img->endian);
	return (1);
}

int	check_n_save_elements(char *s, t_game *game)
{
	int	success;

	success = 0;
	if (ft_strcmp(s, "NO") == 0)
		success = store_wall_value(game, &(game->wall_no), s);
	else if (ft_strcmp(s, "SO") == 0)
		success = store_wall_value(game, &(game->wall_so), s);
	else if (ft_strcmp(s, "WE") == 0)
		success = store_wall_value(game, &(game->wall_we), s);
	else if (ft_strcmp(s, "EA") == 0)
		success = store_wall_value(game, &(game->wall_ea), s);
	else if (ft_strcmp(s, "F") == 0)
		success = store_color_value(&(game->f_color), s);
	else if (ft_strcmp(s, "C") == 0)
		success = store_color_value(&(game->c_color), s);
	return (success);
}

int	store_elements(t_game *game, char **lines)
{
	int	limit;
	int	i;
	int	success;

	limit = get_splits_no(lines) - game->map_size.y;
	i = 0;
	printf("limit: %d\n", limit);
	while (i < limit)
	{
		while (lines[i][0] == '\0')
			i++;
		if (i >= limit)
			break ;
		success = check_n_save_elements(lines[i], game);
		if (!success)
			return (0);
		i++;
	}
	return (1);
}
