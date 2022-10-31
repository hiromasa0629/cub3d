/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:09:53 by hyap              #+#    #+#             */
/*   Updated: 2022/10/31 12:27:13 by hyap             ###   ########.fr       */
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
typedef struct s_minimap		t_minimap;
typedef struct s_matrix			t_matrix;
typedef struct s_player			t_player;
typedef struct s_double_pos		t_double_pos;

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

struct s_matrix
{
	double x0;
	double x1;
	double y0;
	double y1;
};

struct s_minimap
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
	int			tile_size;
	int			block_size;
	t_img		wall05;
	t_img		floor05;
	t_img		player05;
	int			pxmove;
	int			even_tiles;
	t_int_pos	start_pos;
	t_int_pos	px_start_pos;
	t_int_pos	px_player_pos;
	int			nx_tiles;
	int			ny_tiles;
};

typedef struct	s_mini {
	t_int_pos	start_pos;
	t_int_pos	pos;
	t_int_pos	pxpos;
	t_img		img;
}	t_mini;

struct s_double_pos {
	double	x;
	double	y;
};

struct s_player {
	t_double_pos	pos;
	t_int_pos		tile_pos;
	t_double_pos	dir;
	t_double_pos	moved;
};


struct s_game {
	void		*mlx;
	void		*win;
	char		**map;
	t_img		wall_NO;
	t_img		wall_SO;
	t_img		wall_EA;
	t_img		wall_WE;
	t_color		color_F;
	t_color		color_C;
	int			map_width;
	int			map_height;
	t_player	player;
	t_minimap	minimap;
};

#endif