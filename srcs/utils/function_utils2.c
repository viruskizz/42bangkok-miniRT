/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:49:47 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/15 22:38:57 by sharnvon         ###   ########.fr       */
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

/*
* [utility function converting float point number to string]
* => [success] : return string that convert from float ponint number with 2 decimal.
* => [exit] : fail allocate form ft_strjoin / ft_itoa.
*/
char	*ft_floattoa(float number)
{
	char	*pointer1;
	char	*pointer2;
	char	*pointer3;
	float	whole_number;
	int		result;
	
	result = 0;
	whole_number = (int)number;
	pointer3 = ft_itoa((int)number);
	if (!pointer3)
		exit_error(FAIL_ALLOC);
	pointer1 = ft_strjoin(pointer3, ".");
	free(pointer3);
	if (!pointer1)
		exit_error(FAIL_ALLOC);
	result = (number - whole_number) * 100;
	if (result < 0)
		result *= -1;
	pointer3 = ft_itoa(result);
	if (!pointer3)
		exit_error(FAIL_ALLOC);
	pointer2 = ft_strjoin_pro(pointer1, pointer3);
	return (pointer2);
}