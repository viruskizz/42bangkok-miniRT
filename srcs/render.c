#include "minirt.h"

t_color	color_inter(t_data *data, t_ray camray, t_ints *ints);

int render_scene(t_data *data)
{
	t_ray	camray;
	t_ints	ints;
	// if (data->scene.img.ptr)
	// 	mlx_destroy_image(data->mlx, data->scene.img.ptr);
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
			if (x == data->w / 2.0 + 100 && y == data->h / 2.0 + 100)
			{
				printf("x = %d / %f, %f\n", x, data->w / 2.0, cox);
				printf("y = %d / %f, %f\n", y, data->h / 2.0, coy);
			}
			if (x == data->w / 2.0 - 100 && y == data->h / 2.0 - 100)
			{
				printf("x = %d / %f, %f\n", x, data->w / 2.0, cox);
				printf("y = %d / %f, %f\n", y, data->h / 2.0, coy);
			}
			camray = cam_ray(data->cam, cox, coy);
			t_list *obj;
			t_list *tmp;

			obj = data->objs;
			tmp = obj;
			int inter = 0;
			int color = rgb_to_int(0, 0, 0);
			while (tmp)
			{
				if (tmp->content)
				{
					t_obj *o = (t_obj *)tmp->content;
					if (o->type == SPHERE)
						sphere_inter(o, camray, &ints);
					if (ints.valid)
					{
						// t_color c = color_inter(data, camray, &ints);
						// printf("(%d,%d) c: %d,%d,%d\n", x, y, c.r, c.g, c.b);
						color = color_to_int(color_inter(data, camray, &ints));
					}
					else
					{
						// color = rgb_to_int(0, 0, 0);
						// color = rgb_to_int(0, 255, 0);
					}
					// printf("%d,%d = %d\n", x, y, 0xFF00);
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
