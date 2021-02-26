/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <rcamilo-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:24:05 by rcamilo-          #+#    #+#             */
/*   Updated: 2021/02/25 20:51:40 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	check_name(char *s)
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

int	check_existence(char *s)
{
	int fd;

	fd = open(s, O_RDONLY);
	if (fd >= 0)
		close(fd);
	else
		perror("Error\nDescription");
	return (fd == -1 ? FAIL : SUCCESS);
}

int	vector_size(char **vector)
{
	int i;

	if (vector == NULL)
		return (0);
	i = 0;
	while (vector[i] != NULL)
		i++;
	return (i);
}

int check_colors(char *s)
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
		while(i < size)
		{
			if (((s[i] - '0') < 0 || (s[i] - '0') > 9 ) && s[i] != ',')
				return (FAIL);
			else if (s[i] == ',')
				comma++;
			i++;
		}
	}
	return (comma != 2 ? FAIL : SUCCESS);
}

int	process_colors(char *line, t_scene *scene)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	char	*temp;



	temp = ft_sanitize(ft_strtrim(line, " ") + 1, " ");
	rgb = ft_split(temp, ',');
	if (check_colors(temp) == FAIL || vector_size(rgb) != 3)
	{
		printf("Error\nColor error in line: ");
		return (FAIL);
	}
	r = atoi(rgb[0]);
	g = atoi(rgb[1]);
	b = atoi(rgb[2]);
	free(rgb);
	free(temp);
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
		return (FAIL);
	}
	scene->control++;
	free(temp);
	return (SUCCESS);
}

int	process_texture(char **token, t_scene *scene)
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

int check_resolution(char *s)
{
	int size;
	int i;

	size = ft_strlen(s);
	i = 0;
	while(i < size)
	{
		if ((s[i] - '0') < 0 || (s[i] - '0') > 9 )
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	process_resolution(char **token, t_scene *scene)
{

	if(!check_resolution(token[1]) || !check_resolution(token[2])
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

char *tab_sanitizer(char *s)
{
	int size;
	int i;
	char *temp;

	size = ft_strlen(s);
	temp = ft_strdup(s);
	i = 0;
	while (i < size)
	{
		if (temp[i] == '\t')
			temp[i] = ' ';
		i++;
	}
	return (temp);
}

int	process_line(char *line, t_scene *scene)
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
	free(token);
	return (control);
}

int	process_file(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	char	*temp;
	int		count;
	int		control;
	char	**token;

	fd = open(file, O_RDONLY);
	count = 0;
	control = 1;
	while (get_next_line(fd, &line) && control)
	{
		temp = tab_sanitizer(line);
		free (line);
		line = temp;
		token = ft_split(line, ' ');
		if (token[0] == '\0')
			control = 1;
		else if (token[0][0] == 'R' || token[0][0] == 'N' || token[0][0] == 'S' || token[0][0] == 'W'
			|| token[0][0] == 'E' || token[0][0] == 'F' || token[0][0] == 'C')
			control = process_line(line, scene);
		else if (token[0][0] == '1' || token[0][0] == ' ')
		{
			if (scene->control != 9)
			{
				printf("Error\nNot enough parameters before map\n");
				return (FAIL);
			}
			//printf("?%s\n", line);
			while (get_next_line(fd, &line))
			{
				if (token[0][0] == '1' || token[0][0] == ' ')
					count = count;
				else
				{
					printf("Error\nError in line: ");
					control = FAIL;
					break;
				}
			}
			return (SUCCESS);
		}
		else
		{
			printf("Error\nError in line: ");
			control = FAIL;
		}
		count += control? 1 : 0;
	}
	free(line);
	close(fd);
	if (control == FAIL)
		printf("%d\n", count);
	return (control);
}

int	main(int argc, char *argv[])
{
	t_scene scene = {0};

	if (argc == 2)
	{
		if (check_name(argv[1]) && check_existence(argv[1]))
			process_file(argv[1], &scene);
		//printf("%s\n", scene.sprite);
		//printf("%d\n", scene.res_width);
		//printf("%d\n", scene.res_height);
	}
	else
	{
		printf("Error");
		return (1);
	}
	return (0);
}
