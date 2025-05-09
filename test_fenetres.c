#include "mlx/mlx.h"
#include <stdlib.h>

typedef struct s_vars {
	void	*mlx;
	void	*win1;
	void	*img1;
	void	*win2;
	void	*img2;
	char	*addr1;
	char	*addr2;
	int		bpp;
	int		line_len;
	int		endian;
}	t_vars;

void	put_pixel(char *addr, int line_len, int bpp, int x, int y, int color)
{
	char	*dst;

	dst = addr + (y * line_len + x * (bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_big_pixel(char *addr, int line_len, int bpp, int x, int y, int size, int color)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			put_pixel(addr, line_len, bpp, x + i, y + j, color);
		}
	}
}

int	main_loop(void *param)
{
	static int	toggle = 0;
	static int	counter = 0;
	t_vars		*vars = (t_vars *)param;

	// Ralentit la fréquence de mise à jour
	if (counter++ < 10000)
		return (0);
	counter = 0;

	// Efface les images
	mlx_clear_window(vars->mlx, vars->win1);
	mlx_clear_window(vars->mlx, vars->win2);

	// Alterne les couleurs entre les fenêtres
	int color1 = toggle ? 0xFF0000 : 0x000000; // Rouge ou noir
	int color2 = toggle ? 0x000000 : 0x00FF00; // Noir ou vert
	put_big_pixel(vars->addr1, vars->line_len, vars->bpp, 100, 100, 10, color1);
	put_big_pixel(vars->addr2, vars->line_len, vars->bpp, 50, 50, 10, color2);

	// Met à jour les fenêtres
	mlx_put_image_to_window(vars->mlx, vars->win1, vars->img1, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->win2, vars->img2, 0, 0);

	// Alterne l'état pour le clignotement
	toggle = !toggle;

	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (1);
	vars.win1 = mlx_new_window(vars.mlx, 400, 300, "Fenetre 1");
	vars.win2 = mlx_new_window(vars.mlx, 400, 300, "Fenetre 2");
	vars.img1 = mlx_new_image(vars.mlx, 400, 300);
	vars.addr1 = mlx_get_data_addr(vars.img1, &vars.bpp, &vars.line_len, &vars.endian);
	vars.img2 = mlx_new_image(vars.mlx, 400, 300);
	vars.addr2 = mlx_get_data_addr(vars.img2, &vars.bpp, &vars.line_len, &vars.endian);

	mlx_loop_hook(vars.mlx, main_loop, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
