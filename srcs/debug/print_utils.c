/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:31:36 by sharnvon          #+#    #+#             */
/*   Updated: 2023/03/12 00:33:56 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
* [debuging function printing char** value]
*/
void	print_twoarray_char(char **str)
{
	printf("======= [print_twoarray_char] =======\n");
	for (int i = 0; str[i]; i++)
		printf("[%d]:|%s|\n", i, str[i]);
	printf("=====================================\n");
}

/*
* [debuging function printing t_vtr value]
*/
void	print_tvector(t_vtr vector)
{
	printf("========== [print_tvector] ==========\n");
	printf("• x: |%.2f|\n• y: |%.2f|\n• z: |%.2f|\n", vector.x, vector.y, vector.z);
	printf("=====================================\n");
}

/*
* [debuging function printing t_color value]
*/
void	print_tcolor(t_color color)
{
	printf("========== [print_tcolor] ==========\n");
	printf("• r: |%d|\n• g: |%d|\n• b: |%d|\n", color.r, color.g, color.b);
	printf("====================================\n");
}

/*
* [debuging function printing t_size value]
*/
void	print_tsize(t_size size)
{
	printf("========== [print_tsize] ==========\n");
	printf("• w: |%.2f|\n• h: |%.2f|\n• d: |%.2f|\n", size.w, size.h, size.d);
	printf("====================================\n");
}

/*
* [debuging function printing t_amb value]
*/
void	print_tambient(t_amb ambient)
{
	printf("========== [print_tambient ==========\n");
	printf("• ratio : |%.2f|\n• color.r: |%d|\n• color.g: |%d|\n• color.b: |%d|\n", ambient.ratio, ambient.color.r, ambient.color.g,ambient.color.b);
	printf("=====================================\n");
}

/*
* [debuging function printing t_cam value]
*/
void	print_tcamara(t_cam camara)
{
	printf("========== [print_tcamara ==========\n");
	printf("• pos.x : |%.2f|\n• pos.y : |%.2f|\n• pos.z : |%.2f|\n• norm.x: |%.2f|\n• norm.y: |%.2f|\n• norm.z: |%.2f|\n• fov   : |%.d|\n"
		,camara.pos.x, camara.pos.y, camara.pos.z, camara.norm.x, camara.norm.y, camara.norm.z, camara.fov);
	printf("=====================================\n");
}

/*
* debuging function printing t_obj value
*/
void	print_tobject(t_obj *object)
{
	printf("========== [print_tobject] ==========\n");
	printf("• idx    : |%d|\n", object->idx);
	printf("• type   : |%d|\n", object->type);
	printf("• name   : |%s|\n", object->name);
	printf("• pos.x  : |%.2f|\n", object->pos.x);
	printf("• pos.y  : |%.2f|\n", object->pos.y);
	printf("• pos.z  : |%.2f|\n", object->pos.z);
	printf("• norm.x : |%.2f|\n", object->norm.x);
	printf("• norm.y : |%.2f|\n", object->norm.y);
	printf("• norm.z : |%.2f|\n", object->norm.z);
	printf("• color.r: |%d|\n", object->color.r);
	printf("• color.g: |%d|\n", object->color.g);
	printf("• color.b: |%d|\n", object->color.b);
	printf("• size.w : |%.2f|\n", object->size.w);
	printf("• size.h : |%.2f|\n", object->size.h);
	printf("• size.d : |%.2f|\n", object->size.d);
	printf("====================================\n");
}