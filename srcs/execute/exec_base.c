#include "../../include/execute.h"

int		closing_pipefd(t_var_redir *var_redir, int which_pipefd,
		int which_entry)
{
	close((var_redir->int_or_out == which_pipefd ?
				var_redir->pipefd_one[which_entry] :
				var_redir->pipefd_two[which_entry]));
	if (var_redir->int_or_out == which_pipefd)
		var_redir->pipefd_one[which_entry] = -1;
	else
		var_redir->pipefd_two[which_entry] = -1;
	return (0);
}

int		close_pipe_child(t_var_redir *var_redir)
{
	if (var_redir->y == 0)
		closing_pipefd(var_redir, 0, 0);
	else if (var_redir->y == var_redir->end_pipe)
		closing_pipefd(var_redir, 1, 1);
	else
	{
		closing_pipefd(var_redir, 0, 0);
		closing_pipefd(var_redir, 1, 1);
	}
	return (0);
}

int		close_pipe_father(t_var_redir *var_redir)
{
	if (var_redir->y == 0)
		closing_pipefd(var_redir, 0, 1);
	else if (var_redir->y == var_redir->end_pipe)
		closing_pipefd(var_redir, 1, 0);
	else
	{
		closing_pipefd(var_redir, 0, 1);
		closing_pipefd(var_redir, 1, 0);
	}
	return (0);
}

int		close_redir_child(t_pipelines pipel, t_var_redir *var_redir)
{
	int		z;

	z = 0;
	while (z < pipel.len)
	{
		if (pipel.redir[z].file_int != NULL)
		{
			if (pipel.redir[z].type == _HEREDOC)
			{
				close(var_redir->pipefd_here[1]);
				var_redir->pipefd_here[1] = -1;
			}
		}
		z++;
	}
	return (0);
}

int	close_redir_father_fork_heredoc(t_redirections redir,
		t_var_redir *var_redir)
{
	pid_t	father;

	father = fork();
	if (father == 0)
	{
		close(var_redir->pipefd_here[0]);
		var_redir->pipefd_here[0] = -1;
		write(var_redir->pipefd_here[1], redir.heredoc, redir.len_heredoc);
		exit(0);
	}
	else if (father > 0)
	{
		close(var_redir->pipefd_here[0]);
		var_redir->pipefd_here[0] = -1;
		close(var_redir->pipefd_here[1]);
		var_redir->pipefd_here[1] = -1;
	}
	else
	{
		write(2, "error fork\n", 11);
		return (1);
	}
	return (0);
}

int	close_redir_father(t_pipelines pipel, t_var_redir *var_redir, int z)
{
	while (z < pipel.len)
	{
		if (pipel.redir[z].file_int != NULL)
		{
			if (pipel.redir[z].type == _RINT)
				close(var_redir->fd_int);
			else if (pipel.redir[z].type == _HEREDOC)
			{
				if (close_redir_father_fork_heredoc(pipel.redir[z],
							var_redir) == 1)
					return (1);
			}
		}
		else if (pipel.redir[z].file_out != NULL)
		{
			if (pipel.redir[z].type == _APPROUT)
				close(var_redir->fd_out);
			else if (pipel.redir[z].type == _ROUT)
				close(var_redir->fd_out);
		}
		z++;
	}
	return (0);
}

int		fork_exec_child(t_separateurs sep, char **my_envp,
		t_var_redir *var_redir)
{
	dup2(var_redir->fd_int, 0);
	dup2(var_redir->fd_out, 1);
	if (sep.len > 1)
		close_pipe_child(var_redir);
	close_redir_child(sep.pipel[var_redir->y], var_redir);
	exec_cmd(sep.pipel[var_redir->y].argc, sep.pipel[var_redir->y].argv,
			my_envp);
	exit(0);
}

int		fork_exec(t_separateurs sep, char **my_envp, t_var_redir *var_redir)
{
	pid_t		father;

	father = fork();
	if (father == 0)
		fork_exec_child(sep, my_envp, var_redir);
	else if (father > 0)
	{
		if (sep.len > 1)
			close_pipe_father(var_redir);
		if (close_redir_father(sep.pipel[var_redir->y], var_redir, 0) == 1)
			return (1);
	}
	else
	{
		write(2, "error fork\n", 11);
		return (1);
	}
	return (0);
}

int		add_redir_int(t_pipelines pipel, t_history *history_first,
		t_var_redir *var_redir, int z)
{
	if (pipel.redir[z].type == _RINT)
		var_redir->fd_int = open(pipel.redir[z].file_int , O_RDONLY);
	else if (pipel.redir[z].type == _HEREDOC)
	{
		creat_heredoc(pipel, history_first, z);
		if (pipe(var_redir->pipefd_here) == -1)
		{
			write(2, "error pipe\n", 11);
			return (1);
		}
		var_redir->fd_int = var_redir->pipefd_here[0];
	}
	return (0);
}

int		add_redir_out(t_pipelines pipel, t_var_redir *var_redir, int z)
{
	if (pipel.redir[z].type == _APPROUT)
		var_redir->fd_out = open(pipel.redir[z].file_out, O_RDWR | O_CREAT
				| O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (pipel.redir[z].type == _ROUT)
		var_redir->fd_out = open(pipel.redir[z].file_out, O_RDWR | O_CREAT
				| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	return (0);
}

int		add_redir(t_pipelines pipel, t_history *history_first,
		t_var_redir *var_redir)
{
	int	z;

	z = 0;
	while (z < pipel.len)
	{
		if (pipel.redir[z].file_int != NULL)
		{
			if (add_redir_int(pipel, history_first, var_redir, z) == 1)
				return (1);
		}
		else if (pipel.redir[z].file_out != NULL)
			add_redir_out(pipel, var_redir, z);
		z++;
	}
	return (0);
}

int		add_pipe_mid(t_var_redir *var_redir)
{
	if (pipe((var_redir->int_or_out == 0 ? var_redir->pipefd_one :
					var_redir->pipefd_two)) == -1)
	{
		write(2, "error pipe\n", 11);
		return (1);
	}
	var_redir->fd_int = (var_redir->int_or_out == 1 ?
			var_redir->pipefd_one[0] : var_redir->pipefd_two[0]);
	var_redir->fd_out = (var_redir->int_or_out == 0 ?
			var_redir->pipefd_one[1] : var_redir->pipefd_two[1]);
	return (0);
}

int		add_pipe(t_var_redir *var_redir)
{
	if (var_redir->y == 0)
	{
		if (pipe((var_redir->int_or_out == 0 ? var_redir->pipefd_one :
						var_redir->pipefd_two)) == -1)
		{
			write(2, "error pipe\n", 11);
			return (1);
		}
		var_redir->fd_out = (var_redir->int_or_out == 0 ?
				var_redir->pipefd_one[1] : var_redir->pipefd_two[1]);
	}
	else if (var_redir->y == var_redir->end_pipe)
		var_redir->fd_int = (var_redir->int_or_out == 1 ?
				var_redir->pipefd_one[0] : var_redir->pipefd_two[0]);
	else
		if (add_pipe_mid(var_redir) == 1)
			return (1);
	return (0);
}

int		while_sep(t_separateurs sep, char **my_envp, t_history *history_first,
		t_var_redir *var_redir)
{
	int			status;
	int			rep;

	while (var_redir->y < sep.len)
	{
		var_redir->fd_int = 0;
		var_redir->fd_out = 1;
		if (sep.len > 1)
			if (add_pipe(var_redir) == 1)
				return (1);
		if (add_redir(sep.pipel[var_redir->y], history_first, var_redir) == 1)
			return (1);
		if (fork_exec(sep, my_envp, var_redir) == 1)
			return (1);
		var_redir->int_or_out = !var_redir->int_or_out;
		var_redir->y++;
	}
	while ((rep = waitpid(-1, &status, 0)) > -1)
	{
		printf("wait = [%d], rep = [%d]\n", rep, WEXITSTATUS(status));
	}
	return (0);
}

int		exec_base(t_parser_shell base, char **my_envp,
		t_history *history_first)
{
	int			x;
	t_var_redir	var_redir;

	x = 0;
	var_redir.pipefd_one[0] = -1;
	var_redir.pipefd_two[0] = -1;
	var_redir.pipefd_here[0] = -1;
	var_redir.pipefd_one[1] = -1;
	var_redir.pipefd_two[1] = -1;
	var_redir.pipefd_here[1] = -1;
	while (x < base.len)
	{
		var_redir.y = 0;
		var_redir.int_or_out = 0;
		var_redir.end_pipe = base.sep[x].len - 1;
		if (while_sep(base.sep[x], my_envp, history_first, &var_redir) == 1)
			return (1);
		x++;
	}
	return (0);
}
