/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <rcamilo-@student.42sp.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:52:21 by rcamilo-          #+#    #+#             */
/*   Updated: 2021/02/20 18:07:08 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/cub3d.h"

int	main(void)
{
	t_vars	vars;

	init_player(&vars.player);
	vars.win_width = W_WIDTH;
	vars.win_height = W_HEIGHT;
	vars.update = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.win_width, vars.win_height, "Mini map");
	mlx_do_key_autorepeatoff(vars.mlx);
	vars.img.img = mlx_new_image(vars.mlx, vars.win_width, vars.win_height);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
									&vars.img.line_length, &vars.img.endian);
	mlx_hook(vars.win, 2, 1L << 0, key_press, &vars);
	mlx_hook(vars.win, 3, 1L << 1, key_release, &vars);
	mlx_hook(vars.win, 33, 1L << 17, close, &vars);
	mlx_loop_hook(vars.mlx, game, &vars);
	mlx_loop(vars.mlx);
	//analisar memory leak no final
	//mlx_destroy_display(vars.mlx);
	//free(vars.mlx);
	return (0);
}
