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

# define LIGHT	0
# define SPHERE	1
# define PLANE	2
# define CYLIND	3
# define CONE	4
# define TRANS_FWD -1
# define TRANS_BCK 1

# define WIDTH		720
# define HEIGHT		480
// # define WIDTH		640
// # define HEIGHT		360
# define PANEL		150

# define HALF_PI	1.5708
# define PI			3.14159265359

# define READ_SIZE	1024
# define COLOR_MAX	255.0
# define COLORF_MAX	1.0
# define TRANSF_VALUE 0.25 //0.05 // 0.25; // 0.04;
# define RESIZE_VALUE 0.25 //0.05 // 0.25; //0.05;

# define COL	0
# define ROW	1

/* 
* define for object_cordition_str parameter mode. */
# define INDEX	0
# define TYPE	1

/* 
* define for window_interface parameter mode. */
# define NONE		0
# define INCREASE	1
# define DECREASE	2

typedef struct s_formula
{
	float	a;
	float	b;
	float	c;
	float	result;
}	t_fml;

typedef struct s_size
{
	float	w; // width
	float	h; // height
	float	d; // depth
}	t_size;

typedef struct s_color
{
	int	r;  // red
	int	g;  // green
	int	b;  // blue
	float	intens;	// intensity [0.0 - 1.0]
}	t_color;

// color between 0.0-1.0
typedef struct s_colorf
{
	float	r;  // red
	float	g;  // green
	float	b;  // blue
	float	alpha;
}	t_colorf;

typedef struct s_vtr
{
	float	x;
	float	y;
	float	z;
	float	mag;
}	t_vtr;

typedef struct s_point
{
	float	a;
	float	b;
	float	c;
}	t_pnt;

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
	float	ratio;	//* range[0.0-1.0];
	t_color	color;	//* range[0-255];
}	t_amb;

typedef struct s_camara
{
	t_vtr	pos;
	t_vtr	norm;	//* range[-1-1];
	int		fov;	//* horizountal field view in degree range[0-180];
	t_vtr	lookat;
	t_vtr	up;
	float	length;
	float	horz;
	float	ratio;
	t_vtr	proj_c;	// norm_vector in projection center screen
	t_vtr	proj_u;	// norm_vector in projection screen u
	t_vtr	proj_v;	// norm_vector in projection screen v
} 	t_cam;

typedef struct s_lht
{
	t_vtr		pos;
	float		bright; //* range[0.0-1.0];
	t_color		color;	// normal color
	t_colorf	colorf;
}	t_lht;

typedef struct s_obj
{
	int			idx;
	int			type;
	char		*name;
	float		bright; //* range[0.0-1.0];
	float		**mtrans;
	float		**itrans;
	t_vtr		pos;
	t_vtr		norm;
	t_color		color;
	t_colorf	colorf;
	t_size		size;
	t_img		img;
}	t_obj;

typedef struct s_ints
{
	float		value;
	int			valid;
	float		dist;
	t_obj		*obj;
	t_vtr		p;
	t_vtr		localn;	// local normal in normalize vector
	t_color		localc; // local color
	t_colorf	illum;
}	t_ints;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		w;
	int		h;
	int		update;
	int		ctrl_key;
	int		lshift_key;
	int		rshift_key;
	int		selectp;
	int		selectv[4];
	t_obj	scene;
	t_amb	amb;
	t_cam	cam;
	t_list	*lht;
	t_list	*objs;
}	t_data;

#endif
