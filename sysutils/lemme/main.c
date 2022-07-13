// lemme - a simple setsuid shell privilege escalator for Mac OS
// Copyright (C) 2022  Walter B. Vaughan
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// When run, replace self with the default (or specified) shell in interactive mode, passing all arguments along as needed.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
extern char **environ;

#ifndef LEMME_DEFAULT_SHELL
#define LEMME_DEFAULT_SHELL "/bin/zsh"
#endif

int main(int argc, char** argv) {
	// fallback to default shell for recent Mac OS (zsh)
	const char* sh = LEMME_DEFAULT_SHELL;

	// shell environment variable to search for
	const char* const shvar = "SHELL";
	const size_t      shlen = strlen(shvar);

	// terminal session ID (don't want to keep this)
	const char* const seshvar = "TERM_SESSION_ID";
	const size_t      seshlen = strlen(seshvar);


	for (char** e = environ; *e != NULL; e++) {
		if ((strncmp(shvar, *e, shlen) == 0) && ((*e)[shlen] == '=')) {
			// if shell is specified, use it instead
			sh = (*e) + shlen + 1;
		} else if ((strncmp(seshvar, *e, seshlen) == 0) && ((*e)[seshlen] == '=')) {
			// truncate terminal session id with 'empty string'
			*e[0] = '\0';
		}
	}

	// overwrite the invoked command name; we don't need it anymore
	// and force interactive mode for (POSIX-compliant) shells
	argv[0] = "-i";

	// run our interactive shell
	execve(sh, argv, environ);
}
