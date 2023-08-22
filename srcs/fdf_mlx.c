/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_windows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:55:36 by marvin            #+#    #+#             */
/*   Updated: 2023/07/20 16:55:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_window(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (free_fdf(fdf));
	fdf->mlx_win = mlx_new_window(fdf->mlx, fdf->win_width, fdf->win_height, \
		fdf->win_name);
	fdf->front_img.img = mlx_new_image(fdf->mlx, fdf->win_width, fdf->win_height);
	fdf->back_img.img = mlx_new_image(fdf->mlx, fdf->win_width, fdf->win_height);
	if (!fdf->mlx_win || !fdf->front_img.img || !fdf->back_img.img)
		return (free_fdf(fdf));
	fdf->front_img.addr = mlx_get_data_addr(fdf->front_img.img, \
		&(fdf->front_img.bpp), &(fdf->front_img.line_len), \
		&(fdf->front_img.endian));
	fdf->back_img.addr = mlx_get_data_addr(fdf->back_img.img, \
		&(fdf->back_img.bpp), &(fdf->back_img.line_len), \
		&(fdf->back_img.endian));
	return (1);
}

int	img_to_window(t_fdf *fdf)
{
	t_mlx_img	swap;

	ft_memset(fdf->back_img.addr, 0, fdf->win_width * fdf->win_height \
		* sizeof(fdf->back_img.bpp));
	draw_image(fdf);
	swap = fdf->back_img;
	fdf->back_img = fdf->front_img;
	fdf->front_img = swap;
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->front_img.img, 0, 0);
	return (1);
}

int fake_render(t_fdf *fdf)
{
	t_mlx_img	swap;
	ft_memset(fdf->back_img.addr, 0, fdf->win_width * fdf->win_height \
		* sizeof(fdf->back_img.bpp));
	t_pixel	start = {LOW_RGB, 100, 100, 0};
	t_pixel end = {HIGH_RGB, 200, 200, 0};
	xiaolinwu_line(fdf, start, end);
	swap = fdf->back_img;
	fdf->back_img = fdf->front_img;
	fdf->front_img = swap;
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->front_img.img, 0, 0);
	return (1);
}

int	rendering_loop(t_fdf *fdf)
{
	mlx_hook(fdf->mlx_win, 2, (1L << 0) | (1L << 1), key_manager, fdf);
	mlx_hook(fdf->mlx_win, 17, (1L << 1), free_fdf, fdf);
	mlx_loop_hook(fdf->mlx, img_to_window, fdf);
	//mlx_loop_hook(fdf->mlx, fake_render, fdf);
	mlx_loop(fdf->mlx);
	return (1);
}
