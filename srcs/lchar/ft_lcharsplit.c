#include "../../include/parser.h"

int			ft_lcharmatch(t_lchar *buf, int start, char **token)
{
	int		count;
	int		count_token;
	int		is_space;

	count_token = 0;
	is_space = 0;
	count = 0;
	while (buf->type[count + start] == _SPACE ||
			buf->type[count + start] == _NEW_LINE)
	{
		is_space = 1;
		count++;
	}
	if (is_space == 1)
		return (count);
	count = 0;
	while (token[count_token] != NULL)
	{
		count = 0;
		while ((token[count_token][count] != '\0' &&
				(count + start < buf->len) &&
				buf->type[count + start] == (int)token[count_token][count]))
			count++;
		if (token[count_token][count] == '\0')
			return (count);
		count_token++;
	}
	return (-1);
}

int			ft_nbrlcharsplit(t_lchar *buf, char **token)
{
	int		ret;
	int		count;
	int		start;
	int		nbr_tab;

	count = 0;
	start = 0;
	nbr_tab = 0;
	while (count < buf->len)
	{
		if ((ret = ft_lcharmatch(buf, count, token)) > -1)
		{
			if (count != start)
			{
				nbr_tab++;
				start = count;
			}
			count = count + ret;
			start = count;
			nbr_tab++;
			if (count >= buf->len)
				return (nbr_tab);
		}
		else
			count++;
	}
	nbr_tab++;
	return (nbr_tab);
}

t_lchar			*ft_lcharndup(t_lchar *src, int start, int end)
{
	int			x;
	t_lchar		*dest;

	if ((dest = ft_memalloc(sizeof(t_lchar))) == NULL)
		return (NULL);
	dest->len = (end - start) + 1;
	if ((dest->c = ft_memalloc(sizeof(char) * (dest->len + 1))) == NULL)
		return (NULL);
	if ((dest->type = ft_memalloc(sizeof(int) * (dest->len + 1))) == NULL)
		return (NULL);
	x = 0;
	while (x < dest->len)
	{
		dest->c[x] = src->c[x + start];
		dest->type[x] = src->type[x + start];
		x++;
	}
	dest->c[x] = '\0';
	dest->type[x] = 0;
	return (dest);
}

int			ft_splitbuf(t_lchar **tab, t_lchar *buf, char **token)
{
	int		ret;
	int		count;
	int		nbr_tab;
	int		start;

	count = 0;
	start = 0;
	nbr_tab = 0;
	while (count < buf->len)
	{
		if ((ret = ft_lcharmatch(buf, count, token)) > -1)
		{
			if (count != start)
			{
				tab[nbr_tab] = ft_lcharndup(buf, start, count - 1);
				nbr_tab++;
				start = count;
			}
			tab[nbr_tab] = ft_lcharndup(buf, start, count + (ret - 1));
			count = count + ret;
			start = count;
			nbr_tab++;
			if (count >= buf->len)
			{
				tab[nbr_tab] = NULL;
				return (0);
			}
		}
		else
			count++;
	}
	tab[nbr_tab] = ft_lcharndup(buf, start, count - 1);
	nbr_tab++;
	tab[nbr_tab] = NULL;
	return (0);
}

t_lchar		**ft_lcharsplit(t_lchar *buf, char **token)
{
	int			len_tab;
	t_lchar		**tab;

	len_tab = ft_nbrlcharsplit(buf, token);
	if ((tab = ft_memalloc(sizeof(t_lchar *) * (len_tab + 1))) == NULL)
		return (NULL);
	ft_splitbuf(tab, buf, token);
	return (tab);
}
