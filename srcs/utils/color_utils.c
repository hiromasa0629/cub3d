/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:54:47 by hyap              #+#    #+#             */
/*   Updated: 2022/11/12 18:11:58 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_color	int_to_rgb(uint32_t color)
{
	t_color	rgb;

	rgb.r = color / 65536;
	rgb.g = (color / 256) % 256;
	rgb.b = color % 256;
	return (rgb);
}

t_color	darker_rgb(t_color rgb)
{
	t_color	new;

	new.r = rgb.r / 2;
	new.g = rgb.g / 2;
	new.b = rgb.b / 2;
	return (new);
}

uint32_t	rgb_to_int(t_color rgb)
{
	uint32_t	color;

	color = rgb.r;
	color = (color << 8) + rgb.g;
	color = (color << 8) + rgb.b;
	return (color);
}
