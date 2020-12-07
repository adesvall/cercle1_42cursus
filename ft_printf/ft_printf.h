/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:20:19 by adesvall          #+#    #+#             */
/*   Updated: 2020/12/07 17:43:50 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef	struct		s_flags
{
	int				already_print;
	int				type;
	int				width;
	int				minus;
	int				zero;
	int				dot;
	int				star;
}					t_flags;

int					ft_printf(const char *str, ...);
int					ft_putchar(int c);
int					ft_putnbr_base(unsigned long long n, char *base);
int					ft_putstrn(char *s, int n);
int					ft_strnlen(char *s, int n);
int					ft_is_in(char c, const char *str);

int					main_display(char c, t_flags flags, va_list args);
int					disp_string(char *str, t_flags flags);
int					disp_char(int c, t_flags flags);
int					disp_width(int width, int rest, int has_zero);
int					disp_pointer(unsigned long long ptr, t_flags flags);

void				flag_minus(t_flags *flags);
void				flag_digit(char c, t_flags *flags);
void				flag_width(va_list args, t_flags *flags);
int					flag_dot(const char *save, int start,
									t_flags *flags, va_list args);

#endif