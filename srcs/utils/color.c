#include "minirt.h"

t_color	rgb_to_color(int r, int g, int b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.intens = 1.0;
	if (c.r > COLORF_MAX)
		c.r = COLORF_MAX;
	if (c.g > COLORF_MAX)
		c.g = COLORF_MAX;
	if (c.b > COLORF_MAX)
		c.b = COLORF_MAX;
	return (c);
}

t_color	colorf_to_color(t_colorf cf)
{
	t_color	c;

	c.r = cf.r * COLOR_MAX;
	c.g = cf.g * COLOR_MAX;
	c.b = cf.b * COLOR_MAX;
	return (c);
}

t_colorf color_to_colorf(t_color color)
{
	t_colorf cf;

	cf.r = color.r / COLOR_MAX;
	cf.g = color.g / COLOR_MAX;
	cf.b = color.b / COLOR_MAX;
	return (cf);
}

t_colorf colorf_add(t_colorf cf1, t_colorf cf2)
{
	t_colorf cfr;

	cfr.r = cf1.r + cf2.r;
	cfr.g = cf1.g + cf2.g;
	cfr.b = cf1.b + cf2.b;
	return (cfr);
}

t_colorf	color_complied_alpha(t_colorf cf)
{
	t_colorf cfr;

	cfr.r = cfr.r * cfr.alpha;
	cfr.g = cfr.g * cfr.alpha;
	cfr.b = cfr.b * cfr.alpha;
	return (cfr);
}
