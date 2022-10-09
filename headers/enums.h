
typedef enum e_controls
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
}	t_symbols;

typedef enum e_tokens
{
	d_quote_str = 1,
	s_quote_str,
	r_in,
	r_out,
	r_append,
	r_heredoc,
	word,
	lpipe
}	t_token_type;

enum e_exits
{
	all_ok,
	malloc_error,
	env_error,
	unclosed_quote_error,
	oldpwd_error,
	chdir_error,
	home_error,
	cwd_error,
	env_arg_error,
	key_error,
	execve_error
	pwd_error,
	execve_error,
	pipe_error,
	fork_error
};

typedef enum e_signals
{
	sig_loop,
	sig_heredoc,
	sig_child
}	t_signal_type;
