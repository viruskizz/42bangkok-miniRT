/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:16:31 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/12 23:46:57 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		cylinder_assignd(int index, char *trimed_obj, t_obj *cylinder);

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

	index = 0;
	cylinder = object_initialise(CYLIND);
	while (object[index])
	{
		if (index > 5)
			exit_error(TOO_MANY_INPUT_CY);
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error(FAIL_TRIM);
		cylinder_assignd(index, trimed_obj, cylinder);
		free(trimed_obj);
		index++;
	}
	cylinder->mtrans = trans_homo(
			cylinder->pos,
			vtrset(0.0, 0.0, 0.0),
			vtrset(cylinder->size.w, cylinder->size.h, cylinder->size.d));
	cylinder->itrans = mtx_inverse(cylinder->mtrans, 4);
	if (index != 6)
		exit_error(TOO_LESS_INPUT_CY);
	if (!tvector_inrange(cylinder->norm, -1.0, 1.0))
		exit_error(INVALID_NORM_CY);
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
		cylinder->norm = ato_tvector(trimed_obj);
	else if (index == 3)
		diameter = ato_float(trimed_obj);
	else if (index == 4)
		cylinder->size = size_initialise(ato_float
				(trimed_obj), diameter, diameter);
	else if (index == 5)
		cylinder->color = ato_tcolor(trimed_obj);
}

void	cylinder_ints(t_obj *obj, t_ray ray, t_ints *ints)
{
	t_vtr	vray;
	t_ray	bvray;
	t_fml	fml;
	t_ints	*intss;

	bvray = trans_ray(ray, obj->itrans);
	vray = vtrnorm(bvray.l);
	fml = cylinder_ints_formula(bvray, vray);
	intss = ft_calloc(sizeof(t_ints), 4);
	intss = cylinder_ints_core(bvray, vray, fml, intss);
	intss = cylinder_ints_cap(bvray, vray, fml, intss);
	ints->valid = 0;
	if (!intss[0].valid && !intss[1].valid && !intss[2].valid && !intss[3].valid)
		return (free(intss));
	if (cylinder_ints_point(intss, ints) < 2)
	{
		obj->norm = vtrset(ints->p.x, 0.0, ints->p.z);
		cylinder_ints_set(obj, ints);
	}
	else if (!close0(vray.y, 0.0) && sqrtf(powf(ints->p.x, 2.0) + powf(ints->p.z, 2.0)) < 1.0)
	{
		obj->norm = vtrset(0, ints->p.y, 0);
		cylinder_ints_set(obj, ints);
	}
	free(intss);
}
