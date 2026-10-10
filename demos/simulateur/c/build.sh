#!/bin/sh
# Compiles the simulator to WebAssembly (requires Emscripten: emcc in PATH).
# Output: ../simulateur.js (the .wasm is embedded, so a single file is produced)
set -e
cd "$(dirname "$0")"
emcc -O2 -std=c99 -Wall -Wextra -Iheaders \
    src/particules.c src/environnement.c src/distributions.c demo.c \
    -o ../simulateur.js \
    -sMODULARIZE=1 -sEXPORT_NAME=createSimulateur \
    -sSINGLE_FILE=1 -sALLOW_MEMORY_GROWTH=1 \
    -sEXPORTED_FUNCTIONS=_demo_init,_demo_step,_demo_positions,_demo_free,_malloc,_free \
    -sEXPORTED_RUNTIME_METHODS=HEAPF32
echo "OK -> simulateur.js"
