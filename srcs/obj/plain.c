#include "minirt.h"

void	plain_obj(t_data *data , int w, int h)
{
	t_img	*img;
	img = malloc(sizeof(t_img));
	img->img = mlx_new_image(data->mlx, w, h);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->lh, &img->endian);

	data->img = img;
	int x = 0;
	int y = 0;
	while (y < h)
	{
		x = 0;
		while(x < w)
		{
			pixel_put_img(img, x, y, 0x00FFFFFF);
			x++;
		}
		y++;
	}
}
