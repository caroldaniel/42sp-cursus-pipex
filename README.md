<h1 align=center>
	<b>pipex</b>
</h1>

<h2 align=center>
	 <i>42cursus' project #6</i>
</h2>

<p align=center>
	The <b>pipex</b> program is a executable for the `pipe` shell command, where you can redirect the output of some commands to the input of others. 
  
---
<div align=center>
<h2>
	Final score
</h2>
	<img src=https://github.com/caroldaniel/caroldaniel-utils/blob/e29ee7c7374778ba118c0d2d91aa428593f0ecb1/pipex_grade.png alt="cado-car's 42Project Score"/>
	<h4>Completed + Bonus</h4>
	<img src=https://github.com/caroldaniel/caroldaniel-utils/blob/e29ee7c7374778ba118c0d2d91aa428593f0ecb1/pipexm.png alt="cado-car's 42Project Badge"/>
</div>

---

<h3 align=center>
Mandatory
</h3>

> <i> pipex <b>must</b>: 
> - read and write from/to files;
> - redirect single pipes and truncate existing file output.</i>

<h3 align=center>
Bonus
</h3>

> <i> pipex <b>can</b>: 
> - redirect multiple commands;
> - open terminal for here_doc option.</i>

---

<h2>
The project
</h2>


### Implementation files
	
- [`Makefile`](Makefile)

Header files
- [`pipex.h`](include/pipex.h)

Main file	
- [`pipex.c`](srcs/pipex.c)

Utilities
- [`pipex_utils1.c`](srcs/pipex_utils1.c)
- [`pipex_utils2.c`](srcs/pipex_utils2.c)

Error management and program closing
- [`pipex_error.c`](srcs/pipex_error.c)

---
<h2>
Usage
</h2>

### Requirements
`pipex` requires a *clang* compiler and some standard libraries. 

### Instructions

Clone this repository in your local computer:

```sh
$> git clone https://github.com/caroldaniel/42sp-cursus-pipex.git path/to/pipex
```

In your local repository, run `make`

```sh
$> make 
```

> `make` suports 6 flags:
> - `make all` or simply `make` compiles pipex in its mandatory format
> - `make bonus` compiles pipex in its bonus format
> - `make clean` deletes the `.o` files generated during compilation
> - `make fclean` deletes the `.o` and the `pipex` file generated
> - `make re` executes `fclean` and `all` in sequence, recompiling the program
> - `make rebonus` executes `fclean` and `bonus` in sequence, recompiling the program with the bonus functions

To run `pipex`, type:
```sh
./pipex files/<choose-input-file> cmd1 cmd2 files/<choose-output-file>
# works like: 
< files/<choose-input-file> cmd1 | cmd2 > files/<choose-output-file>
```
For bonus' here_doc option, type: 
```sh
./pipex here_doc LIMITER cmd1 cmd2 files/<choose-output-file>
# works like: 
cmd1 << LIMITER | cmd2 >> files/<choose-output-file>
```
`./pipex` also works with multiple pipes. 
