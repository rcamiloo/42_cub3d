#include <stdio.h>
#include <fcntl.h>
#include "../libft/libft.h"

#define SUCESS 1
#define FAIL 0

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

}				t_scene;

int	create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int check_name(char *s)
{
	int size;
	char *check;

	check = NULL;
	size = ft_strlen(s);
	if (size > 4)
		check = ft_strnstr((s + size - 4), ".cub", size);
	if (check == NULL)
		printf("Error\nDescription: Wrong file extension\n");
	return (check == NULL ? FAIL : SUCESS);
}

int check_existence(char *s)
{
	int fd;
	fd = open(s, O_RDONLY);
	if (fd >= 0)
		close(fd);
	else
		perror("Error\nDescription");
	return (fd == -1 ? FAIL : SUCESS);
}

int vector_size(char **vector)
{
	int i;

	if (vector == NULL)
		return(0);
	i = 0;
	while (vector[i] != NULL)
		i++;
	return (i);
}

int process_colors(char **token, t_scene *scene)
{
	char **rgb;
	int r;
	int g;
	int b;

	rgb = ft_split(token[1], ',');
	r = atoi(rgb[0]);
	g = atoi(rgb[1]);
	b = atoi(rgb[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return FAIL;
	if (!ft_strncmp(token[0], "C\0", 2) && !scene->color_ceiling)
		scene->color_ceiling = create_trgb(0, r, g, b);
	else if (!ft_strncmp(token[0], "F\0", 2) && !scene->color_floor)
		scene->color_floor = create_trgb(0, r, g, b);
	else
		return(FAIL);
	return (SUCESS);
}

int process_texture(char **token, t_scene *scene)
{

	if (check_existence(token[1]) == FAIL)
		return (FAIL);
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
		return(FAIL);
	return (SUCESS);
}

int process_resolution(char **token, t_scene *scene)
{

	if (!scene->res_height && !scene->res_width)
	{
		scene->res_width = ft_atoi(token[1]);
		scene->res_height = ft_atoi(token[2]);
	}
	else
		return(FAIL);
	return (SUCESS);
}

int process_line (char *line, t_scene *scene)
{
	char **token;
	int i;
	int size;

	token = ft_split(line, ' ');
	size = vector_size(token);

	if((!ft_strncmp(token[0], "NO\0", 3) || !ft_strncmp(token[0], "SO\0", 3)
	|| !ft_strncmp(token[0], "WE\0", 3) || !ft_strncmp(token[0], "EA\0", 3)
	|| !ft_strncmp(token[0], "S\0", 2)) && size == 2)
		process_texture(token, scene);
	else if((!ft_strncmp(token[0], "F\0", 2) || !ft_strncmp(token[0], "C\0", 2)) && size == 2)
		process_colors(token, scene);
	else if(!ft_strncmp(token[0], "R\0", 2) && size == 3)
		process_resolution(token, scene);
	else
		printf("FAIL\n");
	return (SUCESS);
}

int process_file (char *file, t_scene *scene)
{
	int fd;
	char *line;

	fd = open(file, O_RDONLY);

	while(get_next_line(fd, &line))
		if(line[0] == 'R' || line[0] == 'N' || line[0] == 'S' || line[0] == 'W'
			|| line[0] == 'E' || line[0] == 'F' || line[0] == 'C')
			process_line(line, scene);
		else if (line[0] == '\0')
			line[0] = '\0';
		else if(line[0] == '1' || line[0] == ' ')
		{
			printf("?%s\n", line);
		 	while(get_next_line(fd, &line))
			{
				if(line[0] == '1' || line[0] == ' ')
					printf("??%s\n", line);
				else
					return (FAIL);
			}
			return (SUCESS);
		}
		else
			return (FAIL);
	close(fd);
	return (SUCESS);
}





int main (int argc, char *argv[])
{
	int fd;
	char *linha;
	char buf[2];
	int exists;
	t_scene scene = {0};

	exists = 0;

	if (argc == 2)
	{
		//printf("Ok\n");
		//printf("%s, %zu\n", argv[1], ft_strlen(argv[1]));
		//printf("tem .cub? %d\n", check_name(argv[1]));
		//printf("existe: %d\n", check_existence(argv[1]));
		if (check_name(argv[1]) && check_existence(argv[1]))
			process_file(argv[1], &scene);

		printf("%s\n", scene.sprite);
		printf("%d\n", scene.res_width);
		printf("%d\n", scene.res_height);
	}
	else
	{
		printf("Error");
		return (1);
	}
	return (0);
}
