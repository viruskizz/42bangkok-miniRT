/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:16:31 by sharnvon          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/26 04:26:29 by sharnvon         ###   ########.fr       */
=======
/*   Updated: 2023/03/23 15:16:37 by sharnvon         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	cone_assignd(int index, char *trimed_obj, t_obj *cone);
<<<<<<< HEAD
static void	cone_ints_set(t_obj *obj, t_ints *ints, t_vtr norm);
=======
static void	cone_ints_set(t_obj *obj, t_ints *ints);
>>>>>>> main

/*
* [function initialise and checking cone value]
* => [success] : intialize value into t_obj
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	cone_inititialize(t_data *data, char **object, int idx)
{
	int		index;
	t_obj	*cone;
	char	*trimed_obj;
<<<<<<< HEAD
	int		bonus_check[2];

	index = 0;
	bonus_check[0] = 0;
	bonus_check[1] = 0;
	cone = object_initialise(CONE);
	while (object[index])
	{
		trimed_obj = ft_strtrim(object[index], "\t");
		if (index > 5)
			bonus_argument(cone, trimed_obj, bonus_check, MANY_CO);
=======

	index = 0;
	cone = object_initialise(CONE);
	while (object[index])
	{
		if (index > 5)
			exit_error(MANY_CO);
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error(FAIL_TRIM);
>>>>>>> main
		cone_assignd(index, trimed_obj, cone);
		free(trimed_obj);
		index++;
	}
<<<<<<< HEAD
	if (index < 6)
=======
	if (index != 6)
>>>>>>> main
		exit_error(LESS_CO);
	if (!tvector_inrange(cone->norm, -1.0, 1.0))
		exit_error(NORM_CO);
	cone->idx = idx;
	ft_lstadd_back(&data->objs, ft_lstnew((void *)cone));
}

/*
* [helper function of cone_inititialize, assigned value into cone]
* => return value will store into  t_obj cone, if the cordition is true.
* => exit when trimed_obj is a invalid value.
*/
static void	cone_assignd(int index, char *trimed_obj, t_obj *cone)
{
	static float	diameter;

	if (index == 0 && ft_strncmp(trimed_obj, "cn", 3))
		exit_error(INVALID_IDENT_CO);
	else if (index == 1)
		cone->pos = ato_tvector(trimed_obj);
	else if (index == 2)
	{
		cone->norm = ato_tvector(trimed_obj);
		cone->n_radian = trans_norm_vtr_rot(cone->norm);
	}
	else if (index == 3)
		diameter = ato_float(trimed_obj);
	else if (index == 4)
	{
		cone->size = size_initialise(ato_float
				(trimed_obj), diameter, diameter);
		cone->mtrans = trans_homo(
				cone->pos, cone->n_radian,
				vtrset(cone->size.w, cone->size.h, cone->size.d));
		cone->itrans = mtx_inverse(cone->mtrans, 4);
	}
	else if (index == 5)
		cone->color = ato_tcolor(trimed_obj);
}

void	cone_ints(t_obj *obj, t_ray ray, t_ints *ints)
{
	t_vtr	vray;
	t_ray	bvray;
	int		ints_idx;
<<<<<<< HEAD
	t_vtr	norm;
=======
>>>>>>> main

	bvray = trans_ray(ray, obj->itrans);
	vray = vtrnorm(bvray.l);
	ints_idx = cone_ints_formula(bvray, vray, ints);
<<<<<<< HEAD
	if (ints_idx >= 0 && ints_idx < 2)
	{
		norm = vtrset(ints->p.x,
				-sqrtf(powf(ints->p.x, 2.0) + powf(ints->p.z, 2.0)), ints->p.z);
		ints->uvz.x = atan2f(ints->p.z, ints->p.x) / PI;
		ints->uvz.y = (ints->p.y * 2.0) + 1.0;
		cone_ints_set(obj, ints, norm);
	}
	else if (ints_idx >= 0 && !close0(vray.y, 0.0)
		&& sqrtf(powf(ints->p.x, 2.0) + powf(ints->p.z, 2.0)) < 1.0)
	{
		norm = vtrset(0, ints->p.y, 0);
		ints->uvz.x = ints->p.x;
		ints->uvz.y = ints->p.y;
		cone_ints_set(obj, ints, norm);
	}
}

static void	cone_ints_set(t_obj *obj, t_ints *ints, t_vtr norm)
=======
	if (ints_idx < 0)
		return ;
	else if (ints_idx < 2)
	{
		obj->norm = vtrset(
				ints->p.x,
				-sqrtf(powf(ints->p.x, 2.0) + powf(ints->p.z, 2.0)),
				ints->p.z);
		cone_ints_set(obj, ints);
	}
	else if (!close0(vray.y, 0.0)
		&& sqrtf(powf(ints->p.x, 2.0) + powf(ints->p.z, 2.0)) < 1.0)
	{
		obj->norm = vtrset(0, ints->p.y, 0);
		cone_ints_set(obj, ints);
	}
}

static void	cone_ints_set(t_obj *obj, t_ints *ints)
>>>>>>> main
{
	obj->pos = trans_vtr(vtrset(0, 0, 0), obj->mtrans);
	ints->hit = 1;
	ints->p = trans_vtr(ints->p, obj->mtrans);
<<<<<<< HEAD
	ints->localn = vtrnorm(vtrsub(trans_vtr(norm, obj->mtrans), obj->pos));
=======
	ints->localn = vtrnorm(vtrsub(trans_vtr(obj->norm, obj->mtrans), obj->pos));
>>>>>>> main
	ints->localc = obj->color;
	ints->illum.alpha = 1.0;
}
