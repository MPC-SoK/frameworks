if exists("b:current_syntax")
  finish
endif

set syntax=c

syntax match frigInclude "\v\#parties"
syntax match frigInclude "\v\#output"
syntax match frigInclude "\v\#input"
highlight link frigInclude Include


let b:current_syntax = "frigate"
