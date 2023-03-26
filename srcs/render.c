/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:57:35 by sharnvon          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/26 01:53:05 by sharnvon         ###   ########.fr       */
=======
/*   Updated: 2023/03/22 05:05:44 by sharnvon         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_colorf	scene_pixel_img(t_data *data, float cox, float coy);
<<<<<<< HEAD
static void		camray_ints(t_data *data, t_ray camray, t_ints *ints);
static void		set_obj_ints(t_ints *ints, t_ints oints);
static void		*function_render(void *input);
void			init_window_value(
					int *start_x, int *y, int *height, int *width);

int	render_scene(t_data *data)
{
	pthread_t	thread[16];
	int			count;

	pthread_mutex_init(&data->mutex, NULL);
	count = 0;
	while (count < 16)
		pthread_create(&thread[count++], NULL, &function_render, (void *)data);
	count = 0;
	while (count < 16)
		pthread_join(thread[count++], NULL);
	pthread_mutex_destroy(&data->mutex);
	mlx_put_image_to_window(data->mlx, data->win, data->scene.img.ptr, 0, 0);
	return (0);
}

static void	*function_render(void *input)
{
	int			c[2];
	int			width;
	int			height;
	int			start_x;
	t_colorf	colorf;

	pthread_mutex_lock(&((t_data *)input)->mutex);
	init_window_value(&start_x, &c[ROW], &height, &width);
	pthread_mutex_unlock(&((t_data *)input)->mutex);
	while (c[ROW] < height)
=======
static t_colorf	lht_ints(t_data *data, t_ints *ints);
static void		camray_ints(t_data *data, t_ray camray, t_ints *ints);
static void		set_obj_ints(t_ints *ints, t_ints oints);

int	render_scene(t_data *data)
{
	int			y;
	int			x;
	t_colorf	colorf;

	y = 0;
	while (y < data->scene.size.h)
>>>>>>> main
	{
		c[COL] = start_x;
		while (c[COL] < width)
		{
			colorf = scene_pixel_img(
<<<<<<< HEAD
					(t_data *)input,
					(c[COL] / ((t_data *)input)->scene.pos.x) - 1.0,
					(c[ROW] / ((t_data *)input)->scene.pos.y) - 1.0);
			pixel_put_img(&((t_data *)input)->scene.img, c[COL],
				c[ROW], colorf_to_int(colorf));
			c[COL]++;
=======
					data,
					(x / data->scene.pos.x) - 1.0,
					(y / data->scene.pos.y) - 1.0);
			pixel_put_img(&data->scene.img, x, y, colorf_to_int(colorf));
			x++;
>>>>>>> main
		}
		c[ROW]++;
	}
	return (0);
}

static t_colorf	scene_pixel_img(t_data *data, float cox, float coy)
<<<<<<< HEAD
{
	t_ray		camray;
	t_ints		ints;
	t_colorf	colorf;

	camray = cam_ray(data->cam, cox, coy);
	colorf = color_to_colorf(data->amb.color);
	ints.hit = 0;
	camray_ints(data, camray, &ints);
	if (ints.hit)
		colorf = material_color(data, &ints);
	return (colorf);
}

static void	camray_ints(t_data *data, t_ray camray, t_ints *ints)
{
	t_ints	oints;
	t_list	*objs;
	t_obj	*obj;

	objs = data->objs;
	ints->t = FLT_MAX;
	ints->camray = camray;
	oints.hit = 0;
	while (objs)
	{
		if (objs->content)
		{
			obj = (t_obj *)objs->content;
			obj_ints(obj, camray, &oints);
			if (oints.hit)
			{
				oints.t = vtrmag(vtrsub(oints.p, camray.a));
				ints->hit = 1;
				set_obj_ints(ints, oints);
			}
		}
		objs = objs->next;
	}
}

=======
{
	t_ray		camray;
	t_ints		ints;
	t_colorf	colorf;

	camray = cam_ray(data->cam, cox, coy);
	colorf = color_to_colorf(data->amb.color);
	ints.hit = 0;
	camray_ints(data, camray, &ints);
	if (ints.hit)
		colorf = lht_ints(data, &ints);
	return (colorf);
}

static t_colorf	lht_ints(t_data *data, t_ints *ints)
{
	t_colorf	colorf;
	t_colorf	colorfl;
	t_list		*light;

	light = data->lht;
	colorf = color_to_colorf(rgb_to_color(0, 0, 0));
	while (light)
	{
		lht_illuminated(*((t_obj *)(light->content)), ints, data->objs);
		if (ints->hit)
		{
			colorf.r += ints->illum.r * ints->illum.alpha;
			colorf.g += ints->illum.g * ints->illum.alpha;
			colorf.b += ints->illum.b * ints->illum.alpha;
		}
		light = light->next;
	}
	if (ints->hit)
	{
		colorfl = color_to_colorf(ints->localc);
		colorf.r = colorfl.r * colorf.r;
		colorf.g = colorfl.g * colorf.g;
		colorf.b = colorfl.b * colorf.b;
	}
	return (colorf);
}

static void	camray_ints(t_data *data, t_ray camray, t_ints *ints)
{
	t_ints	oints;
	t_list	*objs;
	t_obj	*obj;

	objs = data->objs;
	ints->t = FLT_MAX;
	oints.hit = 0;
	while (objs)
	{
		if (objs->content)
		{
			obj = (t_obj *)objs->content;
			obj_ints(obj, camray, &oints);
			if (oints.hit)
			{
				oints.t = vtrmag(vtrsub(oints.p, camray.a));
				ints->hit = 1;
				set_obj_ints(ints, oints);
			}
		}
		objs = objs->next;
	}
}

>>>>>>> main
static void	set_obj_ints(t_ints *ints, t_ints oints)
{
	if (oints.t < ints->t)
	{
		ints->t = oints.t;
		ints->obj = oints.obj;
		ints->p = oints.p;
		ints->localn = oints.localn;
		ints->localc = oints.localc;
	}
}
