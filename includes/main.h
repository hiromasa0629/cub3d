/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:16:41 by hyap              #+#    #+#             */
/*   Updated: 2022/11/05 22:21:15 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "mlx.h"
# include "get_next_line_bonus.h"
# include "container.h"
# include "utils.h"
# include "parsing.h"
# include "minimap.h"
/* Keycodes */
# define ESC_BTN 53
# define RIGHT_BTN 124
# define LEFT_BTN 123
# define W_BTN 13
# define A_BTN 0
# define S_BTN 1
# define D_BTN 2
# define PLAYER_STEP 0.25
# define SCALE 20
/* Minimap max tiles */
# define MI_WIDTH 10
# define MI_HEIGHT 10
/* Minimap max px */
# define MI_PX_WIDTH 200
# define MI_PX_HEIGHT 200
/* Colors */
# define GREEN 0x7FFF00
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000

#endif
