#include "minirt.h"

void	put_obj_img_to_win(t_data *data, t_obj *obj);

void	render_objects(t_data *data)
{
	t_list *obj;
	t_list *tmp;

	obj = data->objs;
	tmp = obj;
	while (tmp)
	{
		// if (tmp->content)
		// 	put_obj_img_to_win(data, tmp->content);
		// 	// print_obj(tmp->content);
		if (tmp->content)
			print_tobject(tmp->content);
		tmp = tmp->next;
	}
}

void	put_obj_img_to_win(t_data *data, t_obj *obj)
{
	if (obj->img.img)
		mlx_put_image_to_window(data->mlx, data->win, obj->img.img, obj->pos.x, obj->pos.y);
}
