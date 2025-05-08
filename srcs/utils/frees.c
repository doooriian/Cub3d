#include "cub3d.h"

void	free_map(char **map)
{
	size_t	i;

	i = 0;
	if (!map || !*map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	destroy_imgs(t_game *game)
{
	if (!game)
		return;
	if (game->imgs.no.img)
		mlx_destroy_image(game->mlx, game->imgs.no.img);
	if (game->imgs.so.img)
		mlx_destroy_image(game->mlx, game->imgs.so.img);
	if (game->imgs.we.img)
		mlx_destroy_image(game->mlx, game->imgs.we.img);
	if (game->imgs.ea.img)
		mlx_destroy_image(game->mlx, game->imgs.ea.img);
}
