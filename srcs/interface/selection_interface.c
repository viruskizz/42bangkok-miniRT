/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_interface.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:36:37 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/16 02:43:33 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*selected_object_string(t_data *data);
static char	*selecting_object_string(t_data *data);
static char	*selecting_value_string(t_data *data, char *pointer1, int count);

/*
* [function put string of selection status to selection interface on window]
* => status[selected] : SELECTED:[0000][ ].
* => status[selecting] : SELECTIN:000[0][ ].
* on selecting, [0] position is depend on data->selectp value.
*/
void	selection_to_window(t_data *data)
{
	char	*string;
	int		colour;
	int		x;
	int		y;

	x = WIDTH + 5;
	y = HEIGHT - 13;
	if (data->selectp < 0)
	{
		colour = rgb_to_int(160, 160, 160);
		string = selected_object_string(data);
	}
	else
	{
		colour = rgb_to_int(224, 224, 224);
		string = selecting_object_string(data);
		// // * selectv = position to add []
		// count = 0;
		// pointer2 = ft_itoa(data->selectv[count++]);
		// if (data->selectp == 0)
		// {
		// 	pointer1 = ft_strjoin("[SELECTIN]:[", pointer2);
		// 	pointer3 = ft_strjoin(pointer1, "]");
		// 	free(pointer1);
		// 	pointer1 = pointer3;
		// }
		// else
		// 	pointer1 = ft_strjoin("[SELECTIN]:", pointer2);
		// free(pointer2);
		// while (count < 4)
		// {
		// 	pointer3 = ft_itoa(data->selectv[count++]);
		// 	if (data->selectp == count - 1)
		// 	{
		// 		pointer2 = ft_strjoin(pointer1, "[");
		// 		free(pointer1);
		// 		pointer1 = ft_strjoin_pro(pointer2, pointer3);
		// 		pointer2 = ft_strjoin(pointer1, "]");
		// 		free(pointer1);
		// 	}
		// 	else
		// 		pointer2 =ft_strjoin_pro(pointer1, pointer3);
		// 	pointer1 = pointer2;
		// }
		// pointer2 = ft_strjoin(pointer1, "[ ]");
		// free(pointer1);
		// pointer1 = pointer2;
	}
	mlx_string_put(data->mlx, data->win, x, y, colour, string);
	free(string);
}

/*
* [helper function of selecting_object_string]
* [arrangement string of selected status]
* => return : string of selected status.
* => exit : fail allocate in ft_itoa.
*/
static char	*selected_object_string(t_data *data)
{
	int		count;
	char	*pointer1;
	char	*pointer2;
	char	*pointer3;

	count = 0;
	pointer2 = ft_itoa(data->selectv[count++]);
	if (!pointer2)
		exit_error(FAIL_ALLOC);
	pointer1 = ft_strjoin("[SELECTED]:[", pointer2);
	free(pointer2);
	while (count < 4)
	{
		pointer3 = ft_itoa(data->selectv[count++]);
		if (!pointer3)
			exit_error(FAIL_ALLOC);
		pointer2 = ft_strjoin_pro(pointer1, pointer3);
		pointer1 = pointer2;
	}
	pointer2 = ft_strjoin(pointer1, "][ ]");
	free(pointer1);
	return (pointer2);
}

/*
* [helper function of selecting_object_string]
* [arrangement string of selecting status]
* => return : string of selecting status.
* => exit : fail allocate in ft_itoa.
*/
static char	*selecting_object_string(t_data *data)
{
	int		count;
	char	*pointer1;
	char	*pointer2;
	char	*pointer3;

	count = 0;
	pointer2 = ft_itoa(data->selectv[count++]);
	if (data->selectp == 0)
	{
		pointer3 = ft_strjoin("[SELECTIN]:[", pointer2);
		pointer1 = ft_strjoin(pointer3, "]");
		free(pointer3);
	}
	else
		pointer1 = ft_strjoin("[SELECTIN]:", pointer2);
	free(pointer2);
	while (count < 4)
	{
		pointer1 = selecting_value_string(data, pointer1, count);
		count++;
	}
	pointer2 = ft_strjoin(pointer1, "[ ]");
	free(pointer1);
	return (pointer2);
}

/*
* [helper function of selecting_object_string]
* [arrangement string of selecting value and return]
* => [return] : string of selection value that will put onto window.
*/
static char	*selecting_value_string(t_data *data, char *pointer1, int count)
{
	char	*pointer2;
	char	*pointer3;

	pointer3 = ft_itoa(data->selectv[count++]);
	if (data->selectp == count - 1)
	{
		pointer2 = ft_strjoin(pointer1, "[");
		free(pointer1);
		pointer1 = ft_strjoin_pro(pointer2, pointer3);
		pointer2 = ft_strjoin(pointer1, "]");
		free(pointer1);
	}
	else
		pointer2 = ft_strjoin_pro(pointer1, pointer3);
	return (pointer2);
}
