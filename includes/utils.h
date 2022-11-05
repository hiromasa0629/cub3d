/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:28:49 by hyap              #+#    #+#             */
/*   Updated: 2022/11/05 17:49:32 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "main.h"

/* ft_split.c */
char	**ft_split(char *s, char c);
int		get_splits_no(char	**splits);
void	free_splits(char **splits);
/* utils.c */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
/* map_utils.c */
int	is_space(char **lines, t_int_pos pos);
int	is_wall(char **lines, t_int_pos pos);
int	is_player(char **lines, t_int_pos pos);
int	is_floor(char **lines, t_int_pos pos);
/* exit.c */
void	exit_error(const char *s);

#endif
