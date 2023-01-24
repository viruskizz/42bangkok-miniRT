#include "minirt.h"

int rt_setup(t_data *data, char *filename)
{
	data->w = WIDTH;
	data->h = HEIGHT;
	data->frame = 0;
	data->objs = NULL;

	set_objs(data);
}
