#include "cub.h"

void	init_data(t_data *data)
{
	int	tile_w;
	int	tile_h;
	int	map_px_w;
	int	map_px_h;

	tile_w = WIDTH / MAP_WIDTH;
	tile_h = HEIGHT / MAP_HEIGHT;
	if (tile_h < tile_w)
		data->tile_size = tile_h;
	else
		data->tile_size = tile_w;
	map_px_w = MAP_WIDTH * data->tile_size;
	map_px_h = MAP_HEIGHT * data->tile_size;
	data->map_offset_x = (WIDTH - map_px_w) / 2;
	data->map_offset_y = (HEIGHT - map_px_h) / 2;
	data->player.x = WIDTH / 2;
	data->player.y = HEIGHT / 2;
}

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->tmp_x = WIDTH / 2;
	player->tmp_y = HEIGHT / 2;
	player->ray_x = WIDTH / 2;
	player->ray_y = HEIGHT / 2;
	player->ray_offset = PLAYER_SIZE / 2;
	player->angle = PI / 2;
	player->go_up = false;
	player->go_down = false;
	player->go_left = false;
	player->go_right = false;
	player->rotate_left = false;
	player->rotate_right = false;
}
