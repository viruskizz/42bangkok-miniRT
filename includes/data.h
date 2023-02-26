#ifndef DATA_H
#define DATA_H

#include "libft.h"

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
	double	intens;	// intensity [0.0 - 1.0]
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
	void	*ptr;
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
	t_vtr	lookat;
	t_vtr	up;
	double	length;
	double	horz;
	double	ratio;
	t_vtr	proj_c;	// norm_vector in projection center screen
	t_vtr	proj_u;	// norm_vector in projection screen u
	t_vtr	proj_v;	// norm_vector in projection screen v
} 	t_cam;

typedef struct s_lht
{
	t_vtr	pos;
	double	bright; //* range[0.0-1.0];
	t_color	color;	// normal color
}	t_lht;

typedef struct s_obj
{
	int		idx;
	int		type;
	char	*name;
	t_vtr	pos;
	t_vtr	norm;
	t_color	color;
	t_size	size;
	t_img	img;
}	t_obj;

typedef struct s_ints
{
	double	value;
	int		valid;
	t_vtr	p;
	t_vtr	localn;	// local normal in normalize vector
	t_color	illum;
}	t_ints;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		w;
	int		h;
	int		frame;
	t_obj	scene;
	t_amb	amb;
	t_cam	cam;
	t_list	*lht;
	t_list	*objs;
}	t_data;

#endif
