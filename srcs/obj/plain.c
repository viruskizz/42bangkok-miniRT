#include "minirt.h"

t_obj	*set_plain_img(t_data *data, t_obj *obj)
{
	double	x;
	double	y;
	int		color;

	obj->img.img = mlx_new_image(data->mlx, obj->size.w, obj->size.h);
	obj->img.addr = mlx_get_data_addr(obj->img.img, &obj->img.bpp, &obj->img.lh, &obj->img.endian);
	y = 0;
	while (y < obj->size.h)
	{
		x = 0;
		while(x < obj->size.w)
		{
			color = rgb_to_int(obj->color.r, obj->color.g, obj->color.b);
			pixel_put_img(&obj->img, x, y, color);
			x++;
		}
		y++;
	}
	return (obj);
}
