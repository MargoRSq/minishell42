enum e_controls
{
	d_quote			= (int)'"',
	s_quote         = (int)'\'',
	l_corner		= (int)'<',
	r_corner	    = (int)'>',
	o_parenth	    = (int)'(',
	c_parenth	    = (int)')',
	escape			= (int)'\\',
	slash			= (int)'/',
	pipes			= (int)'|',
	colon			= (int)':',
	equal		    = (int)'=',
	question		= (int)'?',
	dollar			= (int)'$',
	ampersand		= (int)'&',
	underscore		= (int)'_',
	space			= (int)' ',
	asterisk		= (int)'*',
	dot				= (int)'.',
	tab				= (int)'\t',
	endl			= (int)'\n',
	vtab			= (int)'\v',
	cr				= (int)'\r',
	ends			= (int)'\0',
};

enum e_tokens
{
	d_quote_str = 1,
	s_quote_str = 2,
	r_in = 3,
	r_out = 4,
	r_append = 5,
	heredoc = 6,
	word = 7
};

enum e_exits
{
	all_ok = 0,
	malloc_error = 1,
	env_error = 2,
	unclosed_quote_error = 3,
	home_error = 4,
	pwd_error = 5
};