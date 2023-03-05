#include "minirt.h"

t_color	color_inter(t_data *data, t_ray camray, t_ints *ints);

int render_scene(t_data *data)
{
	t_ray	camray;
	t_ints	ints;

	int y;
	int x;
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
	double d = vtrmag(vtrsub(camray.a, ints->p));
	color.r = ints->localc.r * ints->illum.intens;
	color.g = ints->localc.g * ints->illum.intens;
	color.b = ints->localc.b * ints->illum.intens;
	return (color);
}
