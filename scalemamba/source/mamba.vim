if exists("b:current_syntax")
  finish
endif

set syntax=python

syntax match mambaType "sint"
syntax match mambaType "cint" 
syntax match mambaType "sfloat" 
syntax match mambaType "cfloat"
syntax match mambaType "sfix" 
syntax match mambaType "cfix"
highlight link mambaType Type

let b:current_syntax = "mamba"

