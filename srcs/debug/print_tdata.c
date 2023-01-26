/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tdata.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:30:37 by sharnvon          #+#    #+#             */
/*   Updated: 2023/01/26 15:30:50 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_tdata(t_data *data)
{
	t_list	*head;
	t_lht	*light;
	t_obj	*object;
	int		index;
	int		sphere = 0, plane = 0, cylinder = 0;

	//* ambient light
	printf("%s================== [ambient light] ====================\n", YELLOW);
	printf("%s|%s • amb-ratio : %.2f\n", YELLOW, GREEN, data->amb.ratio);
	printf("%s|%s • color     : r[%d],g[%d],b[%d]\n", YELLOW, GREEN, data->amb.color.r, data->amb.color.g, data->amb.color.b);
	// *camara
	printf("%s===================== [camara] ========================\n", YELLOW);
	printf("%s|%s • coordinate: x[%.2f],y[%.2f],z[%.2f]\n", YELLOW, GREEN, data->cam.pos.x, data->cam.pos.y, data->cam.pos.z);
	printf("%s|%s • normalize : x[%.2f],y[%.2f],z[%.2f]\n", YELLOW, GREEN, data->cam.norm.x, data->cam.norm.y, data->cam.norm.z);
	printf("%s|%s • fov degree: %d\n", YELLOW, GREEN, data->cam.fov);
	// * light
	head = data->lht;
	index = 1;
	while(head != NULL)
	{
		light = (t_lht *)head->content;
		printf("%s====================== [light %d] ======================\n", YELLOW, index++);
		printf("%s|%s • coordinete: x[%.2f],y[%.2f],z[%.2f]\n", YELLOW, GREEN, light->pos.x, light->pos.y, light->pos.z);
		printf("%s|%s • brightness: %.2f\n", YELLOW, GREEN, light->bright);
		printf("%s|%s • color     : r[%d],g[%d],b[%d]\n", YELLOW, GREEN, light->color.r, light->color.g, light->color.b);
		head = head->next;
	}
	// * object
	head = data->objs;
	index = 1;
	while(head != NULL)
	{
		object = (t_obj *)head->content;
		if (object->type == SPHERE)
		{
			printf("%s================= [object %d][sphere] ==================\n", YELLOW, index++);
			printf("|%s • index     : %d\n", GREEN, object->idx);
			printf("%s|%s • type      : %d\n", YELLOW, GREEN, object->type);
			printf("%s|%s • name      : %s\n", YELLOW, GREEN, object->name);
			printf("%s|%s • coordinete: x[%.2f],y[%.2f],z[%.2f]\n", YELLOW, GREEN, object->pos.x, object->pos.y, object->pos.z);
			printf("%s|%s • normalize : x[%.2f],y[%.2f],z[%.2f] [unuse]\n", YELLOW, BLACK, object->norm.x, object->norm.y, object->norm.z);
			printf("%s|%s • size      : h[%.2f],w[%.2f],d[%.2f]\n", YELLOW, GREEN, object->size.h, object->size.w, object->size.d);
			printf("%s|%s • color     : r[%d],g[%d],b[%d]\n", YELLOW, GREEN, object->color.r, object->color.g, object->color.b);
		}
		else if (object->type == PLANE)
		{
			printf("%s================== [object %d][plane] ==================\n", YELLOW, index++);
			printf("|%s • index     : %d\n", GREEN, object->idx);
			printf("%s|%s • type      : %d\n", YELLOW, GREEN, object->type);
			printf("%s|%s • name      : %s\n", YELLOW, GREEN, object->name);
			printf("%s|%s • coordinete: x[%.2f],y[%.2f],z[%.2f]\n", YELLOW, GREEN, object->pos.x, object->pos.y, object->pos.z);
			printf("%s|%s • normalize : x[%.2f],y[%.2f],z[%.2f]\n", YELLOW, GREEN, object->norm.x, object->norm.y, object->norm.z);
			printf("%s|%s • size      : h[%.2f],w[%.2f],d[%.2f] [unuse]\n", YELLOW, BLACK, object->size.h, object->size.w, object->size.d);
			printf("%s|%s • color     : r[%d],g[%d],b[%d]\n", YELLOW, GREEN, object->color.r, object->color.g, object->color.b);
		}
		else if (object->type == CYLIND)
		{
			printf("%s=============== [object %d][cylinder] =================\n", YELLOW, index++);
			printf("|%s • index     : %d\n", GREEN, object->idx);
			printf("%s|%s • type      : %d\n", YELLOW, GREEN, object->type);
			printf("%s|%s • name      : %s\n", YELLOW, GREEN, object->name);
			printf("%s|%s • coordinete: x[%.2f],y[%.2f],z[%.2f]\n", YELLOW, GREEN, object->pos.x, object->pos.y, object->pos.z);
			printf("%s|%s • normalize : x[%.2f],y[%.2f],z[%.2f]\n", YELLOW, GREEN, object->norm.x, object->norm.y, object->norm.z);
			printf("%s|%s • size      : h[%.2f],w[%.2f],d[%.2f]\n", YELLOW, GREEN, object->size.h, object->size.w, object->size.d);
			printf("%s|%s • color     : r[%d],g[%d],b[%d]\n", YELLOW, GREEN, object->color.r, object->color.g, object->color.b);
		}
		head = head->next;
	}
	printf("%s======================================================\n", YELLOW);
	printf("•-------------------------•\n");
	printf("|%s • total lights  => %d ea %s|\n", GREEN, ft_lstsize(data->lht), YELLOW);
	printf("|%s • total objects => %d ea %s|\n", GREEN, ft_lstsize(data->objs), YELLOW);
	printf("•-------------------------•\n");
	printf("\033[0m");
}