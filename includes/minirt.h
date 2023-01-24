#ifndef MINIRT_H
#define MINIRT_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
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

/* reading size */
# define	READ_SIZE 10

// typedef struct s_vtr
// {
// 	float	x;
// 	float	y;
// 	float	z;
// }	t_vtr;

// typedef struct s_obj {
// 	int		type;
// 	char	*name;
// 	t_vtr	pos;
// }	t_obj;

// typedef struct s_data
// {
// 	void	*mlx;
// 	void	*win;
// 	int		w;
// 	int		h;
// 	int		frame;
// 	t_list	*obj;
// }	t_data;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

// * parsing structure //

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_ambient
{
	double	ratio;	//* range[0.0-1.0];
	int32_t	colour; //* range[0-255];
}	t_amb;

typedef struct s_camara
{
	t_vec	coordinate;
	t_vec	normalized;	// * range[-1-1];
	int		fov; 		//* horizountal field view in degree range[0-180];
} 	t_cam;

typedef struct s_light
{
	t_vec	coordinate;
	double	birghtness; //* range[0.0-1.0];
	int32_t	colour;
}	t_lht;

typedef struct s_sphere
{
	t_vec	coordinate;
	double	sp_diameter;
	int32_t	colour;
}	t_sp;

typedef struct s_plane
{
	t_vec	coordinate;
	t_vec	normalized; // * range[-1.1]
	int32_t	colour;
}	t_pl;

typedef struct s_cylinder
{
	t_vec	coordinate;
	t_vec	normalized;
	double	diameter;
	double	hight;
	int32_t	colour;
}	t_cy;

typedef struct s_object
{
	int		identify; //* [sp, pl, cy];
	void	*attribute;
}	t_obj;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_amb	amb;
	t_cam	cam;
	t_lht	lht;
	t_list	*obj;
}	t_data;

int rt_close(t_data *data, int code);
int	error_exit(t_data *data, int code);

int rt_setup(t_data *data, char *filename);

// * parsing_intput
t_data	*parsing_input(int argc, char **argv);

// render
void	render_objects(t_data *data);

// Debug
void	print_obj(t_obj *obj);

#endif
