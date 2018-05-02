#ifndef TIEMPO__H
#define TIEMPO__H 1
#include "procesamiento_de_estados.h"

#define FCT_CONV_SEC_TO_MIN_TO_H 60
#define FCT_CONV_SEC_TO_H 3600

#define MSJ_HOURS_UNITS "[hs]"
#define MSJ_MIN_UNITS "[min]"
#define MSJ_SEC_UNITS "[s]"

status_t cnv_seg_to_hhmmss(int segundos, int* h, int* min, int* seg);

#endif