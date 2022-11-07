/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:07:10 by hyap              #+#    #+#             */
/*   Updated: 2022/11/07 13:16:07 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "container.h"

/* key_hooks.c */
void	handle_keypress(int key, t_game *game);
/* minimap.c */
void	init_minimap(t_game *game);

#endif