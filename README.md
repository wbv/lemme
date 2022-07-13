lemme
=====

## Warning

This program is a terrible idea to have laying around. It explicitly allows any
user on a system to acquire the permissions of the user who installed it. It
was explicitly designed to get around the fact that most operating systems
choose not to honor setsuid when invoked on a shell program, a choice which was
made because of the immense security problems such an escalation creates. This
program recreates that security hole.

Only install this program if you are familiar with the dangers of setsuid and
the sticky bit, and you want to give every user of your machine (including
uninvited or hostile users if your machine is compromised over the network) the
ability to run a shell with root privileges.

-------------------------------------------------------------------------------

*lemme* is a simple set-suid program for MacPorts which intentionally breaks
reasonable security measures by allowing users to run an interactive shell with
escalated privileges. If installed by root, you will be able to elevate your
effective user and group IDs to root. If installed as another user, you will
inherit the effective user and group IDs of the user who installed the program.

By default, lemme starts `$SHELL` or `/bin/zsh` with the environment variables
of its invoking shell.

### Installation
After cloning this repository, `cd` into the it, all the way into folder
containing the Portfile. Then install via `port` as the root user:

```
user@macbook ~ % cd lemme/sysutils/lemme
user@macbook lemme % sudo port install
```

And check that it works:

```
user@macbook lemme % id -u && -g
502     # user ID
20      # group ID
user@macbook lemme % lemme
user@macbook lemme #
0       # root's user ID
80      # admin's group ID
user@macbook lemme # exit
user@macbook lemme ~
```

## Making changes
The Portfile is written to download the tar.gz from the same directory you're
in, so you'll need `lemme.tar.gz` to actually install it. There might be a
better way to do this, but I clearly don't know how MacPorts works that well.

If you want to change the source code and reinstall, you'll need to rebuild the
`lemme.tar.gz` distributable which requires `make` and `tar`, but you probably
have those installed if you are able to install `lemme` in the first place.

## Bugfixes or other platforms
I have no intention of modifying this to work with anybody else's setup. Sorry.
PRs will likely be ignored.
