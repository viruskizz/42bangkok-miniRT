/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_txtr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiva <tsomsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:01:25 by araiva            #+#    #+#             */
/*   Updated: 2023/03/24 23:01:26 by araiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minirt.h"

static float	**txtr_mtx_trans_rot(t_vtr trans, float rot);
static float	*mtx_crs(float **m33, float *m31);
static float	*vtrtmtx(t_vtr v);

// Transform matrix 3x3
t_vtr	txtr_vtr(t_vtr vtr, float **mtrans)
{
	float	*mtxv;
	float	*mtx;
	t_vtr	v;

	mtxv = vtrtmtx(vtr);
	mtx = mtx_crs(mtrans, mtxv);
	v = vtrset(mtx[0], mtx[1], 0.0);
	free(mtx);
	free(mtxv);
	return(v);
}

float	**txtr_mtx_trans(t_vtr trans, float rot, t_vtr scale)
{
	float	**mtx;
	float	**mtx_trans_rot;
	float	**mtx_scale;

	mtx_trans_rot = txtr_mtx_trans_rot(trans, rot);

	// printf("mtx_trans_rot: \n");
	// mtx_print(mtx_trans_rot, 3);

	mtx_scale = mtx_identity(3);
	mtx_scale[0][0] = scale.x;
	mtx_scale[1][1] = scale.y;
	mtx = mtx_multi(mtx_trans_rot, mtx_scale, 3);

	// printf("mtx: \n");
	// mtx_print(mtx, 3);

	free(mtx_trans_rot);
	free(mtx_scale);
	return(mtx);
}

static float	**txtr_mtx_trans_rot(t_vtr trans, float rot)
{
	float	**mtx_trans;
	float	**mtx_rot;
	float	**mtx;

	mtx_trans = mtx_identity(3);
	mtx_rot = mtx_identity(3);

	mtx_trans[0][2] = trans.x;
	mtx_trans[1][2] = trans.y;

	mtx_rot[0][0] = cosf(rot);
	mtx_rot[0][1] = -sinf(rot);
	mtx_rot[1][0] = sin(rot);
	mtx_rot[1][1] = cos(rot);
	mtx = mtx_multi(mtx_trans, mtx_rot, 3);
	free(mtx_trans);
	free(mtx_rot);
	return (mtx);
}

static float	*mtx_crs(float **m33, float *m31)
{
	float	*m;
	int		i;
	int		j;

	m = ft_calloc(3, sizeof(float));
	i = -1;
	while (++i < 3)
	{
		j = -1;
		m[i] = 0;
		while (++j < 3)
			m[i] += m33[i][j] * m31[j];
	}
	return (m);
}

static float	*vtrtmtx(t_vtr v)
{
	float	*m;

	m = ft_calloc(3, sizeof(float));
	m[0] = v.x;
	m[1] = v.y;
	m[2] = v.z;
	return (m);
}
