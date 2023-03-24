/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:43:42 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/24 17:17:46 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		sphere_assigned(int index, char *trimed_obj, t_obj *sphere);
static int	intersec_tranf(t_obj *obj, t_ints *ints, t_pnt point, t_ray bvray);

/*
* [function initialise and checking sphere value]
* => [success] : intialize value into t_obj
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	sphere_initialise(t_data *data, char **object, int idx)
{
	int		index;
	t_obj	*sphere;
	char	*trimed_obj;
	int		bonus_check[2];

	index = 0;
	bonus_check[0] = 0;
	bonus_check[1] = 0;
	sphere = object_initialise(SPHERE);
	while (object[index])
	{
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error(FAIL_TRIM);
		if (index > 3)
			bonus_argument(sphere, trimed_obj, bonus_check, MANY_SP);
		sphere_assigned(index, trimed_obj, sphere);
		free(trimed_obj);
		index++;
	}
	if (index < 4)
		exit_error(LESS_SP);
	sphere->idx = idx;
	ft_lstadd_back(&data->objs, ft_lstnew((void *)sphere));
}

/*
* [helper function of sphere_initialise, assigning value into (t_obj *)sphere]
* => returtn value will restore into (t_obj*)sphere, if the corditio is true.
* => exit will ocurred when trimed_obj is invalid.
*/
void	sphere_assigned(int index, char *trimed_obj, t_obj *sphere)
{
	static float	diameter;

	if (index == 0 && ft_strncmp(trimed_obj, "sp", 3))
		exit_error(INVALID_IDENT_SP);
	else if (index == 1)
		sphere->pos = ato_tvector(trimed_obj);
	else if (index == 2)
	{
		diameter = ato_float(trimed_obj);
		sphere->size = size_initialise(diameter, diameter, diameter);
	}
	else if (index == 3)
	{
		sphere->color = ato_tcolor(trimed_obj);
		sphere->mtrans = trans_homo(
				sphere->pos,
				vtrset(0.0, 0.0, 0.0),
				vtrset(diameter, diameter, diameter));
		sphere->itrans = mtx_inverse(sphere->mtrans, 4);
	}	
}

/*
* [function checking intersection point betaween scene and sphere]
* => success: if the point is intersection and store into ints(t_ints).
*/
void	sphere_ints(t_obj *obj, t_ray ray, t_ints *ints)
{
	t_vtr	vray;
	t_ray	bvray;
	t_pnt	point;

	bvray = trans_ray(ray, obj->itrans);
	vray = vtrnorm(bvray.l);
	point.a = 1.0;
	point.b = 2.0 * vtrdot(bvray.a, vray);
	point.c = vtrdot(bvray.a, bvray.a) - 1.0;
	ints->t = point.b * point.b - 4.0 * point.c;
	ints->hit = 0;
	if (ints->t > 0.0)
	{
		if (!intersec_tranf(obj, ints, point, bvray))
			return ;
		ints->hit = 1;
	}
}

/*
* [helper fucntion of sphere_inter]
* [tranform the intersection point into real world coordinate.]
* => return (1): unsuccesful tranform the intersection point.
* => return (0): succesful tranform the intersection point.
*/
static int	intersec_tranf(t_obj *obj, t_ints *ints, t_pnt point, t_ray bvray)
{
	float	sqt;
	float	t1;
	float	t2;
	t_vtr	vray;

	vray = vtrnorm(bvray.l);
	sqt = sqrtf(ints->t);
	t1 = (-point.b + sqt) / 2.0;
	t2 = (-point.b - sqt) / 2.0;
	if (t1 < 0.0 || t2 < 0.0)
		return (0);
	else
	{
		if (t1 < t2)
			ints->p = vtradd(bvray.a, vtrscale(vray, t1));
		else
			ints->p = vtradd(bvray.a, vtrscale(vray, t2));
		ints->p = trans_vtr(ints->p, obj->mtrans);
		obj->pos = trans_vtr(vtrset(0, 0, 0), obj->mtrans);
		ints->localn = vtrnorm(vtrsub(ints->p, obj->pos));
		ints->localc = obj->color;
		ints->illum.alpha = 1.0;
	}
	return (1);
}
