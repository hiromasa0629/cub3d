/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:36:12 by hyap              #+#    #+#             */
/*   Updated: 2022/10/19 22:17:13 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* Check extension .cub and filename exist */
void	validate_extension(char *map_path)
{
	int		i;
	char	*file;
	
	i = ft_strlen(map_path) - 1;
	while (map_path[i] && map_path[i] != '/')
		i--;
	if (map_path[i] == '/')
		i++;
	else
		i = 0;
	file = &map_path[i];
	i = 0;
	while (file[i])
	{
		if (file[i] == '.' && i != 0)
			break ;
		i++;
	}
	if (!file[i])
		exit_error("Missing extension !\n");
	if (ft_strncmp(&file[++i], "cub", 3) != 0)
		exit_error("Invalid extension !\n");
}

int	is_asset_exist(char *file)
{
	int	fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	return (1);
}

int	is_valid_hex_color(char *hex)
{
	
}

int	has_error_line(char *line)
{
	char	**splits;
	int		has_error;
	
	splits = ft_split(line, ' ');
	has_error = 0;
	if (get_splits_no(splits) != 2)
		has_error = 1;
	if (!is_element(splits[0])
		has_error = 1;
	
}

void	validate_lines(char **lines)
{
	int		i;
	char	**splits;
	int		has_error;
	
	i = 0;
	has_error = 0;
	while (lines[i])
	{
		if (lines[i][0] == '\0')
			continue ;
		splits = ft_split(lines[i], ' ');
		if (get_splits_no(splits) != 2)
		{
			has_error = 1;
			break ;
		}
		if (!is_element(splits[0]))
		{
			has_error = 1;
			break ;
		}
		i++;
	}
	if (has_error)
		exit_error("Invalid element\n");
}