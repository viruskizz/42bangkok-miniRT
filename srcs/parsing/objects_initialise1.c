/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_initialise1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:34:22 by sharnvon          #+#    #+#             */
/*   Updated: 2023/01/26 23:43:05 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	camara_value_check(int	inputs, t_data *data);

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
			exit_error (TOO_MANY_INPUT_A);
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error (FAIL_TRIM);
		if (index == 0 && ft_strncmp(trimed_obj, "A", 2))
			exit_error (INVALID_IDENT_A);
		else if (index == 1)
			data->amb.ratio = ato_double(trimed_obj);
		else if (index == 2)
			data->amb.color = ato_tcolor(trimed_obj);
		free(trimed_obj);
		index++;
	}
	if (index != 3)
		exit_error(TOO_LESS_INPUT_A);
	if (data->amb.ratio < 0.0 || data->amb.ratio > 1.0)
		exit_error (INVALID_RATIO_A);
}

/*
* [function initialise and checking camara value]
* => [success] : intialize value into t_cam.
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	camara_initialise(t_data *data, char **object)
{
	int		index;
	char	*trimed_obj;

	index = 0;
	while (object[index])
	{
		if (index > 3)
			exit_error (TOO_MANY_INPUT_C);
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error (FAIL_TRIM);
		if (index == 0 && ft_strncmp(trimed_obj, "C", 2))
			exit_error (INVALID_IDENT_C);
		else if (index == 1)
			data->cam.pos = ato_tvector(trimed_obj);
		else if (index == 2)
			data->cam.norm = ato_tvector(trimed_obj);
		else if (index == 3)
			data->cam.fov = ft_atoi(trimed_obj);
		free(trimed_obj);
		index++;
	}
	camara_value_check(index, data);
}

/*
* [helper function of camara_initialise checking camara value]
* => [success] : all value is valid.
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
static void	camara_value_check(int	inputs, t_data *data)
{
	if (inputs != 4)
		exit_error(TOO_LESS_INPUT_C);
	if (!tvector_inrange(data->cam.norm, -1.0, 1.0))
		exit_error(INVALID_NORM_C);
	if (data->cam.fov < 0 || data->cam.fov > 180)
		exit_error(INVALID_FOV_C);
}

/*
* [function initialise and checking light value]
* => [success] : intialize value into t_lht.
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	light_initialise(t_data* data, char **object)
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
			exit_error(TOO_MANY_INPUT_L);
		trimed_obj = ft_strtrim(object[index], "/t");
		if (!trimed_obj)
			exit_error(FAIL_TRIM);
		if (index == 0 && ft_strncmp(trimed_obj, "L", 2))
			exit_error(INVALID_IDENT_L);
		else if (index == 1)
			light->pos = ato_tvector(trimed_obj);
		else if (index == 2)
			light->bright = ato_double(trimed_obj);
		else if (index == 3)
			light->color = ato_tcolor(trimed_obj);
		free(trimed_obj);
		index++;
	}
	if (index < 3)
		exit_error(TOO_LESS_INPUT_L);
	if (light->bright < 0.0 || light->bright > 1.0)
		exit_error(INVALID_BRIGHT_L);
	ft_lstadd_back(&data->lht, ft_lstnew((void *)light));
}