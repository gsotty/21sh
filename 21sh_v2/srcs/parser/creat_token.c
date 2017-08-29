#include "./../../vingt_et_un_sh.h"

int			skip_quote_and_backslash(char *cmd, int len, int *count)
{
	if (cmd[*count] == '\\')
	{
		*count = *count + 1;
		return (1);
	}
	else if (cmd[*count] == '\'')
	{
		*count = *count + 1;
		while (cmd[*count] != '\'' && *count < len)
			*count = *count + 1;
		return (1);
	}
	else if (cmd[*count] == '\"')
	{
		*count = *count + 1;
		while (cmd[*count] != '\"' && *count < len)
			*count = *count + 1;
		return (1);
	}
	return (0);
}

t_token		*creat_token_sep(char *cmd, int len, int first_call)
{
	static int		x;
	static int		cut_sep;
	int				end;
	int				start;

	if (first_call == 1)
		x = 0;
	end = 0;
	start = x;
	while (x < len)
	{
		if (skip_quote_and_backslash(cmd, len, &x) == 0)
		{
			if (cmd[x] == ';' && cut_sep == 0)
			{
				end = x;
				cut_sep = 1;
				return (token_new(cmd + start, end - start, 0));
			}
			else if (cmd[x] == ';' && cut_sep == 1)
			{
				x++;
				end = x;
				cut_sep = 0;
				return (token_new(cmd + start, end - start, 0));
			}
		}
		x++;
	}
	if (x == len)
	{
		end = x;
		x++;
		return (token_new(cmd + start, end - start, 0));
	}
	else
		return (NULL);
}

t_token		*creat_token_and_or(char *cmd, int len, int first_call)
{
	static int		x;
	static int		cut_and;
	static int		cut_or;
	int				end;
	int				start;

	if (first_call == 1)
		x = 0;
	end = 0;
	start = x;
	while (x < len)
	{
		if (skip_quote_and_backslash(cmd, len, &x) == 0)
		{
			if (cmd[x] == '|' && cmd[x + 1] == '|' && cut_or == 0)
			{
				end = x;
				cut_or = 1;
				return (token_new(cmd + start, end - start, 0));
			}
			else if (cmd[x] == '|' && cmd[x + 1] == '|' && cut_or == 1)
			{
				x = x + 2;
				end = x;
				cut_or = 0;
				return (token_new(cmd + start, end - start, 0));
			}
			else if (cmd[x] == '&' && cmd[x + 1] == '&' && cut_and == 0)
			{
				end = x;
				cut_and = 1;
				return (token_new(cmd + start, end - start, 0));
			}
			else if (cmd[x] == '&' && cmd[x + 1] == '&' && cut_and == 1)
			{
				x = x + 2;
				end = x;
				cut_and = 0;
				return (token_new(cmd + start, end - start, 0));
			}
		}
		x++;
	}
	if (x == len)
	{
		end = x;
		x++;
		return (token_new(cmd + start, end - start, 0));
	}
	else
		return (NULL);
}

t_token		*creat_token_pipe(char *cmd, int len, int first_call, int type)
{
	static int		x;
	static int		cut_pipe;
	int				end;
	int				start;

	if (first_call == 1)
		x = 0;
	end = 0;
	start = x;
	while (x < len)
	{
		if (skip_quote_and_backslash(cmd, len, &x) == 0)
		{
			if (cmd[x] == '|' && cut_pipe == 0 && type != _OR_IF)
			{
				end = x;
				cut_pipe = 1;
				return (token_new(cmd + start, end - start, 0));
			}
			if (cmd[x] == '|' && cut_pipe == 1 && type != _OR_IF)
			{
				x++;
				end = x;
				cut_pipe = 0;
				return (token_new(cmd + start, end - start, 0));
			}
		}
		x++;
	}
	if (x == len)
	{
		end = x;
		x++;
		return (token_new(cmd + start, end - start, 0));
	}
	else
		return (NULL);
}

t_token		*creat_token_dg_dl(char *cmd, int len, int first_call)
{
	static int		x;
	static int		cut_dless;
	static int		cut_dgreat;
	int				end;
	int				start;

	if (first_call == 1)
		x = 0;
	end = 0;
	start = x;
	while (x < len)
	{
		if (skip_quote_and_backslash(cmd, len, &x) == 0)
		{
			if (cmd[x] == '>' && cmd[x + 1] == '>' && cut_dgreat == 0)
			{
				end = x;
				cut_dgreat = 1;
				return (token_new(cmd + start, end - start, 0));
			}
			else if (cmd[x] == '>' && cmd[x + 1] == '>' && cut_dgreat == 1)
			{
				x = x + 2;
				end = x;
				cut_dgreat = 0;
				return (token_new(cmd + start, end - start, 0));
			}
			else if (cmd[x] == '<' && cmd[x + 1] == '<' && cut_dless == 0)
			{
				end = x;
				cut_dless = 1;
				return (token_new(cmd + start, end - start, 0));
			}
			else if (cmd[x] == '<' && cmd[x + 1] == '<' && cut_dless == 1)
			{
				x = x + 2;
				end = x;
				cut_dless = 0;
				return (token_new(cmd + start, end - start, 0));
			}
		}
		x++;
	}
	if (x == len)
	{
		end = x;
		x++;
		return (token_new(cmd + start, end - start, 0));
	}
	else
		return (NULL);
}

t_token		*creat_token_gr_le(char *cmd, int len, int first_call, int type)
{
	static int		x;
	static int		cut_gr;
	static int		cut_le;
	int				end;
	int				start;

	if (first_call == 1)
		x = 0;
	end = 0;
	start = x;
	while (x < len)
	{
		if (skip_quote_and_backslash(cmd, len, &x) == 0)
		{
			if (cmd[x] == '>' && cut_gr == 0 && type != _DGREAT)
			{
				end = x;
				cut_gr = 1;
				return (token_new(cmd + start, end - start, 0));
			}
			if (cmd[x] == '>' && cut_gr == 1 && type != _DGREAT)
			{
				x++;
				end = x;
				cut_gr = 0;
				return (token_new(cmd + start, end - start, 0));
			}
			if (cmd[x] == '<' && cut_le == 0 && type != _DLESS)
			{
				end = x;
				cut_le = 1;
				return (token_new(cmd + start, end - start, 0));
			}
			if (cmd[x] == '<' && cut_le == 1 && type != _DLESS)
			{
				x++;
				end = x;
				cut_le = 0;
				return (token_new(cmd + start, end - start, 0));
			}
		}
		x++;
	}
	if (x == len)
	{
		end = x;
		x++;
		return (token_new(cmd + start, end - start, 0));
	}
	else
		return (NULL);
}

t_token		*creat_token_space(char *cmd, int len, int first_call)
{
	static int		x;
	static int		cut_space;
	int				end;
	int				start;

	if (first_call == 1)
		x = 0;
	end = 0;
	start = x;
	while (x < len)
	{
		if (skip_quote_and_backslash(cmd, len, &x) == 0)
		{
			if (cmd[x] == ' ' && cut_space == 0)
			{
				end = x;
				cut_space = 1;
				return (token_new(cmd + start, end - start, 0));
			}
			if (cmd[x] == ' ' && cut_space == 1)
			{
				while (cmd[x] == ' ' && x < len)
					x++;
				end = x;
				cut_space = 0;
				return (token_new(cmd + start, end - start, 0));
			}
		}
		x++;
	}
	if (x == len)
	{
		end = x;
		x++;
		return (token_new(cmd + start, end - start, 0));
	}
	else
		return (NULL);
}
