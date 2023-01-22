#include "minirt.h"

void	render_objects(t_data *data)
{
	t_list *obj;
	t_list *tmp;

	obj = data->obj;
	tmp = obj;
	while (tmp)
	{
		if (!data->frame)
			print_obj(tmp->content);
		tmp = tmp->next;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 10, 10);
}
