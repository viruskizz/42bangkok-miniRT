#include "minirt.h"


float	**trans_homo(t_vtr trans, t_vtr rotate, t_vtr scale, int dir)
{
	float	**result;
	float	**mtrans;
	float	**mrotx;
	float	**mroty;
	float	**mrotz;
	float	**mscale;

	mtrans = mtx_identity(4);
	mrotx = mtx_identity(4);
	mroty = mtx_identity(4);
	mrotz = mtx_identity(4);
	mscale = mtx_identity(4);

	mtrans[0][3] = trans.x;
	mtrans[1][3] = trans.y;
	mtrans[2][3] = trans.z;

	mrotx[1][1] = cosf(rotate.x);
	mrotx[1][2] = -sinf(rotate.x);
	mrotx[2][1] = sinf(rotate.x);
	mrotx[2][2] = cosf(rotate.x);

	mroty[0][0] = cosf(rotate.y);
	mroty[0][2] = sinf(rotate.y);
	mroty[2][0] = -sinf(rotate.y);
	mroty[2][2] = cosf(rotate.y);

	mrotz[0][0] = cosf(rotate.z);
	mrotz[0][1] = -sinf(rotate.z);
	mrotz[1][0] = sinf(rotate.z);
	mrotz[1][1] = cosf(rotate.z);

	mscale[0][0] = scale.x;
	mscale[1][1] = scale.y;
	mscale[2][2] = scale.z;

	result = mtx_multi(mtrans, mscale, 4);
	result = mtx_multi(result, mrotx, 4);
	result = mtx_multi(result, mroty, 4);
	result = mtx_multi(result, mrotz, 4);

	if (dir == TRANS_FWD)
		return result;
	// else
	// 	return mtx_invert();
	return result;
}
