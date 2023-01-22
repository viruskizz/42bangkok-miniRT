#include "minirt.h"

int	rgb(int r, int g, int b)
{
	return ((r & 0xff) << 16 | (g & 0xff) << 8 | (b & 0xff));
}

void	pixel_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->lh + x * (img->bpp / 8));
	// printf("%s\n", dst);
	*(unsigned int*)dst = rgb(128, 128, 128);
	// *(unsigned int*)dst = color;
	// *dst = color;
	// printf(">> %s\n", dst);
	// mlx_put_image_to_window(data->mlx, data->win, data->img->img, 5, 5);
}
