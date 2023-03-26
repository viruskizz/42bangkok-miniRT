/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:16:31 by sharnvon          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/26 01:39:58 by sharnvon         ###   ########.fr       */
=======
/*   Updated: 2023/03/23 17:36:18 by sharnvon         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	cylinder_assignd(int index, char *trimed_obj, t_obj *cylinder);
<<<<<<< HEAD
static void	cylinder_ints_set(t_obj *obj, t_ints *ints, t_vtr norm);
=======
static void	cylinder_ints_set(t_obj *obj, t_ints *ints);
>>>>>>> main

/*
* [function initialise and checking cylinder value]
* => [success] : intialize value into t_obj
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	cylinder_inititialize(t_data *data, char **object, int idx)
{
	int		index;
	t_obj	*cylinder;
	char	*trimed_obj;
<<<<<<< HEAD
	int		bonus_check[2];

	index = 0;
	bonus_check[0] = 0;
	bonus_check[1] = 0;
	cylinder = object_initialise(CYLIND);
	while (object[index])
	{
		trimed_obj = ft_strtrim(object[index], "\t");
		if (index > 5)
			bonus_argument(cylinder, trimed_obj, bonus_check, MANY_CY);
=======

	index = 0;
	cylinder = object_initialise(CYLIND);
	while (object[index])
	{
		if (index > 5)
			exit_error(MANY_CY);
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error(FAIL_TRIM);
>>>>>>> main
		cylinder_assignd(index, trimed_obj, cylinder);
		free(trimed_obj);
		index++;
	}
<<<<<<< HEAD
	if (index < 6)
=======
	if (index != 6)
>>>>>>> main
		exit_error(LESS_CY);
	if (!tvector_inrange(cylinder->norm, -1.0, 1.0))
		exit_error(NORM_CY);
	cylinder->idx = idx;
	ft_lstadd_back(&data->objs, ft_lstnew((void *)cylinder));
}

/*
* [helper function of cylinder_inititialize, assigned value into cylinder]
* => return value will store into  t_obj cylinder, if the cordition is true.
* => exit when trimed_obj is a invalid value.
*/
static void	cylinder_assignd(int index, char *trimed_obj, t_obj *cylinder)
{
	static float	diameter;

	if (index == 0 && ft_strncmp(trimed_obj, "cy", 3))
		exit_error(INVALID_IDENT_CY);
	else if (index == 1)
		cylinder->pos = ato_tvector(trimed_obj);
	else if (index == 2)
	{
		cylinder->norm = ato_tvector(trimed_obj);
		cylinder->n_radian = trans_norm_vtr_rot(cylinder->norm);
	}
	else if (index == 3)
		diameter = ato_float(trimed_obj);
	else if (index == 4)
	{
		cylinder->size = size_initialise(ato_float
				(trimed_obj), diameter, diameter);
		cylinder->mtrans = trans_homo(
				cylinder->pos,
				cylinder->n_radian,
				vtrset(cylinder->size.w, cylinder->size.h, cylinder->size.d));
		cylinder->itrans = mtx_inverse(cylinder->mtrans, 4);
	}
	else if (index == 5)
		cylinder->color = ato_tcolor(trimed_obj);
}

void	cylinder_ints(t_obj *obj, t_ray ray, t_ints *ints)
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
	ints_idx = cylinder_ints_formula(bvray, vray, ints);
	if (ints_idx < 0)
		return ;
	else if (ints_idx < 2)
	{
<<<<<<< HEAD
		norm = vtrset(ints->p.x, 0.0, ints->p.z);
		ints->uvz.x = atan2f(ints->p.z, ints->p.x) / PI;
		ints->uvz.y = ints->p.y;
		cylinder_ints_set(obj, ints, norm);
=======
		obj->norm = vtrset(ints->p.x, 0.0, ints->p.z);
		cylinder_ints_set(obj, ints);
>>>>>>> main
	}
	else if (!close0(vray.y, 0.0)
		&& sqrtf(powf(ints->p.x, 2.0) + powf(ints->p.z, 2.0)) < 1.0)
	{
<<<<<<< HEAD
		norm = vtrset(0, ints->p.y, 0);
		ints->uvz.x = ints->p.x;
		ints->uvz.y = ints->p.y;
		cylinder_ints_set(obj, ints, norm);
	}
}

static void	cylinder_ints_set(t_obj *obj, t_ints *ints, t_vtr norm)
=======
		obj->norm = vtrset(0, ints->p.y, 0);
		cylinder_ints_set(obj, ints);
	}
}

static void	cylinder_ints_set(t_obj *obj, t_ints *ints)
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
