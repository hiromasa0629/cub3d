/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 10:41:27 by hyap              #+#    #+#             */
/*   Updated: 2022/11/14 13:52:35 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_space(char **lines, t_int_pos pos)
{
	if (lines[pos.y][pos.x] == ' ')
		return (1);
	return (0);
}

int    is_wall_door(char **lines, t_int_pos pos)
{
    if (lines[pos.y][pos.x] == '1')
        return (1);
    else if (lines[pos.y][pos.x] == '2')
        return (2);
    else if (lines[pos.y][pos.x] == '3')
        return (3);
    return (0);
}

int	is_player(char **lines, t_int_pos pos)
{
	if (lines[pos.y][pos.x] == 'N' || lines[pos.y][pos.x] == 'S' || \
		lines[pos.y][pos.x] == 'E' || lines[pos.y][pos.x] == 'W')
		return (1);
	return (0);
}

int	is_floor(char **lines, t_int_pos pos)
{
	if (lines[pos.y][pos.x] == '0')
		return (1);
	return (0);
}

int	is_map_element(char **lines, t_int_pos pos)
{
	if (is_space(lines, pos) || is_wall_door(lines, pos) || \
		is_player(lines, pos) || is_floor(lines, pos))
		return (1);
	return (0);
}
