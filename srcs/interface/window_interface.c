/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 01:08:44 by sharnvon          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/26 05:06:59 by sharnvon         ###   ########.fr       */
=======
/*   Updated: 2023/03/22 05:02:21 by sharnvon         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		selection_to_window(t_data *data);
void		put_template_to_window(t_data *data, int objects, int *colour);
void		put_elements_to_window(
				t_data *data, int object_amount, t_obj **objects);
static int	get_object_ptr(
				t_data *data, t_obj **buff, int *colour, int first_element);
static void	move_list_to_first(t_list **objects, t_list **lights, int first);

/*
* [function put elements interface to window]
*/
int	window_interface(t_data *data, int mode)
{
	int			colour[5];
	t_obj		*objects[5];
	int			objects_amount;
	int			list_size;
	static int	first_element = 1;

<<<<<<< HEAD
	list_size = ft_lstsize(data->lht) + ft_lstsize(data->objs);
	objects_amount = (HEIGHT - 28 - 37) / 83;
	if (mode == INCREASE && list_size - (first_element + objects_amount) >= 0)
=======
	list_size = ft_lstsize(data->objs) + ft_lstsize(data->objs);
	objects_amount = (HEIGHT - 28 - 37) / 83;
	if (mode == INCREASE && list_size - (first_element + objects_amount) > 0)
>>>>>>> main
		first_element += objects_amount;
	else if (mode == DECREASE && first_element >= objects_amount)
		first_element -= objects_amount;
	objects_amount = get_object_ptr(data, objects, colour, first_element);
	put_template_to_window(data, objects_amount, colour);
	put_elements_to_window(data, objects_amount, objects);
	selection_to_window(data);
	return (0);
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

	count = 0;
	objects = data->objs;
	lights = data->lht;
	move_list_to_first(&objects, &lights, first);
	while ((objects || lights) && count < (HEIGHT - 28 - 37) / 83)
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
