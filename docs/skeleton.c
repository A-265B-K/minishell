main
	init_program
	get_input
		display_prompt
		readline
		add_history
	process_input
		tokenize
			count odd/even quotes
			split into tokens
		shell_expand
	redirect
		remove redirections from tokens
	execute
	return exit code