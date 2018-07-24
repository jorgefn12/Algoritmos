#include "simpletron.h"
#include "tipos.h"
#include "memoria.h"
#include "argumentos.h"
#include "comun.h"
#include "errores.h"
#include "dump.h"
#include <stdlib.h>

pfx_lms instrucciones[] = {
    &lms_leer,
    &lms_escribir,
    &lms_cargar,
    &lms_guardar,
    &lms_pcargar,
    &lms_pguardar,
    &lms_sumar,
    &lms_restar,
    &lms_dividir,
    &lms_multiplicar,
    &lms_jmp,
    &lms_jmpneg,
    &lms_jmpzero,
    &lms_jnz,
    &lms_djnz,
    &lms_halt
};
palabra_t opcode_validos[] = {
    OP_LEER,
    OP_ESCRIBIR,
    OP_CARGAR,
    OP_GUARDAR,
    OP_PCARGAR,
    OP_PGUARDAR,
    OP_SUMAR,
    OP_RESTAR,
    OP_DIVIDIR,
    OP_MULTIPLICAR,
    OP_JMP,
    OP_JMPNEG,
    OP_JMPZERO,
    OP_JNZ,
    OP_DJNZ,
    OP_HALT
};

bool_t crear_simpletron(params_t * param, simpletron_t ** simpletron){
    if(param == NULL)
        return FALSE;
    if((*simpletron = (simpletron_t *)calloc(1, sizeof(simpletron_t))) == NULL)
        return FALSE;
    if(((*simpletron)->memoria = (vector_t **)calloc(1, sizeof(vector_t*) * param->cant_archivos)) == NULL){
        destruir_simpletron(simpletron, param);
        return FALSE;
    }
    return TRUE;
}

void destruir_simpletron(simpletron_t ** simpletron, params_t * param){
	size_t i;

    if(simpletron && *simpletron){
        if((*simpletron)->memoria){
            for(i = 0; i < param->cant_archivos; i++){
            	vector_destruir(&((*simpletron)->memoria[i]));
            }
            free((*simpletron)->memoria);
            (*simpletron)->memoria = NULL;
        }
        free(*simpletron);
        *simpletron = NULL;
    }
}

bool_t palabra_es_valida(palabra_t palabra){
    int operando, opcode;
    
    if (palabra > MAX_PALABRA || palabra < MIN_PALABRA)
        return FALSE;

    operando = palabra % OPCODE_OPERANDO_MULTIPLIER;
    if (operando < OPERANDO_MIN || operando > OPERANDO_MAX)
        return FALSE;

    opcode = palabra / OPCODE_OPERANDO_MULTIPLIER;
    if (opcode < OPCODE_FIELD_MIN || opcode > OPCODE_FIELD_MAX)
        return FALSE;

    return TRUE;
}
status_t ejecutar_codigo(simpletron_t * simpletron, params_t * param){
    size_t i,j;
    int memoria_pedida, dato;
    status_t status;
    pfx_lms operacion;
    fprintf(stdout, "%s\n", MSJ_COMIENZO_EJECUCION);
    for(i = 0; i < param->cant_archivos; i++){
    	fprintf(stdout, "%s\n", MSJ_COMIENZO_ARCHIVO);

        memoria_pedida = obtener_pedido(simpletron->memoria[i]);

        for(simpletron->program_counter = 0, simpletron->acumulador = 0; simpletron->program_counter < memoria_pedida; simpletron->program_counter++){
            /*Obtengo opcode y operandos*/
            dato = obtener_dato(simpletron->memoria[i], simpletron->program_counter + 1);
            simpletron->opcode = dato / OPCODE_OPERANDO_MULTIPLIER;
            simpletron->operando = dato % OPCODE_OPERANDO_MULTIPLIER;
            simpletron->instruccion = simpletron->opcode * OPCODE_OPERANDO_MULTIPLIER + simpletron->operando;
            /*Valida que operando pueda ser accdedido*/
            if(simpletron->operando > memoria_pedida - 1 || simpletron->operando < 0){
                fprintf(stdout,"%s\n",MSJ_ST_ERROR_SEGMENTATION_FAULT);
                fprintf(stdout,"%s\n",MSJ_FIN_EJECUCION);
                return ST_ERROR_SEGMENTATION_FAULT;
            }
            /*Valido que los opcode sean validos*/
            for(j = 0; simpletron->opcode != opcode_validos[j]; j++){
                if((j+1) == sizeof(opcode_validos)/sizeof(int)){
                    fprintf(stdout,"%s\n",MSJ_ST_ERROR_OPCODE_INVALIDO);
                    fprintf(stdout,"%s\n",MSJ_FIN_EJECUCION);
                    return ST_ERROR_OPCODE_INVALIDO;
                }
            }
            /*Ejecuta opcde*/
            operacion = instrucciones[j];
            status = (*operacion)(simpletron, simpletron->memoria[i]);
            if (status != ST_OK){
                if(status != ST_HALT){
                    fprintf(stdout,"%s\n", MSJ_FIN_EJECUCION);
                    return status;
                }
                break;
            }
        }
        fprintf(stdout, "%s\n", MSJ_FIN_ARCHIVO);
        
        imprimir_dump(simpletron, simpletron->memoria[i], param);
        
    }
    fprintf(stdout, "%s\n", MSJ_FIN_EJECUCION);

    return ST_OK;
}

status_t lms_leer(simpletron_t * simpletron, vector_t * memoria){
    char buffer[MAX_STR];
    long temp;
    char * pch;
    
    fprintf(stdout,"%s ",MSJ_INGRESO_PALABRA);
    if(fgets(buffer, MAX_STR, stdin) == NULL){
        fprintf(stdout, "%s\n", MSJ_ST_ERROR_LEER_PALABRA);
        return ST_ERROR_LEER_PALABRA;
    }
    if((temp = strtol(buffer, &pch, 10)) > MAX_PALABRA || temp < MIN_PALABRA || (*pch != '\n' && *pch != '\0' && *pch != EOF)){
        fprintf(stdout, "%s\n", MSJ_ST_ERROR_PALABRA_NO_VALIDA);
        return ST_ERROR_PALABRA_NO_VALIDA;
    }
    
    vector_guardar_int(memoria, simpletron->operando + 1, (int*)&temp);

    return ST_OK;
}
status_t lms_escribir(simpletron_t * simpletron, vector_t * memoria){
    fprintf(stdout,"%s %i: %i\n",MSJ_IMPRIMIR_PALABRA,simpletron->operando,obtener_dato(memoria, simpletron->operando + 1));
    return ST_OK;
}   
status_t lms_cargar(simpletron_t * simpletron, vector_t * memoria){
    simpletron->acumulador = obtener_dato(memoria, simpletron->operando + 1);
    return ST_OK;
}
status_t lms_guardar(simpletron_t * simpletron, vector_t * memoria){
    if(simpletron->acumulador < MIN_PALABRA || simpletron->acumulador > MAX_PALABRA){
        fprintf(stdout,"%s\n", MSJ_ST_ERROR_PALABRA_NO_VALIDA);
        return ST_ERROR_PALABRA_NO_VALIDA;
    }
    vector_guardar_int(memoria, simpletron->operando + 1, (int*)&simpletron->acumulador);
    return ST_OK;
}
int obtener_dato(vector_t * v, size_t i);
int obtener_usado(vector_t * v);
int obtener_pedido(vector_t * v);
status_t lms_pcargar(simpletron_t * simpletron, vector_t * memoria){
    if(obtener_dato(memoria, simpletron->operando + 1) > obtener_pedido(memoria) + 1 || obtener_dato(memoria, simpletron->operando + 1) < 0){
        fprintf(stdout,"%s\n",MSJ_ST_ERROR_SEGMENTATION_FAULT);
        return ST_ERROR_SEGMENTATION_FAULT;
    }
    simpletron->acumulador = obtener_dato(memoria, obtener_dato(memoria, simpletron->operando + 1));

    return ST_OK;
}
status_t lms_pguardar(simpletron_t * simpletron, vector_t * memoria){
    if(obtener_dato(memoria, simpletron->operando + 1) > obtener_pedido(memoria) + 1 || obtener_dato(memoria, simpletron->operando + 1) < 0){
        fprintf(stdout,"%s\n",MSJ_ST_ERROR_SEGMENTATION_FAULT);
        return ST_ERROR_SEGMENTATION_FAULT;
    }
    vector_guardar_int(memoria, obtener_dato(memoria, simpletron->operando + 1), (int*)&simpletron->acumulador);

    return ST_OK;
}
status_t lms_sumar(simpletron_t * simpletron, vector_t * memoria){
    palabra_t resultado;
    if((resultado = simpletron->acumulador + obtener_dato(memoria, simpletron->operando + 1)) > MAX_PALABRA || resultado < MIN_PALABRA){
        fprintf(stdout,MSJ_ST_ERROR_OVERFLOW);
        return ST_ERROR_OVERFLOW;
    }
    simpletron->acumulador = resultado;
    return ST_OK;
}
status_t lms_restar(simpletron_t * simpletron, vector_t * memoria){
    simpletron->acumulador -= obtener_dato(memoria, simpletron->operando + 1);
    return ST_OK;
}
status_t lms_dividir(simpletron_t * simpletron, vector_t * memoria){
    simpletron->acumulador /= obtener_dato(memoria, simpletron->operando + 1);
    return ST_OK;
}
status_t lms_multiplicar(simpletron_t * simpletron, vector_t * memoria){
    simpletron->acumulador *= obtener_dato(memoria, simpletron->operando + 1);
    return ST_OK;
}
status_t lms_jmp(simpletron_t * simpletron, vector_t * memoria){
    simpletron->program_counter = simpletron->operando -1;
    return ST_OK;
}
status_t lms_jmpneg(simpletron_t * simpletron, vector_t * memoria){
    if(simpletron->acumulador < 0)
        simpletron->program_counter = simpletron->operando -1;
    return ST_OK;
}
status_t lms_jmpzero(simpletron_t * simpletron, vector_t * memoria){
    if(!simpletron->acumulador)
        simpletron->program_counter = simpletron->operando -1;
    return ST_OK;
}
status_t lms_jnz(simpletron_t * simpletron, vector_t * memoria){
    if(simpletron->acumulador)
        simpletron->program_counter = simpletron->operando -1;
    return ST_OK;
}
status_t lms_djnz(simpletron_t * simpletron, vector_t * memoria){
    simpletron->acumulador--;
    if(simpletron->acumulador)
        simpletron->program_counter = simpletron->operando -1;
    return ST_OK;
}
status_t lms_halt(simpletron_t * simpletron, vector_t * memoria){
    return ST_HALT;
}