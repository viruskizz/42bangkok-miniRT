#include "minirt.h"
#include "math.h"

static void	initial(t_data *data, char *filename);
static int	render(t_data *data);

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_draw_circle(t_data data, t_img img, float diameter, int cox, int coy)
{
	int	radian = diameter / 2;
	int		x = data.w / 2 + cox;
	int		y = data.h / 2 - coy;

	for (float angle = 0; angle < M_PI * 2; angle += 0.005)
	{
		for (float i = 0;radian * cos(angle) >= 0 && i < radian * cos(angle);i += 1)
			my_mlx_pixel_put(&img, i + x, y + (radian * sin(angle)), 0x00990066);
		for (float i = 0;radian * cos(angle) <= 0 && i > radian * cos(angle); i -= 1)
			my_mlx_pixel_put(&img, i + x, y + (radian * sin(angle)), 0x00990066);
	}
	// mlx_put_image_to_window(data.mlx, data.win, img.img, 0, 0);
}

void	ft_fine_coordinate(t_img *img, float x, float y, float z, int scale)
{
	char	*dest;
	printf("line-length: %d, bit/pix: %d\n",img->line_length, img->bits_per_pixel);

	// dest = img->addr + 

	// return(dest);
}

int main(int argc, char **argv)
{
	t_img	img;
	t_data	data;
	int		height = 100;
	int		width = 100;
	data.w = 800;
	data.h = 800;
	int		x = data.w / 2;
	int		y = data.h / 2;
	int		z;


	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.w, data.h, "hello");

	img.img = mlx_new_image(data.mlx, data.w, data.h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// for (int y = 0; y < height; y++)
	// {
	// 	for (int x = 0; x < width; x++)
	// 		// my_mlx_pixel_put(&img, x + (1200/2), y + (700/2), 0x00FFFFFF);
	// 		my_mlx_pixel_put(&img, x, y, 0x00FFFFFF);
	// }
	// float radian = 200;
	// for (float angle = 0; angle < M_PI * 2; angle += 0.005)
	// {
	// 	for (float i = 0;radian * cos(angle) >= 0 && i < radian * cos(angle);i += 1)
	// 		my_mlx_pixel_put(&img, i + x, y + (radian * sin(angle)), 0x00FFFFFF);
	// 	for (float i = 0;radian * cos(angle) <= 0 && i > radian * cos(angle); i -= 1)
	// 		my_mlx_pixel_put(&img, i + x, y + (radian * sin(angle)), 0x00FFFFFF);
	// }
	// * draw the origin (0, 0, 0);
	ft_draw_circle(data, img, 10, 0, 0);
	my_mlx_pixel_put(&img, x, y, 0x00FFFFFF);

	// * y asix //
	for (int i = x; i < data.w; i++)
		my_mlx_pixel_put(&img, i, y, 0x0000FFFF);
	// * z asix //
	for (int i = y; i >= 0; i--)
		my_mlx_pixel_put(&img, x, i, 0x0000FFFF);
	// * x asix //
	float	angle = (3 * M_PI) / 4;
	for (int radiun = 0; radiun < data.h; radiun += 1)
		my_mlx_pixel_put(&img, x + (radiun * cos(angle)), y + (radiun * sin(angle)), 0x0000FFFF);

	// ft_fine_coordinate(&img, 0, 0, 0);
	

	// int	radiun = 0;
	// for (float angle = 0; angle < M_PI * 2; angle += 0.005)
	// {
	// 	my_mlx_pixel_put(&img, x + (radiun * cos(angle)), y + (radiun * sin(angle)), 0x0000FFFF);
	// 	radiun++;
	// }

	// for (float )
	// 	my_mlx_pixel_put(&img, x, y, 0x0000FFFF);

	// for (float i = (float)x; i < data.w; i++)
	// {
	// 	my_mlx_pixel_put(&img, x + (i * cos(M_PI)),y - (i * sin(M_PI)), 0x0000FFFF);
	// 	printf(">> %.6f\n", i);
	// }

	ft_draw_circle(data, img, 200, -200, -200);
	// // char	*filename;

	// // if (argc == 1)
	// // 	return (printf("Need file argument\n"), 0);
	// // else
	// // 	filename = argv[1];
	// // printf("%s = %d\n", filename, ft_strlen(filename));
	// // initial(&data, filename);
	// // mlx_loop_hook(data.mlx, &render, &data);
	mlx_put_image_to_window(data.mlx, data.win, img.img, 0, 0);
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
