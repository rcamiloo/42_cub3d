
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int	create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

typedef struct  s_img {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_img;

typedef struct Player{
	float x;
	float y;
	float size;
	int turnDirection;
	int walkDirection;
	float RotationAngle;
	float walkSpeed;
	float turnSpeed;
	int color;
} player;

typedef struct  s_vars {
        void    *mlx;
        void    *win;
		player player;
		int update;
		t_img img;
}               t_vars;

void            draw_px(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


void line(t_img *data, int x, int y, int size, int color)
{
	int i;

	i = 0;
	while (i < size)
	{
		draw_px(data, x + i, y, color);
		i++;
	}
}

void draw_line(t_img *data, int start_x, int start_y, int end_x, int end_y, int color)
{
	int dx;
	int dy;
	float calc_y;
	int calc_x;

	dx = end_x - start_x;
	dy = end_y - start_y;

	if (dx != 0)
	{
		calc_x = start_x;
		while (calc_x <= end_x)
		{
			calc_y = start_y + (dy/dx) * (calc_x - start_x);
			draw_px(data, calc_x, calc_y, color);
			calc_x++;
		}
	}else{
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

void 	filled_square(t_img *data, int x, int y, int size, int color)
{
	int i;

	i= 0;
	while (i <= size)
	{
		draw_line(data, x, y + i , x + size, y + i, color);
		i++;
	}
}


void 	draw_map(t_vars *vars, int ytiles, int xtiles, int map[ytiles][xtiles], int tile_size){
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
			x = j * tile_size;
			y = i * tile_size;
			if (map[i][j] == 1)
			{
				filled_square(&vars->img, x, y, tile_size, white);
			}
			else
			{
				filled_square(&vars->img, x, y, tile_size, black);
			}
			j++;
		}
		i++;
	}

}



void init_player(player *player)
{
	player->x = 50;
	player->y = 50;
	player->size = 5;
	player->turnDirection = 0;
	player->walkDirection = 0;
	player->RotationAngle = 3.14/2;
	player->walkSpeed = 10;
	player->turnSpeed = 45 * (3.14/2);
	player->color = create_trgb(0, 255, 0, 0);
}





int close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	vars->win = NULL;
	exit(1);
	return (0);
}

int keyPress(int keycode, t_vars *vars)
{
//	printf("press %d\n", keycode);
    if (keycode == 65307)
		close(vars);
    if (keycode == 65362)
		vars->player.walkDirection = 1;
    if (keycode == 65364)
		vars->player.walkDirection = -1;
	vars->update =  1;
	return (0);
}

int keyRelease(int keycode, t_vars *vars)
{
//	printf("release %d\n", keycode);
    if (keycode == 65362)
		vars->player.walkDirection = 0;
	if (keycode == 65364)
		vars->player.walkDirection = 0;
	vars->update =  1;
	return (0);
}



int movePlayer(t_vars *vars)
{
	float newX = vars->player.x + vars->player.walkDirection * 5;
	float newY = vars->player.y + vars->player.walkDirection * 5;

//	if (newX > 50)
//		printf("%f\n", newX);
	vars->player.x = newX;
	vars->player.y = newY;

	return(0);
}

int render(t_vars *vars)
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
	draw_map(vars, 14, 33, map, 20);
	//render_map
	//renderPlayer
	renderPlayer(vars);
	int i = 0;
	return (0);

}

int update(t_vars *vars)
{
	movePlayer(vars);
//	if (vars->player.x > 50)
//		printf("%f\n", vars->player.x);
	return (0);

}

int game(t_vars *vars)
{
	//process_input (keypress keyrelease)
	if (vars->update)
	{
		update (vars);
		render(vars);
	}
	return (0);
}


int main(){

	t_vars    vars;



	init_player(&vars.player);
	vars.update = 0;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 500, "mlx 42");
	vars.img.img = mlx_new_image(vars.mlx, 800, 600);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
                                 &vars.img.endian);

	//mlx_string_put(mlx_ptr, win_ptr, 250, 250, red, "Rodrigo");
	//line(mlx_ptr, win_ptr, 260, 260, 30);
	//square(mlx_ptr, win_ptr, 260, 270, 30);
	//circle(mlx_ptr, win_ptr, 250, 250, 30);
	//filled_square(mlx_ptr, win_ptr, 260, 270, 30);

	//draw_map(vars.mlx, vars.win, 14, 33, map, 20);

	mlx_hook(vars.win, 2, 1L<<0, keyPress, &vars);
	mlx_hook(vars.win, 3, 1L<<1, keyRelease, &vars);
	mlx_hook(vars.win, 33, 1L<<17, close, &vars);
	mlx_loop_hook(vars.mlx, game, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_loop(vars.mlx);

	// analisar memory leak no final
	//mlx_destroy_display(vars.mlx);
	//free(vars.mlx);
	return (0);

}
