/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:29:07 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/09 03:32:47 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	plane_assigned(int index, t_obj *plane, char *trimed_obj);

/*
* [function initialise and checking plane value]
* => [success] : intialize value into t_obj
* => [exit] : unsuccessful initialize value cause invalid value or character.
*/
void	plane_initialise(t_data *data, char **object)
{
	int		index;
	t_obj	*plane;
	char	*trimed_obj;

	index = 0;
	plane = object_initialise(PLANE);
	while (object[index])
	{
		if (index > 4)
			exit_error(TOO_MANY_INPUT_PL);
		trimed_obj = ft_strtrim(object[index], "\t");
		if (!trimed_obj)
			exit_error(FAIL_TRIM);
		plane_assigned(index, plane, trimed_obj);
		free(trimed_obj);
		index++;
	}
	if (index != 4)
		exit_error(TOO_LESS_INPUT_PL);
	if (!tvector_inrange(plane->norm, -1.0, 1.0))
		exit_error(INVALID_NORM_PL);
	ft_lstadd_back(&data->objs, ft_lstnew((void *)plane));
}

/*
* [helper function assigned value "pl" from a trimed_obj(char*) to t_obj]
* => return value will store in plane(t_obj), if the cordition is true.
* => exit when trimed_obj is a invalid value.
*/
static void	plane_assigned(int index, t_obj *plane, char *trimed_obj)
{
	if (index == 0 && ft_strncmp(trimed_obj, "pl", 3))
		exit_error(INVALID_IDENT_PL);
	else if (index == 1)
		plane->pos = ato_tvector(trimed_obj);
	else if (index == 2)
		plane->norm = ato_tvector(trimed_obj);
	else if (index == 3)
		plane->color = ato_tcolor(trimed_obj);
}

t_obj	*set_plain_img(t_data *data, t_obj *obj)
{
	float	x;
	float	y;
	int		color;

	obj->img.ptr = mlx_new_image(data->mlx, (int)obj->size.w, (int)obj->size.h);
	obj->img.addr = mlx_get_data_addr
		(obj->img.ptr, &obj->img.bpp, &obj->img.lh, &obj->img.endian);
	y = 0;
	while (y < obj->size.h)
	{
		x = 0;
		while (x < obj->size.w)
		{
			color = rgb_to_int(obj->color.r, obj->color.g, obj->color.b);
			pixel_put_img(&obj->img, x, y, color);
			x++;
		}
		y++;
	}
	return (obj);
}
