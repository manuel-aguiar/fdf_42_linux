/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_help_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:49:19 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/08/27 17:10:30 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

static int	help_string2(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx, fdf->mlx_win, 50, 125, 0xffffff, 		\
	"Press N to reset to Parallel Projection");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 50, 140, 0xffffff, 		\
	"Press M to reset to Top-view Projection");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 50, 155, 0xffffff,	\
	"Left-Mouse click-and-drag to move the model");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 50, 170, 0xffffff,	\
	"Mouse Wheel to zoom in and out towards the mouse pointer");
	mlx_string_put(fdf->mlx, fdf->mlx_win, 50, 185, 0xffffff,	\
	"Press H to close Help!");
	return (1);
}

int	help_string(t_fdf *fdf)
{
	if (!(fdf->win_height >= 250 && fdf->win_width >= 400))
		return (1);
	if (!((fdf->keys >> BIT_HELP) & 1))
		mlx_string_put(fdf->mlx, fdf->mlx_win, 50, 50, 0xffffff, \
		"Press H for help!");
	else
	{
		mlx_string_put(fdf->mlx, fdf->mlx_win, 50, 50, 0xffffff,  \
		"Press A and D to rotate around the x-axis");
		mlx_string_put(fdf->mlx, fdf->mlx_win, 50, 65, 0xffffff,	\
		"Press S and W to rotate around the y-axes");
		mlx_string_put(fdf->mlx, fdf->mlx_win, 50, 80, 0xffffff,	\
		"Press Q and E to rotate around the z-axis");
		mlx_string_put(fdf->mlx, fdf->mlx_win, 50, 95, 0xffffff, 	\
		"Press R and F to increase/decrease map height range");
		mlx_string_put(fdf->mlx, fdf->mlx_win, 50, 110, 0xffffff, 	\
		"Press B to reset to Isometric Projection");
		help_string2(fdf);
	}
	return (1);
}
