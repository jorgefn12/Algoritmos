#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "comun.h"
#include "ejecutar_codigo.h"

int opcode_validos[] = {
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
/*Asume que le llegan bloques de memoria validados de acuerdo al rango (correccion del tp1)*/
status_t ejecutar_codigo(simpletron_s * simpletron, params_s * params){
    palabra_s * nodo_inicial;
    palabra_s * nodo_actual;
    size_t i;
    status_t status;
    pfx_lms operacion;
    
    fprintf(stdout,"%s\n",MSJ_COMIENZO_EJECUCION);
    
    /*El ciclo se detiene hasta que se acabe la lista de simpletron (NULL)*/
    while(simpletron){
        printf("Dirección de simpletron: %p\n",(void*)simpletron);
        printf("Dirección de simpletron->sig: %p\n",(void*)simpletron->sig);
        printf("Dirección de archivo->memoria: %p\n",(void*)&(simpletron->archivo->memoria));
        /*Guarda registros para no perder referencia de la posicion de la lista*/
        nodo_inicial = simpletron->archivo->memoria;
        nodo_actual = simpletron->archivo->memoria;
        /*Recorre la lista de palabras dentro de la memoria de cada simpletron hasta que se acaben las palabras (NULL)*/
        for(simpletron->program_counter = 0, simpletron->acumulador = 0; nodo_actual; simpletron->program_counter++){
            /*Obteniene opcode y operando de la linea correspondiente*/
            simpletron->opcode = nodo_actual->dato / OPCODE_OPERANDO;
            simpletron->operando = nodo_actual->dato % OPCODE_OPERANDO;
            simpletron->instruccion = simpletron->opcode * OPCODE_OPERANDO + simpletron->operando;            
            /*Valida que operando pueda ser accdedido*/
            if(simpletron->operando > simpletron->archivo->cant_palabras || simpletron->operando < 0){
                fprintf(stdout,"%s\n",MSJ_FIN_EJECUCION);
                return ST_ERROR_SEGMENTATION_FAULT;
            }
            /*Valido que los opcode sean validos*/
            for(i = 0; simpletron->opcode != opcode_validos[i]; i++){
                if((i+1) == sizeof(opcode_validos)/sizeof(int))
                    return ST_ERROR_OPCODE_INVALIDO;
            }
            /*Ejecuta opcde*/
            operacion = seleccionar_operacion(simpletron->opcode);
            status = operacion(simpletron,nodo_inicial,nodo_actual);
            
            if(status != ST_OK){
                if(status != ST_HALT){
                    fprintf(stdout,"%s\n", MSJ_FIN_EJECUCION);
                    return status;
                }
                break;
            }
            /*Avanza lista*/
            nodo_actual = saltar_lista(nodo_inicial, nodo_actual, simpletron->program_counter, simpletron->program_counter + 1);
        }
        /*Avanza al siguiente simpletron en la lista*/
        simpletron = simpletron->sig;
    }
    return ST_OK;
}
/*Asume que le llegan opcodes validados*/
pfx_lms seleccionar_operacion (opcode_t op){
    switch(op){
        case(OP_LEER):
            return lms_leer;
        case(OP_ESCRIBIR):
            return lms_escribir;
        case(OP_CARGAR):
            return lms_cargar;
        case(OP_GUARDAR):
            return lms_guardar;
        case(OP_PCARGAR):
            return lms_pcargar;
        case(OP_PGUARDAR):
            return lms_pguardar;
        case(OP_SUMAR):
            return lms_sumar;
        case(OP_RESTAR):
            return lms_restar;
        case(OP_DIVIDIR):
            return lms_dividir;
        case(OP_MULTIPLICAR):
            return lms_multiplicar;
        case(OP_JMP):
            return lms_jmp;
        case(OP_JMPNEG):
            return lms_jmpneg;
        case(OP_JMPZERO):
            return lms_jmpzero;
        case(OP_JNZ):
            return lms_jnz;
        case(OP_DJNZ):
            return lms_djnz;
        case(OP_HALT):
            return lms_halt;
        default:
            return NULL;
    }
}
palabra_s* saltar_lista (palabra_s* nodo_inicial, palabra_s* nodo_actual, size_t desde,size_t hasta){
    /*Validacion*/
    if(!nodo_inicial || !nodo_actual || desde < 0 || hasta < 0)
        return NULL;
    /*Condicionales*/
    if(desde == hasta){
        return nodo_actual;
    }
    if(desde < hasta){
        return avanzar_lista_n (nodo_actual, hasta - desde);
    }
    return avanzar_lista_n (nodo_inicial, hasta);
}
palabra_s* avanzar_lista_n (palabra_s * nodo, size_t n){
    if(!nodo || n < 0)
        return NULL;
    return n ? avanzar_lista_n(nodo->sig, n-1) : nodo;
}
/*Creo que se estan haciendo validaciones demás, chequeo bien cuando juntemos todo*/
/*La validación extra sería: validar que al saltar linea, me devuelva NULL*/
status_t lms_leer(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    char aux[MAX_STR];
    size_t i;
    long temp;
    char* pch;
    
    for(i = 0; i < MAX_INGRESOS; i++){
        fprintf(stdout,"%s ",MSJ_INGRESO_PALABRA);
        if(fgets(aux, MAX_STR, stdin) == NULL){
            fprintf(stdout, "%s %s\n", MSJ_NUEVO_INGRESO, MSJ_ST_ERROR_LEER_PALABRA);
        }
        else if((temp = strtol(aux, &pch, 10)) > MAX_PALABRA || temp < MIN_PALABRA || (*pch != '\n' && *pch != '\0' && *pch != EOF)){
            fprintf(stdout, "%s %s\n", MSJ_NUEVO_INGRESO, MSJ_ST_ERROR_PALABRA_NO_VALIDA);
        }
        break;
    }
    if(i == MAX_INGRESOS){
        fprintf(stdout,"%s\n",MSJ_FIN_EJECUCION);
        return ST_ERROR_MAX_INGRESOS_SUPERADO;
    }
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    nodo_actual->dato = temp;
    return ST_OK;
}
status_t lms_escribir(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    fprintf(stdout,"%s %i: %i\n",MSJ_IMPRIMIR_PALABRA,simpletron->operando,nodo_actual->dato);
    return ST_OK;
}   
status_t lms_cargar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    simpletron->acumulador = nodo_actual->dato;
    return ST_OK;
}
status_t lms_guardar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    /*VALIDAR EN OTRA PARTE QUE EL ACUMULADOR NO SUPERE RANGOS*/
    nodo_actual->dato = simpletron->acumulador;
    return ST_OK;
}
status_t lms_pcargar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    /*Valido que el puntero pueda ser accedido*/
    if(nodo_actual->dato > simpletron->archivo->cant_palabras || nodo_actual->dato < 0){
        fprintf(stdout,"%s\n", MSJ_FIN_EJECUCION);
        return ST_ERROR_SEGMENTATION_FAULT;
    }
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->operando,nodo_actual->dato)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    simpletron->acumulador = nodo_actual->dato;
    return ST_OK;
}
status_t lms_pguardar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    /*Valido que el puntero pueda ser accedido*/
    if(nodo_actual->dato > simpletron->archivo->cant_palabras || nodo_actual->dato < 0){
        fprintf(stdout,"%s\n", MSJ_FIN_EJECUCION);
        return ST_ERROR_SEGMENTATION_FAULT;
    }
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->operando,nodo_actual->dato)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    nodo_actual->dato = simpletron->acumulador;
    return ST_OK;
}
status_t lms_sumar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    simpletron->acumulador += nodo_actual->dato;
    return ST_OK;
}
status_t lms_restar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    simpletron->acumulador -= nodo_actual->dato;
    return ST_OK;
}
status_t lms_dividir(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    simpletron->acumulador /= nodo_actual->dato;
    return ST_OK;
}
status_t lms_multiplicar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if((nodo_actual = saltar_lista(nodo_inicial,nodo_actual,simpletron->program_counter,simpletron->operando)) == NULL)
        return ST_ERROR_NODO_VACIO;
    
    simpletron->acumulador *= nodo_actual->dato;
    return ST_OK;
}
status_t lms_jmp(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    simpletron->program_counter = simpletron->operando - 1;
    return ST_OK;
}
status_t lms_jmpneg(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if(simpletron->acumulador < 0)
        simpletron->program_counter = simpletron->operando - 1;
    return ST_OK;
}
status_t lms_jmpzero(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if(!simpletron->acumulador)
        simpletron->program_counter = simpletron->operando - 1;
    return ST_OK;
}
status_t lms_jnz(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    if(simpletron->acumulador)
        simpletron->program_counter = simpletron->operando - 1;
    return ST_OK;
}
status_t lms_djnz(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    simpletron->acumulador--;
    if(simpletron->acumulador)
        simpletron->program_counter = simpletron->operando;
    return ST_OK;
}
status_t lms_halt(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual){
    return ST_HALT;
}
