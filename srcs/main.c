#include "minirt.h"

static void	initial(t_data *data, char *filename);
static int	render(t_data *data);

int main(int argc, char **argv)
{
	t_data data;
	char	*filename;

	if (argc == 1)
		return (printf("Need file argument\n"), 0);
	else
		filename = argv[1];
	initial(&data, filename);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win, X_EVENT_KEY_EXIT, 1L << 0, &rt_close, &data);
	mlx_loop(data.mlx);
	return (0);
}

static void	initial(t_data *data, char *filename)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit(data, ERROR_MLX);
	rt_setup(data, filename);
	data->win = mlx_new_window(data->mlx, data->w, data->h, "miniRT");
	if (!data->win)
		error_exit(data, ERROR_WIN);
}

static int	render(t_data *data)
{
	if (data->frame == FRAME_RATE)
		data->frame = 0;
	else
		data->frame += 1;
	render_objects(data);
	return (0);
}
