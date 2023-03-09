#ifndef MINIRT_H
#define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
// # include <mlx.h>
# include "mlx.h"
# include <float.h>
# include <math.h>
# include "libft.h"
# include "key.h"
# include "error.h"
# include "data.h"
# include "utils.h"
# include "trans.h"

int	rt_close(t_data *data, int code);
int	error_exit(t_data *data, int code);

int rt_setup(t_data *data, char *filename);

// * parsing_intput
t_data	parsing_input(int argc, char **argv);
void	ambient_initialise(t_data *data, char **object);
t_obj	*object_initialise(int type);
void	plane_initialise(t_data *data, char **object);
void	cylinder_inititialize(t_data *data, char **object);

// * render
void	render_objects(t_data *data);
int 	render_scene(t_data *data);

// * camera
void	cam_initialise(t_data *data, char **object);
void	cam_geometry(t_cam *cam);
t_ray	cam_ray(t_cam cam, float proj_x, float proj_y);

// * light
void	lht_initialise(t_data* data, char **object);
void	lht_illuminated(t_lht lht, t_ints *ints, t_list *objs);

// * obj
void	set_objs(t_data *data);
t_obj	*new_obj(t_data *data);
void	obj_ints(t_obj *obj, t_ray ray, t_ints *ints);
void	free_obj(t_obj *obj);
void	scene_initialise(t_data *data);
void	sphere_initialise(t_data *data, char **object);
void	sphere_ints(t_obj *obj, t_ray ray, t_ints *ints);
t_obj	*set_plane_img(t_data *data, t_obj *obj);
void	plane_ints(t_obj *obj, t_ray ray, t_ints *ints);

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
