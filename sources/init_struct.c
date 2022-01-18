#include "fdf.h"

void ft_fill_line(t_map *map, char **coords_char, int **coords)
{
	int i;

	i = 0;
	while (coords_char[i])
	{
		(*coords)[i] = ft_atoi(coords_char[i]);
		if (map->z_min > (*coords)[i])
			map->z_min = (*coords)[i];
		if (map->z_max < (*coords)[i])
			map->z_max = (*coords)[i];
		i++;
	}
}

t_map *ft_init_map(int y, char **coords_char, int width)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
//    map->width = ft_size_arr(coords);
	map->coords = NULL;
	map->coords = ft_calloc(sizeof(int), width);
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
  //  map->line = malloc(sizeof(int) * map->width);
	ft_fill_line(map, coords_char, &(map->coords));
//	printf("%d - %d\n", map->z_min, map->z_max);
	map->y = y;
	map->next = NULL;
	return (map);
}

t_cam	*ft_init_cam()
{
	t_cam *cam;

	cam = malloc(sizeof(t_cam));
	cam->alpha = 0;
	cam->beta = 0;
	cam->gamma = 0;
	cam->shift_x = 0;
	cam->shift_y = 0;
	cam->prev_shift_x = cam->shift_x;
	cam->prev_shift_y = cam->shift_y;
	cam->zoom_count = 0;
	cam->projection = ISOMETRIC;
	return (cam);
}

t_fdf *ft_init_fdf()
{
	t_fdf *fdf;
	fdf = malloc(sizeof(t_fdf));
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	fdf->img.img = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &(fdf->img.bits_per_pixel),
			&(fdf->img.line_length), &(fdf->img.endian));
	fdf->cam = ft_init_cam();
	set_win_close(fdf);
	fdf->z_min = INT_MAX;
	fdf->z_max = INT_MIN;
	return (fdf);
}

t_dot	ft_init_dot(int x, int y, int z, t_fdf *fdf)
{
	t_dot dot;

	dot.x = x;
	dot.y = y;
	dot.z = z;
	dot.color = get_default_color(z, fdf);
	return (dot);
}