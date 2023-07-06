/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 06:01:15 by seok              #+#    #+#             */
/*   Updated: 2023/07/07 06:07:16 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

void	init_mlx(t_vars *vars, t_data *image)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIN_W, WIN_H, "Hellow World!");
	image->img = mlx_new_image(vars->mlx, WIN_W, WIN_H);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length, &image->endian);
}

void	init_hook(t_vars *vars)
{
	// mlx_key_hook(vars->win, key_hook, &vars);
	mlx_hook(vars->win, ON_KEYUP, 0, key_hook, vars);
	mlx_hook(vars->win, ON_DESTROY, 0, close_window, vars);
	mlx_mouse_hook(vars->win, mouse_hook, vars);
	// mlx_hook(vars->win, ON_MOUSEDOWN, 0, mouse_down, vars);
	// mlx_hook(vars->win, ON_MOUSEUP, 0, mouse_down, vars);
	// mlx_hook(vars->win, ON_MOUSEMOVE, 0, mouse_down, vars);
}
