:let mapleader = ","
:nnoremap <leader>ev :vsplit $MYVIMRC<cr>
:inoremap jk <esc>

":inoremap <esc> <nop>
":inoremap <left> <nop>
":inoremap <right> <nop>
":inoremap <up> <nop>
":inoremap <down> <nop>
":nnoremap <left> <nop>
":nnoremap <right> <nop>
":nnoremap <up> <nop>
":nnoremap <down> <nop>

":autocmd BufWritePre,BufRead *.cpp,*.[ch],sh,*.java :normal! gg=G
":autocmd BufWritePre *.cpp,*.[ch],sh,*.java :normal! gg=G


set nu
syntax on
"set cindent
set tabstop=4
set softtabstop=4
set shiftwidth=4
set noerrorbells
set hlsearch
set tags=tags;/
set nocompatible
set laststatus=2
set statusline=%F%m%r%h%w\ [FORMAT=%{&ff}]\ [TYPE=%Y]\ [POS=%l,%v][%p%%]\ %{strftime(\"%d/%m/%y\ -\ %H:%M\")} "
set showmatch
set completeopt=preview,menu

set cursorline
" Default Colors for CursorLine
highlight  CursorLine ctermbg=Blue ctermfg=Red
" Change Color when entering Insert Mode
autocmd InsertEnter * highlight  CursorLine
" Revert Color to default when leaving Insert Mode
autocmd InsertLeave * highlight  CursorLine ctermbg=Blue ctermfg=Red


autocmd BufNewFile *.cpp,*.cc,*.[ch],*.sh,*.java exec ":call SetTitle()"

func SetTitle()

if &filetype == 'sh'
call setline(1,"\################################################")
call append(line("."), "\# Copyright (c) 2015 xxxx Inc, All rights reserved.")
call append(line(".")+1, "\#")
call append(line(".")+2, "\# Script Name: ".expand("%"))
call append(line(".")+3, "\#")
call append(line(".")+4, "\# Description:")
call append(line(".")+5, "\#")
call append(line(".")+6, "\# Created: ".strftime("%F"))
call append(line(".")+7, "\# Author: written by jiangzhe.")
call append(line(".")+8, "\#")
call append(line(".")+9, "\################################################")
call append(line(".")+10, "\#! /bin/sh -")
call append(line(".")+11, " ")
else
call setline(1, "/*")
call append(line("."), " * Copyright (c) 2015 xxxx Inc, All rights reserved.")
call append(line(".")+1, " * Created: ".strftime("%F"))
call append(line(".")+2, " */")
call append(line(".")+3, " ")
endif

if &filetype == 'cpp'
"call append(line(".")+12, "#include<iostream>")
"call append(line(".")+13, "using namespace std;")
"call append(line(".")+14, "")
endif

if &filetype == 'c'
"call append(line(".")+12, "#include<stdio.h>")
"call append(line(".")+13, "")
endif

endfunc

autocmd BufNewFile * :normal! G

