#include "cub3d.h"

static	void	player_orientation(t_game *game, int i, int j)
{
	if (game->map_data.map[i][j] == 'N')
		game->player.angle = 3 * PI / 2;
	else if (game->map_data.map[i][j] == 'S')
		game->player.angle = PI / 2;
	else if (game->map_data.map[i][j] == 'E')
		game->player.angle = 0;
	else if (game->map_data.map[i][j] == 'W')
		game->player.angle = PI;
}

static void	player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map_data.map[i])
	{
		j = 0;
		while (game->map_data.map[i][j])
		{
			if (game->map_data.map[i][j] == 'N' || game->map_data.map[i][j] == 'S'
				|| game->map_data.map[i][j] == 'E' || game->map_data.map[i][j] == 'W')
			{
				game->player.x = j * game->tile_size + game->tile_size / 2;
				game->player.y = i * game->tile_size + game->tile_size / 2;
				game->player.tmp_x = game->player.x;
				game->player.tmp_y = game->player.y;
				game->player.ray_x = game->player.x;
				game->player.ray_y = game->player.y;
				player_orientation(game, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_data(t_game *game)
{
	int	tile_w;
	int	tile_h;
	int	map_px_w;
	int	map_px_h;

	game->map_width = get_max_len(game->map_data.map);
	game->map_height = get_map_height(game->map_data.map);
	tile_w = MAP_WIDTH / game->map_width;
	tile_h = MAP_HEIGHT / game->map_height;
	if (tile_h < tile_w)
		game->tile_size = tile_h;
	else
		game->tile_size = tile_w;
	map_px_w = game->map_width * game->tile_size;
	map_px_h = game->map_height * game->tile_size;
	game->map_offset_x = (MAP_WIDTH - map_px_w) / 2;
	game->map_offset_y = (MAP_HEIGHT - map_px_h) / 2;
	player_position(game);
}

void	init_player(t_player *player)
{
	player->ray_offset = PLAYER_SIZE / 2;
	player->go_up = false;
	player->go_down = false;
	player->go_left = false;
	player->go_right = false;
	player->rotate_left = false;
	player->rotate_right = false;
}
