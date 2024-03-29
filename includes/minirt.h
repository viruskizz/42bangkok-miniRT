/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 03:22:07 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/26 08:40:50 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
// # include <mlx.h>
# include "../mlx/mlx.h"
# include "../mlx_Linux/mlx.h"
# include <float.h>
# include <math.h>
# include "libft.h"
# include "key.h"
# include "error.h"
# include "data.h"
# include "utils.h"

int			rt_close(t_data *data, int code);
int			error_exit(t_data *data, int code);

// * interface
int			window_interface(t_data *data, int mode);

// * parsing_intput
t_data		parsing_input(int argc, char **argv);
void		ambient_initialise(t_data *data, char **object);
t_obj		*object_initialise(int type);
void		plane_initialise(t_data *data, char **object, int idx);
void		cylinder_inititialize(t_data *data, char **object, int idx);
int			validate_code(char **object, int index);
int			validate_file(char *file);
void		bonus_argument(
				t_obj *object, char *trimed_obj, int *check, char *err);

// * render
int			render_scene(t_data *data);

// * camera
void		cam_initialise(t_data *data, char **object);
void		cam_geometry(t_cam *cam);
t_ray		cam_ray(t_cam cam, float proj_x, float proj_y);

// * light
void		lht_initialise(t_data *data, char **object, int idx);
t_colorf	diffuse_light(t_obj lht, t_ints *ints, t_list *objs);
t_colorf	specular_light(t_obj lht, t_ints *ints, t_list *objs);
void		lht_inst_objs(
				t_ray lray, t_ints *linst, t_ints *ints, t_list *objs);

// materials
t_colorf	material_color(t_data *data, t_ints *ints);
t_colorf	diffuse_color(t_data *data, t_ints *ints);
t_colorf	specular_color(t_data *data, t_ints *ints);
t_vtr		txtr_vtr(t_vtr vtr, float **mtrans);
float		**txtr_mtx_trans(t_vtr trans, float rot, t_vtr scale);
t_colorf	txtr_checker_colorf(t_vtr uvz, float **mtrans);
t_img		txtr_checker_test(t_data *data);

t_vtr		txtr_vtr(t_vtr vtr, float **mtrans);
float		**txtr_mtx_trans(t_vtr trans, float rot, t_vtr scale);
t_colorf	txtr_checker_colorf(t_vtr uvz, float **mtrans);
t_img		txtr_checker_test(t_data *data);

// * obj
void		set_objs(t_data *data);
t_obj		*new_obj(void);
void		obj_ints(t_obj *obj, t_ray ray, t_ints *ints);
void		free_obj(t_obj *obj);
void		scene_initialise(t_data *data);
void		sphere_initialise(t_data *data, char **object, int idx);
void		sphere_ints(t_obj *obj, t_ray ray, t_ints *ints);
t_obj		*set_plane_img(t_data *data, t_obj *obj);
void		plane_ints(t_obj *obj, t_ray ray, t_ints *ints);

void		cylinder_ints(t_obj *obj, t_ray ray, t_ints *ints);
int			cylinder_ints_formula(t_ray bvray, t_vtr vray, t_ints *ints);

void		cone_inititialize(t_data *data, char **object, int idx);
void		cone_ints(t_obj *obj, t_ray ray, t_ints *ints);
int			cone_ints_formula(t_ray bvray, t_vtr vray, t_ints *ints);

// tran
float		**trans_homo(t_vtr trans, t_vtr rotate, t_vtr scale);
void		trans_rot_xyz(t_vtr rotate, float ***result);
t_vtr		trans_vtr(t_vtr v, float **mtxtrans);
t_ray		trans_ray(t_ray ray, float **mtxtrans);
t_vtr		trans_norm_vtr_rot(t_vtr norm);

#endif
