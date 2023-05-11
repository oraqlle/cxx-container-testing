# Copyright 2023 Tyler Swann
# makedb.sh

#! /usr/bin/bash

[ -d "poac-out/debug" ] && ninja -C ./poac-out/debug -f ninja.build -t compdb > ./poac-out/debug/compile_commands.json
[ -d "poac-out/release" ] && ninja -C ./poac-out/release -f ninja.build -t compdb > ./poac-out/release/compile_commands.json
