/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   earth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:32:34 by seok              #+#    #+#             */
/*   Updated: 2023/07/08 20:25:42 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define FACTOR	0
#define ORI_X	1
#define ORI_Y	2
#define ORI_Z	3
#define HIGH	4
#define WIDT	5
#define TOTAL	6

float	ft_max(float a, float b)
{
	if (a > b)
		return(a);
	return (b);
}

float	ft_fabs(float a)
{
	return (((a < 0) * (-1) + (a >= 0)) * a);
}

float	ft_factor(t_vars *vars, float f[10])
{
	float	min;
	float	max;
	int		i;

	i = 0;
	min = vars->orimap[0].z;
	while (++i < f[TOTAL])
	{
		if (max < vars->orimap[i].z)
			max = vars->orimap[i].z;
		if (min > vars->orimap[i].z)
			min = vars->orimap[i].z;
	}
	return(10 * ft_max(ft_fabs(min), ft_fabs(max)));
}

void	make_earth(t_vars *vars)
{
	int				i;
	float			f[10];

	f[HIGH] = vars->info.height;
	f[WIDT] = vars->info.width;
	f[TOTAL] = vars->info.height * vars->info.width;
	f[FACTOR] = ft_factor(vars, f);
	// vars->ear = malloc(sizeof(t_coordinate) * f[HIGH] * f[WIDT]);
	// copy_ori(vars, vars->orimap, vars->ear);
	i = -1;
	while (++i < f[WIDT] * f[HIGH])
	{
		f[ORI_X] = vars->orimap[i].x;
		f[ORI_Y] = vars->orimap[i].y;
		f[ORI_Z] = vars->orimap[i].z;
		vars->map[i].x = vars->info.scale * (f[FACTOR] + f[ORI_Z]) * sin((f[ORI_Y] + 1) * M_PI / (f[HIGH] + 2)) * cos(f[ORI_X] * 2 * M_PI / (f[WIDT] + 1));
		vars->map[i].y = vars->info.scale * (f[FACTOR] + f[ORI_Z]) * sin((f[ORI_Y] + 1) * M_PI / (f[HIGH] + 2)) * sin(f[ORI_X] * 2 * M_PI / (f[WIDT] + 1));
		vars->map[i].z = vars->info.scale * (f[FACTOR] + f[ORI_Z]) * cos((f[ORI_Y] + 1) * M_PI / (f[HIGH] + 2));
	}
	clear_img(vars);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
}