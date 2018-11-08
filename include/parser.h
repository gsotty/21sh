#ifndef PARSER_H
# define PARSER_H

#include <unistd.h>

/*
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
*/

/*
** Define du lexer
*/

# define _WORD 1
# define _SEP 2
# define _PIPE 3
# define _ROUT 4
# define _RINT 5
# define _APPROUT 6
# define _HEREDOC 7
# define _OR 8
# define _AND 9
# define _DUP_ROUT 10
# define _DUP_RINT 11
# define _ROUTERR 12
# define _FD 13
# define _DIGIT 14
# define _ARGV 15
# define _SPACE 16
# define _TIRET 17
# define _CMD 18
# define _FILE_NAME 19
# define _NEW_LINE 20
# define _NBR 21

#endif
