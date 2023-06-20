/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_make_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:37:34 by seok              #+#    #+#             */
/*   Updated: 2023/06/20 23:12:32 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

void	set_position(t_position *pos, t_coordinate *dot)
{
	pos->x = dot->x;
	pos->y = dot->y;
	pos->dx = ft_abs(dot->x - dot->next->x);
	pos->dy = ft_abs(dot->y - dot->next->y);
	if (dot->x < dot->next->x)
		pos->add_x = 1;
	else
		pos->add_x = -1;
	if (dot->y < dot->next->y)
		pos->add_y = 1;
	else
		pos->add_y = -1;
}

void	make_line2(t_position *pos, coordinates p, t_data *image)
{
	if (pos->dy <= pos->dx)
	{
		if (p <= 0)
			p += 2 * pos->dy;
		else
		{
			p += 2 * (pos->dy - pos->dx);
			pos->y += pos->add_y;
		}
	}
	else
	{
		if (p <= 0)
			p += 2 * pos->dx;
		else
		{
			p += 2 * (pos->dx - pos->dy);
			pos->x += pos->add_x;
		}
	}
	my_mlx_pixel_put(image, pos->x, pos->y, COLOR);
	// pos->x += pos->add_x;
}

void	make_line(t_coordinate *dot, t_data *image)
{
	int			p;
	t_position	pos;

	set_position(&pos, dot);
	if (pos.dy <= pos.dx)
	{
		p = 2 * (pos.dy - pos.dx);
		if (dot->x <= dot->next->x)
		{
			while (pos.x <= dot->next->x)
			{
				make_line2(&pos, p, image);
	pos.x += pos.add_x;
				
			}
		}
		else
		{
			while (pos.x >= dot->next->x)
			{
				make_line2(&pos, p, image);
	pos.x += pos.add_x;
				
			}
		}
	}
	else
	{
		p = 2 * (pos.dx - pos.dy);
		if (dot->y <= dot->next->y)
		{
			while (pos.y <= dot->next->y)
			{
				make_line2(&pos, p, image);
	pos.y += pos.add_y;
				
			}
		}
		else
		{
			while (pos.y >= dot->next->y)
			{
				make_line2(&pos, p, image);
	pos.y += pos.add_y;
				
			}
		}
	}
}