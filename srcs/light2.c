/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 04:11:43 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/26 04:49:32 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	specular_light_alpha(t_ints *ints, t_ray lray);

t_colorf	diffuse_light(t_obj lht, t_ints *ints, t_list *objs)
{
	t_vtr	lvtr;
	t_ray	lray;
	t_ints	lints;
	float	angle;

	lvtr = vtrnorm(vtrsub(lht.pos, ints->p));
	lray = set_ray(ints->p, vtradd(ints->p, lvtr));
	lht_inst_objs(lray, &lints, ints, objs);
	ints->illum.alpha = 0.0;
	if (!lints.hit)
	{
		angle = acos(vtrdot(ints->localn, lvtr));
		if (angle <= HALF_PI)
		{
			ints->hit = 1;
			ints->illum.alpha = lht.bright * (1.0 - (angle / HALF_PI));
		}
	}
	return (colorf_set(
			lht.colorf.r * ints->illum.alpha,
			lht.colorf.g * ints->illum.alpha,
			lht.colorf.b * ints->illum.alpha));
}

t_colorf	specular_light(t_obj lht, t_ints *ints, t_list *objs)
{
	t_vtr		lvtr;
	t_ray		lray;
	t_ints		lints;
	float		alpha;
	t_colorf	cf;

	alpha = 0.0;
	lvtr = vtrnorm(vtrsub(lht.pos, ints->p));
	lray = set_ray(ints->p, vtradd(ints->p, vtrscale(lvtr, 0.001)));
	lht_inst_objs(lray, &lints, ints, objs);
	if (!lints.hit)
	{
		alpha = specular_light_alpha(ints, lray);
	}
	cf.r = lht.colorf.r * alpha;
	cf.g = lht.colorf.g * alpha;
	cf.b = lht.colorf.b * alpha;
	return (cf);
}

static float	specular_light_alpha(t_ints *ints, t_ray lray)
{
	t_vtr	r;
	t_vtr	v;
	float	dot;

	r = vtrnorm(vtrsub(lray.l,
				vtrscale(ints->localn, vtrdot(lray.l, ints->localn) * 2)));
	v = vtrnorm(ints->camray.l);
	dot = vtrdot(r, v);
	if (dot > 0.0)
		return (ints->obj->mat.reflc * pow(dot, ints->obj->mat.shin));
	return (0.0);
}

void	lht_inst_objs(t_ray lray, t_ints *lints, t_ints *ints, t_list *objs)
{
	t_list	*obj;
	t_obj	*o;

	obj = objs;
	lints->hit = 0;
	while (obj)
	{
		o = (t_obj *) obj->content;
		if (o != ints->obj)
			obj_ints(o, lray, lints);
		if (lints->hit)
			return ;
		obj = obj->next;
	}
}
