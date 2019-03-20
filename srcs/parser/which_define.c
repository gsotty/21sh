#include "../../include/parser.h"

static char	*which_define_five(int nbr)
{
	if (nbr == 45)
		return ("_DUP_ROUT");
	else if (nbr == 46)
		return ("_DUP_RINT");
	else if (nbr == 47)
		return ("_ROUTERR");
	else if (nbr == 48)
		return ("_FD");
	else if (nbr == 49)
		return ("_ARGV");
	else if (nbr == 50)
		return ("_CMD");
	else if (nbr == 51)
		return ("_FILE_NAME");
	else if (nbr == 52)
		return ("_DEL");
	else if (nbr == -5)
		return ("_WORD");
	else if (nbr == -6)
		return ("_SKIP");
	else
		return ("unknown");
}

static char	*which_define_four(int nbr)
{
	if (nbr == 10)
		return ("_NEW_LINE");
	else if (nbr == 38)
		return ("_WORD");
	else if (nbr == 39)
		return ("_ROUT");
	else if (nbr == 40)
		return ("_RINT");
	else if (nbr == 41)
		return ("_APPROUT");
	else if (nbr == 42)
		return ("_HEREDOC");
	else if (nbr == 43)
		return ("_OR");
	else if (nbr == 44)
		return ("_AND");
	else
		return (which_define_five(nbr));
}

static char	*which_define_three(int nbr)
{
	if (nbr == 93)
		return ("_SQUARE_BRACKET_RIGHT");
	else if (nbr == 94)
		return ("_CARET");
	else if (nbr == 95)
		return ("_UNDERSCORE");
	else if (nbr == 96)
		return ("_PRIME");
	else if (nbr == 123)
		return ("_CURLY_BRACKET_RIGHT");
	else if (nbr == 124)
		return ("_PIPE");
	else if (nbr == 125)
		return ("_CURLY_BRACKET_LEFT");
	else if (nbr == 126)
		return ("_TILDE");
	else
		return (which_define_four(nbr));
}

static char	*which_define_two(int nbr)
{
	if (nbr == 59)
		return ("_SEP");
	else if (nbr == 60)
		return ("_GUILLEMET_LEFT");
	else if (nbr == 61)
		return ("_EQUAL_SIGN");
	else if (nbr == 62)
		return ("_GUILLEMET_RIGHT");
	else if (nbr == 63)
		return ("_QUESTION_MARK");
	else if (nbr == 64)
		return ("_AT_SIGN");
	else if (nbr == -4)
		return ("_ALPHA");
	else if (nbr == 91)
		return ("_SQUARE_BRACKET_LEFT");
	else if (nbr == 92)
		return ("_BACKSLASH");
	else
		return (which_define_three(nbr));
}

static char	*which_define_one(int nbr)
{
	if (nbr == 41)
		return ("_ROUND_BRACKET_RIGHT");
	else if (nbr == 42)
		return ("_ASTERISK");
	else if (nbr == 43)
		return ("_PLUS_SIGN");
	else if (nbr == 44)
		return ("_COMMA");
	else if (nbr == 45)
		return ("_HYPHEN");
	else if (nbr == 46)
		return ("_FULL_STOP");
	else if (nbr == 47)
		return ("_SLASH");
	else if (nbr == -3)
		return ("_DIGIT");
	else if (nbr == 58)
		return ("_COLON");
	else
		return (which_define_two(nbr));
}


char	*which_define(int nbr)
{
	if (nbr == -1)
		return ("_NOPRINT");
	else if (nbr == -2)
		return ("_SPACE");
	else if (nbr == 4)
		return ("_EOT");
	else if (nbr == 33)
		return ("_EXCLAMATION_MARK");
	else if (nbr == 34)
		return ("_DOUBLE_QUOTE");
	else if (nbr == 35)
		return ("_POUND");
	else if (nbr == 36)
		return ("_DOLLAR_SIGN");
	else if (nbr == 37)
		return ("_PORCENT_SIGN");
	else if (nbr == 38)
		return ("_AMPERSAND");
	else if (nbr == 39)
		return ("_APOSTROPHE");
	else if (nbr == 40)
		return ("_ROUND_BRACKET_LEFT");
	else
		return (which_define_one(nbr));
}
