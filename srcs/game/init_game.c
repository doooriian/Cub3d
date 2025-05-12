#include "cub3d.h"

static	void	player_orientation(t_game *data, int i, int j)
{
	if (data->map_data.map[i][j] == 'N')
		data->player.angle = 3 * PI / 2;
	else if (data->map_data.map[i][j] == 'S')
		data->player.angle = PI / 2;
	else if (data->map_data.map[i][j] == 'E')
		data->player.angle = 0;
	else if (data->map_data.map[i][j] == 'W')
		data->player.angle = PI;
}

static void	player_position(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map_data.map[i])
	{
		j = 0;
		while (data->map_data.map[i][j])
		{
			if (data->map_data.map[i][j] == 'N' || data->map_data.map[i][j] == 'S'
				|| data->map_data.map[i][j] == 'E' || data->map_data.map[i][j] == 'W')
			{
				data->player.x = j * data->tile_size + data->tile_size / 2;
				data->player.y = i * data->tile_size + data->tile_size / 2;
				data->player.tmp_x = data->player.x;
				data->player.tmp_y = data->player.y;
				data->player.ray_x = data->player.x;
				data->player.ray_y = data->player.y;
				player_orientation(data, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_data(t_game *data)
{
	int	tile_w;
	int	tile_h;
	int	map_px_w;
	int	map_px_h;

	data->map_width = get_max_len(data->map_data.map);
	data->map_height = get_map_height(data->map_data.map);
	tile_w = MAP_WIDTH / data->map_width;
	tile_h = MAP_HEIGHT / data->map_height;
	if (tile_h < tile_w)
		data->tile_size = tile_h;
	else
		data->tile_size = tile_w;
	map_px_w = data->map_width * data->tile_size;
	map_px_h = data->map_height * data->tile_size;
	data->map_offset_x = (MAP_WIDTH - map_px_w) / 2;
	data->map_offset_y = (MAP_HEIGHT - map_px_h) / 2;
	player_position(data);
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
