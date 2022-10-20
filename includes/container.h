/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:09:53 by hyap              #+#    #+#             */
/*   Updated: 2022/10/20 22:22:37 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_H
# define CONTAINER_H

typedef	struct s_game		t_game;
typedef struct s_elements	t_elements;

struct s_game {
	void	*mlx;
	void	*win;
	char	**map;
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

#endif