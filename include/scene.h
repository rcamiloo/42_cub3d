/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <rcamilo-@student.42sp.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:07:00 by rcamilo-          #+#    #+#             */
/*   Updated: 2021/03/13 14:13:58 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define SUCCESS 1
# define FAIL 0

typedef struct	s_map
{
char	**matrix;
int		max_columns;
int		max_lines;
char	player_face;
int		player_x;
int		player_y;
}				t_map;

typedef struct	s_scene {
	char	*wall_so;
	char	*wall_no;
	char	*wall_we;
	char	*wall_ea;
	char	*sprite;
	int		color_floor;
	int		color_ceiling;
	int		res_width;
	int		res_height;
	int		control;
	t_map	map;
}				t_scene;



int	create_trgb(char *t, char *r, char *g, char *b);
int	check_name(char *s);
int	check_existence(char *s);
int	vector_size(char **vector);
int check_colors(char *s);
int	process_colors(char **line, t_scene *scene);
int	process_texture(char **token, t_scene *scene);
int check_resolution(char *s);
int	process_resolution(char **token, t_scene *scene);
void tab_sanitizer(char **s);
int	process_config(char **line, t_scene *scene);
int	process_file(char *file, t_scene *scene);

#endif
