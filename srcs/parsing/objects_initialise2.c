/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_initialise2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:28:05 by sharnvon          #+#    #+#             */
/*   Updated: 2023/01/27 00:39:16 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_obj	*object_initialise(int type);

/*
* [function initialise and checking sphere value]
* => [success] : intialize value into t_obj
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	sephere_initialise(t_data *data, char **object)
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
	if (index != 4)
		exit_error(TOO_LESS_INPUT_PL);
	if (!tvector_inrange(plane->norm, -1.0, 1.0))
		exit_error(INVALID_NORM_PL);
	ft_lstadd_back(&data->objs, ft_lstnew((void *)plane));
}

/*
* [function initialise and checking cylinder value]
* => [success] : intialize value into t_obj
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	cylinder_inititialize(t_data *data, char **object)
{
	int		index;
	t_obj	*cylinder;
	char	*trimed_obj;
	double	diameter;

	index = 0;
	cylinder = object_initialise(CYLIND);
	while (object[index])
	{
		if (index > 5)
			exit_error(TOO_MANY_INPUT_CY);
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error(FAIL_TRIM);
		if (index == 0 && ft_strncmp(trimed_obj, "cy", 3))
			exit_error(INVALID_IDENT_CY);
		else if (index == 1)
			cylinder->pos = ato_tvector(trimed_obj);
		else if (index == 2)
			cylinder->norm = ato_tvector(trimed_obj);
		else if (index == 3)
			diameter = ato_double(trimed_obj);
		else if (index == 4)
			cylinder->size = size_initialise(ato_double(trimed_obj), diameter, diameter);
		else if (index == 5)
			cylinder->color = ato_tcolor(trimed_obj);
		free(trimed_obj);
		index++;
	}
	if (index != 6)
		exit_error(TOO_LESS_INPUT_CY);
	if (!tvector_inrange(cylinder->norm, -1.0, 1.0))
		exit_error(INVALID_NORM_CY);
	ft_lstadd_back(&data->objs, ft_lstnew((void *)cylinder));
}

/*
* helper function intialise defult value
*/
static t_obj	*object_initialise(int type)
{
	t_obj	*object;

	object = (t_obj *)ft_calloc(sizeof(t_obj), 1);
	if (!object)
		exit_error(FAIL_ALLOC);
	object->idx = 0;
	object->type = type;
	object->name = NULL;
	object->pos = ato_tvector("0,0,0");
	object->norm = ato_tvector("0,0,0");
	object->color = ato_tcolor("0,0,0");
	object->size = size_initialise(0, 0, 0);
	return (object);
}