#ifndef LIB_CMP_H
#define LIB_CMP_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _text;
struct _glist;
typedef struct _glist t_cpd_canvas;
#define t_canvas struct _glist
typedef struct _text t_object;

/** 
 * \return pointer to last root (top) canvas or 0 if not found
 */
t_cpd_canvas* cpd_root_canvas_last();

/**
 * Returns number of root (top) canvases
 */
size_t cpd_root_canvas_count();

/**
  * Returns pointer to next canvas in list
  */
t_cpd_canvas* cpd_root_canvas_next(t_cpd_canvas* cnv);

/**
 * Returns pointer to root canvas at given position
 */
t_cpd_canvas* cpd_root_canvas_at(size_t n);

/**
 * Returns canvas name
 */
const char* cpd_canvas_name(t_cpd_canvas* c);

/**
  * Removes canvas
  */
int cpd_canvas_free(t_cpd_canvas* c);

////
/// \brief initializes pd library
/// \return 1 on success, 0 on error
///
int cpd_init();

int cpd_stop();

////
/// \brief creates new t_canvas
/// \return new canvas or 0 if failed
///
t_canvas* cpd_new_patch();

////
/// \brief closes and frees the canvas
/// \param canvas
///
void cpd_delete_patch(t_canvas* canvas);

////
/// \brief check if canvas given
/// \param x - pointer to object
/// \return 1 is given object is canvas, otherwise 0
///
int cpd_is_canvas(t_object* x);

////
///
///
////
void cpd_error(const char* msg, ...);

#ifdef __cplusplus
}
#endif

#endif // LIB_CMP_H
