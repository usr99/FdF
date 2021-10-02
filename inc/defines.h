/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 00:42:30 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/02 02:23:32 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** WINDOW
*/

# define WIN_WIDTH			800
# define WIN_HEIGHT			600

/*
** MATH STUFF
*/

# define IVECT_X_DEFAULT	0.5
# define JVECT_X_DEFAULT	-0.5
# define IVECT_Y_DEFAULT	0.25
# define JVECT_Y_DEFAULT	0.25

# define Z_FACT_DEFAULT		0.05
# define Z_FACT_MIN			0
# define Z_FACT_INCR		0.001

# define ROTATION_DEFAULT	0.785398
# define ROTATION_INCR		0.005

# define MAX_ZOOM			150
# define MIN_ZOOM			1
# define IN					1
# define OUT				-1

# define MAX_TRANSLATION_X	WIN_WIDTH
# define MAX_TRANSLATION_Y	WIN_HEIGHT
# define TRANSLATION_STEP	5

/*
** COLORS
*/

# define GRADIENT_SIZE		512
# define BYTES_PER_PIXEL	4
# define COLOR_WHITE		0xFFFFFF
# define COLOR_RED			0xFF0000
# define COLOR_YELLOW		0xFFFF00

/*
** EVENTS
*/

# define BUTTON_LEFT		Button1
# define BUTTON_RIGHT		Button3
# define WHEEL_UP			Button4
# define WHEEL_DOWN			Button5
# define MOUSE_SENSITIVITY	500

/*
** OTHER
*/

# define TRUE				1
# define FALSE				0
