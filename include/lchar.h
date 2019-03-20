#ifndef LCHAR_H
# define LCHAR_H

typedef struct		s_lchar
{
	int				len;
	char			*c;
	int				*type;
}					t_lchar;

t_lchar				*ft_lchardup(t_lchar *dest, t_lchar *srs, int n);
int					ft_addtype(t_lchar *buf, int start, int end);
t_lchar				*add_lchar(t_lchar *buf_start, t_lchar *buf_add);
t_lchar				**ft_lcharsplit(t_lchar *buf, char **token);

#endif
