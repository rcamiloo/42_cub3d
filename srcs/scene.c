/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <rcamilo-@student.42sp.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:24:05 by rcamilo-          #+#    #+#             */
/*   Updated: 2021/03/06 22:52:53 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ft_free(void *pointer)
{
	free(pointer);
	pointer = NULL;
	return;
}

void free_matrix(char **matrix)
{
	int i;

	if (matrix == NULL)
		return;
	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

int		check_name(char *s)
{
	int		size;
	char	*check;

	check = NULL;
	size = ft_strlen(s);
	if (size > 4)
		check = ft_strnstr((s + size - 4), ".cub", size);
	if (check == NULL)
		printf("Error\nDescription: Wrong file extension\n");
	return (check == NULL ? FAIL : SUCCESS);
}

int		check_existence(char *s)
{
	int fd;

	fd = open(s, O_RDONLY);
	if (fd >= 0)
		close(fd);
	else
		perror("Error\nDescription");
	return (fd == -1 ? FAIL : SUCCESS);
}

int		vector_size(char **vector)
{
	int i;

	if (vector == NULL)
		return (0);
	i = 0;
	while (vector[i] != NULL)
		i++;
	return (i);
}

int		check_colors(char *s)
{
	int size;
	int i;
	int comma;

	size = ft_strlen(s);
	comma = 0;
	if (size < 5)
		return (FAIL);
	else
	{
		i = 0;
		while (i < size)
		{
			if (((s[i] - '0') < 0 || (s[i] - '0') > 9) && s[i] != ',')
				return (FAIL);
			else if (s[i] == ',')
				comma++;
			i++;
		}
	}
	return (comma != 2 ? FAIL : SUCCESS);
}

int		process_colors(char *line, t_scene *scene)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	char	*temp1;
	char	*temp2;

	temp1 = ft_strtrim(line, " ");
	temp2 = ft_sanitize(temp1 + 1, " ");
	free(temp1);
	rgb = ft_split(temp2, ',');
	if (check_colors(temp2) == FAIL || vector_size(rgb) != 3)
	{
		printf("Error\nColor error in line: ");
		free_matrix(rgb);
		free(temp2);
		return (FAIL);
	}
	r = atoi(rgb[0]);
	g = atoi(rgb[1]);
	b = atoi(rgb[2]);
	free_matrix(rgb);
	free(temp2);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
	{
		printf("Error\nColor error in line: ");
		return (FAIL);
	}
	rgb = ft_split(line, ' ');
	if (rgb[0][0] == 'C' && !scene->color_ceiling)
		scene->color_ceiling = create_trgb(0, r, g, b);
	else if (rgb[0][0] == 'F' && !scene->color_floor)
		scene->color_floor = create_trgb(0, r, g, b);
	else
	{
		printf("Error\nColor error in line: ");
		free_matrix(rgb);
		return (FAIL);
	}
	scene->control++;
	free_matrix(rgb);
	return (SUCCESS);
}

int		process_texture(char **token, t_scene *scene)
{
	if (check_existence(token[1]) == FAIL)
	{
		printf("Error on line: ");
		return (FAIL);
	}
	if (!ft_strncmp(token[0], "NO\0", 3) && !scene->wall_no)
		scene->wall_no = token[1];
	else if (!ft_strncmp(token[0], "SO\0", 3) && !scene->wall_so)
		scene->wall_so = token[1];
	else if (!ft_strncmp(token[0], "WE\0", 3) && !scene->wall_we)
		scene->wall_we = token[1];
	else if (!ft_strncmp(token[0], "EA\0", 3) && !scene->wall_ea)
		scene->wall_ea = token[1];
	else if (!ft_strncmp(token[0], "S\0", 2) && !scene->sprite)
		scene->sprite = token[1];
	else
	{
		printf("Error\nDuplicated parameter in line: ");
		return (FAIL);
	}
	scene->control++;
	return (SUCCESS);
}

int		check_resolution(char *s)
{
	int size;
	int i;

	size = ft_strlen(s);
	i = 0;
	while (i < size)
	{
		if ((s[i] - '0') < 0 || (s[i] - '0') > 9)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int		process_resolution(char **token, t_scene *scene)
{
	if (!check_resolution(token[1]) || !check_resolution(token[2])
		|| !ft_atoi(token[1]) || !ft_atoi(token[2]))
	{
		printf("Error\nResolution error in line: ");
		return (FAIL);
	}
	if (!scene->res_height && !scene->res_width)
	{
		scene->res_width = ft_atoi(token[1]);
		scene->res_height = ft_atoi(token[2]);
		scene->control += 2;
	}
	else
	{
		printf("Error\nResolution error in line: ");
		return (FAIL);
	}
	return (SUCCESS);
}

char	*tab_sanitizer(char *s)
{
	int		size;
	int		i;
	char	*temp;

	size = ft_strlen(s);
	if(!(temp = ft_strdup(s)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (temp[i] == '\t')
			temp[i] = ' ';
		i++;
	}
	return (temp);
}

int		process_line(char *line, t_scene *scene)
{
	char	**token;
	int		i;
	int		size;
	int		control;

	token = ft_split(line, ' ');
	size = vector_size(token);
	if ((!ft_strncmp(token[0], "NO\0", 3) || !ft_strncmp(token[0], "SO\0", 3)
	|| !ft_strncmp(token[0], "WE\0", 3) || !ft_strncmp(token[0], "EA\0", 3)
	|| !ft_strncmp(token[0], "S\0", 2)) && size == 2)
		control = process_texture(token, scene);
	else if ((!ft_strncmp(token[0], "F\0", 2)
			|| !ft_strncmp(token[0], "C\0", 2)))
		control = process_colors(line, scene);
	else if (!ft_strncmp(token[0], "R\0", 2) && size == 3)
		control = process_resolution(token, scene);
	else
	{
		control = FAIL;
		printf("Error\nProcessing line: ");
	}
	free_matrix(token);
	return (control);
}


void print_matrix(char **matrix)
{
	int i;

	i = 0;
	while(matrix[i] != NULL)
		printf("pp%s\n", matrix[i++]);
}



char	**matrix_increase(char **matrix, int max_lines, int increase)
{
	char **temp;
	int i;

	if (!(temp = (char **)malloc (sizeof (char *) * (max_lines + increase + 1))))
		return NULL;

	i = 0;
	while (i < max_lines)
	{
		if (!(temp[i] = ft_strdup(matrix[i])))
			return NULL;
		i++;
	}
	while (i <= max_lines + increase)
		temp[i++] = NULL;
	return temp;
}



int	add_line(char *line, t_map *map)
{
	char **temp;

	if (!(temp = matrix_increase(map->matrix, map->max_lines, 1)))
		return (FAIL);
	if (!(temp[map->max_lines] = ft_strdup(line)))
		return (FAIL);
	free_matrix (map->matrix);
	map->matrix = temp;
	map->max_lines++;
	map->max_columns = ft_strlen(line) > map->max_columns ?
						ft_strlen(line) : map->max_columns;

	return (SUCCESS);
}

int normalize_map(t_map *map)
{
	char	*temp;
	int		size;
	int		i;
	int		j;

	i = 0;
	while(map->matrix[i])
	{
		size = ft_strlen((map->matrix[i]));
		if(!(temp = (char *)malloc(sizeof(char) * (map->max_columns + 1))))
			return (FAIL);
		j = 0;
		while (j < size)
		{
			temp[j] = map->matrix[i][j];
			j++;
		}
		while (j < map->max_columns)
			temp[j++] = ' ';
		temp[map->max_columns] = '\0';
		free(map->matrix[i]);
		map->matrix[i] = temp;
		i++;
	}
	return (SUCCESS);
}

int		check_line(t_map *map, int line)
{
	int i;

	i = 0;
	while(i < map->max_columns)
	{
		if (map->matrix[line][i] != ' ' && map->matrix[line][i] != '1')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int		check_column(t_map *map, int column)
{
	int i;

	i = 0;
	while(i < map->max_lines)
	{
		if (map->matrix[i][column] != ' ' && map->matrix[i][column] != '1')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int		verify_zero(t_map *map, int i, int j)
{
	int a = (ft_strrchr("012NEWS", map->matrix[i - 1][j - 1])
		&& ft_strrchr("012NEWS", map->matrix[i - 1][j])
		&& ft_strrchr("012NEWS", map->matrix[i - 1][j +1])
		&& ft_strrchr("012NEWS", map->matrix[i][j - 1])
		&& ft_strrchr("012NEWS", map->matrix[i][j + 1])
		&& ft_strrchr("012NEWS", map->matrix[i + 1][j - 1])
		&& ft_strrchr("012NEWS", map->matrix[i + 1][j])
		&& ft_strrchr("012NEWS", map->matrix[i + 1][j + 1]));
	if (a)
		return (SUCCESS);
	else
		return (FAIL);
}

int		check_elements(t_map *map)
{
	int i;
	int j;
	int control;

	i = 1;
	while (i <(map->max_lines - 1))
	{
		j = 1;
		while (j < (map->max_columns - 1))
		{
			if(ft_strrchr("0NSWE2", map->matrix[i][j]))
			{
				//printf("%c ", map->matrix[i][j]);
				if(!(control = verify_zero(map, i, j)))
					return (FAIL);
				if(ft_strrchr("NSWE", map->matrix[i][j]))
				{
					if (map->player_face)
						return (FAIL);
					map->player_face =  map->matrix[i][j];
					map->player_x = j;
					map->player_y = i;
				}
			}
			j++;
		}
		i++;
		//printf("\n i = %d\n", i);
	}
	return (SUCCESS);
}


int		check_map(t_map *map)
{
	int control;

	control = normalize_map(map);
	if(!(check_line(map, 0) && check_line(map, map->max_lines - 1)
		&& check_column(map, 0) && check_column(map, map->max_columns - 1)))
		return (FAIL);
	if(!check_elements(map))
		return (FAIL);
	if(!(map->player_face && map->player_x && map->player_y))
		return (FAIL);
	if (control && 0)
	{
		print_matrix(map->matrix);
		printf("max_columns: %d\n", map->max_columns);
		printf("max_lines: %d\n", map->max_lines);
	}
	return (SUCCESS);
}

int		process_map(int fd, char *line, t_map *map)
{
	int		count;
	int		control;
	int		gnl;

	control = add_line(line, map);
	count = 0;

	while ((gnl = get_next_line(fd, &line)) >= 0 && control)
	{
		if (line[0] == '1' || line[0] == ' ' || line[0] == '\0')
		{
			control = add_line(line, map);
			count ++;
		}
		else
		{
			control = FAIL;
		}
		free(line);
		line = NULL;
		if(!gnl)
			break;
	}
	control = control ? check_map(map) : FAIL;
	// if (control == FAIL)
	// 		free_matrix(map->matrix);
	if(line)
		free(line);
	return (control == SUCCESS ? 0 : count);
}


int		process_file(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	char	*temp;
	int		count;
	int		control;
	char	**token;
	int		gnl;

	fd = open(file, O_RDONLY);
	count = 0;
	control = 1;
	line = NULL;
	while (((gnl = get_next_line(fd, &line)) >= 0) && control)
	{
		temp = tab_sanitizer(line);
		free(line);
		line = temp;
		token = ft_split(line, ' ');
		if (token[0] == '\0')
			control = 1;
		else if (token[0][0] == 'R' || token[0][0] == 'N'
			|| token[0][0] == 'S' || token[0][0] == 'W' || token[0][0] == 'E'
			|| token[0][0] == 'F' || token[0][0] == 'C')
			control = process_line(line, scene);
		else if (token[0][0] == '1' || token[0][0] == ' ')
		{
			if (scene->control != 9)
			{
				printf("Error\nNot enough parameters before map\n");
				free_matrix(token);
				free(line);
				line = NULL;
				close(fd);
				return (FAIL);
			}
			else if ((control = process_map(fd, line, &scene->map))) //se mapa processado ok retorno 0
			{
				count += control;
				control = FAIL;
				printf("Error\nError in line: ");
			}
			else
				control = SUCCESS;
		}
		else
		{
			printf("Error\nError in line: ");
			control = FAIL;
		}
		count += control ? 1 : 0;
		free(line);
		line = NULL;
		free_matrix(token);
		if(!gnl)
			break;
	}
	if(line)
		free(line);
	close(fd);
	if(!scene->map.player_face)
		printf("Error\n");
	if (control == FAIL)
		printf("%d\n", count);
	return (control);
}

int		main(int argc, char *argv[])
{
	t_scene scene = {0};
	int i;

	if (argc == 2)
	{
		if (check_name(argv[1]) && check_existence(argv[1]))
			process_file(argv[1], &scene);
			i = 0;
			// while(scene.map.matrix[i])
			// 	printf("%s\n", scene.map.matrix[i++]);
			// printf("max_columns: %d\n", scene.map.max_columns);
			// printf("max_lines: %d\n", scene.map.max_lines);
	}
	else
	{
		printf("Error");
		return (1);
	}
	free_matrix(scene.map.matrix);
	return (0);
}
