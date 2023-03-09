#include "minirt.h"

t_colorf	scene_pixel_img(t_data *data, float cox, float coy);
t_colorf	lht_ints(t_data *data, t_ray camray, t_ints *ints);
void		objs_ints(t_data *data, t_ray camray, t_ints *ints);

int render_scene(t_data *data)
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
				(y / data->scene.pos.y) - 1.0
			);
			pixel_put_img(&data->scene.img, x, y, colorf_to_int(colorf));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->scene.img.ptr, 0, 0);
	return (0);
}
t_colorf	scene_pixel_img(t_data *data, float cox, float coy)
{
	t_ray	camray;
	t_ints	ints;
	t_colorf	colorf;

	camray = cam_ray(data->cam, cox, coy);
	colorf = color_to_colorf(data->amb.color);
	ints.valid = 0;
	objs_ints(data, camray, &ints);
	if (ints.valid)
		colorf = lht_ints(data, camray, &ints);
	return (colorf);
}

t_colorf	lht_ints(t_data *data, t_ray camray, t_ints *ints)
{
	t_colorf colorf;
	t_color color;
	t_list	*lht;
	t_lht	*light;

	lht = data->lht;
	colorf = color_to_colorf(rgb_to_color(0, 0, 0));
	while (lht)
	{
		light = (t_lht *) lht->content;
		lht_illuminated(*light, ints);
		colorf = colorf_add(colorf, color_complied_alpha(ints->illum));
		lht = lht->next;
	}
	double d = vtrmag(vtrsub(camray.a, ints->p));
	// ints->illum
	color.r = ints->localc.r * ints->illum.alpha;
	color.g = ints->localc.g * ints->illum.alpha;
	color.b = ints->localc.b * ints->illum.alpha;
	colorf = color_to_colorf(color);
	return (colorf);
}

void	objs_ints(t_data *data, t_ray camray, t_ints *ints)
{
	t_ints	oints;
	t_list	*obj;

	obj = data->objs;
	ints->dist = MAXFLOAT;
	oints.valid = 0;
	while (obj)
	{
		if (obj->content)
		{
			t_obj *o = (t_obj *)obj->content;
			if (o->type == SPHERE)
				sphere_inter(o, camray, &oints);
			else if (o->type == PLANE)
				plane_ints(o, camray, &oints);
			if (oints.valid)
			{
				oints.dist = vtrmag(vtrsub(oints.p, camray.a));
				ints->valid = 1;
				if (oints.dist < ints->dist)
				{
					ints->dist = oints.dist;
					ints->obj = o;
					ints->p = oints.p;
					ints->localn = oints.localn;
					ints->localc = oints.localc;
				}
			}
		}
		obj = obj->next;
	}
}
