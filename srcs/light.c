/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:27:38 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/22 05:46:49 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		lht_inst_objs(
				t_ray lray, t_ints *linst, t_ints *ints, t_list *objs);
static void	light_assigned(int index, char *trimed_obj, t_obj *light);

/*
* [function initialize and checking ambient light value]
* => [success] : intialize value into t_amb.
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	ambient_initialise(t_data *data, char **object)
{
	int		index;
	char	*trimed_obj;

	index = 0;
	while (object[index])
	{
		if (index > 2)
			exit_error (MANY_AM);
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error (FAIL_TRIM);
		if (index == 0 && ft_strncmp(trimed_obj, "A", 2))
			exit_error (INVALID_ID_A);
		else if (index == 1)
			data->amb.ratio = ato_float(trimed_obj);
		else if (index == 2)
			data->amb.color = ato_tcolor(trimed_obj);
		free(trimed_obj);
		index++;
	}
	if (index != 3)
		exit_error(LESS_AM);
	if (data->amb.ratio < 0.0 || data->amb.ratio > 1.0)
		exit_error (INVALID_RA_A);
	data->check[0]++;
}

/*
* old
* [function initialise and checking light value]
* => [success] : intialize value into t_lht.
* => [exit] : unsuccessful initialize value cause invalid value or character.
void	lht_initialise(t_data *data, char **object)
{
	int		index;
	char	*trimed_obj;
	t_lht	*light;

	index = 0;
	light = (t_lht *)ft_calloc(sizeof(t_lht), 1);
	if (!light)
		exit_error(FAIL_ALLOC);
	while (object[index])
	{
		if (index > 3)
			exit_error(MANY_L);
		trimed_obj = ft_strtrim(object[index], "/t");
		if (!trimed_obj)
			exit_error(FAIL_TRIM);
		light_assigned(index, trimed_obj, light);
		free(trimed_obj);
		index++;
	}
	if (index < 3)
		exit_error(LESS_L);
	if (light->bright < 0.0 || light->bright > 1.0)
		exit_error(BRIGHT_L);
	light->colorf = color_to_colorf(light->color);
	ft_lstadd_back(&data->lht, ft_lstnew((void *)light));
}
*/

/*
* new
* [function initialise and checking light value]
* => [success] : intialize value into t_lht.
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	lht_initialise(t_data *data, char **object, int idx)
{
	int		index;
	char	*trimed_obj;
	t_obj	*light;

	index = 0;
	light = (t_obj *)ft_calloc(sizeof(t_obj), 1);
	if (!light)
		exit_error(FAIL_ALLOC);
	while (object[index])
	{
		if (index > 3)
			exit_error(MANY_L);
		trimed_obj = ft_strtrim(object[index], "/t");
		if (!trimed_obj)
			exit_error(FAIL_TRIM);
		light_assigned(index, trimed_obj, light);
		free(trimed_obj);
		index++;
	}
	if (index < 3)
		exit_error(LESS_L);
	if (light->bright < 0.0 || light->bright > 1.0)
		exit_error(BRIGHT_L);
	light->idx = idx;
	ft_lstadd_back(&data->lht, ft_lstnew((void *)light));
}

/*
* new
* [helper function of lht_initialise]
* [checking string of light input, converting and assigned into light(t_lht)]
* => [return] : valid input, covert and store into light.
* => [exit] : invalid input, print error and exit program.
*/
static void	light_assigned(int index, char *trimed_obj, t_obj *light)
{
	if (index == 0 && ft_strncmp(trimed_obj, "L", 2))
		exit_error(INVALID_IDENT_L);
	else if (index == 1)
		light->pos = ato_tvector(trimed_obj);
	else if (index == 2)
		light->bright = ato_float(trimed_obj);
	else if (index == 3)
	{
		light->color = ato_tcolor(trimed_obj);
		light->colorf = color_to_colorf(light->color);
		light->type = LIGHT;
	}
}

/*
* old
* [helper function of lht_initialise]
* [checking string of light input, converting and assigned into light(t_lht)]
* => [return] : valid input, covert and store into light.
* => [exit] : invalid input, print error and exit program.

static void	light_assigned(int index, char *trimed_obj, t_lht *light)
{
	if (index == 0 && ft_strncmp(trimed_obj, "L", 2))
		exit_error(INVALID_IDENT_L);
	else if (index == 1)
		light->pos = ato_tvector(trimed_obj);
	else if (index == 2)
		light->bright = ato_float(trimed_obj);
	else if (index == 3)
		light->color = ato_tcolor(trimed_obj);
}
*/

/*
 * new
 * compute light between light point and intersection point
 * reflecing the local normal surface (inside object)
 ? lvtr = light vector in normalize
 ? svtr = starting vector
*/
void	lht_illuminated(t_obj lht, t_ints *ints, t_list *objs)
{
	t_vtr	lvtr;
	t_ray	lray;
	t_ints	lints;
	float	angle;

	lvtr = vtrnorm(vtrsub(lht.pos, ints->p));
	lray = set_ray(ints->p, vtradd(ints->p, lvtr));
	lht_inst_objs(lray, &lints, ints, objs);
	ints->illum = lht.colorf;
	ints->hit = 0;
	ints->illum.alpha = 0.0;
	if (!lints.hit)
	{
		angle = acos(vtrdot(ints->localn, lvtr));
		if (angle <= HALF_PI)
		{
			ints->hit = 1;
			ints->illum.alpha = lht.bright * (1.0 - (angle / HALF_PI));
		}
	}
}

void	lht_inst_objs(t_ray lray, t_ints *lints, t_ints *ints, t_list *objs)
{
	t_list	*obj;
	t_obj	*o;

	obj = objs;
	lints->hit = 0;
	while (obj)
	{
		o = (t_obj *) obj->content;
		if (o != ints->obj)
			obj_ints(o, lray, lints);
		if (lints->hit)
			return ;
		obj = obj->next;
	}
}
