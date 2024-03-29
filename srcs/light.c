/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:27:38 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/26 04:20:33 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	if (index < 4)
		exit_error(LESS_L);
	if (light->bright < 0.0 || light->bright > 1.0)
		exit_error(BRIGHT_L);
	light->idx = idx;
	ft_lstadd_back(&data->lht, ft_lstnew((void *)light));
}

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
