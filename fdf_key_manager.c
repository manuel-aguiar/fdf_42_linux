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
	if ((key >> BIT_MVU) & 1 || (key >> BIT_MVD) & 1 \
	|| (key >> BIT_MVR) & 1 || (key >> BIT_MVL) & 1)
		adjust_offset(fdf, key, 2);
	if ((key >> BIT_ZIN) & 1 || (key >> BIT_ZOUT) & 1)
		adjust_zoom(fdf, key, 1);
	if ((key >> BIT_H_UP) & 1 || (key >> BIT_H_DOWN) & 1)
		adjust_height(fdf, key, 0.002f);
	if ((key >> BIT_RX_L) & 1 || (key >> BIT_RX_R) & 1 \
	|| (key >> BIT_RY_L) & 1 || (key >> BIT_RY_R) & 1 \
	|| (key >> BIT_RZ_L) & 1 || (key >> BIT_RZ_R) & 1)
		adjust_rotation(fdf, key, 0.004f);
	if ((key >> BIT_VISO) & 1)
		apply_projection(fdf, key);
	if ((key >> BIT_VPLL) & 1)
		apply_projection(fdf, key);
	if ((key >> BIT_VTOP) & 1)
		apply_projection(fdf, key);
	setup_vertices(fdf);
	return (0);
}

int	adjust_height(t_fdf *fdf, int key, float change)
{
	float	chg;

	if (fdf->view.z_multi < 0.000005f)
		return (1);
	chg = ft_fmin(ft_max(fdf->mrows, fdf->mcols) / (float)fdf->z_range, change);
	if ((key >> BIT_H_UP) & 1)
		fdf->view.z_multi += chg;
	if ((key >> BIT_H_DOWN) & 1)
		fdf->view.z_multi -= chg;
	if (fdf->view.z_multi < 0.00001f)
		fdf->view.z_multi = 0.00001f;
	return (1);
}

int	adjust_rotation(t_fdf *fdf, int key, float change)
{
	if ((key >> BIT_RX_L) & 1)
		fdf->view.x_angle -= change;
	if ((key >> BIT_RX_R) & 1)
		fdf->view.x_angle += change;
	if ((key >> BIT_RY_L) & 1)
		fdf->view.y_angle -= change;
	if ((key >> BIT_RY_R) & 1)
		fdf->view.y_angle += change;
	if ((key >> BIT_RZ_L) & 1)
		fdf->view.z_angle -= change;
	if ((key >> BIT_RZ_R) & 1)
		fdf->view.z_angle += change;
	setup_trigonometry(fdf);
	return (1);
}
