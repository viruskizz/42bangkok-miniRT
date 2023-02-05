#ifndef MINIRT_H
#define MINIRT_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <mlx.h>
# include <float.h>
# include <math.h> 
# include "libft.h"
# include "key.h"
# include "minirt_error.h"

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

# define PLANE	1
# define PLAN	1
# define SPHERE	2
# define CYLIND	3
# define C		3

# define WIDTH	1280
# define HEIGHT	720

# define READ_SIZE 1024

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
	double	mag;
}	t_vtr;

typedef struct s_ray
{
	t_vtr	a;
	t_vtr	b;
	t_vtr	l;
}	t_ray;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		lh;
	int		endian;
}	t_img;

typedef struct s_ambient
{
	double	ratio;	//* range[0.0-1.0];
	t_color	color;	//* range[0-255];
}	t_amb;

typedef struct s_camara
{
	t_vtr	pos;
	t_vtr	norm;	//* range[-1-1];
	int		fov;	//* horizountal field view in degree range[0-180];
} 	t_cam;

typedef struct s_light
{
	t_vtr	pos;
	double	bright; //* range[0.0-1.0];
	t_color	color;
}	t_lht;

typedef struct s_obj {
	int		idx;
	int		type;
	char	*name;
	t_vtr	pos;
	t_vtr	norm;
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
	t_amb	amb;
	t_cam	cam;
	t_list	*lht;
	t_list	*objs;
}	t_data;

int	rt_close(t_data *data, int code);
int	error_exit(t_data *data, int code);

int rt_setup(t_data *data, char *filename);

// * parsing_intput
t_data	parsing_input(int argc, char **argv);
void	ambient_initialise(t_data *data, char **object);
void	camara_initialise(t_data *data, char **object);
void	light_initialise(t_data* data, char **object);
void	sephere_initialise(t_data *data, char **object);
void	plane_initialise(t_data *data, char **object);
void	cylinder_inititialize(t_data *data, char **object);

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

t_vtr	vtrset(double x, double y, double z);
double	vtrmag(t_vtr v);
t_vtr	vtrnorm(t_vtr v);
t_vtr	vtradd(t_vtr a, t_vtr b);
t_vtr	vtrsub(t_vtr a, t_vtr b);
t_vtr	vtrscale(t_vtr v, double s);
double	vtrdot(t_vtr a, t_vtr b);
t_vtr	vtrcross(t_vtr a, t_vtr b);

t_ray	rayset(t_vtr a, t_vtr b);


// * utils from sharnvon..
void	exit_error(char *str);
void	free_twopointer_char(char **ptr);
char	*ft_strjoin_pro(char *str1, char *str2);
int		character_count(char *str, char c);
double	ato_double(char *str);
t_color	ato_tcolor(char *str);
t_vtr	ato_tvector(char *str);
int		tvector_inrange(t_vtr vactor, double min, double max);
t_size	size_initialise(double height, double width, double depth);


// * Debug
void	print_obj(t_obj *obj);
void	print_tdata(t_data *data);
void	print_twoarray_char(char **str);
void	print_tvector(t_vtr vector);
void	print_tobject(t_obj *object);
void	printf_tcamara(t_cam camara);
void	printf_tambient(t_amb ambient);
void	printf_tsize(t_size size);
void	print_tcolor(t_color color);

#endif
