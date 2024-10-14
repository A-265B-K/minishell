Steps
	1. Get input
	2. Break the input apart into words and operators
		These are called tokens
		this follows quoting rules https://www.gnu.org/software/bash/manual/bash.html#Quoting
		tokens are seperated by metacharacters
		alias expansion is performed
	3. Parses tokens into simple and compound commands
	4. Performs shell expansions
		https://www.gnu.org/software/bash/manual/bash.html#Shell-Expansions
	5. (Optionally) performs redirections
		removes redirection operators and their operands from the argument list
	6. Execute commands
	7. (optionally) wait for the command to complete and collect its exit status

Summary
	When the shell reads input, it proceeds through a sequence of operations. If the input indicates the beginning of a comment, the shell ignores the comment symbol (‘#’), and the rest of that line.

	Otherwise, roughly speaking, the shell reads its input and divides the input into words and operators, employing the quoting rules to select which meanings to assign various words and characters.

	The shell then parses these tokens into commands and other constructs, removes the special meaning of certain words or characters, expands others, redirects input and output as needed, executes the specified command, waits for the command’s exit status, and makes that exit status available for further inspection or processing. 

Subject requiremens
	Display a prompt when waiting for a new command.
	Have a working history.
	Search and launch the right executable (based on the PATH variable or using a
		relative or an absolute path).
	Avoid using more than one global variable to indicate a received signal. Consider
	the implications: this approach ensures that your signal handler will not access your
	main data structures
	have a working history
	handle single quotes '
	handle double quotes "
	Implement redirections < << > >>
	implement pipes |
	Handle environment variables $
	handle $?
	handle ctrl-C, ctrl-D, ctrl-\, and handle them in interactive mode (what is interactive mode, and do they work differently there?)
	implement builtins:
		echo, with option -n
		cd, with only a relative or absolute path
		pwd
		export
		unset
		env
		exit
	The readline() function can cause memory leaks. You don’t have to fix them. But
		that doesn’t mean your own code can have memory leaks.

	Bonus
		&& and || with parenthesis for priorities
		wildcards should work for the current working directory

	questions
		are compound commands required?
		are shell expansions required?


definitions
	quoting
		Quoting is used to remove the special meaning of certain characters or words to the shell. Quoting can be used to disable special treatment for special characters, to prevent reserved words from being recognized as such, and to prevent parameter expansion. 
		There are three quoting mechanisms: the escape character, single quotes, and double quotes. 

		https://www.gnu.org/software/bash/manual/bash.html#Quoting

	token
		A sequence of characters considered a single unit by the shell. It is either a word or an operator.
		Whitespace is not part of a token and separates tokens.
		A token is made up of ordinary characters, or of operator characters ()<>&|;, but not both. For example, foo<@a&>b consists of the tokens foo (ordinary), < (operator), @a (ordinary), &> (operator) and b.

	Compound command
		A compound command is a couple of commands that are grouped in some way and are all executed in close succession
		From man bash:

		Compound Commands

		A compound command is one of the following. In most cases a list in a command's description may be separated from the rest of the command by one or more newlines, and may be followed by a newline in place of a semicolon.

		(list)

		list is executed in a subshell environment (see COMMAND EXECUTION ENVIRONMENT below). Variable assignments and builtin commands that affect the shell's environment do not remain in effect after the command completes. The return status is the exit status of list.

		{ list; }

		list is simply executed in the current shell environment. list must be terminated with a newline or semicolon. This is known as a group command. The return status is the exit status of list. Note that unlike the metacharacters ( and ), { and } are reserved words and must occur where a reserved word is permitted to be recognized. Since they do not cause a word break, they must be separated from list by whitespace or
		another shell metacharacter.

		((expression))

		The expression is evaluated according to the rules described below under ARITHMETIC EVALUATION. If the value of the expression is non-zero, the return status is 0; otherwise the return status is 1. This is exactly equivalent to let "expression".

		[[ expression ]]

		Return a status of 0 or 1 depending on the evaluation of the conditional expression expression. Expressions are composed of the primaries described below under CONDITIONAL EXPRESSIONS. Word splitting and pathname expansion are not performed on the words between the [[ and ]]; tilde expansion, parameter and variable expansion, arithmetic expansion, command substitution, process substitution, and quote removal are performed. Conditional operators such as -f must be unquoted to be recognized as primaries.

		When used with [[, the < and > operators sort lexicographically using the current locale.
