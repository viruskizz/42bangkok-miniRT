#include "minirt.h"

int rt_setup(t_data *data, char *filename)
{
	data->w = WIDTH;
	data->h = HEIGHT;
	data->frame = 0;
	data->obj = NULL;
}

t_obj	*new_objs()
{
	t_obj *obj;

	obj = ft_calloc(sizeof(t_obj), 1);
	obj->type = PLAN;
	obj->name = ft_strdup("PLAN");
	obj->pos.x = 0;
	obj->pos.y = 0;
	obj->pos.z = 0;
}
