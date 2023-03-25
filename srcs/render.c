/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:57:35 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/26 00:28:31 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_colorf	scene_pixel_img(t_data *data, float cox, float coy);
static void		camray_ints(t_data *data, t_ray camray, t_ints *ints);
static void		set_obj_ints(t_ints *ints, t_ints oints);
static void		*function_render(void *input);
void			init_window_value(int *start_x, int *y, int *height, int *width);

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
	{
		c[COL] = start_x;
		while (c[COL] < width)
		{
			colorf = scene_pixel_img(
					(t_data *)input,
					(c[COL] / ((t_data *)input)->scene.pos.x) - 1.0,
					(c[ROW] / ((t_data *)input)->scene.pos.y) - 1.0);
			pixel_put_img(&((t_data *)input)->scene.img, c[COL],
					c[ROW], colorf_to_int(colorf));
			c[COL]++;
		}
		c[ROW]++;
	}
	return (0);
}

static t_colorf	scene_pixel_img(t_data *data, float cox, float coy)
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
