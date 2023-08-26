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
	if ((key >> BIT_MVU) & 1 || (key >> BIT_MVD) & 1 || (key >> BIT_MVR) & 1 || (key >> BIT_MVL) & 1)
		adjust_offset(fdf, key, 2);
	if ((key >> BIT_ZIN) & 1 || (key >> BIT_ZOUT) & 1)
		adjust_zoom(fdf, key, 1);
	if ((key >> BIT_H_UP) & 1 || (key >> BIT_H_DOWN) & 1)
		adjust_height(fdf, key, 0.002f);
	if ((key >> BIT_RX_L) & 1 || (key >> BIT_RX_R) & 1 || (key >> BIT_RY_L) & 1 \
			|| (key >> BIT_RY_R) & 1 || (key >> BIT_RZ_L) & 1 || (key >> BIT_RZ_R) & 1)
		adjust_rotation(fdf, key, 0.004f);
	if ((key >> BIT_VISO) & 1 || (key >> BIT_VPLL) & 1 || (key >> BIT_VTOP) & 1)
		apply_projection(fdf, key);
	setup_vertices(fdf);
	return (0);
}

int	adjust_height(t_fdf *fdf, int key, float change)
{
	if ((key >> BIT_H_DOWN) & 1)
		change *= -1;
	fdf->view.z_multi += change;
	if (fdf->view.z_multi < 0.01f)
		fdf->view.z_multi = 0.01f;
	return (1);
}

int	adjust_rotation(t_fdf *fdf, int key, float change)
{
	if ((key >> BIT_RY_L) & 1 || (key >> BIT_RX_R) & 1 || (key >> BIT_RZ_L) & 1)
		change *= -1;
	if ((key >> BIT_RY_L) & 1 || (key >> BIT_RY_R) & 1)
	{
		fdf->view.x_angle += change;
		fdf->view.cos_x = cosf(fdf->view.x_angle);
		fdf->view.sin_x = sinf(fdf->view.x_angle);
	}
	if ((key >> BIT_RX_L) & 1 || (key >> BIT_RX_R) & 1)
	{
		fdf->view.y_angle += change;
		fdf->view.cos_y = cosf(fdf->view.y_angle);
		fdf->view.sin_y = sinf(fdf->view.y_angle);
	}
	if ((key >> BIT_RZ_L) & 1 || (key >> BIT_RZ_R) & 1)
	{
		fdf->view.z_angle += change;
		fdf->view.cos_z = cosf(fdf->view.z_angle);
		fdf->view.sin_z = sinf(fdf->view.z_angle);
	}
	return (1);
}
