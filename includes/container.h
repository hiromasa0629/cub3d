/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:09:53 by hyap              #+#    #+#             */
/*   Updated: 2022/11/12 17:35:35 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_H
# define CONTAINER_H

typedef struct s_game			t_game;
typedef struct s_elements		t_elements;
typedef struct s_map_validation	t_map_validation;
typedef struct s_int_pos		t_int_pos;
typedef struct s_img			t_img;
typedef struct s_color			t_color;
typedef struct s_minimap		t_minimap;
typedef struct s_texture		t_texture;
typedef struct s_matrix			t_matrix;
typedef struct s_player			t_player;
typedef struct s_double_pos		t_double_pos;
typedef struct s_raycast		t_raycast;
typedef struct s_weapons		t_weapons;
typedef struct s_helper			t_helper;

struct s_color {
	int	r;
	int	g;
	int	b;
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

struct s_int_pos {
	int	x;
	int	y;
};

struct s_double_pos
{
	double	x;
	double	y;
};

struct s_texture {
	t_int_pos	tex_pos;
	double		tex_start;
	double		step;
	t_img		img;
};

struct s_matrix
{
	double	x0;
	double	x1;
	double	y0;
	double	y1;
};

struct s_player
{
	t_matrix	pos;
	double		angle;
	char		c;
};

struct s_minimap
{
	t_img			img;
	t_matrix		player_pos;
	double			player_angle;
	t_int_pos		size;
	t_int_pos		pxsize;
	t_double_pos	start;
};

struct s_weapons {
	int			x;
	int			y;
	int			status;
	t_int_pos	start_pos;
	t_img		*images;
};

struct s_game {
	void		*mlx;
	void		*win;
	char		**map;
	int			f_color;
	int			c_color;
	t_img		wall_no;
	t_img		wall_so;
	t_img		wall_ea;
	t_img		wall_we;
	t_int_pos	map_size;
	t_minimap	minimap;
	t_player	player_pos;
	t_img		img_3d;
	t_weapons	weapons;
	int			prev_mouse_x;
	int			paused;
	t_img		paused_img;
};

/* For checking duplicated elements 
	by defining a static struct
*/
struct s_elements {
	int	had_no;
	int	had_so;
	int	had_we;
	int	had_ea;
	int	had_f;
	int	had_c;
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
/* For raycasting use */
struct s_raycast {
	t_matrix		draw_ray;
	t_int_pos		map_pos;
	t_int_pos		step;
	t_int_pos		ray_deduct;
	t_double_pos	raydir;
	t_double_pos	sidedist;
	t_double_pos	deltadist;
	t_double_pos	wall;
	t_texture		texture;
	double			perpwalldist;
	double			angle;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				hit;
	int				side;
};
/* Helper */
struct s_helper {
	int		line_no;
	char	**lines;
	char	*line;
	int		gnl;
	int		fd;
};

#endif