/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <rcamilo-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 23:14:23 by camilo            #+#    #+#             */
/*   Updated: 2021/02/25 19:58:52 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

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

