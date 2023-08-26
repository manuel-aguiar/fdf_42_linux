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

int	key_manager(t_fdf *fdf)
{
	int key;

	key = fdf->keys;
	if ((key >> BIT_ESC) & 1)
		free_fdf(fdf);
	if ((key >> BIT_AU) & 1 || (key >> BIT_AD) & 1 || (key >> BIT_AR) & 1 || (key >> BIT_AL) & 1)
		adjust_offset(fdf, key, 2);
	if ((key >> BIT_O) & 1 || (key >> BIT_P) & 1)
		adjust_zoom(fdf, key, 1);
	if ((key >> BIT_H) & 1 || (key >> BIT_L) & 1)
		adjust_height(fdf, key, 0.002f);
	if ((key >> BIT_A) & 1 || (key >> BIT_D) & 1 || (key >> BIT_S) & 1 \
			|| (key >> BIT_W) & 1 || (key >> BIT_Q) & 1 || (key >> BIT_E) & 1)
		adjust_rotation(fdf, key, 0.004f);
	if ((key >> BIT_B) & 1 || (key >> BIT_N) & 1 || (key >> BIT_M) & 1)
		apply_projection(fdf, key);
	setup_vertices(fdf);
	return (0);
}

int	adjust_height(t_fdf *fdf, int key, float change)
{
	if ((key >> BIT_L) & 1)
		change *= -1;
	fdf->view.z_multi += change;
	if (fdf->view.z_multi < 0.01f)
		fdf->view.z_multi = 0.01f;
	return (1);
}

int	adjust_rotation(t_fdf *fdf, int key, float change)
{
	if ((key >> BIT_S) & 1 || (key >> BIT_D) & 1 || (key >> BIT_Q) & 1)
		change *= -1;
	if ((key >> BIT_S) & 1|| (key >> BIT_W) & 1)
	{
		fdf->view.x_angle += change;
		fdf->view.cos_x = cosf(fdf->view.x_angle);
		fdf->view.sin_x = sinf(fdf->view.x_angle);
	}
	if ((key >> BIT_A) & 1 || (key >> BIT_D) & 1)
	{
		fdf->view.y_angle += change;
		fdf->view.cos_y = cosf(fdf->view.y_angle);
		fdf->view.sin_y = sinf(fdf->view.y_angle);
	}
	if ((key >> BIT_Q) & 1 || (key >> BIT_E) & 1)
	{
		fdf->view.z_angle += change;
		fdf->view.cos_z = cosf(fdf->view.z_angle);
		fdf->view.sin_z = sinf(fdf->view.z_angle);
	}
	return (1);
}
