/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 01:32:23 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/09 03:34:12 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	set_color(int r, int g, int b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_size	set_size(float w, float h, float d)
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
