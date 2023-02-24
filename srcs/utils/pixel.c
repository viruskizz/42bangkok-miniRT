#include "minirt.h"

int	rgb_to_int(int r, int g, int b)
{
	// return ((r & 0xff) << 16 | (g & 0xff) << 8 | (b & 0xff));
	return (r << 16 | g << 8 | b);
}

void	pixel_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->lh + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}
