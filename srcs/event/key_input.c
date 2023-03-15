/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:54:53 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/15 18:30:34 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	object_update(t_data *data, int index)
{
	t_list	*objects;
	t_obj	*object;

	objects = data->objs;
	while(objects)
	{
		object = (t_obj *)objects->content;
		if (object->idx == index)
		{
			object->mtrans = trans_homo(
				object->pos,
				vtrset(0.0, 0.0, 0.0),
				vtrset(object->size.w,
					object->size.h,
					object->size.d));
			object->itrans = mtx_inverse(object->mtrans, 4);
			break ;
		}
		objects = objects->next;
	}
}

int	keyhandler_release(int keycode, t_data *data)
{
	if (keycode == KEY_RCTRL || keycode == KEY_LCTRL)
		data->ctrl_key = 0;
	if (keycode == KEY_LSHIFT)
		data->lshift_key = 0;
	if (keycode == KEY_RSHIFT)
		data->rshift_key = 0;
	return(0);
}

void	sphere_key_transformation(t_data *data, int keycode, t_obj *object)
{
	// TODO define position_value, size_value in data.h 
	float	position_value = 0.25; // 0.04;
	float	size_value = 0.25; //0.05;

	if (data->lshift_key && keycode == KEY_UP)
	{
		// * move spherer forward.
		object->pos.z -= position_value;
	}
	else if (data->lshift_key && keycode == KEY_DOWN)
	{
		// * move phere backward.
		object->pos.z += position_value;
	}
	else if (keycode == KEY_RIGHT)
	{
		// * move sphere right.
		object->pos.x += position_value;
	}
	else if (keycode == KEY_LEFT)
	{
		// * move sphere left.
		object->pos.x -= position_value;
	}
	else if (keycode == KEY_UP)
	{
		// * move sphere up.
		object->pos.y -= position_value;
	}
	else if (keycode == KEY_DOWN)
	{
		// * move sphere down.
		object->pos.y += position_value;
	}
	else if (keycode == KEY_PLUS)
	{
		//* incrase size sphere.
		object->size.w += size_value;
		object->size.h += size_value;
		object->size.d += size_value;

	}
	else if (keycode == KEY_MINUS)
	{
		// * decread size sphere.
		object->size.w -= size_value;
		object->size.h -= size_value;
		object->size.d -= size_value;
	}
}

void	camera_key_transformation(t_data *data, int keycode)
{
	// TODO define position_value, size_value in data.h 
	float	position_value = 0.25; // 0.04;
	float	size_value = 0.25; //0.05;

	if (data->ctrl_key && data->rshift_key && keycode == KEY_RIGHT)
	{
		// * rotate camera right along z-axis.
		printf("change up?? 1\n");
		// data->cam.pos.z += 1;
	}
	else if (data->ctrl_key && data->rshift_key && keycode == KEY_LEFT)
	{
		// * rotate camera left along z-axis.
		printf("change up?? 2\n");
		// data->cam.pos.z -= 1;
	}
	else if (data->ctrl_key && keycode == KEY_RIGHT)
	{
		// * rotate camera right.
		data->cam.lookat.x += 1;
		if (data->cam.lookat.x > 180)
			data->cam.lookat.x = -180; 
		// data->cam.pos.x += position_value;
	}
	else if (data->ctrl_key && keycode == KEY_LEFT)
	{
		// * rotate camera left.
		data->cam.lookat.x -= position_value;
	}
	else if (data->ctrl_key && keycode == KEY_UP)
	{
		// * rotate camera up.
		data->cam.lookat.y -= position_value;
	}
	else if (data->ctrl_key && keycode == KEY_DOWN)
	{
		// * rotate camera down
		data->cam.lookat.y += position_value;
	}
	// *
	else if (keycode == KEY_RIGHT)
	{
		// * move camera right.
		data->cam.pos.x += position_value;
		data->cam.lookat.x += position_value;
	}
	else if (keycode == KEY_LEFT)
	{
		// * move camera left.
		data->cam.pos.x -= position_value;
		data->cam.lookat.x -= position_value;
	}
	else if (keycode == KEY_UP)
	{
		// * move camera up.
		data->cam.pos.y -= position_value;
		data->cam.lookat.y -= position_value;
	}
	else if (keycode == KEY_DOWN)
	{
		// * move camera down
		data->cam.pos.y += position_value;
		data->cam.lookat.y += position_value;
	}
	else if (keycode == KEY_PLUS)
	{
		// * move camera forward.
		data->cam.pos.z -= 1;
	}
	else if (keycode == KEY_MINUS)
	{
		// * move camera backward.
		data->cam.pos.z += 1;
	}
}

/*
* [function handler key input]
* KEY_LEFT	: object move left.
* KEY_RIGHT	: object move right.
* KEY_UP	: object move up.
* KEY_DOWN	: object move down.
* key[+]	: object move forward (zoom in).
* key[-]	: object move back (zoom out).
* KEY_LEFT + KEY_CMD	: object rotate left	(y-axis).
* KEY_RIGHT + KEY_CMD	: object rotate right	(y-axis).
* KEY_UP + KEY_CMD		: object rotate up		(x-axis).
* KEY_DOWN + KEY_CMD	: object rotate down	(x-axis).
* KEY_LEFT + KEY_SHIFT	: object rotate left 	(z-axis).
* KEY_RIGHT + KEY_SHIFT	: object roatate right	(z-axis).
* key[+] + KEY_CMD		: increase obj size.
* key[-] + KEY_CMD		: decrease move size.
*/

int	keyhandler_press(int keycode, t_data *data)
{
	// TODO define position_value, size_value in data.h 
	float	position_value = 0.04;
	float	size_value = 0.05;

	if (keycode == KEY_RCTRL || keycode == KEY_LCTRL)
		data->ctrl_key = 1;
	if (keycode == KEY_LSHIFT)
		data->lshift_key = 1;
	if (keycode == KEY_RSHIFT)
		data->rshift_key = 1;
	if (keycode == KEY_ESC)
		rt_close(data, keycode);
	// * interface key_handler.
	if (keycode == KEY_ENTER && data->selectp == -1)
	{
		data->selectp = 3;
		window_interface(data, NONE);
	}
	else if (keycode == KEY_ENTER && data->selectp > -1)
	{
		data->selectp = -1;
		window_interface(data, NONE);
	}
	if (data->rshift_key && keycode == KEY_UP)
		window_interface(data, DECREASE);
	else if (data->rshift_key && keycode == KEY_DOWN)
		window_interface(data, INCREASE);
	else if (data->selectp > -1)
	{
		if (keycode == KEY_LEFT)
		{
			data->selectp = (data->selectp - 1) % 4;
			if (data->selectp < 0)
				data->selectp = 3;
		}
		else if (keycode == KEY_RIGHT)
			data->selectp = (data->selectp + 1) % 4;
		else if (keycode == KEY_UP)
			data->selectv[data->selectp] = +(data->selectv[data->selectp] + 1) % 10;
		else if (keycode == KEY_DOWN)
		{
			data->selectv[data->selectp] = (data->selectv[data->selectp] - 1) % 10;
			if (data->selectv[data->selectp] < 0)
				data->selectv[data->selectp] = 9;
		}
		window_interface(data, NONE);
	}
	else if (keycode == KEY_SPACE)
	{
		data->cam.lookat.x = 0;
		data->cam.lookat.y = 0;
		data->cam.lookat.z = 0;
	}
	else
	{
		t_list	*objects;
		t_obj	*object;
		int 	count;
		int		object_id = 0;

		count = 0;
		mlx_clear_window(data->mlx, data->win);
		objects = data->objs;
		while (count < 4)
			object_id = (object_id * 10) + data->selectv[count++];
		printf("object_id: %d | count: %d\n", object_id, count);
		if (object_id == 0)
			camera_key_transformation(data, keycode);
		else
		{
			// * do_object_thing.
			while (objects)
			{
				object = (t_obj *)objects->content;
				if (object->idx == object_id)
					break ;
				objects = objects->next;
			}
			if (objects && object->type == SPHERE)
				sphere_key_transformation(data, keycode, object);
			else if (objects && object->type == PLANE)
				printf("do plane transform.\n");
			else if (objects && object->type == CYLIND)
				printf("do cylinder tranform.\n");
			else if (objects && object->type == CONE)
				printf("do cone tranform.\n");
		}
		if (object_id > 0)
			object_update(data, object->idx);
		window_interface(data, NONE);
	}
	cam_geometry(&data->cam);
	render_scene(data);
	printf("ctrl_key: %d | keycode: %d\n", data->ctrl_key, keycode); 
	return (1);
}

/*
* camera prptotype.
*/
// else if (data->hold_key && keycode == KEY_RIGHT)
	// 	data->cam.pos.x -= value;
	// else if (data->hold_key && keycode == KEY_LEFT)
	// 	data->cam.pos.x += value;
	// else if (data->hold_key && keycode == KEY_UP)
	// 	data->cam.pos.y += value;
	// else if (data->hold_key && keycode == KEY_DOWN)
	// 	data->cam.pos.y -= value;
	// else if (data->hold_key && keycode == 24)
	// 	data->cam.pos.z += value;
	// else if (data->hold_key && keycode == 27)
	// 	data->cam.pos.z -= value;
	// else if (!data->hold_key && keycode == KEY_UP)
	// {
	// 	data->cam.lookat.y -= 1;
	// 	cam_geometry(&data->cam);
	// }
	// else if (!data->hold_key && keycode == KEY_DOWN)
	// {
	// 	data->cam.lookat.y += value + 1;
	// 	cam_geometry(&data->cam);
	// }
	// else if (!data->hold_key && keycode == KEY_RIGHT)
	// {
	// 	data->cam.lookat.x -= value + 1;
	// 	cam_geometry(&data->cam);
	// }
	// else if (!data->hold_key && keycode == KEY_LEFT)
	// {
	// 	data->cam.lookat.x += value + 1;
	// 	cam_geometry(&data->cam);
	// }