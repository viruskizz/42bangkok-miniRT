/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_interface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 02:28:50 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/16 02:41:09 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char *get_string_postion_value(t_obj *object, int count);

/*
* [helper function of put_elements_to_window]
* [put diameter and height of elements to window]
*/
int	put_size_to_window(t_data *data, t_obj *object, int line)
{
	char	*pointer1;
	char	*pointer2;
	int		colour;

	colour = color_to_int(ato_tcolor("244,244,244"));
	pointer2 = ft_floattoa(object->size.h);
	if (object->type != PLANE)
		pointer1 = ft_strjoin("|HEIGHT:   ", pointer2);
	else
		pointer1 = ft_strjoin("|HEIGHT:   NON", "E");
	free(pointer2);
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, pointer1);
	free(pointer1);
	line += 11;
	pointer2 = ft_floattoa(object->size.w);
	if (object->type != PLANE)
		pointer1 = ft_strjoin("|DIAMETER: ", pointer2);
	else
		pointer1 = ft_strjoin("|DIAMETER: NON", "E");
	free(pointer2);
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, pointer1);
	free(pointer1);
	return (line += 17);
}

/*
* [helper function of put_object_to_window]
* INDEX mode : cordition of index, add 0 to index until get 4 digit [0000].
* TYPE mode : cordition of type, join string with object's type.
*/
static char	*object_cordition_str(t_obj *object, char *string, int mode)
{
	if (mode == INDEX)
	{
		if (object->idx < 10)
			return (ft_strjoin("[000", string));
		else if (object->idx < 100)
			return (ft_strjoin("[00", string));
		else if (object->idx < 1000)
			return (ft_strjoin("[0", string));
		else
			return (ft_strjoin("[", string));
	}
	else if (mode == TYPE)
	{
		if (object->type == SPHERE)
			return (ft_strjoin("|[ ]SPHERE", string));
		else if (object->type == PLANE)
			return (ft_strjoin("|[ ]PLANE", string));
		else if (object->type == CYLIND)
			return (ft_strjoin("|[ ]CYINDER", string));
		else if (object->type == CONE)
			return (ft_strjoin("|[ ]CONE", string));
	}
	return (NULL);
}

/*
* [helper function of put_elements_to_window]
* [put type and index of elements to window]
*/
int	put_object_to_window(t_data *data, t_obj *object, int line)
{
	char	*pointer1;
	char	*pointer2;
	int		colour;

	colour = rgb_to_int(244, 244, 244);
	pointer1 = ft_itoa(object->idx);
	pointer2 = object_cordition_str(object, pointer1, INDEX);
	if (!pointer2)
		exit_error(FAIL_ALLOC);
	free(pointer1);
	pointer1 = object_cordition_str(object, pointer2, TYPE);
	if (!pointer1)
		exit_error(FAIL_ALLOC);
	free(pointer2);
	pointer2 = ft_strjoin(pointer1, "]");
	free(pointer1);
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, pointer2);
	free(pointer2);
	return (line + 11);
}

/*
* [helper function of put_elements_to_window]
* [put coordinates of elements to window]
*/
int	put_coordinates_to_window(t_data *data, t_obj *object, int line)
{
	char	*pointer1;
	char	*pointer2;
	char	*pointer3;
	int		count;

	count = 0;
	mlx_string_put(data->mlx, data->win, WIDTH, line, 0xE0E0E0, "|COORDINATES:");
	while (count < 3)
	{
		line += 11;
		pointer1 = get_string_postion_value(object, count);
		pointer2 = ft_strjoin(pointer1, "]");
		free(pointer1);
		mlx_string_put(data->mlx, data->win, WIDTH, line, 0xE0E0E0, pointer2);
		free(pointer2);
		count++;
	}
	return (line + 11);
}

static char *get_string_postion_value(t_obj *object, int count)
{
	char	*pointer1;
	char	*pointer2;

	if (count == 0)
	{
		pointer2 = ft_floattoa(object->pos.x);
		pointer1 = ft_strjoin("||X-[", pointer2);
	}
	else if (count == 1)
	{
		pointer2 = ft_floattoa(object->pos.y);
		pointer1 = ft_strjoin("||Y-[", pointer2);
	}
	else
	{
		pointer2 = ft_floattoa(object->pos.z);
		pointer1 = ft_strjoin("||Z-[", pointer2);
	}
	free(pointer2);
	return (pointer1);
}

/*
* [helper function of put_elements_to_window]
* [put none elements to window]
*/
static int	put_none_to_window(t_data *data, int line)
{
	int colour;

	colour = rgb_to_int(255, 255, 255);
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, "|[X]NONE[NONE]");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, "|COORDINATES:");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, "||X-[NONE]");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, "||Y-[NONE]");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, "||Z-[NONE]");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, "|HEIGHT:   NONE");
	line += 11;
	mlx_string_put(data->mlx, data->win, WIDTH, line, colour, "|DIAMETER: NONE");
	line += 17;
	return (line);
}

/*
* [function put elements identifier from data to window by put_string]
* line will start at 40.
* each line for a chracter is 11.
*/
void	put_elements_to_window(t_data *data, t_list *objects)
{
	int		count;
	t_obj	*object;
	int		line;

	count = 0;
	line = 40;
	mlx_string_put(data->mlx, data->win, WIDTH + 1, 18,
		 0xE0E0E0, "[ELEMENTS-IDENTIFIER]");
	while (count < 5)
	{
		if (objects)
		{
			object = objects->content;
			line = put_object_to_window(data, object, line);
			line = put_coordinates_to_window(data, object, line);
			line = put_size_to_window(data, object, line);
			objects = objects->next;
		}
		else
			line = put_none_to_window(data, line);
		count++;
	}
}