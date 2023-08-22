/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_moves_cont.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:27:56 by marvin            #+#    #+#             */
/*   Updated: 2023/08/14 14:27:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_manager(int key, t_fdf *fdf)
{
	if (key == ESC)
		free_fdf(fdf);
	else if (key == ARR_U || key == ARR_D || key == ARR_R || key == ARR_L)
		adjust_offset(fdf, key, 5);
	else if (key == 'o' || key == 'p')
		adjust_zoom(fdf, key, 1);
	else if (key == 'h' || key == 'l')
		adjust_height(fdf, key, 0.01f);
	else if (key == 'a' || key == 'd' || key == 's' \
			|| key == 'w' || key == 'q' || key == 'e')
		adjust_rotation(fdf, key, 0.02f);
	else if (key == 'b' || key == 'n' || key == 'm')
		apply_projection(fdf, key);
	setup_vertices(fdf);
	return (0);
}

int	adjust_height(t_fdf *fdf, int key, float change)
{
	if (key == 'l')
		change *= -1;
	fdf->view.z_multi += change;
	if (fdf->view.z_multi < 0.01f)
		fdf->view.z_multi = 0.01f;
	return (1);
}

int	adjust_rotation(t_fdf *fdf, int key, float change)
{
	if (key == 's' || key == 'd' || key == 'q')
		change *= -1;
	if (key == 's' || key == 'w')
	{
		fdf->view.x_angle += change;
		fdf->view.cos_x = cosf(fdf->view.x_angle);
		fdf->view.sin_x = sinf(fdf->view.x_angle);
	}
	else if (key == 'a' || key == 'd')
	{
		fdf->view.y_angle += change;
		fdf->view.cos_y = cosf(fdf->view.y_angle);
		fdf->view.sin_y = sinf(fdf->view.y_angle);
	}
	else if (key == 'q' || key == 'e')
	{
		fdf->view.z_angle += change;
		fdf->view.cos_z = cosf(fdf->view.z_angle);
		fdf->view.sin_z = sinf(fdf->view.z_angle);
	}
	return (1);
}
