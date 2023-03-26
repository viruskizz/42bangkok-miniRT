/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:49:47 by sharnvon          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/26 06:51:46 by sharnvon         ###   ########.fr       */
=======
/*   Updated: 2023/03/22 04:53:58 by sharnvon         ###   ########.fr       */
>>>>>>> main
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
		exit_error("ERROR::invalid height value.\n" \
			"(hint) • the object height must be positive number.");
	if (width < 0.0)
		exit_error("ERROR::invalid width value.\n" \
			"(hint) •the object diameter must be positive number.");
	if (depth < 0.0)
		exit_error("ERROR::invalid depth value.\n" \
			"(hint) •the object diameter must be positive number.");
	size.d = depth;
	size.w = width;
	size.h = height;
	return (size);
}

/*
* [utility function converting float point number to string]
* => [success] : return converted str from float ponint number with 2 decimal.
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
	if (number > -1.0f && number < 0.0f)
	{
		pointer2 = ft_strjoin("-", pointer3);
		free(pointer3);
		pointer3 = pointer2;
	}
	pointer1 = ft_strjoin(pointer3, ".");
	free(pointer3);
	result = (number - whole_number) * 100;
	if (result < 0)
		result *= -1;
	pointer3 = ft_itoa(result);
	pointer2 = ft_strjoin_pro(pointer1, pointer3);
<<<<<<< HEAD
	free(pointer3);
=======
>>>>>>> main
	return (pointer2);
}
