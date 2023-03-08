/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_rot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:32:39 by tsomsa            #+#    #+#             */
/*   Updated: 2023/03/09 02:15:36 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	**rotate_x(t_vtr rotate);
static float	**rotate_y(t_vtr rotate);
static float	**rotate_z(t_vtr rotate);

void	trans_rot_xyz(t_vtr rotate, float ***result)
{
	float	**mrotxy;
	float	**mrotx;
	float	**mroty;
	float	**mrotz;

	mrotx = rotate_x(rotate);
	mroty = rotate_y(rotate);
	mrotz = rotate_z(rotate);
	mrotxy = mtx_multi(mrotx, mroty, 4);
	*result = mtx_multi(mrotxy, mrotz, 4);
	mtx_free(mrotx, 4);
	mtx_free(mroty, 4);
	mtx_free(mrotz, 4);
	mtx_free(mrotxy, 4);
}

static float	**rotate_x(t_vtr rotate)
{
	float	**mrotx;

	mrotx = mtx_identity(4);
	mrotx[1][1] = cosf(rotate.x);
	mrotx[1][2] = -sinf(rotate.x);
	mrotx[2][1] = sinf(rotate.x);
	mrotx[2][2] = cosf(rotate.x);
	return (mrotx);
}

static float	**rotate_y(t_vtr rotate)
{
	float	**mroty;

	mroty = mtx_identity(4);
	mroty[0][0] = cosf(rotate.y);
	mroty[0][2] = sinf(rotate.y);
	mroty[2][0] = -sinf(rotate.y);
	mroty[2][2] = cosf(rotate.y);
	return (mroty);
}

static float	**rotate_z(t_vtr rotate)
{
	float	**mrotz;

	mrotz = mtx_identity(4);
	mrotz[0][0] = cosf(rotate.z);
	mrotz[0][1] = -sinf(rotate.z);
	mrotz[1][0] = sinf(rotate.z);
	mrotz[1][1] = cosf(rotate.z);
	return (mrotz);
}
