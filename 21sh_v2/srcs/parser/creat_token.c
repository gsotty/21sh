#include "./../../vingt_et_un_sh.h"

t_token		*creat_token_2(char *cmd, int len, char *delim, int first_call)
{
	static int		z;
	int				y;
	int				start;
	int				end;
	int				start_token;

	if (first_call == 1)
		z = 0;
	end = 0;
	start = z;
	start_token = 1;
	while (z < len)
	{
		y = 0;
		while (delim[y] != '\0')
		{
			if (cmd[z + 1] == delim[y])
			{
				z++;
				end = z;
				return (token_new(cmd + start, end - start, 0));
			}
			else if (cmd[z] == delim[y])
			{
				z++;
				end = z;
				return (token_new(cmd + start, end - start, 0));
			}
			y++;
		}
		z++;
	}
	if (z == len)
	{
		end = z;
		z++;
		return (token_new(cmd + start, end - start, 0));
	}
	else
		return (NULL);
}

t_token		*creat_token(char *cmd, int len, char *delim, int first_call)
{
	static int		x;
	int				y;
	int				start;
	int				end;
	int				start_token;

	if (first_call == 1)
		x = 0;
	end = 0;
	start = x;
	start_token = 1;
	while (x < len)
	{
		y = 0;
		while (delim[y] != '\0')
		{
			if (cmd[x + 1] == delim[y])
			{
				x++;
				end = x;
				return (token_new(cmd + start, end - start, 0));
			}
			else if (cmd[x] == delim[y])
			{
				x++;
				end = x;
				return (token_new(cmd + start, end - start, 0));
			}
			y++;
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
