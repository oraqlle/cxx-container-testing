# Copyright 2023 Tyler Swann
# makedb.sh

#! /usr/bin/bash

MATPLOT_LIB="$(brew --prefix)/lib"
MATPLOT_INC="$(brew --prefix)/include"

# Build compile command
~/bin/poac/build/poac build >/dev/null 2>&1

# Fix escaped slashes
./makedb-new.sh

# Extract command key-value from `compile_command.json`
COMMAND=$(head -4 ./poac-out/$1/compile_commands.json | tail +4)

# Extract value (compile command)
COMMAND=$(echo $COMMAND | cut -c13- | rev | cut -c3- | rev)

# Append link command for matplot++
COMMAND="$COMMAND -I$MATPLOT_INC -L$MATPLOT_LIB -lmatplot"

# Build again with matplot++ linked
$($COMMAND)

# Rerun compilation database fixer
./makedb-new.sh

# Run program
./poac-out/$1/cxx-container-testing
