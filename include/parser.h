/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:35:02 by gsotty            #+#    #+#             */
/*   Updated: 2019/04/04 16:41:26 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <sys/wait.h>
# include "../lib/libft/libft.h"
# include "./vingt_et_un_sh.h"
# include "./history.h"
# include "./lchar.h"

/*
**	1er block:
**		' " and \
**
**	1er block:
**		_SEP = separateur: {;}
**	2eme block:
**		_PIPE = pipe: {|}
**	3eme block:
**		_ROUTERR = redirection output est erreur: {&>} || {>&} fd = 2 est
**						digit = 1
**		_DUP_FD = dupication fd: {[N][<>]&digit}
**		_CLOSE_FD = close fd: {[N][<>]&-}
**		_APPROUT = append redirection output: {[N]>>} N de base a 1
**		_HEREDOC = Here documents: {[N]<<[-]} N de base a 0
**	4eme block:
**		_RINT = redirection input: {[N]<} N de base a 0
**		_ROUT = redirection output: {[N]>[|]} N de base a 1
**	5eme block:
**		_FD = les fd pour les redirection: avant une redirection [*0-9]
**		_FILE = fichier pour les redirection: aprait une redirection
**		_WORD = cmd est argv: c'est les mot restant
**		_SPACE = espace: [ ]
**
**		(^ _) = _OTHER
**		" " = _SPACE
**		! = _EXCLAMATION_MARK
**		" = _DOUBLE_QUOTE
**		# = _POUND
**		$ = _DOLLAR_SIGN
**		% = _PORCENT_SIGN
**		& = _AMPERSAND
**		' = _APOSTROPHE
**		( = _ROUND_BRACKET_LEFT
**		) = _ROUND_BRACKET_RIGHT
**		* = _ASTERISK
**		+ = _PLUS_SIGN
**		, = _COMMA
**		- = _HYPHEN
**		. = _FULL_STOP
**		/ = _SLASH
**		(all the number) = _DIGIT
**		: = _COLON
**		; = _SEP
**		< = _GUILLEMET_LEFT
**		= = _EQUAL_SIGN
**		> = _GUILLEMET_RIGHT
**		? = _QUESTION_MARK
**		@ = _AT_SIGN
**		(all the letter) = _ALPHA
**		[ = _SQUARE_BRACKET_LEFT
**		\ = _BACKSLASH
**		] = _SQUARE_BRACKET_RIGHT
**		^ = _CARET
**		_ = _UNDERSCORE
**		` = _PRIME
**		{ = _CURLY_BRACKET_LEFT
**		| = _PIPE
**		} = _CURLY_BRACKET_RIGHT
**		~ = _TILDE
**		(\t \v) = _TAB
**		(\n) = _NEW_LINE
*/

# define _NOPRINT -1
# define _SPACE -2
# define _EOT 4
# define _NEW_LINE 10
# define _EXCLAMATION_MARK 33
# define _DOUBLE_QUOTE 34
# define _POUND 35
# define _DOLLAR_SIGN 36
# define _PORCENT_SIGN 37
# define _AMPERSAND 38
# define _APOSTROPHE 39
# define _ROUND_BRACKET_LEFT 40
# define _ROUND_BRACKET_RIGHT 41
# define _ASTERISK 42
# define _PLUS_SIGN 43
# define _COMMA 44
# define _HYPHEN 45
# define _FULL_STOP 46
# define _SLASH 47
# define _DIGIT -3
# define _COLON 58
# define _SEP 59
# define _GUILLEMET_LEFT 60
# define _EQUAL_SIGN 61
# define _GUILLEMET_RIGHT 62
# define _QUESTION_MARK 63
# define _AT_SIGN 64
# define _ALPHA -4
# define _SQUARE_BRACKET_LEFT 91
# define _BACKSLASH 92
# define _SQUARE_BRACKET_RIGHT 93
# define _CARET 94
# define _UNDERSCORE 95
# define _PRIME 96
# define _CURLY_BRACKET_LEFT 123
# define _PIPE 124
# define _CURLY_BRACKET_RIGHT 125
# define _TILDE 126

# define _NOT 0
# define _WORD 1

# define _RINT 2

# define _ROUT 3
# define _APPROUT 4

# define _RRDWR 5

# define _HEREDOC 6

# define _DUPINT 7
# define _DUPOUT 8

# define _INTFD 9
# define _FILE 10

/*
**	stack la commande avant execution:
**		;
**			|
**				&>, <&, >&, <<, >>
**					<, >
**						[*0-9], [file], [cmd], [argv], [ ]
**
**	effect ['], ["], [\]
*/

typedef struct		s_var_redir
{
	int				y;
	int				end_pipe;
	int				fd_int;
	int				fd_out;
	int				int_or_out;
	int				pipefd_one[2];
	int				pipefd_two[2];
	int				pipefd_here[2];
}					t_var_redir;

typedef struct		s_redir
{
	int				type;
	int				fd_int;
	char			*file_int;
	int				fd_out;
	char			*file_out;
}					t_redir;

typedef struct		s_redirections
{
	int				type;
	int				fd_int;
	char			*file_int;
	int				fd_out;
	char			*file_out;
	int				len_heredoc;
	char			*heredoc;
}					t_redirections;

typedef struct		s_pipefd
{
	int				var;
	int				one[2];
	int				two[2];
	int				here_doc[2];
}					t_pipefd;

typedef struct		s_fdexec
{
	int				in;
	int				out;
	int				fd_in;
	int				fd_out;
	int				close;
	int				src;
	int				dest;
	t_lchar			*here_document;
}					t_fdexec;

typedef struct		s_process
{
	int				rep;
	pid_t			id;
}					t_process;

typedef struct		s_lenexec
{
	int				nbr_process;
	int				sep;
	int				*pipe;
	int				**cmd;
}					t_lenexec;

typedef struct		s_typecmd
{
	int				len;
	char			*c;
	int				*type;

	int				type_cmd;
	t_lchar			*here_document;
	int				l_fd;
	int				r_fd;
	int				digit;
	t_lchar			*file;

	int				block;

	int				len_heredoc;
	char			*heredoc;
}					t_typecmd;

typedef struct		s_pipelines
{
	int				argc;
	t_typecmd		**argv;
}					t_pipelines;

typedef struct		s_separateurs
{
	t_pipelines		*pipel;
	int				len;
}					t_separateurs;

typedef struct		s_parser_shell
{
	t_separateurs	*sep;
	int				len;
}					t_parser_shell;

#endif
