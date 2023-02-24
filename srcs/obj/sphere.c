#include "minirt.h"

int	sphere_inter(t_ray ray, t_vtr *ivtr)
{
	t_vtr	vray; // compute the values of a,b,c

	vray = vtrnorm(ray.l);
	double a = 1.0;
	double b = 2.0 * vtrdot(ray.a, vray);
	double c =  vtrdot(ray.a, ray.a) - 1.0;

	double inter = b * b - 4.0 * c;
	if (inter > 0.0)
	{
		double sqt = sqrtf(inter);
		double t1 = (-b + sqt) / 2.0;
		double t2 = (-b - sqt) / 2.0;
		if (t1 < 0.0 || t2 < 0.0)
		{
			return (0);
		}
		else
		{
			if (t1 < t2)
			{
				*ivtr = vtradd(ray.a, vtrscale(vray, t1));
			}
			else
			{
				*ivtr = vtradd(ray.a, vtrscale(vray, t2));
			}

		}
		return (1);
	}
	else
	{
		return (0);
	}
}
