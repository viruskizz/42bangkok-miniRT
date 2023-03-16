/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_key_transformation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:01:48 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/17 05:46:07 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	plane_value_update(t_obj *object);
static int	rotation_key_check(t_data *data, int keycode, t_obj *object);
static int	moving_key_check(t_data *data, int keycode, t_obj *object);
// static void	resizing_key_check(t_data *data, int keycode, t_obj *object);

int	plane_key_transformation(t_data *data, int keycode ,t_obj *object)
{
	int	update;

	update = 0;
	if (!rotation_key_check(data, keycode, object))
	{
		if (!moving_key_check(data, keycode, object))
			return (0);
			// resizing_key_check(data, keycode, object);
	}
	plane_value_update(object);
	return (1);
}

static int	rotation_key_check(t_data *data, int keycode, t_obj *object)
{
	int	update;

	update = 0;
	if (data->ctrl_key && data->lshift_key && keycode == KEY_RIGHT && !update++)
		object->norm.z -= TRANSF_VALUE;
	else if (data->ctrl_key && data->lshift_key && keycode == KEY_LEFT && !update++)
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

static void	plane_value_update(t_obj *object)
{
	object->mtrans = trans_homo(
		object->pos,
		vtrset(object->norm.x, object->norm.y, object->norm.z),
		vtrset(5.0, 5.0, 5.0));
	object->itrans = mtx_inverse(object->mtrans, 4);
	object->colorf = color_to_colorf(object->color);
}
