#include "minirt.h"

int	color_to_int(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	pixel_put_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->lh + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}
