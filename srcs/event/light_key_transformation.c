/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_key_transformation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 03:45:27 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/19 03:29:19 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
* [function apply transformation to light with keycode input]
* ========================= moving ========================= 
* [up] : move object up (increase position [pos.y] value)
* [down] : move object down (decrease position [pos.y] value)
* [right] : move object right (increase position [pos.x] value)
* [left] : move object right (decrease position [pos.x] value)
* [lshif] + [up] : move object forward (increase position [pos.z] value)
* [lshif] + [down] : move object forward (decrease position [pos.z] value)
* return [1] : keycode is in cordition and some value was changed.
* return [0] : keycode is not in cordition.
*/
void	light_key_transf(t_data *data, int keycode, t_obj *object)
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
	data->update = update;
}
