/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcamilo- <rcamilo-@student.42sp.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:53:14 by rcamilo-          #+#    #+#             */
/*   Updated: 2021/02/20 18:11:04 by rcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx_linux/mlx.h"
# include <math.h>
# include <stdlib.h>

# define TILE_SIZE 50
# define MAP_ROWS 14
# define MAP_COLS 33

# define W_WIDTH (MAP_COLS * TILE_SIZE)
# define W_HEIGHT (MAP_ROWS * TILE_SIZE)

# define M_PI 3.14159265358979323846

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_player{
	float	x;
	float	y;
	float	size;
	int		turn_direction;
	int		walk_direction;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
	int		color;
}				t_player;

typedef struct	s_map
{
	int **map;
	int x;
	int y;
}				t_map;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	t_player	player;
	int			update;
	t_img		img;
	t_map		map;
}				t_vars;

int				create_trgb(int t, int r, int g, int b);
int				close(t_vars *vars);
int				key_press(int keycode, t_vars *vars);
int				key_release(int keycode, t_vars *vars);
int				render_player(t_vars *vars);
int				is_wall(float x, float y, t_vars *vars);
int				render(t_vars *vars);
int				move_player(t_vars *vars);
int				update(t_vars *vars);
int				game(t_vars *vars);
void			init_player(t_player *player);
void			draw_px(t_img *data, int x, int y, int color);
void			draw_line(t_img *data, int start_x, int start_y, int end_x,
						int end_y, int color);
void			filled_square(t_img *data, int x, int y, int size, int color);
void			draw_map(t_img *img, int ytiles, int xtiles,
						int map[ytiles][xtiles]);

#endif
