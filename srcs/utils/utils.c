/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:47:20 by hyap              #+#    #+#             */
/*   Updated: 2022/10/19 22:04:41 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]) != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	is_element(char *s)
{
	if (ft_strncmp(s, "NO", 2) == 0)
		return (1);
	if (ft_strncmp(s, "SO", 2) == 0)
		return (1);
	if (ft_strncmp(s, "WE", 2) == 0)
		return (1);
	if (ft_strncmp(s, "EA", 2) == 0)
		return (1);
	if (ft_strncmp(s, "F", 1) == 0)
		return (1);
	if (ft_strncmp(s, "C", 1) == 0)
		return (1);
	return (0);
}
