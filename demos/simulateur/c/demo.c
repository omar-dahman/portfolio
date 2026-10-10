/**
 * \file    demo.c
 * \brief   WebAssembly entry points for the browser demo
 * \details Thin wrapper around the PRIN12 simulator (branch lot_i of
 *          github.com/omar-dahman/simulateur-particules). The files in src/
 *          and headers/ are copied unchanged; only this file is specific to
 *          the demo. It replaces main.c and interface.c, which read their
 *          parameters from stdin and cannot run in a browser.
 */
#include <math.h>
#include <stdlib.h>
#include <emscripten/emscripten.h>

#include "environnement.h"
#include "distributions.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

static env e = NULL;
static float *positions = NULL;

/**
 * \brief   Frees the current simulation, if any
 */
EMSCRIPTEN_KEEPALIVE void demo_free(void) {
    if (e) {
        free_environnement(e);
        e = NULL;
    }
    free(positions);
    positions = NULL;
}

/**
 * \brief   Creates a new simulation
 * \details Particles get a uniform random position in the environment and a
 *          uniform random direction (create_environnement puts them all at
 *          the center with the same speed).
 * \return  1 on success, 0 on allocation failure
 */
EMSCRIPTEN_KEEPALIVE int demo_init(int n, float w, float h, float r, float dt, unsigned int seed) {
    demo_free();
    srand(seed);
    e = create_environnement(n, w, h, r, dt);
    positions = malloc(2 * n * sizeof(float));
    if (!e || !positions) {
        demo_free();
        return 0;
    }
    for (int i = 0; i < n; i++) {
        particule p = get_particule(e, i);
        float angle = uniform(0, 2 * M_PI);
        set_position(p, uniform(0, w), uniform(0, h));
        set_speed(p, cosf(angle), sinf(angle));
    }
    return 1;
}

/**
 * \brief   Advances the simulation by one iteration
 */
EMSCRIPTEN_KEEPALIVE void demo_step(void) {
    if (e) {
        move_particules(e);
    }
}

/**
 * \brief   Returns the positions as a flat array [x0, y0, x1, y1, ...]
 * \return  pointer into WebAssembly memory, valid until the next demo_init
 */
EMSCRIPTEN_KEEPALIVE float *demo_positions(void) {
    if (!e) {
        return NULL;
    }
    int n = get_n(e);
    for (int i = 0; i < n; i++) {
        particule p = get_particule(e, i);
        positions[2 * i] = get_x(p);
        positions[2 * i + 1] = get_y(p);
    }
    return positions;
}
