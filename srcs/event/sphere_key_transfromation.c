/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_key_transfromation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:00:29 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/17 05:42:08 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	resizing_key_check(t_obj *object, int keycode);
static void	sphere_value_update(t_obj *object);

int	sphere_key_transformation(t_data *data, int keycode, t_obj *object)
{
	int	update;

	update = 0;
	if (data->lshift_key && keycode == KEY_UP && !update++)
		object->pos.z -= TRANSF_VALUE;
	else if (data->lshift_key && keycode == KEY_DOWN && !update++)
		object->pos.z += TRANSF_VALUE;
	else if (keycode == KEY_RIGHT && !update++)
		object->pos.x += TRANSF_VALUE;
	else if (keycode == KEY_LEFT && !update++)
		object->pos.x -= TRANSF_VALUE;
	else if (keycode == KEY_UP && !update++)
		object->pos.y -= TRANSF_VALUE;
	else if (keycode == KEY_DOWN && !update++)
		object->pos.y += TRANSF_VALUE;
	if (!update)
		update = resizing_key_check(object, keycode);
	sphere_value_update(object);
	return (update);
}

static int	resizing_key_check(t_obj *object, int keycode)
{
	int	update;

	update = 0;
	if (keycode == KEY_PLUS && !update++)
	{
		object->size.w += RESIZE_VALUE;
		object->size.h += RESIZE_VALUE;
		object->size.d += RESIZE_VALUE;

	}
	else if (keycode == KEY_MINUS && !update++)
	{
		object->size.w -= RESIZE_VALUE;
		object->size.h -= RESIZE_VALUE;
		object->size.d -= RESIZE_VALUE;
	}
	return (update);
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