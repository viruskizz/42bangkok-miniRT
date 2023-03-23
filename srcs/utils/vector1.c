/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:11:52 by araiva            #+#    #+#             */
/*   Updated: 2023/03/10 00:12:32 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vtr	vtradd(t_vtr a, t_vtr b)
{
	return (vtrset(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vtr	vtrsub(t_vtr a, t_vtr b)
{
	return (vtrset(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vtr	vtrscale(t_vtr v, float s)
{
	return (vtrset(v.x * s, v.y * s, v.z * s));
}

float	vtrdot(t_vtr a, t_vtr b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vtr	vtrcross(t_vtr a, t_vtr b)
{
	t_vtr	crs;

	crs.x = a.y * b.z - a.z * b.y;
	crs.y = - (a.x * b.z - a.z * b.x);
	crs.z = a.x * b.y - a.y * b.x;
	return (crs);
}
