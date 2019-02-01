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
 **		_DUP_INPUT = dupication input: {[N]<&digit[-]} N de base a 0
 **		_DUP_OUTPUT = dupication output: {[N]>&digit[-]} N de base a 1
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
 **
 */

# define _OTHER 0
# define _SPACE 1
# define _EXCLAMATION_MARK 2
# define _DOUBLE_QUOTE 3
# define _POUND 4
# define _DOLLAR_SIGN 5
# define _PORCENT_SIGN 6
# define _AMPERSAND 7
# define _APOSTROPHE 8
# define _ROUND_BRACKET_LEFT 9
# define _ROUND_BRACKET_RIGHT 10
# define _ASTERISK 11
# define _PLUS_SIGN 12
# define _COMMA 13
# define _HYPHEN 14
# define _FULL_STOP 15
# define _SLASH 16
# define _DIGIT 17
# define _COLON 18
# define _SEP 19
# define _GUILLEMET_LEFT 20
# define _EQUAL_SIGN 21
# define _GUILLEMET_RIGHT 22
# define _QUESTION_MARK 23
# define _AT_SIGN 24
# define _ALPHA 25
# define _SQUARE_BRACKET_LEFT 26
# define _BACKSLASH 27
# define _SQUARE_BRACKET_RIGHT 28
# define _CARET 29
# define _UNDERSCORE 30
# define _PRIME 31
# define _CURLY_BRACKET_LEFT 32
# define _PIPE 33
# define _CURLY_BRACKET_RIGHT 34
# define _TILDE 35
# define _TAB 36
# define _NEW_LINE 37

/*
 ** Define du lexer
 */

# define _WORD 38
# define _ROUT 39
# define _RINT 40
# define _APPROUT 41
# define _HEREDOC 42
# define _OR 43
# define _AND 44
# define _DUP_ROUT 45
# define _DUP_RINT 46
# define _ROUTERR 47
# define _FD 48
# define _ARGV 49
# define _CMD 50
# define _FILE_NAME 51
# define _DEL 52

/*
 **	stack la commande avant execution:
 **		;
 **			|
 **				&>, <&, >&, <<, >>
 **					<, >
 **						[*0-9], [file], [cmd], [argv], [ ]
 **
 **	effect ['], ["], [\]
 **
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

typedef struct		s_pipelines
{
	char			**argv;
	int				argc;
	t_redirections	*redir;
	int				len;
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

char	*which_define(int nbr);
int		cut_quoting(t_lchar *buf);
int		cut_commands(t_lchar *buf);
int		creat_cmd(t_lchar *buf, int start_pipe,
		int end_pipe, t_pipelines *pipe);
int		creat_redirection(t_lchar *buf, int start_pipe,
		int end_pipe, t_pipelines *pipe);
int		creat_pipe(t_lchar *buf, int start_sep,
		int end_sep, t_separateurs *sep);
int		creat_sep(t_lchar *buf, t_parser_shell *base);
int		creat_heredoc(t_pipelines pipe, t_history *history_first, int z);

#endif
