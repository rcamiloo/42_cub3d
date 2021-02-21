
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void            draw_px(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


void line(t_data *data, int x, int y, int size, int color)
{
	int i;

	i = 0;
	while (i < size)
	{
		draw_px(data, x + i, y, color);
		i++;
	}
}

void draw_line(t_data *data, int start_x, int start_y, int end_x, int end_y, int color)
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

void 	filled_square(t_data *data, int x, int y, int size, int color)
{
	int i;

	i= 0;
	while (i <= size)
	{
		draw_line(data, x, y + i , x + size, y + i, color);
		i++;
	}
}


int             main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 800, 600, "Hello world!");
    img.img = mlx_new_image(mlx, 800, 600);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    draw_px(&img, 400, 300, 0x00FFFFFF);
	line(&img, 200, 200, 50, 0x00FFFFFF);
	draw_line(&img, 300, 300, 300, 300, 0x00FFFFFF);
	filled_square(&img, 100, 100, 50, 0x00FF0000);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}
