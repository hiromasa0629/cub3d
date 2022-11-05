/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:00:51 by hyap              #+#    #+#             */
/*   Updated: 2022/11/05 17:52:36 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_duplicated_element(char *s)
{
	static t_elements	el = {0, 0, 0, 0, 0, 0};

	if (((ft_strcmp(s, "NO") == 0) && el.had_NO) || \
		((ft_strcmp(s, "SO") == 0) && el.had_SO) || \
		((ft_strcmp(s, "WE") == 0) && el.had_WE) || \
		((ft_strcmp(s, "EA") == 0) && el.had_EA) || \
		((ft_strcmp(s, "F") == 0) && el.had_F) || \
		((ft_strcmp(s, "C") == 0) && el.had_C))
		return (1);
	if (ft_strcmp(s, "NO") == 0)
		el.had_NO = 1;
	else if (ft_strcmp(s, "SO") == 0)
		el.had_SO = 1;
	else if (ft_strcmp(s, "WE") == 0)
		el.had_WE = 1;
	else if (ft_strcmp(s, "EA") == 0)
		el.had_EA = 1;
	else if (ft_strcmp(s, "F") == 0)
		el.had_F = 1;
	else if (ft_strcmp(s, "C") == 0)
		el.had_C = 1;
	return (0);
}

int	is_wall_element(char *s)
{
	if (ft_strcmp(s, "NO") == 0)
		return (1);
	if (ft_strcmp(s, "SO") == 0)
		return (1);
	if (ft_strcmp(s, "WE") == 0)
		return (1);
	if (ft_strcmp(s, "EA") == 0)
		return (1);
	return (0);
}

int	is_fnc_element(char *s)
{
	if (ft_strcmp(s, "F") == 0)
		return (1);
	if (ft_strcmp(s, "C") == 0)
		return (1);
	return (0);
}

int	is_str_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

