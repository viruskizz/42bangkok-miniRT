/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_key_transfromation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:00:29 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/16 22:17:46 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	sphere_value_update(t_obj *object);

void	sphere_key_transformation(t_data *data, int keycode, t_obj *object)
{
	if (data->lshift_key && keycode == KEY_UP)
		object->pos.z -= TRANSF_VALUE;
	else if (data->lshift_key && keycode == KEY_DOWN)
		object->pos.z += TRANSF_VALUE;
	else if (keycode == KEY_RIGHT)
		object->pos.x += TRANSF_VALUE;
	else if (keycode == KEY_LEFT)
		object->pos.x -= TRANSF_VALUE;
	else if (keycode == KEY_UP)
		object->pos.y -= TRANSF_VALUE;
	else if (keycode == KEY_DOWN)
		object->pos.y += TRANSF_VALUE;
	else if (keycode == KEY_PLUS)
	{
		object->size.w += RESIZE_VALUE;
		object->size.h += RESIZE_VALUE;
		object->size.d += RESIZE_VALUE;

	}
	else if (keycode == KEY_MINUS)
	{
		object->size.w -= RESIZE_VALUE;
		object->size.h -= RESIZE_VALUE;
		object->size.d -= RESIZE_VALUE;
	}
	sphere_value_update(object);
}

/*
* [function recompute new value of object]
*/
static void	sphere_value_update(t_obj *object)
{	
	object->mtrans = trans_homo(
		object->pos,
		vtrset(0.0, 0.0, 0.0),
		vtrset(object->size.w,
			object->size.h,
			object->size.d));
	object->itrans = mtx_inverse(object->mtrans, 4);
}