#include "minirt.h"

int	sphere_inter(t_ray ray)
{
	t_vtr	vray; // compute the values of a,b,c

	vray = vtrnorm(ray.l);
	double a = 1.0;
	double b = 2.0 * vtrdot(ray.a, vray);
	double c =  vtrdot(ray.a, ray.a) - 1.0;

	double inter = b * b - 4.0 * c;
	if (inter > 0.0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
