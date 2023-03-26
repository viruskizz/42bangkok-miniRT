/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_key_transformation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:45:52 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/26 05:41:45 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	moving_key_check(t_data *data, int keycode);
int			camera_rotation_z(t_data *data, int keycode);
int			camera_rotation_x(t_data *data, int keycode);
int			camera_rotation_y(t_data *data, int keycode);

void	camera_key_transformation(t_data *data, int keycode)
{
	if (!camera_rotation_z(data, keycode))
	{
		if (!camera_rotation_y(data, keycode))
		{
			if (!camera_rotation_x(data, keycode))
			{
				if (!moving_key_check(data, keycode))
					return ;
			}
		}
	}
	data->update = 1;
}

static int	moving_key_check(t_data *data, int keycode)
{
	int	update;

	update = 0;
	if (data->lshift_key && !data->ctrl_key
		&& keycode == KEY_UP && !update++)
		data->cam.pos.z -= 1;
	else if (data->lshift_key && !data->ctrl_key
		&& keycode == KEY_DOWN && !update++)
		data->cam.pos.z += 1;
	else if (!data->lshift_key && !data->ctrl_key
		&& keycode == KEY_RIGHT && !update++)
		data->cam.pos.x += TRANSF_VALUE;
	else if (!data->lshift_key && !data->ctrl_key
		&& keycode == KEY_LEFT && !update++)
		data->cam.pos.x -= TRANSF_VALUE;
	else if (!data->lshift_key && !data->ctrl_key
		&& keycode == KEY_UP && !update++)
		data->cam.pos.y -= TRANSF_VALUE;
	else if (!data->lshift_key && !data->ctrl_key
		&& keycode == KEY_DOWN && !update++)
		data->cam.pos.y += TRANSF_VALUE;
	return (update);
}
