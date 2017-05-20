/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 10:40:26 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/11 12:10:14 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <stdint.h>
# include <stdlib.h>
# include <limits.h>

typedef struct		s_flag
{
	unsigned int	tiret : 1;
	unsigned int	plus : 1;
	unsigned int	espace : 1;
	unsigned int	diese : 1;
	unsigned int	zero : 1;
	unsigned int	negatif : 1;
	unsigned int	nbr_zero : 1;
}					t_flag;

typedef struct		s_width
{
	int				number;
	unsigned int	etoile : 1;
}					t_width;

typedef struct		s_precision
{
	int				number;
	unsigned int	etoile : 1;
}					t_precision;

typedef struct		s_lenght
{
	unsigned int	h : 1;
	unsigned int	hh : 1;
	unsigned int	l : 1;
	unsigned int	ll : 1;
	unsigned int	j : 1;
	unsigned int	z : 1;
}					t_lenght;

typedef struct		s_specifier
{
	unsigned int	c : 1;
	unsigned int	cm : 1;
	unsigned int	d : 1;
	unsigned int	dm : 1;
	unsigned int	i : 1;
	unsigned int	o : 1;
	unsigned int	om : 1;
	unsigned int	s : 1;
	unsigned int	sm : 1;
	unsigned int	u : 1;
	unsigned int	um : 1;
	unsigned int	x : 1;
	unsigned int	xm : 1;
	unsigned int	p : 1;
	unsigned int	pourcent : 1;
	unsigned int	no_specifier : 1;
	char			c_str;
}					t_specifier;

typedef struct		s_struc
{
	char			*str;
	t_flag			flag;
	t_width			width;
	t_precision		precision;
	t_lenght		lenght;
	t_specifier		specifier;
}					t_struc;

typedef struct		s_len
{
	int				len_str;
	int				len_tmp;
	int				pos_buf;
	int				pos_str;
	unsigned int	null : 1;
}					t_len;

int					ft_printf(const char *str, ...);
int					ft_printf_e(const char *str, ...);
int					ft_sprintf(char *buf, const char *str, ...);
char				*write_buf(t_struc *struc, char *buf, t_len *len,
		va_list ap);
int					ft_verif_char(int c);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memalloc(size_t size);
void				ft_putnbr(int nb);
void				ft_putchar(char c);
void				ft_putnstr_e(char *str, size_t n);
char				*ft_flag_1(char *tmp, t_len *len, char *str,
		size_t len_str);
char				*ft_itoa_int_min(int n);
char				*ft_itoa_base(int n, int base);
char				*ft_itoa_base_m(int n, int base);
char				*ft_unsigned_itoa(unsigned int n);
char				*ft_unsigned_itoa_base(unsigned int n, int base);
char				*ft_unsigned_char_itoa_base(unsigned char n, int base);
char				*ft_unsigned_itoa_base_m(unsigned int n, int base);
char				*ft_long_itoa_base(long n, int base);
char				*ft_unsigned_long_itoa_base(unsigned long n, int base);
char				*ft_unsigned_long_itoa_base_m(unsigned long n, int base);
char				*ft_uintmax_t_itoa_base(uintmax_t n, int base);
char				*ft_intmax_t_itoa_base(intmax_t n, int base);
char				*ft_intmax_t_itoa_base_m(intmax_t n, int base);
char				*ft_uintmax_t_itoa_base_m(uintmax_t n, int base);
int					check_specifier(t_struc *struc, const char *str, int z);
int					check_flag(t_struc *struc, int z, int y);
int					check_width(t_struc *struc, int z, int y, va_list ap);
size_t				ft_wcsnlen(const wchar_t *wcs, size_t n);
size_t				ft_wcslen(const wchar_t *wcs);
int					ft_wctomb(char *s, wchar_t wc);
size_t				ft_wcstombs(char *dest, const wchar_t *src, size_t n);
char				*modif_longeur_o(t_struc *struc, va_list ap);
char				*modif_longeur_om(t_struc *struc, va_list ap);
char				*modif_longeur_x(t_struc *struc, va_list ap);
char				*modif_longeur_xm(t_struc *struc, va_list ap);
char				*modif_longeur_d_and_i(t_struc *struc, va_list ap);
char				*modif_longeur_dm(t_struc *struc, va_list ap, intmax_t tmp);
int					check_precision(t_struc *struc, int z, int y, va_list ap);
int					check_lenght(t_struc *struc, int z, int y);
char				*write_d_and_i(t_struc *struc, char *buf, t_len *len,
		va_list ap);
char				*write_pourcent(t_struc *struc, char *buf, t_len *len);
char				*write_o(t_struc *struc, char *buf, t_len *len,
		va_list ap);
char				*write_om(t_struc *struc, char *buf, t_len *len,
		va_list ap);
char				*write_x(t_struc *struc, char *buf, t_len *len,
		va_list ap);
char				*write_xm(t_struc *struc, char *buf, t_len *len,
		va_list ap);
char				*write_u(t_struc *struc, char *buf, t_len *len,
		va_list ap);
char				*write_dm(t_struc *struc, char *buf, t_len *len,
		va_list ap);
char				*write_p(t_struc *struc, char *buf, t_len *len,
		va_list ap);
char				*write_um(t_struc *struc, char *buf, t_len *len,
		va_list ap);
char				*write_s(t_struc *struc, char *buf, t_len *len,
		va_list ap);
char				*write_sm(t_struc *struc, char *buf, t_len *len,
		va_list ap);
char				*write_c(t_struc *struc, char *buf, t_len *len,
		va_list ap);
char				*write_cm(t_struc *struc, char *buf, t_len *len,
		va_list ap);
char				*write_no_specifier(t_struc *struc, char *buf, t_len *len);

# ifndef FT_LS_H

char				*ft_remalloc(char *dest, int len_d, int len_s);

# endif

# ifndef LIBFT_H

void				*ft_memmove(void *dest, const void *src, size_t n);
char				*ft_itoa(int n);
void				*ft_memset(void *s, int c, size_t n);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strnew(size_t size);
void				ft_putstr(char *str);
void				ft_putnstr(char *str, size_t n);
int					ft_atoi(char *nptr);
size_t				ft_strlen(char *str);
void				*ft_bzero(void *s, size_t n);
char				*ft_strdup(char *src);

# endif
#endif
