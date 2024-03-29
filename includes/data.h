/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 03:15:26 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/26 05:46:29 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "libft.h"

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
# define TRANSF_VALUE 0.1
# define RESIZE_VALUE 0.05
# define ROTATE_VALUE HALF_PI / 4

# define COL	0
# define ROW	1
# define X		0
# define Y		1
# define Z		2

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
	float	w;
	float	h;
	float	d;
}	t_size;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	float	intens;
}	t_color;

typedef struct s_colorf
{
	float	r;
	float	g;
	float	b;
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
	float	ratio;
	t_color	color;
}	t_amb;

typedef struct s_camara
{
	t_vtr	pos;
	t_vtr	norm;
	int		fov;
	t_vtr	lookat;
	t_vtr	up;
	float	length;
	float	horz;
	float	ratio;
	t_vtr	proj_c;
	t_vtr	proj_u;
	t_vtr	proj_v;
}	t_cam;

typedef struct s_lht
{
	t_vtr		pos;
	float		bright;
	t_color		color;
	t_colorf	colorf;
}	t_lht;

typedef struct s_texture
{
	int		has;
	float	**mtrans;
	t_img	img;
}	t_txtr;

typedef struct s_material
{
	float	shin;
	float	reflc;
}	t_mat;

typedef struct s_obj
{
	int			idx;
	int			type;
	char		*name;
	float		bright;
	float		**mtrans;
	float		**itrans;
	t_vtr		pos;
	t_vtr		norm;
	t_vtr		n_radian;
	t_color		color;
	t_colorf	colorf;
	t_size		size;
	t_mat		mat;
	t_img		img;
	char		*texture;
	t_txtr		txtr;
}	t_obj;

typedef struct s_ints
{
	t_ray		camray;
	int			hit;
	float		t;
	t_obj		*obj;
	t_vtr		p;
	t_vtr		localn;
	t_color		localc;
	t_colorf	illum;
	t_vtr		uvz;
}	t_ints;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	int				w;
	int				h;
	int				update;
	int				ctrl_key;
	int				lshift_key;
	int				rshift_key;
	int				selectp;
	int				check[2];
	int				selectv[4];
	t_obj			scene;
	t_amb			amb;
	t_cam			cam;
	t_list			*lht;
	t_list			*objs;
	pthread_mutex_t	mutex;
}	t_data;

#endif
