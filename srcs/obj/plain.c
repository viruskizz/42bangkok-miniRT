#include "minirt.h"


/*
* [function initialise and checking plane value]
* => [success] : intialize value into t_obj
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	plane_initialise(t_data *data, char **object)
{
	int		index;
	t_obj	*plane;
	char	*trimed_obj;

	index = 0;
	plane = object_initialise(PLANE);
	while(object[index])
	{
		if (index > 4)
			exit_error(TOO_MANY_INPUT_PL);
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error(FAIL_TRIM);
		if (index == 0 && ft_strncmp(trimed_obj, "pl", 3))
			exit_error(INVALID_IDENT_PL);
		else if (index == 1)
			plane->pos = ato_tvector(trimed_obj);
		else if (index == 2)
			plane->norm = ato_tvector(trimed_obj);
		else if (index == 3)
			plane->color = ato_tcolor(trimed_obj);
		free(trimed_obj);
		index++;
	}
	plane->mtrans = trans_homo(
		plane->pos,
		vtrset(0.0, 0.0, 0.0),
		vtrset(10.0, 10.0, 10.0)
	);
	plane->itrans = mtx_inverse(plane->mtrans, 4);
	if (index != 4)
		exit_error(TOO_LESS_INPUT_PL);
	if (!tvector_inrange(plane->norm, -1.0, 1.0))
		exit_error(INVALID_NORM_PL);
	ft_lstadd_back(&data->objs, ft_lstnew((void *)plane));
}

t_obj	*set_plain_img(t_data *data, t_obj *obj)
{
	double	x;
	double	y;
	int		color;

	obj->img.ptr = mlx_new_image(data->mlx, (int)obj->size.w, (int)obj->size.h);
	obj->img.addr = mlx_get_data_addr(obj->img.ptr, &obj->img.bpp, &obj->img.lh, &obj->img.endian);
	y = 0;
	while (y < obj->size.h)
	{
		x = 0;
		while(x < obj->size.w)
		{
			color = rgb_to_int(obj->color.r, obj->color.g, obj->color.b);
			pixel_put_img(&obj->img, x, y, color);
			x++;
		}
		y++;
	}
	return (obj);
}

void	plain_inter(t_obj *obj, t_ray ray, t_ints *ints)
{
	t_vtr	vray; // compute the values of a,b,c
	t_ray	bvray; // compute the values of a,b,c
	float	a;
	float	b;
	float	c;

	bvray = trans_ray(ray, obj->itrans);
	vray = vtrnorm(bvray.l);
	ints->value = 0;
	if (!close0(vray.y, 0.0f))
	{
		// printf("not close\n");
		ints->value = bvray.a.y / -vray.y;
		if (ints->value > 0.0)
		{
			float u = bvray.a.x + (vray.x * ints->value);
			float v = bvray.a.z + (vray.z * ints->value);
			if ((fabsf(u) < 1.0) && (fabsf(v) < 1.0))
			{
				ints->valid = 1;
				ints->p = vtradd(bvray.a, vtrscale(vray, ints->value));
				ints->p = trans_vtr(ints->p, obj->mtrans);
				t_vtr pos0 = vtrset(0, 0, 0);
				obj->pos = trans_vtr(pos0, obj->mtrans);
				ints->localn = trans_vtr(obj->norm, obj->mtrans);
				ints->localn = vtrnorm(vtrsub(ints->localn, obj->pos));
				ints->localc = obj->color;
			}
		}
	}
}

// void	sphere_inter(t_obj *obj, t_ray ray, t_ints *ints)
// {
// 	t_vtr	vray; // compute the values of a,b,c
// 	t_ray	bvray; // compute the values of a,b,c
// 	float	a;
// 	float	b;
// 	float	c;

// 	bvray = trans_ray(ray, obj->itrans);
// 	vray = vtrnorm(bvray.l);
// 	// a = 1.0;
// 	b = 2.0 * vtrdot(bvray.a, vray);
// 	c = vtrdot(bvray.a, bvray.a) - 1.0;
// 	ints->value = b * b - 4.0 * c;
// 	ints->valid = 0;

// 	if (ints->value > 0.0)
// 	{
// 		float sqt = sqrtf(ints->value);
// 		float t1 = (-b + sqt) / 2.0;
// 		float t2 = (-b - sqt) / 2.0;
// 		if (t1 < 0.0 || t2 < 0.0)
// 			return ;
// 		else
// 		{
// 			if (t1 < t2)
// 			{
// 				ints->p = vtradd(bvray.a, vtrscale(vray, t1));
// 			}
// 			else
// 			{
// 				ints->p = vtradd(bvray.a, vtrscale(vray, t2));
// 			}
// 			// Transform the intersection point back into world coordinates.
// 			ints->p = trans_vtr(ints->p, obj->mtrans);
// 			t_vtr pos0 = vtrset(0, 0, 0);
// 			obj->pos = trans_vtr(pos0, obj->mtrans);
// 			ints->localn = vtrnorm(vtrsub(ints->p, obj->pos));
// 			ints->localc = obj->color;
// 			ints->illum.intens = 1.0;
// 		}
// 		ints->valid = 1;
// 	}
// }
