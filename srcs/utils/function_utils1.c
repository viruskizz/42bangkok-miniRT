/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:45:09 by sharnvon          #+#    #+#             */
/*   Updated: 2023/01/27 01:00:07 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
* [utility function print error and exit the program.]
*/
void	exit_error(char *str)
{
	printf("%s\n", str);
	exit (EXIT_FAILURE);
}

/* 
*[utility function for free char** pointer]
*/
void	free_twopointer_char(char **ptr)
{
	int	index;
	
	index = 0;
	while (ptr[index])
		free(ptr[index++]);
	free(ptr);
}

/*
* [utility function joining string "str1+str2 "and free the first argument]
* str1 -> first string
* str2 -> seccond string
*=> !NULL : new string is joined
*/
char	*ft_strjoin_pro(char *str1, char *str2)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	len;

	len = 0;
	if (str1)
		len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (!str1)
		result = (char *)ft_calloc(sizeof(char), len2 + 1);
	else
		result = (char *)ft_calloc(sizeof(char), len1 + len2 + 1);
	if (!result)
		exit_error(FAIL_ALLOC);
	if (str1)
		len = ft_strlcpy(result, str1, len1 + 1);
	ft_strlcpy(&result[len], str2, len2 +1);
	if (str1)
		free(str1);
	return (result);
}

/*
* [utility function return amount of character "c" in string "str"]
* => 0 : unfound any character "c" in string "str".
* => >0 : found and return amount of character "c" in string "str"
*/
int	character_count(char *str, char c)
{
	int index;
	int	count;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (str[index] == c)
			count++;
		index++;
	}
	return (count);
}

/*
* [utility function check value of vactor is betaween min and max ?]
* => [1] : all vactor value is in range of min and max.
* => [0] : some vactor isn't in the range of min and max.
*/
int	tvector_inrange(t_vtr vactor, double min, double max)
{
	if (vactor.x < min || vactor.x > max)
		return (0);
	if (vactor.y < min || vactor.y > max)
		return (0);
	if (vactor.z < min || vactor.z > max)
		return (0);
	return (1);
}
