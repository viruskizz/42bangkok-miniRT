/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_homo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:32:27 by tsomsa            #+#    #+#             */
/*   Updated: 2023/03/10 00:45:14 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		trans_trans(t_vtr trans, t_vtr scale, float ***result);
static float	**trans_scale(t_vtr scale);
static float	**trans_move(t_vtr trans);

float	**trans_homo(t_vtr trans, t_vtr rotate, t_vtr scale)
{
	float	**result;
	float	**mtrans;
	float	**mrot;

	trans_trans(trans, scale, &mtrans);
	// vtrprint(trans);
	// vtrprint(rotate);
	trans_rot_xyz(rotate, &mrot);
	// printf("mtrans\n");
	// mtx_print(mtrans, 4);
	// printf("mrot\n");
	// mtx_print(mrot, 4);
	result = mtx_multi(mtrans, mrot, 4);
	mtx_free(mtrans, 4);
	mtx_free(mrot, 4);
	return (result);
}

static void	trans_trans(t_vtr trans, t_vtr scale, float ***result)
{
	float	**mtrans;
	float	**mscale;

	mtrans = trans_move(trans);
	mscale = trans_scale(scale);
	*result = mtx_multi(mtrans, mscale, 4);
	mtx_free(mtrans, 4);
	mtx_free(mscale, 4);
}

static float	**trans_move(t_vtr trans)
{
	float	**mtrans;

	mtrans = mtx_identity(4);
	mtrans[0][3] = trans.x;
	mtrans[1][3] = trans.y;
	mtrans[2][3] = trans.z;
	return (mtrans);
}

static float	**trans_scale(t_vtr scale)
{
	float	**mscale;

	mscale = mtx_identity(4);
	mscale[0][0] = scale.x;
	mscale[1][1] = scale.y;
	mscale[2][2] = scale.z;
	return (mscale);
}
