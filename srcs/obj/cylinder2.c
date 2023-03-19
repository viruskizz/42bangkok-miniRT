/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_ints.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiva <tsomsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:51:17 by araiva            #+#    #+#             */
/*   Updated: 2023/03/19 23:51:19 by araiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
#include "minirt.h"

t_fml	cylinder_ints_formula(t_ray bvray, t_vtr vray)
{
	t_fml	fml;

	fml.a = powf(vray.x, 2.0) + powf(vray.z, 2.0);
	fml.b = 2.0 * (bvray.a.x * vray.x + bvray.a.z * vray.z);
	fml.c = powf(bvray.a.x, 2.0) + powf(bvray.a.z, 2.0) - 1.0;
	fml.result = sqrtf(powf(fml.b, 2.0) - 4.0 * fml.a * fml.c);
	return (fml);
}

t_ints	*cylinder_ints_core(t_ray bvray, t_vtr vray, t_fml fml, t_ints *intss)
{
	intss[0].valid = 0;
	intss[1].valid = 0;
	intss[0].dist = 100e6;
	intss[1].dist = 100e6;
	if (fml.result > 0.0)
	{
		intss[0].dist = (-fml.b + fml.result) / (2.0 * fml.a);
		intss[1].dist = (-fml.b - fml.result) / (2.0 * fml.a);
		intss[0].p = vtradd(bvray.a, vtrscale(vray, intss[0].dist));
		intss[1].p = vtradd(bvray.a, vtrscale(vray, intss[1].dist));
		if ((intss[0].dist > 0.0) && (fabsf(intss[0].p.y) < 1.0))
			intss[0].valid = 1;
		else
			intss[0].dist = 100e6;
		if ((intss[1].dist > 0.0) && (fabsf(intss[1].p.y) < 1.0))
			intss[1].valid = 1;
		else
			intss[1].dist = 100e6;
	}
	return (intss);
}

t_ints	*cylinder_ints_cap(t_ray bvray, t_vtr vray, t_fml fml, t_ints *intss)
{
	intss[2].valid = 0;
	intss[3].valid = 0;
	intss[2].dist = 100e6;
	intss[3].dist = 100e6;
	if (!close0(vray.y, 0.0))
	{
		intss[2].dist = (bvray.a.y + 1.0) / -vray.y;
		intss[3].dist = (bvray.a.y - 1.0) / -vray.y;
		intss[2].p = vtradd(bvray.a, vtrscale(vray, intss[2].dist));
		intss[3].p = vtradd(bvray.a, vtrscale(vray, intss[3].dist));
		if ((intss[2].dist > 0.0)
			&& (sqrtf(powf(intss[2].p.x, 2.0) + powf(intss[2].p.z, 2.0)) < 1.0))
			intss[2].valid = 1;
		else
			intss[2].dist = 100e6;
		if ((intss[3].dist > 0.0)
			&& (sqrtf(powf(intss[3].p.x, 2.0) + powf(intss[3].p.z, 2.0)) < 1.0))
			intss[3].valid = 1;
		else
			intss[3].dist = 100e6;
	}
	return (intss);
}

int	cylinder_ints_point(t_ints *intss, t_ints *ints)
{
	float	val;
	int		i;
	int		idx;

	val = 10e6;
	i = -1;
	idx = 0;
	while (++i < 4)
	{
		if (intss[i].dist < val)
		{
			val = intss[i].dist;
			idx = i;
		}
	}
	ints->p = intss[idx].p;
	return (idx);
}

int	cylinder_ints_set(t_obj *obj, t_ints *ints)
{
	obj->pos = trans_vtr(vtrset(0, 0, 0), obj->mtrans);
	ints->valid = 1;
	ints->p = trans_vtr(ints->p, obj->mtrans);
	ints->localn = vtrnorm(vtrsub(trans_vtr(obj->norm, obj->mtrans), obj->pos));
	ints->localc = obj->color;
	ints->illum.alpha = 1.0;
}
