#include "minirt.h"

t_color	color_inter(t_data *data, t_ray camray, t_ints *ints);

int render_scene(t_data *data)
{
	t_ray	camray;
	t_vtr	ivtr;
	t_vtr	local_normal;
	t_vtr	local_color;
	t_ints	ints;
	t_color	color;
	// if (data->scene.img.ptr)
	// 	mlx_destroy_image(data->mlx, data->scene.img.ptr);
	float y;
	float x;
	float cw = data->w / 2.0;
	float ch = data->h / 2.0;
	float cox;
	float coy;
	float ratio = data->w / (float) data->h;
	t_vtr	coord;
	t_obj	sphere;
	y = 0;
	while (y < data->h)
	{
		x = 0;
		while (x < data->w)
		{
			// coord = vtrset(x / data->w, y / data->h, 0);
			cox = (x / cw) - 1.0;
			coy = 1.0 - (y / ch);
			cox *= ratio;
			coord = vtrset(cox, coy, 0.0);
			camray.a = vtrset(0, 0, 2);
			camray.b = vtrset(coord.x, coord.y, -1);
			sphere.pos = vtrset(0, 0, 0);
			// color = set_color(ints.p.x * 255.0, ints.p.y * 255.0, 0);
			sphere_ints(sphere, camray, &ints);
			pixel_put_img(&data->scene.img, x, y, color_to_int(ints.illum));
			x++;
		}
		y++;
	}
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
