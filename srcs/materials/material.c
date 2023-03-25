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

t_colorf	material_color(t_data *data, t_ints *ints)
{
	t_colorf	difclr;
	t_colorf	spcclr;

	difclr = diffuse_color(data, ints);
	spcclr = color_to_colorf(rgb_to_color(0, 0, 0));
	if (ints->obj->mat.shin > 0.0)
		spcclr = specular_color(data, ints);
	return (colorf_add(difclr, spcclr));
}

t_colorf	diffuse_color(t_data *data, t_ints *ints)
{
	t_colorf	difclr;
	t_colorf	colorfl;
	t_list		*light;
	t_colorf	cf;

	light = data->lht;
	difclr = colorf_set(0, 0, 0);
	while (light)
	{
		cf = diffuse_light(*((t_obj *)(light->content)), ints, data->objs);
		difclr = colorf_add(difclr, cf);
		light = light->next;
	}
	if (ints->obj->txtr.has)
		colorfl = txtr_checker_colorf(ints->uvz, ints->obj->txtr.mtrans);
	else
		colorfl = color_to_colorf(ints->localc);
	difclr.r *= colorfl.r;
	difclr.g *= colorfl.g;
	difclr.b *= colorfl.b;
	return (difclr);
}

t_colorf	specular_color(t_data *data, t_ints *ints)
{
	t_colorf	cf;
	t_colorf	spcclr;
	t_list		*light;

	light = data->lht;
	spcclr = colorf_set(0, 0, 0);
	while (light)
	{
		cf = specular_light(*((t_obj *)(light->content)), ints, data->objs);
		spcclr = colorf_add(spcclr, cf);
		light = light->next;
	}
	return (spcclr);
}
