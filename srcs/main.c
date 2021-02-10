
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int	create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}


void line(void *mlx, void *win, int x, int y, int size, int color)
{
	int i;

	i = 0;
	while (i < size){
		mlx_pixel_put(mlx, win, x + i, y, color);
		i++;
	}

}

void 	square(void *mlx, void *window, int x, int y, int size, int color)
{
	int i;

	i= 0;
	while (i <= size)
	{
		mlx_pixel_put(mlx, window, x + i, y, color);
		mlx_pixel_put(mlx, window, x, y + i, color);
		mlx_pixel_put(mlx, window, x + size, y + i, color);
		mlx_pixel_put(mlx, window, x + i, y + size, color);
		i++;
	}

}


void 	filled_square(void *mlx, void *window, int x, int y, int size, int color)
{
	int i;

	i= 0;
	while (i <= size)
	{
		line(mlx, window, x, y + i , size, color);
		i++;
	}

}



void	circle(void *mlx, void *window, int x, int y, int raio)
{
	float	ang;
	float	addang;
	int	new_x;
	int	new_y;

	ang = 0.0;
	addang = 0.001;
	// printf('%f', PI);
	while (ang < 2 * 3.14)
	{
		new_x = x + (raio * cos(ang));
		new_y = y + (raio * sin(ang));
		printf("%d, %d\n", new_x, new_y);
		mlx_pixel_put(mlx, window, new_x, new_y, 0777777777);
		ang += addang;
	}
}

void 	draw_map(void *mlx, void *window, int ytiles, int xtiles, int map[ytiles][xtiles], int tile_size){
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
				filled_square(mlx, window, x, y, tile_size, white);
			}
			else
			{
				square(mlx, window, x, y, tile_size, black);
			}
			j++;
		}
		i++;
	}

}

typedef struct Player{
	float x;
	float y;
	float size;
	int turnDirection;
	int walkDirection;
	float RotationAngle;
	float walkSpeed;
	float turnSpeed;
} player;

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

}



typedef struct  s_vars {
        void    *mlx;
        void    *win;
}               t_vars;



int close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	vars->win = NULL;
	exit(1);
	return (0);
}

int keypress(int keycode, t_vars *vars)
{
    if (keycode == 53 || keycode == 65307)
	{
		close(vars);
	}
	return (0);
}


int main(){
	player player;
	t_vars    vars;
	int red;
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


	red = create_trgb(0, 255, 0, 0);
	init_player(&player);



	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 500, "mlx 42");
	//mlx_string_put(mlx_ptr, win_ptr, 250, 250, red, "Rodrigo");
	//line(mlx_ptr, win_ptr, 260, 260, 30);
	//square(mlx_ptr, win_ptr, 260, 270, 30);
	//circle(mlx_ptr, win_ptr, 250, 250, 30);
	//filled_square(mlx_ptr, win_ptr, 260, 270, 30);
	draw_map(vars.mlx, vars.win, 14, 33, map, 20);

	printf("%f, %f", player.x, player.y);
	filled_square(vars.mlx, vars.win, player.x, player.y, player.size, red);


	mlx_hook(vars.win, 2, 1L<<0, keypress, &vars);
	mlx_hook(vars.win, 33, 1L<<17, close, &vars);

	mlx_loop(vars.mlx);

	// analisar memory leak no final
	//mlx_destroy_display(vars.mlx); 
	//free(vars.mlx);
	return (0);

}
