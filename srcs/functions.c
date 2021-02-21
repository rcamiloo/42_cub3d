/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <rcamilo-@student.42sp.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:03:23 by rcamilo-          #+#    #+#             */
/*   Updated: 2021/02/20 18:43:23 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

// void init_map (t_map *map)
// {
// int matrix[14][33] = {
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,2,0,0,0,0,0,1},
// 		{1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
// 		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1},
// 		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,0,1,0,0,0,1,1,1,1,1},
// 		{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1},
// 		{1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,0,1,0,0,0,1,1,1,1,1},
// 		{1,1,0,0,0,0,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,0,0,1,1,1,1,1},
// 		{1,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,0,1,0,0,0,1,1,1,1,1},
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// 	};

// 	map->map = matrix;
// 	map->x = 14;
// 	map->y = 33;
// }

void	init_player(t_player *player)
{
	player->x = 9 * TILE_SIZE;
	player->y = 5 * TILE_SIZE;
	player->size = 10;
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = (M_PI/2);
	player->walk_speed = 1;
	player->turn_speed = 2 * (M_PI/180);
	player->color = create_trgb(0, 255, 0, 0);
}

void	draw_px(t_img *data, int x, int y, int color)
{
    char    *dst;

	if (x <= W_WIDTH && x >= 0 && y <= W_HEIGHT && y >= 0)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    	*(unsigned int*)dst = color;
	}
}


void	draw_line(t_img *data, int start_x, int start_y, int end_x, int end_y, int color)
{
	int dx;
	int dy;
	int calc_y;
	int calc_x;

	dx = end_x - start_x;
	dy = end_y - start_y;

	if (dx > 0)
	{
		calc_x = start_x;
		while (calc_x <= end_x)
		{
			calc_y = (int)floor(start_y + (dy/dx) * (calc_x - start_x));
			draw_px(data, calc_x, calc_y, color);
			calc_x++;
		}
	}
	else if (dx < 0)
	{
	calc_x = start_x;
		while (calc_x >= end_x)
		{
			calc_y = (int)floor(start_y + (dy/dx) * (calc_x - start_x));
			draw_px(data, calc_x, calc_y, color);
			calc_x--;
		}
	}
	else{
		int add = dy < 0 ? +1 : -1;
		while (dy != 0)
		{
			draw_px(data, start_x, start_y, color);
			start_y += add;
			dy += add;
		}
		if (dy == 0)
			draw_px(data, start_x, start_y, color);
	}
}

void	filled_square(t_img *data, int x, int y, int size, int color)
{
	int i;

	i= 0;
	while (i <= size)
	{
		draw_line(data, x, y + i , x + size, y + i, color);
		i++;
	}
}

void 	draw_map(t_img *img, int ytiles, int xtiles, int map[ytiles][xtiles]){
	int i;
	int j;
	int x;
	int y;
	int black;
	int white;

	black = create_trgb(0, 0, 0, 0);
	white = create_trgb(0, 255, 255, 255);

	i = 0;
	while (i < ytiles)
	{
		j = 0;
		while (j < xtiles)
		{
			x = j * TILE_SIZE;
			y = i * TILE_SIZE;
			if (map[i][j] == 1)
				filled_square(img, x, y, TILE_SIZE, white);
			else
				filled_square(img, x, y, TILE_SIZE, black);
			j++;
		}
		i++;
	}

}

int	close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	vars->win = NULL;
	exit(1);
	return (0);
}

int	key_press(int keycode, t_vars *vars)
{
    if (keycode == 65307)
		close(vars);
    if (keycode == 65362)
		vars->player.walk_direction = 1;
    if (keycode == 65364)
		vars->player.walk_direction = -1;
	if (keycode == 65363)
		vars->player.turn_direction = 1;
    if (keycode == 65361)
		vars->player.turn_direction = -1;
	vars->update =  1;
	return (0);
}

int	key_release(int keycode, t_vars *vars)
{
    if (keycode == 65362)
		vars->player.walk_direction = 0;
    if (keycode == 65364)
		vars->player.walk_direction = 0;
	if (keycode == 65363)
		vars->player.turn_direction = 0;
    if (keycode == 65361)
		vars->player.turn_direction = 0;
	vars->update =  1;
	return (0);
}

int	render_player(t_vars *vars)
{
	int playerX;
	int playerY;

	playerX = vars->player.x;
	playerY = vars->player.y;
	filled_square(&vars->img, playerX, playerY,
	vars->player.size, vars->player.color);
	draw_line(&vars->img,
					playerX ,
					playerY ,
					playerX + cos(vars->player.rotation_angle) * 50,
					playerY + sin(vars->player.rotation_angle) * 50,
					vars->player.color);
	draw_line(&vars->img,
					playerX + 1,
					playerY + 1,
					playerX + 1 + cos(vars->player.rotation_angle) * 50,
					playerY + 1 + sin(vars->player.rotation_angle) * 50,
					vars->player.color);
	return(0);
}

int	is_wall(float x, float y, t_vars *vars)
{
	int grid_x;
	int grid_y;
	int matrix[14][33] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,2,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,0,1,0,0,0,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1},
		{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,0,1,0,0,0,1,1,1,1,1},
		{1,1,0,0,0,0,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,0,0,1,1,1,1,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,0,1,0,0,0,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	if (x > W_WIDTH && x < 0 && y > W_HEIGHT && y < 0)
		return (1);
	grid_x = (int)floor(x / TILE_SIZE);
	grid_y = (int)floor(y / TILE_SIZE);

	return (matrix[grid_y][grid_x] == 1);
}

int	render(t_vars *vars)
{
	int map[14][33] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,2,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,0,1,0,0,0,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1},
		{1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,0,1,0,0,0,1,1,1,1,1},
		{1,1,0,0,0,0,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,0,0,1,1,1,1,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,0,1,0,0,0,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};

	draw_map(&vars->img, MAP_ROWS, MAP_COLS, map);
	render_player(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int	move_player(t_vars *vars)
{
	float move_step;
	float newX;
	float newY;

	vars->player.rotation_angle += vars->player.turn_direction * vars->player.turn_speed;
	move_step = vars->player.walk_direction * vars->player.walk_speed;
	newX = vars->player.x +  cos(vars->player.rotation_angle) * move_step;
	newY = vars->player.y +  sin(vars->player.rotation_angle) * move_step;

	if (!(is_wall(newX, newY, vars)))
	{
		vars->player.x = newX;
		vars->player.y = newY;
	}
	return(0);
}

int	update(t_vars *vars)
{
	move_player(vars);
	return (0);
}

int	game(t_vars *vars)
{
	if (vars->update)
	{
		update(vars);
	}
	render(vars);
	return (0);
}
