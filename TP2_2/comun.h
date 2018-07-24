#ifndef COMUN__H
#define COMUN__H

#define MAX_STR 200
#define STR_FIN_CARGA "-99999999"
#define MIN_PALABRA -640511  /*Maximo alcanzable en formato texto que puede abarcar el formato binario*/
#define MAX_PALABRA 630511
#define OPCODE_OPERANDO_MULTIPLIER 10000
#define OPERANDO_MIN 0 /*xxxxxxx000000000*/
#define OPERANDO_MAX 511 /*xxxxxxx111111111*/
#define OPCODE_MIN 0 /*0000000xxxxxxxxx*/
#define OPCODE_MAX 127 /*1111111xxxxxxxxx*/
#define OPCODE_FIELD_MIN -64 /*1000000xxxxxxxxx*/
#define OPCODE_FIELD_MAX 63 /*0111111xxxxxxxxx*/

#endif