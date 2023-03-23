/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:57:35 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/22 05:05:44 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_colorf	scene_pixel_img(t_data *data, float cox, float coy);
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
