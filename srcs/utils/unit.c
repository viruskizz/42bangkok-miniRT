#include "minirt.h"

t_color	set_color(int r, int g, int b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_size set_size(double w, double h, double d)
{
	t_size	size;

	size.w = w;
	size.h = h;
	size.d = d;
	return (size);
}
