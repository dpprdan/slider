#include "slurrr.h"

SEXP strings_empty = NULL;

SEXP syms_dot_x = NULL;
SEXP syms_dot_y = NULL;
SEXP syms_dot_l = NULL;

// -----------------------------------------------------------------------------

void r_int_fill_seq(SEXP x, int start, R_len_t n) {
  int* data = INTEGER(x);

  for (R_len_t i = 0; i < n; ++i, ++data, ++start) {
    *data = start;
  }
}

void r_int_fill_seq_rev(SEXP x, int end, R_len_t n) {
  int* data = INTEGER(x);

  for (R_len_t i = 0; i < n; ++i, ++data, --end) {
    *data = end;
  }
}

SEXP r_seq(R_len_t from, R_len_t to) {
  R_len_t n = to - from;

  bool forward = true;
  if (n < 0) {
    forward = false;
  }

  n = abs(n) + 1;

  SEXP seq = PROTECT(Rf_allocVector(INTSXP, n));

  if (forward) {
    r_int_fill_seq(seq, from, n);
  } else {
    r_int_fill_seq_rev(seq, from, n);
  }

  UNPROTECT(1);
  return seq;
}

// -----------------------------------------------------------------------------

int r_int_get(SEXP x, int i) {
  return INTEGER(x)[i];
}

bool r_lgl_get(SEXP x, int i) {
  return LOGICAL(x)[i];
}

// -----------------------------------------------------------------------------

// [[register()]]
void slurrr_init_utils() {
  syms_dot_x = Rf_install(".x");
  syms_dot_y = Rf_install(".y");
  syms_dot_l = Rf_install(".l");

  strings_empty = Rf_allocVector(STRSXP, 1);
  R_PreserveObject(strings_empty);
  SET_STRING_ELT(strings_empty, 0, Rf_mkChar(""));
}
