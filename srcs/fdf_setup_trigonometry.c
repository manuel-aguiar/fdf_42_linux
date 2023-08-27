/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_setup_trigonometry.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:00:46 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/08/27 18:00:52 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	setup_trigonometry(t_fdf *fdf)
{
	fdf->view.cos_x = cosf(fdf->view.x_angle);
	fdf->view.sin_x = sinf(fdf->view.x_angle);
	fdf->view.cos_y = cosf(fdf->view.y_angle);
	fdf->view.sin_y = sinf(fdf->view.y_angle);
	fdf->view.cos_z = cosf(fdf->view.z_angle);
	fdf->view.sin_z = sinf(fdf->view.z_angle);
	return (1);
}
