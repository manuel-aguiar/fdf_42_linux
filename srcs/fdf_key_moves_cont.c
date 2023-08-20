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

int	key_rotate_x(t_fdf *fdf, float change)
{
	fdf->view.x_angle += change;
	fdf->view.cos_x = cosf(fdf->view.x_angle);
	fdf->view.sin_x = sinf(fdf->view.x_angle);
	setup_vertices(fdf);
	return (1);
}

int	key_rotate_y(t_fdf *fdf, float change)
{
	fdf->view.y_angle += change;
	fdf->view.cos_y = cosf(fdf->view.y_angle);
	fdf->view.sin_y = sinf(fdf->view.y_angle);
	setup_vertices(fdf);
	return (1);
}

int	key_rotate_z(t_fdf *fdf, float change)
{
	fdf->view.z_angle += change;
	fdf->view.cos_z = cosf(fdf->view.z_angle);
	fdf->view.sin_z = sinf(fdf->view.z_angle);
	setup_vertices(fdf);
	return (1);
}
