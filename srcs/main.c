
#include "mlx.h"
#include <math.h>
#include <stdio.h>

void line(void *mlx, void *win, int x, int y, int size)
{
	int i;

	i = 0;
	while (i < size){
		mlx_pixel_put(mlx, win, x + i, y, 0255255255);
		i++;
	}

}

void 	square(void *mlx, void *window, int x, int y, int size)
{
	int i;

	i= 0;
	while (i <= size)
	{
		mlx_pixel_put(mlx, window, x + i, y, 0777777777);
		mlx_pixel_put(mlx, window, x, y + i, 0777777777);
		mlx_pixel_put(mlx, window, x + size, y + i, 0777777777);
		mlx_pixel_put(mlx, window, x + i, y + size, 0777777777);
		i++;
	}

}


void 	filled_square(void *mlx, void *window, int x, int y, int size)
{
	int i;

	i= 0;
	while (i <= size)
	{
		line(mlx, window, x, y + i , size);
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

void 	draw_map(void *mlx, void *window, int map[5][5], int tile_size, int nr_tiles){
	int i;
	int j;
	int x;
	int y;

	i = 0;
	while (i < nr_tiles)
	{
		j = 0;
		while (j < nr_tiles)
		{
			x = j * tile_size;
			y = i * tile_size;
			if (map[i][j] == 1)
				{
				printf("a");
				filled_square(mlx, window, x, y, tile_size);
				}
			else
			{
				printf("b");
				square(mlx, window, x, y, tile_size);

			}
			j++;
		}
		i++;
	}

}




int main(){
	void *mlx_ptr;
	void *win_ptr;
	int map[5][5] = {
		{1, 1, 1, 1, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1},
		{1, 1, 1, 1, 1}
	};






	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
	//mlx_string_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF, "Rodrigo");
	//line(mlx_ptr, win_ptr, 260, 260, 30);
	//square(mlx_ptr, win_ptr, 260, 270, 30);
	//circle(mlx_ptr, win_ptr, 250, 250, 30);
	//filled_square(mlx_ptr, win_ptr, 260, 270, 30);
	draw_map(mlx_ptr, win_ptr, map, 100, 5);

	mlx_loop(mlx_ptr);

}
