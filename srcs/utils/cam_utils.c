#include "minirt.h"

void	camgeometry(t_cam *cam)
{
	t_vtr	l;
	t_vtr	u;
	t_vtr	v;

	l = vtrnorm(vtrsub(cam->lookat, cam->pos));
	u = vtrnorm(vtrcross(l, cam->up));
	v = vtrnorm(vtrcross(u, l));
	cam->proj_c = vtradd(cam->pos, vtrscale(l, cam->length));
	cam->proj_u = vtrscale(u, cam->horz);
	cam->proj_v = vtrscale(v, (cam->horz / cam->ratio));
}

t_ray	camray(float projx, float projy)
{
	t_ray	r;


	return r;
}