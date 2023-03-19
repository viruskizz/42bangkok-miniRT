/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:02:54 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/11 22:06:17 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
* helper function intialise defult value
*/
t_obj	*object_initialise(int type)
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

void	set_objs(t_data *data)
{
	t_obj	*obj;
	t_list	*lst;

	obj = new_obj(data);
	// if (type == 'p')
	obj = set_plane_img(data, obj);
	lst = ft_lstnew(obj);
	if (data->objs)
		data->objs = lst;
	else
		ft_lstadd_back(&data->objs, lst);
}

t_obj	*new_obj(t_data *data)
{
	t_obj	*obj;

	obj = ft_calloc(sizeof(t_obj), 1);
	obj->type = PLANE;
	obj->name = ft_strdup("PLAN");
	obj->pos = vtrset(0, 0, 0);
	obj->color = set_color(128, 128, 0);
	obj->size = set_size(WIDTH, HEIGHT, 0);
	return (obj);
}

void	obj_ints(t_obj *obj, t_ray ray, t_ints *ints)
{
	ints->obj = obj;
	if (obj->type == SPHERE)
		sphere_ints(obj, ray, ints);
	else if (obj->type == PLANE)
		plane_ints(obj, ray, ints);
	else if (obj->type == CYLIND)
		cylinder_ints(obj, ray, ints);
	else if (obj->type == CONE)
		cone_ints(obj, ray, ints);
}

void	free_obj(t_obj *obj)
{
	free(obj->name);
}
