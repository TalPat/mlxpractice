/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpatter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 18:28:33 by talon             #+#    #+#             */
/*   Updated: 2018/08/15 14:18:31 by tpatter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;

void			ft_drline(float sx, float sy, float ex, float ey, t_mlx *mlx)
{
	float	grad;
	float	gradinv;

	if (sx == ex)
	{
		if (sy < ey)
			while (sy <= ey)
			{
				mlx_pixel_put(mlx->mlx, mlx->win, sx, sy, 0xffffff);
				sy++;
			}
		else
			while (sy >= ey)
			{
				mlx_pixel_put(mlx->mlx, mlx->win, sx, sy, 0xffffff);
				sy--;
			}
	}
	else
	{
		grad = (sy - ey) / (sx - ex);
		if (grad < 1 && grad > -1)
		{
			while (sx - ex > 0.5 || sx - ex < -0.5)
			{
				mlx_pixel_put(mlx->mlx, mlx->win, sx, sy, 0xffffff);
				if (sx <= ex)
				{
					sy += grad;
					sx++;
				}
				else
				{
					sy -= grad;
					sx--;
				}
			}
			mlx_pixel_put(mlx->mlx, mlx->win, ex, ey, 0xffffff);
		}
		else
		{
			gradinv = (sx - ex) / (sy - ey);
			while (sy - ey > 0.5 || sy - ey < -0.5)
			{
				mlx_pixel_put(mlx->mlx, mlx->win, sx, sy, 0xffffff);
				if (sy <= ey)
				{
					sx += gradinv;
					sy++;
				}
				else
				{
					sx -= gradinv;
					sy--;
				}
			}
			mlx_pixel_put(mlx->mlx, mlx->win, ex, ey, 0xffffff);
		}
	}
}

void			ft_drcirc(float cx, float cy, float r, t_mlx *mlx)
{
	float	x;
	float	y;

	x = cx - r;
	while (x <= cx + r)
	{
		y = sqrtf((r * r) - ((x - cx) * (x - cx))) + cy;
		mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0xffffff);
		y = -sqrtf((r * r) - ((x - cx) *(x - cx))) + cy;
		mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0xffffff);
		x++;
	}
	y = cy - r;
	while (y <= cy + r)
	{
		x = sqrtf((r * r) - ((y - cy) * (y - cy))) + cx;
		mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0xffffff);
		x = -sqrtf((r * r) - ((y - cy) *(y - cy))) + cx;
		mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0xffffff);
		y++;
	}
}

void			ft_drcircfill(float cx, float cy, float r, int color, t_mlx *mlx)
{
	float	x;
	float	y1;
	float	y2;

	x = cx - r;
	while (x <= cx + r)
	{
		y1 = sqrtf((r * r) - ((x - cx) * (x - cx))) + cy;
		mlx_pixel_put(mlx->mlx, mlx->win, x, y1, color);
		y2 = -sqrtf((r * r) - ((x - cx) * (x - cx))) + cy;
		mlx_pixel_put(mlx->mlx, mlx->win, x, y2, color);
		while (y2 <= y1)
		{
			mlx_pixel_put(mlx->mlx, mlx->win, x, y2, color);
			y2++;
		}
		x++;
	}
}

void			ft_drpoly(int sides, float len, float sx, float sy, t_mlx *mlx)
{
	float	angle;
	float	ex;
	float	ey;
	int		i;

	i = 0;
	angle = ((sides - 2) * M_PI) / sides;
	while (i < sides)
	{
		ex = sx + (len * cosf((M_PI - angle) * i));
		ey = sy + (len * sinf((M_PI - angle) * i));
		ft_drline(sx, sy, ex, ey, mlx);
		sx = ex;
		sy = ey;
		i++;
	}
}

void			ft_drgrid(int col, int row, float width, float height, float sx, float sy, t_mlx *mlx)
{
	float	colwid;
	float	rowheight;
	int		i;

	colwid = width / col;
	rowheight = height / row;
	i = 0;
	while (i <= row)
	{
		ft_drline(sx, sy + (rowheight * i), sx + width, sy + (rowheight * i), mlx);
		i++;
	}
	i = 0;
	while (i <= col)
	{
		ft_drline(sx + (colwid * i), sy, sx + (colwid * i), sy + height, mlx);
		i++;
	}
}

int				ft_keyread(int keycode, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	if (keycode == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	printf("key event %d\n", keycode);
	return (0);
}

int				main(void)
{
	t_mlx	*mlx;
	int		x;

	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, 1000, 1000, "My Window");
	mlx_pixel_put(mlx->mlx, mlx->win, 200, 200, 0x00ff00);
//	x = 1;
//	while (x < 10000)
//	{
//		if (x / 5000)
//		{
//			x = 0;
//			ft_drcircfill(500, 500, 800, 0x1111dd, mlx);
//		}
//		ft_drpoly(rand() % 5 + 3, rand() % 50 + 50, rand() % 1000, rand() % 1000, mlx);
//		x++;
//	}
	ft_drcirc(100, 100, 75, mlx);
	ft_drcircfill(360, 200, 175, 0x5030ff, mlx);
	ft_drpoly(2000, 1, 500, 0, mlx);
	ft_drgrid(50, 50, 200, 200, 100, 100, mlx);
	mlx_key_hook(mlx->win, ft_keyread, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}