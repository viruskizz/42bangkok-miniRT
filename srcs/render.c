/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 00:29:22 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/09 03:23:29 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color		color_inter(t_data *data, t_ray camray, t_ints *ints);
static void	draw_objects(t_data *data, t_ray camray, int x, int y);

/*
int render_scene(t_data *data)
{
	t_ray	camray;
	t_ints	ints;
	int		y;
	int 	x;

	y = 0;
	while (y < data->scene.size.h)
	{
		x = 0;
		while (x < data->scene.size.w)
		{
			// coordinate from center (left and down is negative)
			float cox = (x / data->scene.pos.x) - 1.0;
			float coy = (y / data->scene.pos.y) - 1.0;
			// float coy = 1.0 - (y / data->scene.pos.y);
			camray = cam_ray(data->cam, cox, coy);
			t_list *obj;
			t_list *tmp;
			obj = data->objs;
			tmp = obj;
			int color = rgb_to_int(0, 0, 0);
			while (tmp)
			{
				if (tmp->content)
				{
					t_obj *o = (t_obj *)tmp->content;
					if (o->type == SPHERE)
						sphere_inter(o, camray, &ints);
					else if (o->type == CYLIND)
						printf("CYLIND\n");
					else if (o->type == PLAN)
						print("Plane\n");
					else
						print("error ???\n");
					if (ints.valid)
					{
						// t_color c = color_inter(data, camray, &ints);
						color = color_to_int(color_inter(data, camray, &ints));
					}
					else
					{
						// color = rgb_to_int(0, 0, 0);
					}
					pixel_put_img(&data->scene.img, x, y, color);
				}
				tmp = tmp->next;
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->scene.img.ptr, 0, 0);
	return (0);
}
*/

/*
* [function drawing image onto window.]
*/
int	render_scene(t_data *data)
{
	t_ray	camray;
	int		y;
	int		x;

	y = 0;
	while (y < data->scene.size.h)
	{
		x = 0;
		while (x < data->scene.size.w)
		{
			// coordinate from center (left and down is negative)
			camray = cam_ray(data->cam,
					(float)(x / data->scene.pos.x) - 1.0,
					(float)(y / data->scene.pos.y) - 1.00);
			draw_objects(data, camray, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->scene.img.ptr, 0, 0);
	return (0);
}

/*
* [helper fucntion of render_scene]
* [check intersection of object and put pixel to image.]
*/
static void	draw_objects(t_data *data, t_ray camray, int x, int y)
{
	t_ints	ints;
	t_list	*objects;
	t_obj	*object;
	int		color;

	objects = data->objs;
	while (objects)
	{
		if (objects->content)
		{
			object = (t_obj *)objects->content;
			if (object->type == SPHERE)
				sphere_inter(object, camray, &ints);
			else if (object->type == CYLIND)
				printf("CYLIND\n");
			else if (object->type == PLANE)
				printf("Plane\n");
			else if (object->type == CONE)
				printf("Cone\n");
			if (ints.valid)
				color = color_to_int(color_inter(data, camray, &ints));
			pixel_put_img(&data->scene.img, x, y, color);
		}
		objects = objects->next;
	}
}

t_color	color_inter(t_data *data, t_ray camray, t_ints *ints)
{
	t_color	color;
	t_list	*lht;
	t_lht	*light;

	lht = data->lht;
	while (lht)
	{
		light = (t_lht *) lht->content;
		lht_illuminated(*light, ints);
		lht = lht->next;
	}
	// double d = vtrmag(vtrsub(camray.a, ints->p));
	color.r = ints->localc.r * ints->illum.intens;
	color.g = ints->localc.g * ints->illum.intens;
	color.b = ints->localc.b * ints->illum.intens;
	return (color);
}
