/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:49:47 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/09 03:33:57 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
* [utility function initialise value of t_size and return]
* => [success] : return the t_size wiht value height, width, depth.
* => [exit] : unsuccessful innitialise value cause invalid value or charactor.
*/
t_size	size_initialise(float height, float width, float depth)
{
	t_size	size;

	if (height < 0.0)
		exit_error("minirt: ERROR::invalid height value.\n" \
			"(hint) • the object height must be positive number.\n");
	if (width < 0.0)
		exit_error("minirt: ERROR::invalid width value.\n" \
			"(hint) •the object diameter must be positive number.\n");
	if (depth < 0.0)
		exit_error("minirt: ERROR::invalid depth value.\n" \
			"(hint) •the object diameter must be positive number.\n");
	size.d = depth;
	size.w = width;
	size.h = height;
	return (size);
}
