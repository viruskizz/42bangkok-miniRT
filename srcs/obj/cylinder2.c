/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:51:17 by araiva            #+#    #+#             */
/*   Updated: 2023/03/22 04:59:41 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
#include "minirt.h"

static int		cy_ints_pt(t_ints *intss, t_ints *ints);
static t_ints	*cy_ints_bd(t_ray bvray, t_vtr vray, t_fml fml, t_ints *intss);
static t_ints	*cy_ints_tp(t_ray bvray, t_vtr vray, t_ints *intss);

int	cylinder_ints_formula(t_ray bvray, t_vtr vray, t_ints *ints)
{
	t_fml	fml;
	t_ints	*intss;
	int		idx;

	fml.a = powf(vray.x, 2.0) + powf(vray.z, 2.0);
	fml.b = 2.0 * (bvray.a.x * vray.x + bvray.a.z * vray.z);
	fml.c = powf(bvray.a.x, 2.0) + powf(bvray.a.z, 2.0) - 1.0;
	fml.result = sqrtf(powf(fml.b, 2.0) - 4.0 * fml.a * fml.c);
	intss = ft_calloc(sizeof(t_ints), 4);
	intss = cy_ints_bd(bvray, vray, fml, intss);
	intss = cy_ints_tp(bvray, vray, intss);
	ints->hit = 0;
	if (!intss[0].hit && !intss[1].hit
		&& !intss[2].hit && !intss[3].hit)
		return (free(intss), -1);
	idx = cy_ints_pt(intss, ints);
	return (free(intss), idx);
}

static t_ints	*cy_ints_bd(t_ray bvray, t_vtr vray, t_fml fml, t_ints *intss)
{
	intss[0].hit = 0;
	intss[1].hit = 0;
	intss[0].t = 100e6;
	intss[1].t = 100e6;
	if (fml.result > 0.0)
	{
		intss[0].t = (-fml.b + fml.result) / (2.0 * fml.a);
		intss[1].t = (-fml.b - fml.result) / (2.0 * fml.a);
		intss[0].p = vtradd(bvray.a, vtrscale(vray, intss[0].t));
		intss[1].p = vtradd(bvray.a, vtrscale(vray, intss[1].t));
		if ((intss[0].t > 0.0) && (fabsf(intss[0].p.y) < 1.0))
			intss[0].hit = 1;
		else
			intss[0].t = 100e6;
		if ((intss[1].t > 0.0) && (fabsf(intss[1].p.y) < 1.0))
			intss[1].hit = 1;
		else
			intss[1].t = 100e6;
	}
	return (intss);
}

static t_ints	*cy_ints_tp(t_ray bvray, t_vtr vray, t_ints *intss)
{
	intss[2].hit = 0;
	intss[3].hit = 0;
	intss[2].t = 100e6;
	intss[3].t = 100e6;
	if (!close0(vray.y, 0.0))
	{
		intss[2].t = (bvray.a.y + 1.0) / -vray.y;
		intss[3].t = (bvray.a.y - 1.0) / -vray.y;
		intss[2].p = vtradd(bvray.a, vtrscale(vray, intss[2].t));
		intss[3].p = vtradd(bvray.a, vtrscale(vray, intss[3].t));
		if ((intss[2].t > 0.0)
			&& (sqrtf(powf(intss[2].p.x, 2.0) + powf(intss[2].p.z, 2.0)) < 1.0))
			intss[2].hit = 1;
		else
			intss[2].t = 100e6;
		if ((intss[3].t > 0.0)
			&& (sqrtf(powf(intss[3].p.x, 2.0) + powf(intss[3].p.z, 2.0)) < 1.0))
			intss[3].hit = 1;
		else
			intss[3].t = 100e6;
	}
	return (intss);
}

static int	cy_ints_pt(t_ints *intss, t_ints *ints)
{
	float	val;
	int		i;
	int		idx;

	val = 10e6;
	i = -1;
	idx = 0;
	while (++i < 4)
	{
		if (intss[i].t < val)
		{
			val = intss[i].t;
			idx = i;
		}
	}
	ints->p = intss[idx].p;
	return (idx);
}
