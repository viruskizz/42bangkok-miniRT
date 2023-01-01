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

typedef struct s_vtr
{
	float	x;
	float	y;
	float	z;
}	t_vtr;

typedef struct s_obj {
	int		type;
	char	*name;
	t_vtr	pos;
}	t_obj;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		w;
	int		h;
	int		frame;
	t_list	*obj;
}	t_data;

int rt_close(t_data *data, int code);
int	error_exit(t_data *data, int code);

int rt_setup(t_data *data, char *filename);

// render
void	render_objects(t_data *data);

// Debug
void	print_obj(t_obj *obj);

#endif
