/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_transformation2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 02:48:46 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/22 05:08:12 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rotation_object_x(t_data *data, t_obj *object, int keycode)
{
	int	update;

	update = 0;
	if ((!data->lshift_key && data->ctrl_key && keycode == KEY_UP
			&& object->norm.z == -1 && object->norm.y > -1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_DOWN
			&& object->norm.z == 1 && object->norm.y > -1 && !update++))
		object->norm.y -= TRANSF_VALUE;
	else if ((!data->lshift_key && data->ctrl_key && keycode == KEY_UP
			&& object->norm.z < 1 && object->norm.y == -1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_DOWN
			&& object->norm.y == 1 && object->norm.z < 1 && !update++))
		object->norm.z += TRANSF_VALUE;
	else if ((!data->lshift_key && data->ctrl_key && keycode == KEY_UP
			&& object->norm.z == 1 && object->norm.y < 1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_DOWN
			&& object->norm.z == -1 && object->norm.y < 1 && !update++))
		object->norm.y += TRANSF_VALUE;
	else if ((!data->lshift_key && data->ctrl_key && keycode == KEY_UP
			&& object->norm.y == 1 && object->norm.z > -1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_DOWN
			&& object->norm.y == -1 && object->norm.z > -1 && !update++))
		object->norm.z -= TRANSF_VALUE;
	return (update);
}

int	rotation_object_y(t_data *data, t_obj *object, int keycode)
{
	int	update;

	update = 0;
	if ((!data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& object->norm.z == -1 && object->norm.x < 1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& object->norm.z == 1 && object->norm.x < 1 && !update++))
		object->norm.x += TRANSF_VALUE;
	else if ((!data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& object->norm.z < 1 && object->norm.x == 1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& object->norm.x == -1 && object->norm.z < 1 && !update++))
		object->norm.z += TRANSF_VALUE;
	else if ((!data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& object->norm.z == 1 && object->norm.x > -1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& object->norm.z == -1 && object->norm.x > -1 && !update++))
		object->norm.x -= TRANSF_VALUE;
	else if ((!data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& object->norm.x == -1 && object->norm.z > -1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& object->norm.x == 1 && object->norm.z > -1 && !update++))
		object->norm.z -= TRANSF_VALUE;
	return (update);
}

int	rotation_object_z(t_data *data, t_obj *object, int keycode)
{
	int	update;

	update = 0;
	if ((data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& object->norm.y == 1 && object->norm.x < 1 && !update++)
		|| (data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& object->norm.y == -1 && object->norm.x < 1 && !update++))
		object->norm.x += TRANSF_VALUE;
	else if ((data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& object->norm.y > -1 && object->norm.x == 1 && !update++)
		|| (data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& object->norm.x == -1 && object->norm.y < -1 && !update++))
		object->norm.y -= TRANSF_VALUE;
	else if ((data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& object->norm.y == -1 && object->norm.x > -1 && !update++)
		|| (data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& object->norm.y == 1 && object->norm.x > -1 && !update++))
		object->norm.x -= TRANSF_VALUE;
	else if ((data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& object->norm.x == -1 && object->norm.z < 1 && !update++)
		|| (data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& object->norm.x == 1 && object->norm.y < 1 && !update++))
		object->norm.y += TRANSF_VALUE;
	return (update);
}
