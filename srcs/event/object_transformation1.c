/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_transformation1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:01:48 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/23 18:00:33 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	object_value_update(t_obj *object);
static int	rotation_key_check(t_data *data, int keycode, t_obj *object);
static int	moving_key_check(t_data *data, int keycode, t_obj *object);
static int	resizing_key_check(t_data *data, int keycode, t_obj *object);

/*
* [function apply transformation to object with keycode input]
*/
void	objects_transformation(t_data *data, int keycode, t_obj *object)
{
	if (!moving_key_check(data, keycode, object))
	{
		if (object->type > 1 && !rotation_key_check(data, keycode, object))
		{
			if (object->type != PLANE
				&& !resizing_key_check(data, keycode, object))
				return ;
		}
		else if (!data->update && object->type != LIGHT)
		{
			if (!resizing_key_check(data, keycode, object))
				return ;
		}
		else if (!data->update)
			return ;
	}
	object_value_update(object);
}

/*
* [apply roatation tranformation to plane object by cordition of keycode input]
* return [update = 1] : keycode input is in cordition.
* return [update = 0] : keycode input is not in cordition.
*/
static int	rotation_key_check(t_data *data, int keycode, t_obj *object)
{
	int	update;

	update = 0;
	if ((data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& !update++))
		object->n_radian.z += ROTATE_VALUE;
	else if ((data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& !update++))
		object->n_radian.z -= ROTATE_VALUE;
	else if (!data->lshift_key && data->ctrl_key && keycode == KEY_UP
		&& !update++)
		object->n_radian.x += ROTATE_VALUE;
	else if (!data->lshift_key && data->ctrl_key && keycode == KEY_DOWN
		&& !update++)
		object->n_radian.x -= ROTATE_VALUE;
	else if (!data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
		&& !update++)
		object->n_radian.y += ROTATE_VALUE;
	else if (!data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
		&& !update++)
		object->n_radian.y -= ROTATE_VALUE;
	data->update = update;
	return (update);
}

/*
* [apply moving tranformation to plane object by cordition of keycode input]
* return [update = 1] : keycode input is in cordition.
* return [update = 0] : keycode input is not in cordition.
*/
static int	moving_key_check(t_data *data, int keycode, t_obj *object)
{
	int	update;

	update = 0;
	if (!data->ctrl_key && data->lshift_key && keycode == KEY_UP && !update++)
		object->pos.z -= TRANSF_VALUE;
	else if (!data->ctrl_key && data->lshift_key
		&& keycode == KEY_DOWN && !update++)
		object->pos.z += TRANSF_VALUE;
	else if (!data->lshift_key &&!data->ctrl_key && keycode == KEY_RIGHT && !update++)
		object->pos.x += TRANSF_VALUE;
	else if (!data->lshift_key &&!data->ctrl_key && keycode == KEY_LEFT && !update++)
		object->pos.x -= TRANSF_VALUE;
	else if (!data->lshift_key &&!data->ctrl_key && keycode == KEY_UP && !update++)
		object->pos.y -= TRANSF_VALUE;
	else if (!data->lshift_key &&!data->ctrl_key && keycode == KEY_DOWN && !update++)
		object->pos.y += TRANSF_VALUE;
	data->update = update;
	return (update);
}

/*
* [resize to plane object by cordition of keycode input]
* return [update = 1] : keycode input is in cordition.
* return [update = 0] : keycode input is not in cordition.
*/
static int	resizing_key_check(t_data *data, int keycode, t_obj *object)
{
	int	update;

	update = 0;
	if (keycode == KEY_PLUS)
	{
		object->size.w += RESIZE_VALUE;
		object->size.h += RESIZE_VALUE;
		object->size.d += RESIZE_VALUE;
		update++;
	}
	else if (keycode == KEY_MINUS)
	{
		object->size.w -= RESIZE_VALUE;
		object->size.h -= RESIZE_VALUE;
		object->size.d -= RESIZE_VALUE;
		update++;
	}
	data->update = update;
	return (update);
}

/*
* [function recompute new mtrans and itrans value of plane object]
*/
static void	object_value_update(t_obj *object)
{
	object->mtrans = trans_homo(
			object->pos,
			object->n_radian,
			vtrset(object->size.w,
				object->size.h,
				object->size.d));
	object->itrans = mtx_inverse(object->mtrans, 4);
}
