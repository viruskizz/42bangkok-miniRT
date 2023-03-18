/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_keyhandler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:54:53 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/19 05:41:53 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// * [MODE:REAL-WORLD]
// * [MODE:SELECTION.]

int			sphere_key_transf(t_data *data, int keycode, t_obj *object);
int			plane_key_transf(t_data *data, int keycode, t_obj *object);
int			light_key_transf(t_data *data, int keycode, t_obj *object);
int			camera_key_transformation(t_data *data, int keycode);
void		revalue_camera_keyhandler(t_data *data);
static void	selection_keyhandler(t_data *data, int keycode);
static void	element_transformation_keyhandler(t_data *data, int keycode);
static void	objects_key_transformation(t_data *data, int id, int keycode);

/*
* [function key press handler]
* ========================= general ========================= 
* [rshift] + [down] : go next page of list objects
* [rshift] + [up] : go back to previous page of list objects
* [esc] : quit the program
* [space] : revalue of camera rotation to 0 (lookat)
* [esc] : quit the program
* ========================= selection mode =========================
* (selected [0000] is always camera)
* [enter] : go to selection mode and repress to finish selecting the object.
* [up] : increase index value of selecting
* [down] : decrease index value of selecting
* [right] : move selecting digit to right
* [left] : move selecting digit to left
* [space] : revalue index of seclecting to [0000]
* ========================= moving ========================= 
* [up] : move object up (increase position [pos.y] value)
* [down] : move object down (decrease position [pos.y] value)
* [right] : move object right (increase position [pos.x] value)
* [left] : move object right (decrease position [pos.x] value)
* [lshif] + [up] : move object forward (increase position [pos.z] value)
* [lshif] + [down] : move object forward (decrease position [pos.z] value)
* ========================= rotating ========================= 
* [ctrl] + [up] : rotate object up along x axis (increase [norm.x] value)
* [ctrl] + [down] : rotate object down along x axis (decrease [norm.x] value)
* [ctrl] + [right] : rotate object right along y axis (increase [norm.y] value)
* [ctrl] + [left] : rotate object down  along y axis (decrease [norm.y] value)
* [lshift] + [ctrl] + [right] : rotate object along z axis (increase [norm.z])
* [lshift] + [ctrl] + [left] : rotate object along z axis (decrease [norm.z])
* ========================= resizing ========================= 
* [+] : increase size object (increase size[size.w, size.h, size.d] value)
* [-] : decrease size object (decrease size[size.w, size.h, size.d] value)
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
	else if (keycode == KEY_SPACE && !data->update)
		revalue_camera_keyhandler(data);
	else if (!data->update)
		element_transformation_keyhandler(data, keycode);
	return (window_interface(data, NONE));
}

/*
* [fucntion key relesase]
*/
int	keyhandler_release(int keycode, t_data *data)
{
	if (keycode == KEY_RCTRL || keycode == KEY_LCTRL)
		data->ctrl_key = 0;
	if (keycode == KEY_LSHIFT)
		data->lshift_key = 0;
	if (keycode == KEY_RSHIFT)
		data->rshift_key = 0;
	return (keycode);
}

/*
* [function change position and value in selection mode]
*/
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

/*
* [function apply tranmation to objecte]
* [apple transformation value to object then clear window and rerender scene]
*/
static void	element_transformation_keyhandler(t_data *data, int keycode)
{
	int		count;
	int		object_id;

	count = 0;
	object_id = 0;
	while (count < 4)
		object_id = (object_id * 10) + data->selectv[count++];
	if (object_id == 0)
		camera_key_transformation(data, keycode);
	else
		objects_key_transformation(data, object_id, keycode);
}

/*
* [helper function of element_transformation_keyhandler]
* [find index of object andchecking type of object then apply ransformation]
*/
static void	objects_key_transformation(t_data *data, int id, int keycode)
{
	t_list	*objects;
	int		next;

	next = 1;
	objects = data->lht;
	while (objects)
	{
		if (((t_obj *)objects->content)->idx == id)
			break ;
		objects = objects->next;
		if (objects == NULL && next-- == 1)
			objects = data->objs;
	}
	if (objects && ((t_obj *)objects->content)->type == SPHERE)
		sphere_key_transf(data, keycode, (t_obj *)objects->content);
	else if (objects && ((t_obj *)objects->content)->type == PLANE)
		plane_key_transf(data, keycode, (t_obj *)objects->content);	// plane_key_transf(data, keycode, object)
	else if (objects && ((t_obj *)objects->content)->type == CYLIND)
		printf("do cylinder tranform.\n");	// cylinder_key_transf(data, keycode, object)
	else if (objects && ((t_obj *)objects->content)->type == CONE)
		printf("do cone tranform.\n");		// cone_key_tranf(data, keycode, object)
	else if (objects && ((t_obj *)objects->content)->type == LIGHT)
		light_key_transf(data, keycode, (t_obj *)objects->content);
}
