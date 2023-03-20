/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:57:35 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/18 18:42:17 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_colorf	scene_pixel_img(t_data *data, float cox, float coy);
static t_colorf	lht_ints(t_data *data, t_ray camray, t_ints *ints);
static void		camray_ints(t_data *data, t_ray camray, t_ints *ints);
static void		set_obj_ints(t_ints *ints, t_ints oints);

int	render_scene(t_data *data)
{
	int			y;
	int			x;
	t_colorf	colorf;

	y = 0;
	while (y < data->scene.size.h)
	{
		x = 0;
		while (x < data->scene.size.w)
		{
			colorf = scene_pixel_img(
					data,
					(x / data->scene.pos.x) - 1.0,
					(y / data->scene.pos.y) - 1.0);
			pixel_put_img(&data->scene.img, x, y, colorf_to_int(colorf));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->scene.img.ptr, 0, 0);
	return (0);
}

static t_colorf	scene_pixel_img(t_data *data, float cox, float coy)
{
	t_ray		camray;
	t_ints		ints;
	t_colorf	colorf;

	camray = cam_ray(data->cam, cox, coy);
	colorf = color_to_colorf(data->amb.color);
	ints.valid = 0;
	camray_ints(data, camray, &ints);
	if (ints.valid)
		colorf = lht_ints(data, camray, &ints);
	return (colorf);
}

static t_colorf	lht_ints(t_data *data, t_ray camray, t_ints *ints)
{
	t_colorf	colorf;
	t_colorf	colorfl;
	t_list		*light;

	light = data->lht;
	colorf = color_to_colorf(rgb_to_color(0, 0, 0));
	while (light)
	{
		lht_illuminated(*((t_obj *)(light->content)), ints, data->objs);
		if (ints->valid)
		{
			colorf.r += ints->illum.r * ints->illum.alpha;
			colorf.g += ints->illum.g * ints->illum.alpha;
			colorf.b += ints->illum.b * ints->illum.alpha;
		}
		light = light->next;
	}
	if (ints->valid)
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
	oints.valid = 0;
	while (objs)
	{
		if (objs->content)
		{
			obj = (t_obj *)objs->content;
			obj_ints(obj, camray, &oints);
			if (oints.valid)
			{
				oints.t = vtrmag(vtrsub(oints.p, camray.a));
				ints->valid = 1;
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
