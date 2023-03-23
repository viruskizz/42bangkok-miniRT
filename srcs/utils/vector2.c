/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:11:52 by araiva            #+#    #+#             */
/*   Updated: 2023/03/10 00:10:31 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Set a vector attribute in 3 dimension
 * @param x value in x axis
 * @param y value in y axis
 * @param z value in z axis
 * @return t_vtr
 */
t_vtr	vtrset(float x, float y, float z)
{
	t_vtr	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

/**
 * Magnitude of vector
*/
float	vtrmag(t_vtr v)
{
	return (sqrtf(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

/**
 * normalize vector to vector in single unit
 */
t_vtr	vtrnorm(t_vtr v)
{
	float	mag;

	mag = vtrmag(v);
	return (vtrset(v.x / mag, v.y / mag, v.z / mag));
}

void	vtrprint(t_vtr v)
{
	printf("{ %f,%f,%f }\n", v.x, v.y, v.z);
}
