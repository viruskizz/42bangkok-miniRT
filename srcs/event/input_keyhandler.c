/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_keyhandler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:54:53 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/16 22:56:41 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// * [MODE:REAL-WORLD]
// * [MODE:SELECTION.]

void	sphere_key_transformation(t_data *data, int keycode, t_obj *object);
void	plane_key_transformation(t_data *data, int keycode ,t_obj *object);
void	camera_key_transformation(t_data *data, int keycode);

static void	selection_keyhandler(t_data *data, int keycode);
static void	revalue_camera_keyhandler(t_data *data);
static void	element_transformation_keyhandler(t_data *data, int keycode);

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
	if (keycode == KEY_RCTRL || keycode == KEY_LCTRL)
		data->ctrl_key = 1;
	if (keycode == KEY_LSHIFT)
		data->lshift_key = 1;
	if (keycode == KEY_RSHIFT)
		data->rshift_key = 1;
	if (keycode == KEY_ESC)
		rt_close(data, keycode);
	if (keycode == KEY_ENTER && data->selectp == -1)
		data->selectp = 3;
	else if (keycode == KEY_ENTER && data->selectp > -1)
		data->selectp = -1;
	if (data->rshift_key && keycode == KEY_UP)
		window_interface(data, DECREASE);
	else if (data->rshift_key && keycode == KEY_DOWN)
		window_interface(data, INCREASE);
	else if (data->selectp > -1)
		selection_keyhandler(data, keycode);
	else if (keycode == KEY_SPACE)
		revalue_camera_keyhandler(data);
	else
		element_transformation_keyhandler(data, keycode);
	window_interface(data, NONE);
	printf("ctrl_key: %d | keycode: %d\n", data->ctrl_key, keycode); 
	return (keycode);
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

static void	selection_keyhandler(t_data *data, int keycode)
{
	int	index;

	index = data->selectp;
	if (keycode == KEY_LEFT)
	{
		data->selectp = (index - 1) % 4;
		if (data->selectp < 0)
			data->selectp = 3;
	}
	else if (keycode == KEY_RIGHT)
		data->selectp = (index + 1) % 4;
	else if (keycode == KEY_UP)
		data->selectv[index] = +(data->selectv[index] + 1) % 10;
	else if (keycode == KEY_DOWN)
	{
		data->selectv[index] = (data->selectv[index] - 1) % 10;
		if (data->selectv[index] < 0)
			data->selectv[index] = 9;
	}
	else if (keycode == KEY_SPACE)
	{
		index = 0;
		while (index < 4)
			data->selectv[index++] = 0;
	}
}

static void	revalue_camera_keyhandler(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	data->cam.lookat.x = 0;
	data->cam.lookat.y = 0;
	data->cam.lookat.z = 0;
	cam_geometry(&data->cam);
	render_scene(data);
}

static void	element_transformation_keyhandler(t_data *data, int keycode)
{
	t_list	*objects;
	t_obj	*object;
	int 	count;
	int		object_id;

	count = 0;
	object_id = 0;
	mlx_clear_window(data->mlx, data->win);
	objects = data->objs;
	while (count < 4)
		object_id = (object_id * 10) + data->selectv[count++];
	if (object_id == 0)
		camera_key_transformation(data, keycode);
	else
	{
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
			plane_key_transformation(data, keycode, object);	// plane_key_transformation(data, keycode, object)
		else if (objects && object->type == CYLIND)
			printf("do cylinder tranform.\n");	// cylinder_key_transformation(data, keycode, object)
		else if (objects && object->type == CONE)
			printf("do cone tranform.\n");		// cone_key_tranformation(data, keycode, object)
		// else if (objects && object->type == LIGHT)
			// light_key_transformation(data, keycode, object)
	}
	cam_geometry(&data->cam);
	render_scene(data);
}
