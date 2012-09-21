/*
 * Copyright © 2012 Michael Heimpold <mhei@heimpold.de>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef _UGPIO_H_
#define _UGPIO_H_

#include "ugpio-version.h"

#ifdef  __cplusplus
# define UGPIO_BEGIN_DECLS  extern "C" {
# define UGPIO_END_DECLS    }
#else
# define UGPIO_BEGIN_DECLS
# define UGPIO_END_DECLS
#endif

UGPIO_BEGIN_DECLS

/* taken from linux/gpio.h */
#define GPIOF_DIR_OUT   (0 << 0)
#define GPIOF_DIR_IN    (1 << 0)

#define GPIOF_INIT_LOW  (0 << 1)
#define GPIOF_INIT_HIGH (1 << 1)

#define GPIOF_IN                (GPIOF_DIR_IN)
#define GPIOF_OUT_INIT_LOW      (GPIOF_DIR_OUT | GPIOF_INIT_LOW)
#define GPIOF_OUT_INIT_HIGH     (GPIOF_DIR_OUT | GPIOF_INIT_HIGH)

#define GPIOF_TRIG_FALL (1 << 2)
#define GPIOF_TRIG_RISE (1 << 3)
#define GPIOF_TRIGGER_MASK (GPIOF_TRIG_FALL | GPIOF_TRIG_RISE)

#define GPIOF_REQUESTED (1 << 4)

/**
 * A structure describing a GPIO with configuration.
 */
struct gpio {
	/* the GPIO number */
	unsigned int  gpio;
	/* GPIO configuration as specified by GPIOF_* */
	unsigned int  flags;
	/* file descriptor of /sys/class/gpio/gpioXY/value */
	int fd;
	/* a literal description string of this GPIO */
	const char    *label;
};
typedef struct gpio ugpio_t;

/**
 * Low level API
 */
extern int gpio_is_requested(unsigned int gpio);
extern int gpio_request(unsigned int gpio, const char *label);
extern int gpio_request_one(unsigned int gpio, unsigned int flags, const char *label);
extern int gpio_request_array(const struct gpio *array, size_t num);
extern int gpio_free(unsigned int gpio);
extern void gpio_free_array(const struct gpio *array, size_t num);

extern int gpio_alterable_direction(unsigned int gpio);
extern int gpio_get_direction(unsigned int gpio);
extern int gpio_direction_input(unsigned int gpio);
extern int gpio_direction_output(unsigned int gpio, int value);

extern int gpio_get_activelow(unsigned int gpio);
extern int gpio_set_activelow(unsigned int gpio, int value);

extern int gpio_get_value(unsigned int gpio);
extern int gpio_set_value(unsigned int gpio, int value);

extern int gpio_alterable_edge(unsigned int gpio);
extern int gpio_set_edge_str(unsigned int gpio, const char *edge);
extern int gpio_set_edge(unsigned int gpio, unsigned int flags);
extern int gpio_get_edge(unsigned int gpio);

/**
 * Higher level API
 */
extern ugpio_t *ugpio_request_one(unsigned int gpio, unsigned int flags, const char *label);
extern void ugpio_free(ugpio_t *ctx);
extern int ugpio_open(ugpio_t *ctx);
extern void ugpio_close(ugpio_t *ctx);
extern int ugpio_fd(ugpio_t *ctx);
extern int ugpio_get_value(ugpio_t *ctx);
extern int ugpio_set_value(ugpio_t *ctx, int value);

UGPIO_END_DECLS

#endif  /* _UGPIO_H_ */
