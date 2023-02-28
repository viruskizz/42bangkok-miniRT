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
	t_ints	ints;
	if (data->scene.img.ptr)
		mlx_destroy_image(data->mlx, data->scene.img.ptr);
	float y;
	float x;
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
			if (x == data->w / 2.0 + 100 && y == data->h / 2.0 + 100)
			{
				printf("x = %f / %f, %f\n", x, data->w / 2.0, cox);
				printf("y = %f / %f, %f\n", y, data->h / 2.0, coy);
			}
			if (x == data->w / 2.0 - 100 && y == data->h / 2.0 - 100)
			{
				printf("x = %f / %f, %f\n", x, data->w / 2.0, cox);
				printf("y = %f / %f, %f\n", y, data->h / 2.0, coy);
			}
			camray = cam_ray(data->cam, cox, coy);
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
						color = color_to_int(color_inter(data, camray, &ints));
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
