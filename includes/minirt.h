#ifndef MINIRT_H
#define MINIRT_H

# include <stdio.h>
# include <mlx.h>
# include "libft.h"
# include "key.h"

# ifdef __linux__
#  define IS_LINUX 1
#  define OS "LINUX"
# else
#  define IS_LINUX 0
#  define OS "MAC"
# endif

# define ERROR_MLX	1
# define ERROR_WIN	2
# define FRAME_RATE	60

# define PLAN	1
# define SPHERE	2
# define C		3

# define WIDTH	1280
# define HEIGHT	720

typedef struct s_size
{
	double	w; // width
	double	h; // height
	double	d; // depth
}	t_size;

typedef struct s_color
{
	int	r;  // red
	int	g;  // green
	int	b;  // blue
}	t_color;

typedef struct s_vtr
{
	double	x;
	double	y;
	double	z;
}	t_vtr;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		lh;
	int		endian;
}	t_img;

typedef struct s_obj {
	int		idx;
	int		type;
	char	*name;
	t_vtr	pos;
	t_color	color;
	t_size	size;
	t_img	img;
}	t_obj;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		w;
	int		h;
	int		frame;
	t_list	*objs;
	t_img	*img;
}	t_data;

int	rt_close(t_data *data, int code);
int	error_exit(t_data *data, int code);

int rt_setup(t_data *data, char *filename);

// render
void	render_objects(t_data *data);

// obj
void	set_objs(t_data *data);
t_obj	*new_obj(t_data *data);
void	free_obj(t_obj *obj);

t_obj	*set_plain_img(t_data *data, t_obj *obj);

// utils
int		rgb_to_int(int r, int g, int b);
void	pixel_put_img(t_img *img, int x, int y, int color);
t_color	set_color(int r, int g, int b);
t_size	set_size(double w, double h, double d);
t_vtr	set_vector(double x, double y, double z);


// Debug
void	print_obj(t_obj *obj);

#endif
