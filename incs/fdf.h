/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:15:27 by marvin            #+#    #+#             */
/*   Updated: 2023/06/23 14:15:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <mlx.h>

# include "libft.h"

# define HEX "0123456789abcdef"

# define ERR_OPEN "open"
# define ERR_MALLOC "malloc"

# define RGB_R(x) ((x >> 16) & 0xFF)
# define RGB_G(x) ((x >> 8) & 0xFF)
# define RGB_B(x) ((x) & 0xFF)
# define MY_PI 3.14159

# define FDF_WINDOW_NAME "FdF"
# define FDF_WIDTH 1920
# define FDF_HEIGHT 1024
# define FDF_RGB_SIZE 3

# define X_ANGLE_ISO -144.74
# define Y_ANGLE_ISO 30
# define Z_ANGLE_ISO 35.26

# define X_ANGLE_TOP 0
# define Y_ANGLE_TOP -180
# define Z_ANGLE_TOP 180

# define X_ANGLE_PLL -150
# define Y_ANGLE_PLL 30
# define Z_ANGLE_PLL 0

//# define Z_MULTI 1
# define Z_MULTI 0.2f

# define RGB(r, g, b) (((r) << 16) | ((g) << 8) | (b))

# define MIN(x, y) (((x) > (y)) * (y) + ((x) < (y)) * (x))
# define MAX(x, y) (((x) > (y)) * (x) + ((x) < (y)) * (y))

# define SIGN(x) ({ __auto_type _v = (x); (_v < 0) * -1 + (_v > 0) * 1;})

# define LOW_RGB RGB(18, 23, 238)
# define HIGH_RGB RGB(255, 255, 255)

/*keys*/

enum e_keys_vals
{
	KEY_ESC = 65307,
	KEY_MVL = 65361,
	KEY_MVU = 65362,
	KEY_MVR = 65363,
	KEY_MVD = 65364,
	KEY_RY_L = 'a',
	KEY_RY_R = 'd',
	KEY_RX_L = 's',
	KEY_RX_R = 'w',
	KEY_RZ_L = 'q',
	KEY_RZ_R = 'e',
	KEY_H_UP = 'r',
	KEY_H_DOWN = 'f',
	KEY_HELP = 'h',
	KEY_ZIN = 'z',
	KEY_ZOUT = 'x',
	KEY_VISO = 'b',
	KEY_VPLL = 'm',
	KEY_VTOP = 'n',
};

enum e_keys_bits
{
	BIT_ESC,
	BIT_MVL,
	BIT_MVU,
	BIT_MVR,
	BIT_MVD,
	BIT_RY_L,
	BIT_RY_R,
	BIT_RX_L,
	BIT_RX_R,
	BIT_RZ_L,
	BIT_RZ_R,
	BIT_H_UP,
	BIT_H_DOWN,
	BIT_HELP,
	BIT_ZIN,
	BIT_ZOUT,
	BIT_VISO,
	BIT_VPLL,
	BIT_VTOP,
};

enum e_button_val_bits
{
	BUT_L = 1,
	BUT_R,
	BUT_M,
	BUT_U,
	BUT_D,
};

typedef struct s_coord
{
	int	height;
	int	colour;
}	t_coord;

typedef struct s_pixel
{
	int	colour;
	int	x;
	int	y;
	int	z;
}	t_pixel;

typedef struct s_rgb
{
	t_uchar	r;
	t_uchar	g;
	t_uchar	b;
}	t_rgb;

typedef struct s_xldata
{
	unsigned short	err_adj;
	unsigned short	err_acc;
	unsigned short	err_temp;
	short			dx;
	short			dy;
	short			save;
	short			slope;
	int				colour;
}	t_xldata;

typedef struct s_lbclip
{
	int		p1;
	int		p2;
	int		p3;
	int		p4;
	int		q1;
	int		q2;
	int		q3;
	int		q4;
	float	posarr[5];
	float	negarr[5];
	int		posind;
	int		negind;
	float	r1;
	float	r2;
	float	r3;
	float	r4;
	int		xn1;
	int		yn1;
	int		xn2;
	int		yn2;
	float	rn1;
	float	rn2;
}	t_lbclip;

typedef struct s_center_start
{
	int	max_x;
	int	min_x;
	int	max_y;
	int min_y;
	int x_offset;
	int	y_offset;
}	t_center_start;

typedef struct s_view
{
	int		zoom;
	int		x_offset;
	int		y_offset;
	float	x_angle;
	float	y_angle;
	float	z_angle;
	float	z_multi;
	float	cos_x;
	float	sin_x;
	float	cos_y;
	float	sin_y;
	float	cos_z;
	float	sin_z;
}	t_view;

typedef struct s_mouse
{
	int	buttons;
	int	cur_x;
	int	cur_y;
	int	prev_x;
	int	prev_y;
}	t_mouse;

typedef struct s_mlx_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_mlx_img;

typedef struct s_fdf
{
	t_coord		*map;
	t_uint		mrows;
	t_uint		mcols;
	t_uint		lenmap;
	int			min_z;
	int			max_z;
	int			low_colour;
	int			high_colour;
	t_uint		z_range;
	t_pixel		*vertices;
	int			win_width;
	int			win_height;
	char		win_name[4];
	t_uint		rgb_size;
	t_view		view;
	int			first_render;
	void		*mlx;
	void		*mlx_win;
	t_mlx_img	front_img;
	t_mlx_img	back_img;
	int			keys;
	int			state_changed;
	t_mouse		mouse;
}	t_fdf;

/*fdf_parsing.c*/
int		file_to_map(t_fdf *fdf, int fd);

/*fdf_setup.c*/
int		setup_trigonometry(t_fdf *fdf);
int		setup_fdf(t_fdf *fdf, char *file);

/*fdf_pixel_utils.c*/
void	swap_pixels(t_pixel *start, t_pixel *end);
void	set_pixel(t_fdf *fdf, int x, int y, int rgb);
int		get_pixel(t_fdf *fdf, int x, int y);
int		avg_colour(int start, int end, int num, int den);

/*fdf_add_to_libft.c*/
int		ft_ternary(int cond, int true, int false);
int		ft_abs(int num);
int		ft_min(int first, int second);
int		ft_max(int first, int second);
float	ft_fmin(float first, float second);
float	ft_fmax(float first, float second);

/*fdf_xiaolinwu.c*/
int		xiaolinwu_line(t_fdf *fdf, t_pixel start, t_pixel end);

/*fdf_xiaolinwu_utils.c*/
int		xiaolin_x_major(t_fdf *fdf, t_pixel *start, t_pixel *end, \
		t_xldata *data);
int		xiaolin_y_major(t_fdf *fdf, t_pixel *start, t_pixel *end, \
		t_xldata *data);

/*fdf_lb_clipping.c*/
int		liang_barsky_clipper(t_fdf *fdf, t_pixel start, t_pixel end, \
		t_pixel new[]);

/*fdf_lb_utils.c*/
float	lb_maxi(float arr[], int n);
float	lb_mini(float arr[], int n);

/*fdf_key_moves.c*/
int		adjust_offset(t_fdf *fdf, int key, int change);
int		adjust_zoom(t_fdf *fdf, int key, int change);
int		adjust_height(t_fdf *fdf, int key, float change);
int		adjust_rotation(t_fdf *fdf, int key, float change);
int		apply_projection(t_fdf *fdf, int key);

/*fdf_key_moves_cont.c*/
int		key_manager(t_fdf *fdf);
int		mouse_manager(t_fdf *fdf);
int		mouse_press(int button, int x, int y, t_fdf *fdf);
int		mouse_release(int button, int x, int y, t_fdf *fdf);
int		mouse_tester(int button, int x, int y, t_fdf *fdf);
int		mouse_position(int x, int y, t_fdf *fdf);

/*fdf_print_utils.c*/
void	print_height(t_fdf *fdf);
void	print_coords(t_fdf *fdf);

/*fdf_mlx.c*/
int		init_window(t_fdf *fdf);
int		img_to_window(t_fdf *fdf);
int		rendering_loop(t_fdf *fdf);

/*fdf_render.c*/
void	offset_from_center(t_fdf *fdf);
void	transform_pixel(t_fdf *fdf, t_pixel *pixel);
int		setup_vertices(t_fdf *fdf);
int		draw_image(t_fdf *fdf);

int		help_string(t_fdf *fdf);

/*fdf_error_msg.c*/
int		perror_msg(char *msg);
int		error_msg(char *msg);

/*fdf_main.c*/
int		free_fdf(t_fdf *fdf);

#endif
