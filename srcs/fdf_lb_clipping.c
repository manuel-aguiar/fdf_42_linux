/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_lb_clipping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:32:18 by marvin            #+#    #+#             */
/*   Updated: 2023/08/14 14:32:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void lb_safety(t_fdf *fdf, t_pixel *start, t_pixel *end)
{
	if (start->x > fdf->win_width - 1)
		start->x = fdf->win_width - 1;
	if (start->x < 0)
		start->x = 0;
	if (start->y > fdf->win_height - 1)
		start->y = fdf->win_height - 1;
	if (start->y < 0)
		start->y = 0;
	if (end->x > fdf->win_width - 1)
		end->x = fdf->win_width - 1;
	if (end->x < 0)
		end->x = 0;
	if (end->y > fdf->win_height - 1)
		end->y = fdf->win_height - 1;
	if (end->y < 0)
		end->y = 0;
}

static void	lb_ratios1(t_lbclip *lb)
{
	if (lb->p1 != 0)
	{
		lb->r1 = (float)lb->q1 / (float)lb->p1;
		lb->r2 = (float)lb->q2 / (float)lb->p2;
		if (lb->p1 < 0)
		{
			lb->negarr[lb->negind++] = lb->r1;
			lb->posarr[lb->posind++] = lb->r2;
		}
		else
		{
			lb->negarr[lb->negind++] = lb->r2;
			lb->posarr[lb->posind++] = lb->r1;
		}
	}
}

static void	lb_ratios2(t_lbclip *lb)
{
	if (lb->p3 != 0)
	{
		lb->r3 = (float)lb->q3 / (float)lb->p3;
		lb->r4 = (float)lb->q4 / (float)lb->p4;
		if (lb->p3 < 0)
		{
			lb->negarr[lb->negind++] = lb->r3;
			lb->posarr[lb->posind++] = lb->r4;
		}
		else
		{
			lb->negarr[lb->negind++] = lb->r4;
			lb->posarr[lb->posind++] = lb->r3;
		}
	}
}

static int	lb_setup(t_fdf *fdf, t_lbclip *lb, t_pixel *start, t_pixel *end)
{
	lb->p1 = -(end->x - start->x);
	lb->p2 = -lb->p1;
	lb->p3 = -(end->y - start->y);
	lb->p4 = -lb->p3;
	lb->q1 = start->x - 0;
	lb->q2 = fdf->win_width - 1 - start->x;
	lb->q3 = start->y - 0;
	lb->q4 = fdf->win_height - 1 - start->y;
	lb->posind = 1;
	lb->negind = 1;
	lb->posarr[0] = 1;
	lb->negarr[0] = 0;
	if ((lb->p1 == 0 && lb->q1 < 0) || (lb->p2 == 0 && lb->q2 < 0) || \
		(lb->p3 == 0 && lb->q3 < 0) || (lb->p4 == 0 && lb->q4 < 0))
		return (0);
	return (1);
}

int	liang_barsky_clipper(t_fdf *fdf, t_pixel start, t_pixel end, t_pixel new[])
{
	t_lbclip	lb;

	if (!lb_setup(fdf, &lb, &start, &end))
		return (0);
	lb_ratios1(&lb);
	lb_ratios2(&lb);
	lb.rn1 = lb_maxi(lb.negarr, lb.negind);
	lb.rn2 = lb_mini(lb.posarr, lb.posind);
	if (lb.rn1 > lb.rn2)
		return (0);
	lb.xn1 = start.x + (float)lb.p2 * lb.rn1;
	lb.yn1 = start.y + (float)lb.p4 * lb.rn1;
	lb.xn2 = start.x + (float)lb.p2 * lb.rn2;
	lb.yn2 = start.y + (float)lb.p4 * lb.rn2;
	start.x = lb.xn1;
	start.y = lb.yn1;
	end.x = lb.xn2;
	end.y = lb.yn2;
	lb_safety(fdf, &start, &end);
	new[0] = start;
	new[1] = end;
	return (1);
}
