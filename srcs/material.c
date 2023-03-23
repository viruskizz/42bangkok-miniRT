/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiva <tsomsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 21:48:38 by araiva            #+#    #+#             */
/*   Updated: 2023/03/23 21:48:40 by araiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_colorf	specular_light(t_obj lht, t_ints *ints, t_list *objs);

t_colorf	material_color(t_data *data, t_ints *ints)
{
	t_colorf	difclr;
	t_colorf	spcclr;

	difclr = diffuse_color(data, ints);

	if (ints->obj->mat.shin > 0.0)
		spcclr = specular_color(data, ints);
	return (colorf_add(difclr, spcclr));
}

t_colorf	diffuse_color(t_data *data, t_ints *ints)
{
	t_colorf	colorf;
	t_colorf	colorfl;
	t_list		*light;

	light = data->lht;
	colorf = color_to_colorf(rgb_to_color(0, 0, 0));
	while (light)
	{
		lht_illuminated(*((t_obj *)(light->content)), ints, data->objs);
		if (ints->hit)
		{
			colorf.r += ints->illum.r * ints->illum.alpha;
			colorf.g += ints->illum.g * ints->illum.alpha;
			colorf.b += ints->illum.b * ints->illum.alpha;
		}
		light = light->next;
	}
	if (ints->hit)
	{
		colorfl = color_to_colorf(ints->localc);
		colorf.r = colorfl.r * colorf.r;
		colorf.g = colorfl.g * colorf.g;
		colorf.b = colorfl.b * colorf.b;
	}
	return (colorf);
}

t_colorf	specular_color(t_data *data, t_ints *ints)
{
	t_colorf	cf;
	t_colorf	spcclr;
	t_list		*light;

	light = data->lht;
	spcclr = color_to_colorf(rgb_to_color(0, 0,0 ));
	while (light)
	{
		cf = specular_light(*((t_obj *)(light->content)), ints, data->objs);
		spcclr = colorf_add(spcclr, cf);
		light = light->next;
	}
	return (spcclr);
}

static t_colorf	specular_light(t_obj lht, t_ints *ints, t_list *objs)
{
	t_vtr	lvtr;
	t_ray	lray;
	t_ints	lints;
	float	alpha;
	t_colorf	cf;

	alpha = 0.0;
	lvtr = vtrnorm(vtrsub(lht.pos, ints->p));
	lray = set_ray(ints->p, vtradd(ints->p, vtrscale(lvtr, 0.001)));
	lht_inst_objs(lray, &lints, ints, objs);
	if (!lints.hit)
	{
		t_vtr	d = lray.l;
		t_vtr	r = vtrscale(ints->localn, vtrdot(lray.l, ints->localn) * 2);
		r = vtrnorm(vtrsub(lray.l, r));
		t_vtr v = vtrnorm(ints->camray.l);
		// t_vtr v = vtrnorm(lray.l);
		float dot = vtrdot(r, v);
		
		if (dot > 0.0)
			alpha = ints->obj->mat.reflc * pow(dot, ints->obj->mat.shin);
	}
	cf.r = lht.colorf.r * alpha;
	cf.g = lht.colorf.g * alpha;
	cf.b = lht.colorf.b * alpha;
	return (cf);
}