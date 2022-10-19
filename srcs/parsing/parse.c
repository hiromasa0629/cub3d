/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:34:31 by hyap              #+#    #+#             */
/*   Updated: 2022/10/19 21:50:36 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_line_no(char *map_path)
{
	int		fd;
	int		gnl;
	int		line_no;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		exit_error("Invalid file !\n");
	gnl = 1;
	line_no = 0;
	while (gnl == 1)
	{
		gnl = get_next_line(fd, &line);
		free(line);
		line_no++;
	}
	close(fd);
	return (line_no);
}

char	**store_tmp_lines(char *map_path)
{
	int		line_no;
	char	**lines;
	char	*line;
	int		gnl;
	int		fd;
	int		i;

	line_no = get_line_no(map_path);
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
	return (lines);
}

void	parse(t_game *game, char *map_path)
{
	(void)game;
	char	**lines;
	
	validate_extension(map_path);
	lines = store_tmp_lines(map_path);
}