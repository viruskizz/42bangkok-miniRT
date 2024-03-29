/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:18:54 by tsomsa            #+#    #+#             */
/*   Updated: 2023/03/23 15:09:02 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	*mtx_crs(float **m44, float *m41);
static float	*vtrtmtx(t_vtr v);

t_vtr	trans_vtr(t_vtr v, float **mtxtrans)
{
	float	*mtxv;
	float	*mtxr;
	t_vtr	vr;

	mtxv = vtrtmtx(v);
	mtxr = mtx_crs(mtxtrans, mtxv);
	vr = vtrset(mtxr[0], mtxr[1], mtxr[2]);
	free(mtxr);
	free(mtxv);
	return (vr);
}

t_ray	trans_ray(t_ray ray, float **mtxtrans)
{
	return (set_ray(
			trans_vtr(ray.a, mtxtrans),
			trans_vtr(ray.b, mtxtrans)));
}

t_vtr	trans_norm_vtr_rot(t_vtr norm)
{
	t_vtr	rot;

	rot.y = atanf(norm.y / -norm.z);
	rot.x = atanf(-norm.z / norm.x);
	rot.z = atanf(norm.x / norm.y);
	if (isnan(rot.x))
		rot.x = 0;
	if (isnan(rot.y))
		rot.y = 0;
	if (isnan(rot.z))
		rot.z = 0;
	return (rot);
}

static float	*mtx_crs(float **m44, float *m41)
{
	float	*m;
	int		i;
	int		j;

	m = ft_calloc(4, sizeof(float));
	i = -1;
	while (++i < 4)
	{
		j = -1;
		m[i] = 0;
		while (++j < 4)
			m[i] += m44[i][j] * m41[j];
	}
	return (m);
}

static float	*vtrtmtx(t_vtr v)
{
	float	*m;

	m = ft_calloc(4, sizeof(float));
	m[0] = v.x;
	m[1] = v.y;
	m[2] = v.z;
	m[3] = 1.0;
	return (m);
}
