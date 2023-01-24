#include "minirt.h"

void	set_objs(t_data *data)
{
	t_obj	*obj;
	t_list	*lst;

	obj = new_obj(data);
	// if (type == 'p')
	obj = set_plain_img(data, obj);
	lst = ft_lstnew(obj);
	if (data->objs)
		data->objs = lst;
	else
		ft_lstadd_back(&data->objs, lst);
}

t_obj	*new_obj(t_data *data)
{
	t_obj *obj;

	obj = ft_calloc(sizeof(t_obj), 1);
	obj->type = PLAN;
	obj->name = ft_strdup("PLAN");
	obj->pos = set_vector(0, 0, 0);
	obj->color = set_color(128, 128, 0);
	obj->size = set_size(WIDTH, HEIGHT, 0);
	return (obj);
}

void	free_obj(t_obj *obj)
{
	free(obj->name);
	// free(obj);
}
