/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_key_transfromation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:00:29 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/19 03:21:46 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	resizing_key_check(t_obj *object, int keycode);
static void	sphere_value_update(t_obj *object);

/*
* [function apply transformation to sphere with keycode input]
* ========================= moving ========================= 
* [up] : move object up (increase position [pos.y] value)
* [down] : move object down (decrease position [pos.y] value)
* [right] : move object right (increase position [pos.x] value)
* [left] : move object right (decrease position [pos.x] value)
* [lshif] + [up] : move object forward (increase position [pos.z] value)
* [lshif] + [down] : move object forward (decrease position [pos.z] value)
* ========================= resizing ========================= 
* [+] : increase size object (increase size[size.w, size.h, size.d] value)
* [-] : decrease size object (decrease size[size.w, size.h, size.d] value)
* return [1] : keycode is in cordition and some value was changed.
* return [0] : keycode is not in cordition.
*/
void	sphere_key_transf(t_data *data, int keycode, t_obj *object)
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
	if (!update)
		update = resizing_key_check(object, keycode);
	sphere_value_update(object);
	data->update = update;
}

/*
* [resize to sphere object by cordition of keycode input]
* return [update = 1] : keycode input is in cordition.
* return [update = 0] : keycode input is not in cordition.
*/
static int	resizing_key_check(t_obj *object, int keycode)
{
	int	update;

	update = 0;
	if (keycode == KEY_PLUS && !update++)
	{
		object->size.w += RESIZE_VALUE;
		object->size.h += RESIZE_VALUE;
		object->size.d += RESIZE_VALUE;
	}
	else if (keycode == KEY_MINUS && !update++)
	{
		object->size.w -= RESIZE_VALUE;
		object->size.h -= RESIZE_VALUE;
		object->size.d -= RESIZE_VALUE;
	}
	return (update);
}

/*
* [function recompute new mtrans and itrans value of sphere object]
*/
static void	sphere_value_update(t_obj *object)
{	
	object->mtrans = trans_homo(
			object->pos,
			vtrset(0.0, 0.0, 0.0),
			vtrset(object->size.w,
				object->size.h,
				object->size.d));
	object->itrans = mtx_inverse(object->mtrans, 4);
}
