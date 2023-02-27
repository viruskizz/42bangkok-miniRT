#include "minirt.h"

void	put_obj_img_to_win(t_data *data, t_obj *obj);

// void	put_obj_img_to_win(t_data *data, t_obj *obj)
// {
// 	if (obj->img.ptr)
// 		mlx_put_image_to_window(data->mlx, data->win, obj->img.ptr, obj->pos.x, obj->pos.y);
// }
// t_color	color_inter(t_ray camray, t_vtr ivtr);
t_color	color_inter(t_data *data, t_ray camray, t_ints *ints);

int render_scene(t_data *data)
{
	t_ray	camray;
	t_vtr	ivtr;
	t_vtr	local_normal;
	t_vtr	local_color;
	t_ints	ints;
	double x_fact = 1.0 / ((double)data->w / 2.0);
	double y_fact = 1.0 / ((double)data->h / 2.0);
	if (data->scene.img.ptr)
		mlx_destroy_image(data->mlx, data->scene.img.ptr);
	double y;
	double x;
	y = 0;
	while (y < data->h)
	{
		x = 0;
		while (x < data->w)
		{
			// normalize the x and y coordinates
			// printf("fact: %f, %f\n", x_fact, y_fact);
			double norm_x = (x * x_fact) - 1.0;
			double norm_y = 1.0 - (y * y_fact);
			// double norm_y = (y * y_fact) - 1.0;
			if (x == data->w / 2.0 + 100 && y == data->h / 2.0 + 100)
			{
				printf("x = %f, %f\n", x, norm_x);
				printf("y = %f, %f\n", y, norm_y);
			}
			if (x == data->w / 2.0 - 100 && y == data->h / 2.0 - 100)
			{
				printf("x = %f, %f\n", x, norm_x);
				printf("y = %f, %f\n", y, norm_y);
			}
			camray = cam_ray(data->cam, norm_x, norm_y);
			t_list *obj;
			t_list *tmp;

			obj = data->objs;
			tmp = obj;
			int inter = 0;
			while (tmp)
			{
				if (tmp->content)
				{
					t_obj *o = (t_obj *)tmp->content;
					if (o->type == SPHERE)
						sphere_inter(camray, &ints);
					int color;
					if (ints.valid)
					{
						// double d = vtrmag(vtrsub(ivtr, camray.a));
						// if (d > maxd)
						// 	maxd = d;
						// if (d < mind)
						// 	mind = d;
						// int r = 255.0 - ((d - 9.0) / 0.94605 * 255.0);
						// color = rgb_to_int(r, 0, 0);
						color = color_to_int(color_inter(data, camray, &ints));
						// if (x == 720 && y == 390)
						// {
						// 	printf("center: %d, %d\n", data->w / 2, data->h / 2);
						// 	printf("x,y: %f, %f\n", x, y);
						// 	printf("norm: %f, %f\n", norm_x, norm_y);
						// 	printf("localn: %f, %f, %f\n", ints.localn.x, ints.localn.y, ints.localn.z);
						// 	printf("ints: %f, %f, %f\n", ints.p.x, ints.p.y, ints.p.z);
						// 	printf("intensity: %f\n", ints.illum.intens);
						// 	printf("u: %f, %f\n", data->cam.proj_u.x, data->cam.proj_u.y);
						// 	printf("v: %f, %f\n", data->cam.proj_v.x, data->cam.proj_v.y);
						// 	mlx_put_image_to_window(data->mlx, data->win, data->scene.img.ptr, 0, 0);
						// 	return 0;
						// }
					}
					else
					{
						color = rgb_to_int(0, 0, 0);
					}
					pixel_put_img(&data->scene.img, x, y, color);
				}
				tmp = tmp->next;
			}
			x++;
		}
		y++;
	}
	// printf("min/max = %f/%f\n", mind, maxd);
	mlx_put_image_to_window(data->mlx, data->win, data->scene.img.ptr, 0, 0);
	return (0);
}

void	render_objects(t_data *data)
{
	t_list *obj;
	t_list *tmp;

	obj = data->objs;
	tmp = obj;
	while (tmp)
	{
		if (tmp->content)
		{

		}
		// put_obj_img_to_win(data, tmp->content);
		tmp = tmp->next;
	}
}

t_color	color_inter(t_data *data, t_ray camray, t_ints *ints)
{
	t_color color;
	t_list	*lht;
	t_lht	*light;

	lht = data->lht;
	while (lht)
	{
		light = (t_lht *) lht->content;
		lht_illuminated(*light, ints);
		lht = lht->next;
	}
	// double d = vtrmag(vtrsub(ints.p, camray.a));
	double d = vtrmag(vtrsub(camray.a, ints->p));
	// color.r = 255.0 - ((d - 9.0) / 0.94605 * 255.0);
	// printf("intens: %f\n", ints->illum.intens);
	color.r = 255.0 * ints->illum.intens;
	color.g = 0;
	color.b = 0;
	// printf("camray_a: %f, %f, %f\n", camray.a.x, camray.a.y, camray.a.z);
	// printf("camray_b: %f, %f, %f\n", camray.b.x, camray.b.y, camray.b.z);
	return (color);
}
