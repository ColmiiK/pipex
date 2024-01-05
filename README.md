<div align="center">
    <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/pipex-light.png?raw=true#gh-light-mode-only" alt="Banner (claro)" />
    <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/pipex-dark.png?raw=true#gh-dark-mode-only" alt="Banner (oscuro)" />
    <br>
    This project will let you discover in detail a UNIX mechanism that you already know
by using it in your program.
    <br>
    <a href='https://profile.intra.42.fr/users/alvega-g' target="_blank">
        <img alt='42 (oscuro)' src='https://img.shields.io/badge/Málaga-black?style=flat&logo=42&logoColor=white'/>
    </a>
    <img src="https://img.shields.io/badge/score- 125%20%2F%20100-success?color=%2312bab9&style=flat" />
    <img src="https://wakatime.com/badge/user/018cd069-7ab6-4658-9d62-78d9b3970dd2/project/018cd069-ed6a-4aad-961f-bb95404cfd4c.svg" alt="Tiempo" />
</div>

---

# Mandatory part

<table>
  <tr>
    <th>Program name</th>
    <td><em>pipex</em></td>
  </tr>
  <tr>
    <th>Turn in files</th>
    <td>Makefile, <code>*.h</code>, <code>*.c</code></td>
  </tr>
  <tr>
	<th>Makefile</th>
	<td><em>NAME</em>, <em>all</em>, <em>clean</em>, <em>fclean</em>, <em>re</em></td>
  </tr>
  <tr>
    <th>Arguments</th>
    <td><code>file 1 cmd1 cmd2 file2</code></td>
  </tr>
  <tr>
    <th>External functions</th>
    <td> <code>open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid</code><br><code>ft_printf</code> and any equivalent YOU coded</td>
  </tr>
  <tr>
	<th>Libft authorized</th>
	<td>Yes</td>
  </td>
  <tr>
    <th>Description</th>
    <td>This project is about handling pipes.</td>
  </tr>
</table>

## Observations

Your program will be executed as follows:
``` bash
./pipex file1 cmd1 cmd2 file2
```
It must take 4 arguments:
- ``file1`` and ``file2`` are __file names__.
- ``cmd1`` and ``cmd2`` are __shell commands__ with their parameters.

It must behave exactly the same as the shell command below:
``` bash
$> < file1 cmd1 | cmd2 > file2
```	

## Examples
``` bash
$> ./pipex infile "ls -l" "wc -l" outfile
```
Should behave like: ``< infile ls -l | wc -l > outfile``
``` bash
$> ./pipex infile "grep a1" "wc -w" outfile
```
Should behave like: ``< infile grep a1 | wc -w > outfile``

## Requirements

Your project must comply with the following rules:
- You have to turn in a _Makefile_ which will compile your source files. It must not
relink.
- You have to handle errors thoroughly. In no way your program should quit unexpectedly (segmentation fault, bus error, double free, and so forth).
- Your program mustn’t have __memory leaks__.
- If you have any doubt, handle the errors like the shell command:
``< file1 cmd1 | cmd2 > file2``
# Bonus part

You will get extra points if you:
- Handle multiple pipes.<br>
This:
``` bash
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```
Should behave like:
``` bash
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
```
- Support « and » when the first parameter is "here_doc".<br>
This:
``` bash
$> ./pipex here_doc LIMITER cmd cmd1 file
```
Should behave like:
``` bash
cmd << LIMITER | cmd1 >> file
```