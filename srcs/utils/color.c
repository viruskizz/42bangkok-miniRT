/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:13:22 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/10 00:13:22 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_colorf	colorf_set(float r, float g, float b)
{
	t_colorf	cf;

	cf.r = r;
	cf.g = g;
	cf.b = b;
	return (cf);
}

t_colorf	color_to_colorf(t_color color)
{
	t_colorf	cf;

	cf.r = color.r / COLOR_MAX;
	cf.g = color.g / COLOR_MAX;
	cf.b = color.b / COLOR_MAX;
	return (cf);
}

t_colorf	colorf_add(t_colorf c1, t_colorf c2)
{
	t_colorf	cf;

	cf.r = c1.r + c2.r;
	cf.g = c1.g + c2.g;
	cf.b = c1.b + c2.b;
	return (cf);
}
