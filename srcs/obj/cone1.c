/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:16:31 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/12 23:46:57 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	cone_assignd(int index, char *trimed_obj, t_obj *cone);
static int	cone_ints_set(t_obj *obj, t_ints *ints);

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

	index = 0;
	cone = object_initialise(CONE);
	while (object[index])
	{
		if (index > 5)
			exit_error(TOO_MANY_INPUT_CY);
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error(FAIL_TRIM);
		cone_assignd(index, trimed_obj, cone);
		free(trimed_obj);
		index++;
	}
	if (index != 6)
		exit_error(TOO_LESS_INPUT_CY);
	if (!tvector_inrange(cone->norm, -1.0, 1.0))
		exit_error(INVALID_NORM_CY);
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
		exit_error(INVALID_IDENT_CY);
	else if (index == 1)
		cone->pos = ato_tvector(trimed_obj);
	else if (index == 2)
		cone->norm = ato_tvector(trimed_obj);
	else if (index == 3)
		diameter = ato_float(trimed_obj);
	else if (index == 4)
	{
		cone->size = size_initialise(ato_float
				(trimed_obj), diameter, diameter);
		cone->mtrans = trans_homo(
				cone->pos,
				vtrset(0.0, 0.0, 0.0),
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

	bvray = trans_ray(ray, obj->itrans);
	vray = vtrnorm(bvray.l);
	ints_idx = cone_ints_formula(bvray, vray, ints);
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

static int	cone_ints_set(t_obj *obj, t_ints *ints)
{
	obj->pos = trans_vtr(vtrset(0, 0, 0), obj->mtrans);
	ints->valid = 1;
	ints->p = trans_vtr(ints->p, obj->mtrans);
	ints->localn = vtrnorm(vtrsub(trans_vtr(obj->norm, obj->mtrans), obj->pos));
	ints->localc = obj->color;
	ints->illum.alpha = 1.0;
}