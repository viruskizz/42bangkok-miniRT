/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiva <tsomsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:07:52 by araiva            #+#    #+#             */
/*   Updated: 2023/02/05 15:07:53 by araiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	rayset(t_vtr a, t_vtr b)
{
	t_ray	r;

	r.a = a;
	r.b = b;
	r.l = vtrsub(b, a);
	return (r);
}
/*
 * generate ray from camera position to projection screen
 */
t_ray	raygen(t_cam cam, float proj_x, float proj_y)
{
	t_vtr	world1;
	t_vtr	screen_pos;

	world1 = vtradd(cam.proj_c, vtrscale(cam.proj_u, proj_x));
	screen_pos = vtradd(world1, vtrscale(cam.proj_v, proj_y));
	return rayset(cam.pos, screen_pos);
}
