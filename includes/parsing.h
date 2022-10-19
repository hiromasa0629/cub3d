/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:07:46 by hyap              #+#    #+#             */
/*   Updated: 2022/10/19 21:51:07 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "main.h"

void	validate_extension(char *map_path);
void	validate_lines(char **lines);
void	parse(t_game *game, char *map_path);

#endif