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

int	key_release(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		fdf->keys &= ~(1 << BIT_ESC);
	else if (keycode == KEY_AL)
		fdf->keys &= ~(1 << BIT_AL);
	else if (keycode == KEY_AU)
		fdf->keys &= ~(1 << BIT_AU);
	else if (keycode == KEY_AR)
		fdf->keys &= ~(1 << BIT_AR);
	else if (keycode == KEY_AD)
		fdf->keys &= ~(1 << BIT_AD);
	else if (keycode == KEY_A)
		fdf->keys &= ~(1 << BIT_A);
	else if (keycode == KEY_S)
		fdf->keys &= ~(1 << BIT_S);
	else if (keycode == KEY_D)
		fdf->keys &= ~(1 << BIT_D);
	else if (keycode == KEY_W)
		fdf->keys &= ~(1 << BIT_W);
	else if (keycode == KEY_Q)
		fdf->keys &= ~(1 << BIT_Q);
	else if (keycode == KEY_E)
		fdf->keys &= ~(1 << BIT_E);
	else if (keycode == KEY_H)
		fdf->keys &= ~(1 << BIT_H);
	else if (keycode == KEY_L)
		fdf->keys &= ~(1 << BIT_L);
	else if (keycode == KEY_O)
		fdf->keys &= ~(1 << BIT_O);
	else if (keycode == KEY_P)
		fdf->keys &= ~(1 << BIT_P);
	else if (keycode == KEY_B)
		fdf->keys &= ~(1 << BIT_B);
	else if (keycode == KEY_M)
		fdf->keys &= ~(1 << BIT_M);
	else if (keycode == KEY_N)
		fdf->keys &= ~(1 << BIT_N);
	return (0);
}

int key_press(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		fdf->keys |= (1 << BIT_ESC);
	else if (keycode == KEY_AL)
		fdf->keys |= (1 << BIT_AL);
	else if (keycode == KEY_AU)
		fdf->keys |= (1 << BIT_AU);
	else if (keycode == KEY_AR)
		fdf->keys |= (1 << BIT_AR);
	else if (keycode == KEY_AD)
		fdf->keys |= (1 << BIT_AD);
	else if (keycode == KEY_A)
		fdf->keys |= (1 << BIT_A);
	else if (keycode == KEY_S)
		fdf->keys |= (1 << BIT_S);
	else if (keycode == KEY_D)
		fdf->keys |= (1 << BIT_D);
	else if (keycode == KEY_W)
		fdf->keys |= (1 << BIT_W);
	else if (keycode == KEY_Q)
		fdf->keys |= (1 << BIT_Q);
	else if (keycode == KEY_E)
		fdf->keys |= (1 << BIT_E);
	else if (keycode == KEY_H)
		fdf->keys |= (1 << BIT_H);
	else if (keycode == KEY_L)
		fdf->keys |= (1 << BIT_L);
	else if (keycode == KEY_O)
		fdf->keys |= (1 << BIT_O);
	else if (keycode == KEY_P)
		fdf->keys |= (1 << BIT_P);
	else if (keycode == KEY_B)
		fdf->keys |= (1 << BIT_B);
	else if (keycode == KEY_M)
		fdf->keys |= (1 << BIT_M);
	else if (keycode == KEY_N)
		fdf->keys |= (1 << BIT_N);
	return (0);
}

int	init_window(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (free_fdf(fdf));
	fdf->mlx_win = mlx_new_window(fdf->mlx, fdf->win_width, fdf->win_height, \
		fdf->win_name);
	fdf->front_img.img = mlx_new_image(fdf->mlx, fdf->win_width, \
		fdf->win_height);
	fdf->back_img.img = mlx_new_image(fdf->mlx, fdf->win_width, \
		fdf->win_height);
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
	key_manager(fdf);
	draw_image(fdf);
	swap = fdf->back_img;
	fdf->back_img = fdf->front_img;
	fdf->front_img = swap;
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->front_img.img, 0, 0);
	return (1);
}

int	rendering_loop(t_fdf *fdf)
{
	mlx_hook(fdf->mlx_win, 2, (1L << 0), key_press, fdf);
	mlx_hook(fdf->mlx_win, 3, (1L << 1), key_release, fdf);
	mlx_hook(fdf->mlx_win, 17, (1L << 1), free_fdf, fdf);
	mlx_do_key_autorepeatoff(fdf->mlx);
	mlx_loop_hook(fdf->mlx, img_to_window, fdf);
	mlx_loop(fdf->mlx);
	return (1);
}
