#ifndef LIB_CMP_H
#define LIB_CMP_H

#include <stddef.h>

#include "cpd_array.h"
#include "cpd_atom.h"
#include "cpd_canvas.h"
#include "cpd_connection.h"
#include "cpd_dsp.h"
#include "cpd_env.h"
#include "cpd_list.h"
#include "cpd_loader.h"
#include "cpd_object.h"
#include "cpd_patch.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief initializes pd library
 * @return 1 on success, 0 on error
 */
CPD_EXTERN int cpd_init();

CPD_EXTERN int cpd_stop();

/**
 * Print Pd error message to console
 * @param msg - formatted messages
 */
CPD_EXTERN void cpd_error(const char* msg, ...);

#ifdef __cplusplus
}
#endif

#endif // LIB_CMP_H
