#include "minirt.h"


/*
* [function initialise and checking sphere value]
* => [success] : intialize value into t_obj
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	sphere_initialise(t_data *data, char **object)
{
	int		index;
	t_obj	*sphere;
	char	*trimed_obj;
	double	diameter;

	index = 0;
	sphere = object_initialise(SPHERE);
	while(object[index])
	{
		if (index > 3)
			exit_error(TOO_MANY_INPUT_SP);
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error(FAIL_TRIM);
		if (index == 0 && ft_strncmp(trimed_obj, "sp", 3))
			exit_error(INVALID_IDENT_SP);
		else if (index == 1)
			sphere->pos = ato_tvector(trimed_obj);
		else if (index == 2)
		{
			diameter = ato_double(trimed_obj);
			sphere->size = size_initialise(diameter, diameter, diameter);
		}
		else if (index == 3)
			sphere->color = ato_tcolor(trimed_obj);
		free(trimed_obj);
		index++;
	}
	if (index != 4)
		exit_error(TOO_LESS_INPUT_SP);
	ft_lstadd_back(&data->objs, ft_lstnew((void *)sphere));
}

void	sphere_inter(t_ray ray, t_ints *ints)
{
	t_vtr	vray; // compute the values of a,b,c
	float	a;
	float	b;
	float	c;

	vray = vtrnorm(ray.l);
	a = 1.0;
	b = 2.0 * vtrdot(ray.a, vray);
	c = vtrdot(ray.a, ray.a) - 1.0;
	ints->value = b * b - 4.0 * c;
	ints->valid = 0;
	if (ints->value > 0.0)
	{
		float sqt = sqrtf(ints->value);
		float t1 = (-b + sqt) / 2.0;
		float t2 = (-b - sqt) / 2.0;
		if (t1 < 0.0 || t2 < 0.0)
			return ;
		else
		{
			if (t1 < t2)
			{
				ints->p = vtradd(ray.a, vtrscale(vray, t1));
			}
			else
			{
				ints->p = vtradd(ray.a, vtrscale(vray, t2));
			}
			ints->localn = vtrnorm(ints->p);
		}
		ints->valid = 1;
	}
}

