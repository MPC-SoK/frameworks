if exists("b:current_syntax")
  finish
endif

" preliminary syntax higlighting for wysteria
" to use, first add filetype detection for wysteria files
"   echo "au BufNewFile,BufRead *.wy set filetype=wysteria" >> "~/.vim/ftdetect/wysteria.vim
" then copy this file to your vim syntax folder
"   cp wysteria.vim ~/.vim/syntax/

syntax keyword wyKeyword let in wfold wire
syntax keyword wyKeyword if then else
syntax keyword wyKeyword sysop send run recv
highlight link wyKeyword Keyword

syntax region wyComment start=/\v\(\*/ end=/\v\*\)/
highlight link wyComment Comment

syntax match wyOp "\v\="
syntax match wyOp "\v\\"
syntax match wyOp "\v\+"
syntax match wyOp "\v\-"
highlight link wyOp Operator

syntax match wyID "\v!\w+"
highlight link wyId Identifier

syntax keyword wyRepeat for do done
highlight link wyRepeat Repeat

syntax match wyFunc "\v\@sec" 
syntax match wyFunc "\v\@ sec" 
syntax match wyFunc "\v\@par" 
syntax match wyFunc "\v\@ par" 
syntax keyword wyFunc select update
syntax match wyFunc "\v\<\-"
highlight link wyFunc Function

syntax keyword wyType array of
highlight link wyType Type

"match numbers (stolen from c)
syn match wyNumber "\d\+\(u\=l\{0,2}\|ll\=u\)\>"
highlight link wyNumber Number
" but don't match numbers at the ends of words
syn match wyGarbage "\v[[:alpha:]]\d+"

let b:current_syntax = "wysteria"
