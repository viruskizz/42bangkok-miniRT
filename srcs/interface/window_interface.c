/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 01:08:44 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/17 04:50:04 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		selection_to_window(t_data *data);
void		put_template_to_window(t_data *data, int objects, int *colour);
void		put_elements_to_window(t_data *data, t_list *objects);
static int	get_objects_colour(t_data *data, int *colour, int first);

/*
* [function put elements interface to window]
*/
void	window_interface(t_data *data, int mode)
{
	int			count;
	t_list		*objects;
	int			colour[5];
	int			objects_amount;
	static int	first_element = 0;

	if (mode == INCREASE && ft_lstsize(data->objs) - (first_element + 5) > 0)
		first_element += 5;
	else if (mode == DECREASE && first_element >= 5)
		first_element -= 5;
	objects_amount = get_objects_colour(data, colour, first_element);
	count = 0;
	objects = data->objs;
	while (objects && count < first_element)
	{
		objects = objects->next;
		count++;
	}
	put_template_to_window(data, objects_amount, colour);
	put_elements_to_window(data, objects);
	selection_to_window(data);
}

/*
* [funtion get 5 element colour from list of objects]
* [start with first_element to first_element + 5 or last element]
* return : amount of elements that successed get colour at return statement.
* return : list of colour that successed getting at colour parameter.
*/
int	get_objects_colour(t_data *data, int *colour, int first)
{
	int		count;
	int		index;
	t_list	*objects;
	t_obj	*object;

	index = 0;
	count = 0;
	objects = data->objs;
	while (objects && count < first + 5)
	{
		object = objects->content;
		if (count >= first)
			colour[index++] = color_to_int(object->color);
		count++;
		objects = objects->next;
	}
	return (index);
}
