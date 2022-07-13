# lemme - a simple setsuid shell privilege escalator for Mac OS
# Copyright (C) 2022  Walter B. Vaughan
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.


# fill in any unresolved automatic variables
TAR ?= tar
RM ?= rm -f
INSTALL ?= install

PREFIX ?= /usr/local

prefix ?= $(PREFIX)
exec_prefix ?= $(prefix)
bindir ?= $(exec_prefix)/bin


all: lemme


lemme: main.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@

install: all
	$(INSTALL) -D -m 6755 lemme $(DESTDIR)$(bindir)/lemme

install-strip: all
	$(INSTALL) -s -D -m 6755 lemme $(DESTDIR)$(bindir)/lemme

dist:
	$(TAR) -czf lemme.tar.gz main.c Makefile

uninstall:
	$(RM) $(DESTDIR)$(bindir)/lemme

clean:
	$(RM) lemme

dist-clean:
	$(RM) lemme.tar.gz


# remove automatic rules
.SUFFIXES:

# none of these targets make a file (they're phony)
.PHONY: all install install-strip dist uninstall clean dist-clean

