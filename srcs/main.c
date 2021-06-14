/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <rcamilo-@student.42sp.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 23:14:23 by camilo            #+#    #+#             */
/*   Updated: 2021/03/26 20:51:45 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/cub3d.h"
#include "scene.h"

int	main(int argc, char *argv[])
{
	t_scene	scene = {0};
	t_vars	vars;

	if (argc == 2)
	{
		if (check_name(argv[1]) && check_existence(argv[1]))
			process_file(argv[1], &scene);
		init_player(&vars.player);
		vars.win_width = W_WIDTH;
		vars.win_height = W_HEIGHT;
		vars.update = 0;
		vars.mlx = mlx_init();
		vars.win = mlx_new_window(vars.mlx, vars.win_width,
				vars.win_height, "Mini map");
		mlx_do_key_autorepeatoff(vars.mlx);
		vars.img.img = mlx_new_image(vars.mlx, vars.win_width, vars.win_height);
		vars.img.addr = mlx_get_data_addr(vars.img.img,
				&vars.img.bits_per_pixel,
				&vars.img.line_length,
				&vars.img.endian);
		mlx_hook(vars.win, 2, 1L << 0, key_press, &vars);
		mlx_hook(vars.win, 3, 1L << 1, key_release, &vars);
		mlx_hook(vars.win, 33, 1L << 17, close, &vars);
		mlx_loop_hook(vars.mlx, game, &vars);
		mlx_loop(vars.mlx);
		//analisar memory leak no final
		//mlx_destroy_display(vars.mlx);
		//free(vars.mlx);
	}
	else
	{
		printf("Error");
		return (1);
	}
	return (0);
}
