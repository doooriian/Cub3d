#include "cub.h"

int	main(void)
{
	void	*mlx;
	void	*img;
	void	*mlx_win;

	mlx = mlx_init();
	img = mlx_new_image(mlx, 1920, 1080);
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
}
