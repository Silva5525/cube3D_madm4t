/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:25:56 by wdegraf           #+#    #+#             */
/*   Updated: 2025/01/30 16:29:03 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42.h>
#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 512
#define HEIGHT 512
#define TILE_SIZE 64
#define SQUARE_SIZE 64

static mlx_image_t *player;
static mlx_image_t *map_image;

void	ft_hook(void* param)
{
	mlx_t	*mlx = param;
	int new_x = player->instances[0].x;
    int new_y = player->instances[0].y;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);

	if (mlx_is_key_down(mlx, MLX_KEY_W))
		new_y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		new_x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		new_y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		new_x += 5;
	
	if (!check_collision(new_x, new_y))
    {
        player->instances[0].x = new_x;
        player->instances[0].y = new_y;
    }
}

/// @brief  Sehr coool
/// @param  void
/// @return  nix
int32_t	main(void)
{
	mlx_t	*mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "WASD Movement", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}

	map_image = mlx_new_image(mlx, WIDTH, HEIGHT);
	draw_map2D(map_image);
	mlx_image_to_window(mlx, map_image, 0, 0);
	
	player = mlx_new_image(mlx, TILE_SIZE / 2, TILE_SIZE / 2);
	
	uint32_t y = 0;
	while (y < player->height)
	{
		uint32_t x = 0;
		while (x < player->width)
		{
			mlx_put_pixel(player, x, y, 0xFF0000FF);
			x++;
		}
		y++;
	}	
	mlx_image_to_window(mlx, player, WIDTH / 2, HEIGHT / 2);	
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
