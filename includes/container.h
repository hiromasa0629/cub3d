/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:09:53 by hyap              #+#    #+#             */
/*   Updated: 2022/10/21 17:56:46 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_H
# define CONTAINER_H

typedef	struct s_game			t_game;
typedef struct s_elements		t_elements;
typedef struct s_map_validation	t_map_validation;
typedef	struct s_int_pos		t_int_pos;
typedef struct s_img			t_img;
typedef struct s_color			t_color;

struct s_color {
	int	r;
	int	g;
	int b;
};

struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		size;
	int		x;
	int		y;
	int		endian;
};

/* For checking duplicated elements 
	by defining a static struct
*/
struct s_elements {
	int	had_NO;
	int	had_SO;
	int	had_WE;
	int	had_EA;
	int	had_F;
	int	had_C;
};
struct s_int_pos {
	int	x;
	int	y;
};
/* For checking space surrounding */
struct s_map_validation {
	int	top;
	int	bottom;
	int	left;
	int	right;
	int	topleft;
	int	topright;
	int	bottomleft;
	int	bottomright;
};

struct s_game {
	void	*mlx;
	void	*win;
	char	**map;
	t_img		wall_NO;
	t_img		wall_SO;
	t_img		wall_EA;
	t_img		wall_WE;
	t_color		color_F;
	t_color		color_C;
	int			map_width;
	int			map_height;
	t_int_pos	player_pos;
};

#endif