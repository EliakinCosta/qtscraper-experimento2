#!/bin/bash

mkdir ../clang-tidy
cd ../clang-tidy

qmake -spec linux-clang ../emile-client
bear make

find ../emile-client -name "*.cpp" | xargs clazy-standalone -checks=level0,level1,level2,assert-with-side-effects,container-inside-loop,inefficient-qlist,isempty-vs-count,qhash-with-char-pointer-key,qrequiredresult-candidates,qstring-varargs,qt-keywords,qt4-qstring-from-array,qvariant-template-instantiation,raw-environment-function,reserve-candidates,thread-with-slots,tr-non-literal,unneeded-cast -p compile_commands.json
find ../emile-client -name "*.cpp" | xargs /usr/share/clang/run-clang-tidy.py -checks=*,-modernize-use-trailing-return-type,-fuchsia-default-arguments-calls,-cppcoreguidelines-owning-memory,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-readability-implicit-bool-conversion,-llvm-header-guard -header-filter=../src/

cd ../ && rm -rf clang-tidy
cd emile-client
