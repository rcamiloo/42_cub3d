#include "../include/scene.h"

int		process_line(int fd, char **line, t_scene *scene)
{
	char	*temp;
	char	**token;
	int		control;

	control = FAIL;
	temp = ft_sanitize(*line, "\t");
	free(line);
	*line = temp;
	token = ft_split(line, ' ');
	if (token[0] == '\0')
		control = SUCCESS;
	else if (ft_strrchr("RNSWEFC", token[0][0]))
		control = process_config(&line, scene);
	else if (ft_strrchr("1 ", token[0][0]))
	{
		if (!(control = (scene->control != 9)))
			printf("Error\nNot enough parameters before map\n");
		else if (!(control = process_map(fd, line, &scene->map)))
			printf("Error\nError in map");
	}
	else
		printf("Error\nError after map");
	free_matrix(token);
	return (control);
}

int		process_file(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	int		control;
	int		gnl;
	char	*next_line;

	control = SUCCESS;
	fd = open(file, O_RDONLY);
	while (control && ((gnl = get_next_line(fd, &line, &next_line)) >= 0))
	{
		control = process_line(fd, &line, scene);
		ft_free(&line);
		if (!gnl)
		{
			next_line = NULL;
			break ;
		}
	}
	ft_free(&next_line);
	ft_free(&line);
	close(fd);
	if (!scene->map.player_face)
		printf("Error\n");
	return (control);
}



int		process_file(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	int		count;
	int		control;
	char	**token;
	int		gnl;
	char	*late_free;
	char	*temp;

	fd = open(file, O_RDONLY);
	count = 0;
	control = 1;
	temp = NULL;
	line = NULL;
	late_free = NULL;
	while (control && ((gnl = get_next_line(fd, &line, &late_free)) >= 0))
	{
		temp = ft_sanitize(line, "\t");
		free(line);
		line = temp;
		token = ft_split(line, ' ');
		if (token[0] == '\0')
		{
			control = 1;
			late_free = NULL;
		}
		else if (token[0][0] == 'R' || token[0][0] == 'N'
			|| token[0][0] == 'S' || token[0][0] == 'W' || token[0][0] == 'E'
			|| token[0][0] == 'F' || token[0][0] == 'C')
			control = process_line(&line, scene);
		else if (token[0][0] == '1' || token[0][0] == ' ')
		{
			if (scene->control != 9)
			{
				printf("Error\nNot enough parameters before map\n");
				free_matrix(token);
				ft_free(&line);
				ft_free(&late_free);
				close(fd);
				return (FAIL);
			}
			else if ((control = process_map(fd, line, &scene->map)))
			{
				count += control;
				control = FAIL;
				late_free = NULL;
				line = NULL;
				printf("Error\nError in line: ");
			}
			else
			{
				control = SUCCESS;
				line = NULL;
			}
		}
		else
		{
			printf("Error\nError in line: ");
			control = FAIL;
		}
		count += control ? 1 : 0;
		free_matrix(token);
		token = NULL;
		ft_free(&line);
		if (!gnl)
		{
			ft_free(&line);
			late_free = NULL;
			break ;
		}
	}
	ft_free(&late_free);
	ft_free(&line);
	close(fd);
	if (!scene->map.player_face)
		printf("Error\n");
	if (control == FAIL)
		printf("%d\n", count);
	return (control);
}
