/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:56:31 by marvin            #+#    #+#             */
/*   Updated: 2023/07/11 09:56:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	free_fdf(t_fdf *fdf)
{
	if (fdf->map)
		free(fdf->map);
	if (fdf->vertices)
		free(fdf->vertices);
	if (fdf->front_img.img)
		mlx_destroy_image(fdf->mlx, fdf->front_img.img);
	if (fdf->back_img.img)
		mlx_destroy_image(fdf->mlx, fdf->back_img.img);
	if (fdf->mlx_win)
		mlx_destroy_window(fdf->mlx, fdf->mlx_win);
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac != 2)
		return (error_msg("fdf: wrong number of arguments\n"));
	if (!setup_fdf(&fdf, av[1]))
		return (0);
	if (!init_window(&fdf))
		return (0);
	rendering_loop(&fdf);
	free_fdf(&fdf);
	return (0);
}
