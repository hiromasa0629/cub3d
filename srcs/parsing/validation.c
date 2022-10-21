/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 21:13:44 by hyap              #+#    #+#             */
/*   Updated: 2022/10/21 17:58:06 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		get_longest_strlen(char **lines)
{
	int	i;
	int	max;

	i = 0;
	max = ft_strlen(lines[0]);
	while (lines[i])
	{
		if (max < ft_strlen(lines[i]))
			max = ft_strlen(lines[i]);
		i++;
	}
	return (max);
}

char	**remalloc_map(t_game *game, char **lines)
{
	int		i;
	int		j;
	char	**new_map;
	
	i = 0;
	game->map_width = get_longest_strlen(lines);
	game->map_height = get_splits_no(lines);
	new_map = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	new_map[game->map_height] = NULL;
	while (lines[i])
	{
		new_map[i] = (char *)malloc(sizeof(char) * (game->map_width + 1));
		new_map[i][game->map_width] = '\0';
		j = -1;
		while (lines[i][++j])
			new_map[i][j] = lines[i][j];
		while (j < game->map_width)
			new_map[i][j++] = ' ';
		i++;
	}
	return (new_map);
}

int	is_valid_file_content(t_game *game, char **lines)
{
	char	**tmp;
	
	tmp = lines;
	if (!is_valid_elements(&tmp))
		return (0);
	while ((*tmp) && (*tmp)[0] == '\0')
		tmp++;
	if (!(*tmp))
		return (0);
	tmp = remalloc_map(game, tmp);
	if (!is_valid_map(game, tmp))
	{
		free_splits(tmp);
		return (0);
	}
	game->map = tmp;
	return (1);
}