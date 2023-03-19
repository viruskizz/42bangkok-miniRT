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
	cone->mtrans = trans_homo(
				cone->pos,
				vtrset(0.0, 0.0, 0.0),
				vtrset(cone->size.w, cone->size.h, cone->size.d));
	cone->itrans = mtx_inverse(cone->mtrans, 4);
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
		cone->size = size_initialise(ato_float
				(trimed_obj), diameter, diameter);
	else if (index == 5)
		cone->color = ato_tcolor(trimed_obj);
}

void	cone_ints(t_obj *obj, t_ray ray, t_ints *ints)
{
	t_vtr	vray;
	t_ray	bvray;
	float	a;
	float	b;
	float	c;

	bvray = trans_ray(ray, obj->itrans);
	vray = vtrnorm(bvray.l);
	a = powf(vray.x, 2.0) + powf(vray.z, 2.0) - powf(vray.y, 2.0);
	b = 2.0 * (bvray.a.x * vray.x + bvray.a.z * vray.z - bvray.a.y * vray.y);
	c = powf(bvray.a.x, 2.0) + powf(bvray.a.z, 2.0) - powf(bvray.a.y, 2.0);
	ints->value = sqrtf(powf(b, 2.0) - 4.0 * a * c);

	int		valid[3];
	float	t[3];
	t_vtr	poi[3];
	if (ints->value > 0.0)
	{
		t[0] = (-b + ints->value) / (2.0 * a);
		t[1] = (-b - ints->value) / (2.0 * a);
		poi[0] = vtradd(bvray.a, vtrscale(vray, t[0]));
		poi[1] = vtradd(bvray.a, vtrscale(vray, t[1]));

		if ((t[0] > 0.0) && (poi[0].y > 0.0) && (poi[0].y < 1.0))
		{
			valid[0] = 1;
		}
		else
		{
			valid[0] = 0;
			t[0] = 100e6;
		}
		if ((t[1] > 0.0) && (poi[1].y > 0.0) && (poi[1].y < 1.0))
		{
			valid[1] = 1;
		}
		else
		{
			valid[1] = 0;
			t[1] = 100e6;
		}
	}
	else
	{
		valid[0] = 0;
		valid[1] = 0;
		t[0] = 100e6;
		t[1] = 100e6;
	}

	// And test the end caps
	if (close0(vray.y, 0.0))
	{
		valid[2] = 0;
		t[2] = 100e6;
	}
	else
	{
		t[2] = (bvray.a.y - 1.0) / -vray.y;
		poi[2] = vtradd(bvray.a, vtrscale(vray, t[2]));
		
		if ((t[2] > 0.0) && (sqrtf(powf(poi[2].x, 2.0) + powf(poi[2].z, 2.0)) < 1.0))
		{
			valid[2] = 1;
		}
		else
		{
			valid[2] = 0;
			t[2] = 100e6;
		}
	}
	ints->valid = 0;
	if (!valid[0] && !valid[1] && !valid[2])
		return ;
	int idx = 0;
	float val = 10e6;
	int i = -1;
	while (++i < 3)
	{
		if (t[i] < val)
		{
			val = t[i];
			idx = i;
		}
	}
	ints->p = poi[idx];
	if (idx < 2)
	{
		ints->valid = 1;
		ints->p = trans_vtr(ints->p, obj->mtrans);
		t_vtr pos0 = vtrset(0, 0, 0);
		obj->pos = trans_vtr(pos0, obj->mtrans);
		t_vtr orgn = vtrset(
			ints->p.x,
			-sqrtf(powf(ints->p.x, 2.0) + powf(ints->p.z, 2.0)),
			ints->p.z);
		ints->localn = vtrnorm(vtrsub(trans_vtr(orgn, obj->mtrans), obj->pos));
		ints->localc = obj->color;
		ints->illum.alpha = 1.0;
	}
	else
	{
		if (!close0(vray.y, 0.0))
		{
			if (sqrtf(powf(ints->p.x, 2.0) + powf(ints->p.z, 2.0)) < 1.0)
			{
				ints->valid = 1;
				ints->p = trans_vtr(ints->p, obj->mtrans);
				t_vtr pos0 = vtrset(0, 0, 0);
				obj->pos = trans_vtr(pos0, obj->mtrans);
				// obj->norm = vtrset(0, 1.0, 0);
				ints->localn = vtrnorm(vtrsub(trans_vtr(obj->norm, obj->mtrans), obj->pos));
				ints->localc = obj->color;
				ints->illum.alpha = 1.0;
			}
		}
	}
}
