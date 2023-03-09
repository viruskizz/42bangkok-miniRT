#include "minirt.h"

static t_colorf	scene_pixel_img(t_data *data, float cox, float coy);
static t_colorf	lht_ints(t_data *data, t_ray camray, t_ints *ints);
static void		objs_ints(t_data *data, t_ray camray, t_ints *ints);

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
static t_colorf	scene_pixel_img(t_data *data, float cox, float coy)
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

static t_colorf	lht_ints(t_data *data, t_ray camray, t_ints *ints)
{
	t_colorf colorf;
	t_colorf colorfl;
	t_color color;
	t_list	*lht;
	t_lht	*light;

	lht = data->lht;
	colorf = color_to_colorf(rgb_to_color(0, 0, 0));
	while (lht)
	{
		light = (t_lht *) lht->content;
		lht_illuminated(*light, ints, data->objs);
		if (ints->valid)
		{
			colorf.r += ints->illum.r * ints->illum.alpha;
			colorf.g += ints->illum.g * ints->illum.alpha;
			colorf.b += ints->illum.b * ints->illum.alpha;
		}
		lht = lht->next;
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

static void	objs_ints(t_data *data, t_ray camray, t_ints *ints)
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
				sphere_ints(o, camray, &oints);
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
