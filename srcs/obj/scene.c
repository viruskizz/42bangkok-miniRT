
#include "minirt.h"

void	scene_initialise(t_data *data)
{
	data->w = WIDTH;
	data->h = HEIGHT;
	data->scene.color.r = 255;
	data->scene.color.g = 255;
	data->scene.color.b = 255;
	data->scene.pos.x = data->w / 2.0;
	data->scene.pos.y = data->h / 2.0;
	data->scene.size.w = data->w;
	data->scene.size.h = data->h;
	set_plain_img(data, &data->scene);
}
