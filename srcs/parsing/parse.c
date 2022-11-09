/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:34:31 by hyap              #+#    #+#             */
/*   Updated: 2022/11/09 21:38:01 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**store_tmp_file_content(char *map_path)
{
	t_helper	helper;
	int			i;

	helper.line_no = get_file_line_no(map_path);
	helper.lines = (char **)malloc(sizeof(char *) * (helper.line_no + 1));
	(helper.lines)[helper.line_no] = NULL;
	helper.fd = open(map_path, O_RDONLY);
	if (helper.fd < 0)
		exit_error("Invalid file !\n");
	helper.gnl = 1;
	i = 0;
	while (helper.gnl == 1)
	{
		helper.gnl = get_next_line(helper.fd, &(helper.line));
		(helper.lines)[i++] = helper.line;
	}
	close(helper.fd);
	return (helper.lines);
}

void	parse(t_game *game, char *map_path)
{
	char	**dptr;

	(void)game;
	validate_extension(map_path);
	dptr = store_tmp_file_content(map_path);
	if (is_valid_file_content(game, dptr) && store_elements(game, dptr))
	{
		free_splits(dptr);
		return ;
	}
	free_splits(dptr);
	exit_error("Invalid file content !\n");
}
