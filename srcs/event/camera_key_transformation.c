/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_key_transformation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:45:52 by sharnvon          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/26 05:41:45 by sharnvon         ###   ########.fr       */
=======
/*   Updated: 2023/03/22 02:46:40 by sharnvon         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	moving_key_check(t_data *data, int keycode);
<<<<<<< HEAD
int			camera_rotation_z(t_data *data, int keycode);
int			camera_rotation_x(t_data *data, int keycode);
int			camera_rotation_y(t_data *data, int keycode);
=======
static int	camera_rotation_z(t_data *data, int keycode);
static int	camera_rotation_x(t_data *data, int keycode);
static int	camera_rotation_y(t_data *data, int keycode);
>>>>>>> main

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

<<<<<<< HEAD
=======
static int	camera_rotation_z(t_data *data, int keycode)
{
	int	update;

	update = 0;
	if ((data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& data->cam.norm.y == 1 && data->cam.norm.x < 1 && !update++)
		|| (data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& data->cam.norm.y == -1 && data->cam.norm.x < 1 && !update++))
		data->cam.norm.x += TRANSF_VALUE;
	else if ((data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& data->cam.norm.y > -1 && data->cam.norm.x == 1 && !update++)
		|| (data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& data->cam.norm.x == -1 && data->cam.norm.y < -1 && !update++))
		data->cam.norm.y -= TRANSF_VALUE;
	else if ((data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& data->cam.norm.y == -1 && data->cam.norm.x > -1 && !update++)
		|| (data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& data->cam.norm.y == 1 && data->cam.norm.x > -1 && !update++))
		data->cam.norm.x -= TRANSF_VALUE;
	else if ((data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& data->cam.norm.x == -1 && data->cam.norm.z < 1 && !update++)
		|| (data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& data->cam.norm.x == 1 && data->cam.norm.y < 1 && !update++))
		data->cam.norm.y += TRANSF_VALUE;
	return (update);
}

static int	camera_rotation_y(t_data *data, int keycode)
{
	int	update;

	update = 0;
	if ((!data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& data->cam.norm.z == -1 && data->cam.norm.x < 1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& data->cam.norm.z == 1 && data->cam.norm.x < 1 && !update++))
		data->cam.norm.x += TRANSF_VALUE;
	else if ((!data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& data->cam.norm.z < 1 && data->cam.norm.x == 1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& data->cam.norm.x == -1 && data->cam.norm.z < 1 && !update++))
		data->cam.norm.z += TRANSF_VALUE;
	else if ((!data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& data->cam.norm.z == 1 && data->cam.norm.x > -1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& data->cam.norm.z == -1 && data->cam.norm.x > -1 && !update++))
		data->cam.norm.x -= TRANSF_VALUE;
	else if ((!data->lshift_key && data->ctrl_key && keycode == KEY_RIGHT
			&& data->cam.norm.x == -1 && data->cam.norm.z > -1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_LEFT
			&& data->cam.norm.x == 1 && data->cam.norm.z > -1 && !update++))
		data->cam.norm.z -= TRANSF_VALUE;
	return (update);
}

static int	camera_rotation_x(t_data *data, int keycode)
{
	int	update;

	update = 0;
	if ((!data->lshift_key && data->ctrl_key && keycode == KEY_UP
			&& data->cam.norm.z == -1 && data->cam.norm.y > -1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_DOWN
			&& data->cam.norm.z == 1 && data->cam.norm.y > -1 && !update++))
		data->cam.norm.y -= TRANSF_VALUE;
	else if ((!data->lshift_key && data->ctrl_key && keycode == KEY_UP
			&& data->cam.norm.z < 1 && data->cam.norm.y == -1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_DOWN
			&& data->cam.norm.y == 1 && data->cam.norm.z < 1 && !update++))
		data->cam.norm.z += TRANSF_VALUE;
	else if ((!data->lshift_key && data->ctrl_key && keycode == KEY_UP
			&& data->cam.norm.z == 1 && data->cam.norm.y < 1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_DOWN
			&& data->cam.norm.z == -1 && data->cam.norm.y < 1 && !update++))
		data->cam.norm.y += TRANSF_VALUE;
	else if ((!data->lshift_key && data->ctrl_key && keycode == KEY_UP
			&& data->cam.norm.y == 1 && data->cam.norm.z > -1 && !update++)
		|| (!data->lshift_key && data->ctrl_key && keycode == KEY_DOWN
			&& data->cam.norm.y == -1 && data->cam.norm.z > -1 && !update++))
			data->cam.norm.z -= TRANSF_VALUE;
	return (update);
}

>>>>>>> main
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
