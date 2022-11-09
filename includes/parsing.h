/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:07:46 by hyap              #+#    #+#             */
/*   Updated: 2022/11/09 21:41:58 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "main.h"

/* element_validation.c */
void	validate_extension(char *map_path);
int		is_valid_elements(char ***lines);
/* map_validation.c */
int		is_valid_map(t_game *game, char **lines);
/* validation.c */
int		is_valid_file_content(t_game *game, char **lines);
/* parse_save.c */
int		store_elements(t_game *game, char **lines);
/* parse.c */
void	parse(t_game *game, char *map_path);

#endif