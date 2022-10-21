/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:34:31 by hyap              #+#    #+#             */
/*   Updated: 2022/10/21 17:09:10 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**store_tmp_file_content(char *map_path)
{
	int		line_no;
	char	**lines;
	char	*line;
	int		gnl;
	int		fd;
	int		i;

	line_no = get_file_line_no(map_path);
	lines = (char **)malloc(sizeof(char *) * (line_no + 1));
	lines[line_no] = NULL;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		exit_error("Invalid file !\n");
	gnl = 1;
	i = 0;
	while (gnl == 1)
	{
		gnl = get_next_line(fd, &line);
		lines[i++] = line;
	}
	close(fd);
	return (lines);
}

int	store_color_value(t_color *color, char *line)
{
	int		i;
	char	**splits;
	
	i = 1;
	while (line[i] == ' ')
		i++;
	splits = ft_split(&(line[i]), ',');
	color->r = ft_atoi(splits[0]);
	color->g = ft_atoi(splits[1]);
	color->b = ft_atoi(splits[2]);
	free_splits(splits);
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

int	store_elements(t_game *game, char **lines)
{
	int	limit;
	int	i;
	int	success;
	
	limit = get_splits_no(lines) - game->map_height;
	i = 0;
	while (i < limit)
	{
		while (lines[i][0] == '\0')
			i++;
		if (ft_strncmp(lines[i], "NO", 2) == 0)
			success = store_wall_value(game, &(game->wall_NO), lines[i]);
		else if (ft_strncmp(lines[i], "SO", 2) == 0)
			success = store_wall_value(game, &(game->wall_SO), lines[i]);
		else if (ft_strncmp(lines[i], "WE", 2) == 0)
			success = store_wall_value(game, &(game->wall_WE), lines[i]);
		else if (ft_strncmp(lines[i], "EA", 2) == 0)
			success = store_wall_value(game, &(game->wall_EA), lines[i]);
		else if (ft_strncmp(lines[i], "F", 1) == 0)
			success = store_color_value(&(game->color_F), lines[i]);
		else if (ft_strncmp(lines[i], "C", 1) == 0)
			success = store_color_value(&(game->color_C), lines[i]);
		i++;
		if (!success)
			return (0);
	}
	return (1);
}

void	parse(t_game *game, char *map_path)
{
	(void)game;
	char	**file_content;
	
	validate_extension(map_path);
	file_content = store_tmp_file_content(map_path);
	if (is_valid_file_content(game, file_content) && \
		store_elements(game, file_content))
		return ;
	free_splits(file_content);
	exit_error("Invalid file content !\n");
}