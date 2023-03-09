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

t_ray	set_ray(t_vtr a, t_vtr b)
{
	t_ray	r;

	r.a = a;
	r.b = b;
	r.l = vtrsub(b, a);
	return (r);
}

int		close0(const float f1, const float f2)
{
	if (fabsf(f1 - f2) < FLT_EPSILON)
		return (1);
	else
		return (0);
}
