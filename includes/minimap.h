/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:30:03 by yang              #+#    #+#             */
/*   Updated: 2022/10/24 16:00:18 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
#define MINIMAP_H

#include "container.h"

#define PI 3.1415926535

typedef struct s_matrix
{
	double x0;
	double x1;
	double y0;
	double y1;
}	t_matrix;

typedef struct s_minimap
{
	int			width;
	int 		height;
	double 		start_x;
	double 		start_y;
	t_matrix	player_pos;
	double 		scale;
	double 		player_delta_x;
	double 		player_delta_y;
	double 		player_angle;
	t_img 		map;
	int			line_len;
} t_minimap;

#endif