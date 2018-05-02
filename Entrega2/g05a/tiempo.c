#include "tiempo.h"
#include "procesamiento_de_estados.h"

/*Las funciones asumen que los datos llegan ya validados*/
status_t cnv_seg_to_hhmmss(int seg, int* hh, int* mm, int* ss){

	if(!hh || !mm || !ss){
		return ST_ERR_PTR_NULO;
	}
	*ss = seg % FCT_CONV_SEC_TO_MIN_TO_H;
	*mm = (seg / FCT_CONV_SEC_TO_MIN_TO_H) % FCT_CONV_SEC_TO_MIN_TO_H;
	*hh = (seg / FCT_CONV_SEC_TO_H);
	return ST_OK;
}