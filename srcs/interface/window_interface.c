/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 01:08:44 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/18 18:37:39 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		selection_to_window(t_data *data);
void		put_template_to_window(t_data *data, int objects, int *colour);
void		put_elements_to_window(
				t_data *data, int object_amount, t_obj **objects);
static int	get_objects_colour(t_data *data, int *colour, int first);
static int	get_object_ptr(
				t_data *data, t_obj **buff, int *colour, int first_element);
static void	move_list_to_first(t_list **objects, t_list **lights, int first);

/*
* [function put elements interface to window]
*/
void	window_interface(t_data *data, int mode)
{
	int			colour[5];
	t_obj		*objects[5];
	int			objects_amount;
	int			list_size;
	static int	first_element = 0;

	list_size = ft_lstsize(data->objs) + ft_lstsize(data->objs);
	if (mode == INCREASE && list_size - (first_element + 5) > 0)
		first_element += 5;
	else if (mode == DECREASE && first_element >= 5)
		first_element -= 5;
	objects_amount = get_object_ptr(data, objects, colour, first_element);
	put_template_to_window(data, objects_amount, colour);
	put_elements_to_window(data, objects_amount, objects);
	selection_to_window(data);
}

/*
* [funtion get 5 elements colour, pointer from list of objects,]
* [start with first_element to first_element + 5 or last element]
* return : amount of elements that successed get colour at return statement.
* return : list of colour that successed getting at colour parameter.
*/
static int	get_object_ptr(t_data *data, t_obj **buff, int *colour, int first)
{
	int		count;
	t_list	*objects;
	t_list	*lights;

	first++;
	count = 0;
	objects = data->objs;
	lights = data->lht;
	move_list_to_first(&objects, &lights, first);
	int n = (HEIGHT - 28 - 37) / 83;
	while ((objects || lights) && count < n)
	{
		if (objects && ((t_obj *)objects->content)->idx == first + count)
		{
			colour[count] = color_to_int(((t_obj *)objects->content)->color);
			buff[count++] = (t_obj *)objects->content;
			objects = objects->next;
		}
		if (lights && ((t_obj *)lights->content)->idx == first + count)
		{
			colour[count] = color_to_int(((t_obj *)lights->content)->color);
			buff[count++] = (t_obj *)lights->content;
			lights = lights->next;
		}
	}
	return (count);
}

/*
* [helper funtion of get_object_ptr]
* [move head of list objects and lights to the ones index greater thane first]
*/
static void	move_list_to_first(t_list **objs, t_list **lhts, int first)
{
	t_list	*objects;
	t_list	*lights;

	objects = *objs;
	lights = *lhts;
	while (objects && ((t_obj *)objects->content)->idx < first)
		objects = objects->next;
	while (lights && ((t_obj *)lights->content)->idx < first)
		lights = lights->next;
	*objs = objects;
	*lhts = lights;
}
