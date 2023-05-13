# Copyright 2023 Tyler Swann
# makedb.sh

#! /usr/bin/bash

[ -d "poac-out/debug" ] && ninja -C ./poac-out/debug -t compdb > ./poac-out/debug/compile_commands.json
[ -d "poac-out/release" ] && ninja -C ./poac-out/release -t compdb > ./poac-out/release/compile_commands.json
