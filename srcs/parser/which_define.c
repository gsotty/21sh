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
	else
		return ("unknown");
}

static char	*which_define_four(int nbr)
{
	if (nbr == 37)
		return ("_NEW_LINE"); 
	else if (nbr == 0)
		return ("_OTHER"); 
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
	if (nbr == 28)
		return ("_SQUARE_BRACKET_RIGHT"); 
	else if (nbr == 29)
		return ("_CARET"); 
	else if (nbr == 30)
		return ("_UNDERSCORE"); 
	else if (nbr == 31)
		return ("_PRIME"); 
	else if (nbr == 32)
		return ("_CURLY_BRACKET_RIGHT"); 
	else if (nbr == 33)
		return ("_PIPE"); 
	else if (nbr == 34)
		return ("_CURLY_BRACKET_LEFT"); 
	else if (nbr == 35)
		return ("_TILDE"); 
	else if (nbr == 36)
		return ("_TAB"); 
	else
		return (which_define_four(nbr));
}

static char	*which_define_two(int nbr)
{
	if (nbr == 19)
		return ("_SEP"); 
	else if (nbr == 20)
		return ("_GUILLEMET_LEFT"); 
	else if (nbr == 21)
		return ("_EQUAL_SIGN"); 
	else if (nbr == 22)
		return ("_GUILLEMET_RIGHT"); 
	else if (nbr == 23)
		return ("_QUESTION_MARK"); 
	else if (nbr == 24)
		return ("_AT_SIGN"); 
	else if (nbr == 25)
		return ("_ALPHA"); 
	else if (nbr == 26)
		return ("_SQUARE_BRACKET_LEFT"); 
	else if (nbr == 27)
		return ("_BACKSLASH"); 
	else
		return (which_define_three(nbr));
}

static char	*which_define_one(int nbr)
{
	if (nbr == 10)
		return ("_ROUND_BRACKET_RIGHT"); 
	else if (nbr == 11)
		return ("_ASTERISK"); 
	else if (nbr == 12)
		return ("_PLUS_SIGN"); 
	else if (nbr == 13)
		return ("_COMMA"); 
	else if (nbr == 14)
		return ("_HYPHEN"); 
	else if (nbr == 15)
		return ("_FULL_STOP"); 
	else if (nbr == 16)
		return ("_SLASH"); 
	else if (nbr == 17)
		return ("_DIGIT"); 
	else if (nbr == 18)
		return ("_COLON"); 
	else
		return (which_define_two(nbr));
}


char	*which_define(int nbr)
{
	if (nbr == 1)
		return ("_SPACE"); 
	else if (nbr == 2)
		return ("_EXCLAMATION_MARK"); 
	else if (nbr == 3)
		return ("_DOUBLE_QUOTE"); 
	else if (nbr == 4)
		return ("_POUND"); 
	else if (nbr == 5)
		return ("_DOLLAR_SIGN"); 
	else if (nbr == 6)
		return ("_PORCENT_SIGN"); 
	else if (nbr == 7)
		return ("_AMPERSAND"); 
	else if (nbr == 8)
		return ("_APOSTROPHE"); 
	else if (nbr == 9)
		return ("_ROUND_BRACKET_LEFT"); 
	else
		return (which_define_one(nbr));
}
