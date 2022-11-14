/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:07:10 by hyap              #+#    #+#             */
/*   Updated: 2022/11/14 16:11:37 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "container.h"

/* key_hooks.c */
int		handle_keypress(int key, t_game *game);
/* minimap.c */
void	draw_minimap(t_game *game);
/* dda_line.c */
void	dda_line(t_matrix matrix, t_game *game);
/* raycasting_texture.c */
void	draw_texture(t_game *game, t_raycast *rc, int x);
void	dda_3d(t_game *game, t_raycast *rc, int x);
void	draw_rays(t_game *game, t_raycast *rc);
/* raycasting.c */
void	init_raycast(t_game *game, t_raycast *rc);
void	set_side_dist_x(t_game *game, t_raycast *rc);
void	set_side_dist_y(t_game *game, t_raycast *rc);
int		determine_hit(t_game *game, t_raycast *rc, bool close_door);
void	draw_3d(t_game *game);
/* floor_n_ceiling.c */
void	draw_floor_n_ceiling(t_img *img, int color, int start_y, int end_y);
/* weapon.c */
void	init_weapon(t_game *game, t_weapons *weapons);
void	draw_weapon(t_game *game);
/* mouse.c */
void	handle_mouse(t_game *game);
/* door.c */
void	handle_door(t_game *game);

#endif