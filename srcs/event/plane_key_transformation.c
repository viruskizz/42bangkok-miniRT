/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_key_transformation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:01:48 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/19 03:25:38 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	plane_value_update(t_obj *object);
static int	rotation_key_check(t_data *data, int keycode, t_obj *object);
static int	moving_key_check(t_data *data, int keycode, t_obj *object);
// static void	resizing_key_check(t_data *data, int keycode, t_obj *object);

/*
* [function apply transformation to plane with keycode input]
* ========================= moving ========================= 
* [up] : move object up (increase position [pos.y] value)
* [down] : move object down (decrease position [pos.y] value)
* [right] : move object right (increase position [pos.x] value)
* [left] : move object right (decrease position [pos.x] value)
* [lshif] + [up] : move object forward (increase position [pos.z] value)
* [lshif] + [down] : move object forward (decrease position [pos.z] value)
* * ========================= rotating ========================= 
* [ctrl] + [up] : rotate object up along x axis (increase [norm.x] value)
* [ctrl] + [down] : rotate object down along x axis (decrease [norm.x] value)
* [ctrl] + [right] : rotate object right along y axis (increase [norm.y] value)
* [ctrl] + [left] : rotate object down  along y axis (decrease [norm.y] value)
* [lshift] + [ctrl] + [right] : rotate object along z axis (increase [norm.z])
* [lshift] + [ctrl] + [left] : rotate object along z axis (decrease [norm.z])
* return [1] : keycode is in cordition and some value was changed.
* return [0] : keycode is not in cordition.
*/
void	plane_key_transf(t_data *data, int keycode, t_obj *object)
{
	if (!rotation_key_check(data, keycode, object))
	{
		if (!moving_key_check(data, keycode, object))
			return ;
			// resizing_key_check(data, keycode, object);
	}
	plane_value_update(object);
	data->update = 1;
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
	if (data->ctrl_key && data->lshift_key && keycode == KEY_RIGHT && !update++)
		object->norm.z -= TRANSF_VALUE;
	else if (data->ctrl_key && data->lshift_key
		&& keycode == KEY_LEFT && !update++)
		object->norm.z += TRANSF_VALUE;
	else if (data->ctrl_key && keycode == KEY_RIGHT && !update++)
		object->norm.y += TRANSF_VALUE;
	else if (data->ctrl_key && keycode == KEY_LEFT && !update++)
		object->norm.y -= TRANSF_VALUE;
	else if (data->ctrl_key && keycode == KEY_UP && !update++)
		object->norm.x -= TRANSF_VALUE;
	else if (data->ctrl_key && keycode == KEY_DOWN && !update++)
		object->norm.x += TRANSF_VALUE;
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
	return (update);
}

/*
* [resize to plane object by cordition of keycode input]
* return [update = 1] : keycode input is in cordition.
* return [update = 0] : keycode input is not in cordition.
*/
// static void	resizing_key_check(t_data *data, int keycode, t_obj *object)
// {
// 	if (keycode == KEY_PLUS)
// 	{
// 		object->size.w += RESIZE_VALUE;
// 		object->size.h += RESIZE_VALUE;
// 		object->size.d += RESIZE_VALUE;

// 	}
// 	else if (keycode == KEY_MINUS)
// 	{
// 		object->size.w -= RESIZE_VALUE;
// 		object->size.h -= RESIZE_VALUE;
// 		object->size.d -= RESIZE_VALUE;
// 	}
// }

/*
* [function recompute new mtrans and itrans value of plane object]
*/
static void	plane_value_update(t_obj *object)
{
	object->mtrans = trans_homo(
			object->pos,
			vtrset(object->norm.x,
				object->norm.y,
				object->norm.z),
			vtrset(5.0, 5.0, 5.0));
	object->itrans = mtx_inverse(object->mtrans, 4);
}
