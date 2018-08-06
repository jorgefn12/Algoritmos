
#include "simpletron.h"
/*********************************SIMPLETRON.C*************************************************/
static const pfx_lms instrucciones[] = {
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
static const palabra_t opcode_validos[] = {
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
bool_t palabra_es_valida(palabra_t palabra){
    palabra_t operando;
    palabra_t opcode;
    
    if (palabra > MAX_PALABRA_TXT || palabra < MIN_PALABRA_TXT)
        return FALSE;
    operando = palabra < 0 ? -palabra % OPCODE_OPERANDO_MULTIPLIER : palabra % OPCODE_OPERANDO_MULTIPLIER;
    if (operando < OPERANDO_MIN || operando > OPERANDO_MAX)
        return FALSE;
    opcode = palabra / OPCODE_OPERANDO_MULTIPLIER;
    if (opcode < OPCODE_FIELD_MIN || opcode > OPCODE_FIELD_MAX)
        return FALSE;
    
    return TRUE;
} /*TESTEADO*/
/*NULL si no hubo memmoria. Todas las variables y punteros inicializados con calloc*/



/************************************************************************************************/
/*Me dan la representacion binaria de los op desplazados a la derecha. Por esto, siempre los toma positivos
 Si quisiera representarlos con signo, necesito hacer complemento a 2 manualmente*/
palabra_t get_opcode(palabra_t palabra, formato_t formato){
    /*Para código más legible, se escribe != FMT_TXT. Siendo FMT_TXT = 0*/
    /*El opcode que se obtiene con el modo texto sólo se utiliza para impresion, no para guardar en memoria
     ya que si llegara a ser negativo, incluiría 1s en las posiciones más significativas de un tipo entero, 
     cuyos campos son invalidos para la representación de una palabra*/
    return formato != FMT_TXT ? (palabra & MASK_OPCODE) >> OPCODE_SHIFT : palabra / OPCODE_OPERANDO_MULTIPLIER;
}   /*TESTEADO*/
palabra_t get_operando(palabra_t palabra, formato_t formato){
    if(palabra < 0)
        palabra = -palabra;
    return formato != FMT_TXT ? palabra & MASK_OPERANDO : palabra % OPCODE_OPERANDO_MULTIPLIER;
}   /*TESTEADO*/
/*Se usa para cambiar de opcode binario a opcode texto si el MSB esta activo*/
palabra_t aplicar_signo_palabra(palabra_t palabra, palabra_t BIT_FIELD ,palabra_t MSB){
    /*Se puede mejoror si en lugar de complementar dos veces, se llenan de 1s en los bits por delante del opcode*/
    /*
    return palabra & MSB ? -(((~palabra) & BIT_FIELD) + 1) : palabra;
    */
    return palabra & MSB ? palabra | (~BIT_FIELD) : palabra;
    
} /*TESTEADO*/
/*Para pasar de texto a binario si el opcode fuera negativo*/
palabra_t quitar_signo_palabra(palabra_t palabra, palabra_t BIT_FIELD){
    return palabra & BIT_FIELD;
}   /*TESTEADO*/
/*Se asume que las palabras estan validadas y llenadas con ceros a la izquierda*/
palabra_t cambiar_fmt_palabra(palabra_t palabra, formato_t actual){
    palabra_t operando;
    palabra_t opcode;
    
    opcode = get_opcode(palabra, actual);
    operando = get_operando(palabra, actual);
    
    switch(actual){
        case FMT_BIN: /*La palabra estaba almacenada en un entero con el formato binario y se quiere pasar al formato texto*/
            opcode = aplicar_signo_palabra(opcode, MASK_OPCODE >> OPCODE_SHIFT, MASK_MSB >> OPCODE_SHIFT);
            return opcode * OPCODE_OPERANDO_MULTIPLIER + (opcode >= 0 ? operando : -operando);
        case FMT_TXT:
            /*Si el opcode fuera negativo, necesito eliminar los 1s delanteros*/
            opcode = quitar_signo_palabra(opcode, MASK_OPCODE >> OPCODE_SHIFT);
            return (( (int) 0 | opcode) << OPCODE_SHIFT) | operando;
        default:
            return palabra;
    }
}   /*TESTEAD*/


simpletron_t * SIMPLETRON_crear(void){
    return (simpletron_t *)calloc(1,sizeof(simpletron_t));
}
void SIMPLETRON_destruir(simpletron_t ** simply){
    if(simply != NULL && *simply != NULL){
        if((*simply)->memoria != NULL){
            VECTOR_destruir(&(*simply)->memoria);  
        }
        free(*simply);
        *simply = NULL;
    }
}
simply_retval_t SIMPLETRON_ejecutar(simpletron_t * simply){
    size_t i;
    int memoria_pedida;
    simply_retval_t status;
    pfx_lms operacion;
    
    if(simply == NULL || simply->memoria == NULL)
        return SMP_RV_ILLEGAL;
    
    memoria_pedida = VECTOR_obtener_memoria_pedida(simply->memoria);
    /*
    fprintf(stdout, "%s\n", MSJ_COMIENZO_EJECUCION);
    */
    for(; simply->program_counter < memoria_pedida; simply->program_counter++){
        /*Obtengo opcode y operandos*/
        simply->instruccion = VECTOR_obtener_dato(simply->memoria, simply->program_counter + 1);
        simply->opcode = get_opcode(simply->instruccion, FMT_BIN);
        simply->operando = get_operando(simply->instruccion, FMT_BIN);
        /*Valida que operando pueda ser accdedido*/
        if(simply->operando > memoria_pedida - 1 || simply->operando < 0){
		            /*
		    fprintf(stdout, "%s\n", MSJ_COMIENZO_EJECUCION);
		    */
            return SMP_RV_SEGMENTATION_FAULT;
        }
        /*Valido que los opcode sean validos*/  
        for(i = 0; simply->opcode != opcode_validos[i] && i < sizeof(opcode_validos)/sizeof(opcode_validos[0]) ; i++){
        }
        if(i == sizeof(opcode_validos)/sizeof(opcode_validos[0])){
            /*
		    fprintf(stdout, "%s\n", MSJ_COMIENZO_EJECUCION);
		    */
            return SMP_RV_OPCODE_INVALIDO;
        }
        /*Ejecuta opcde*/
        operacion = instrucciones[i];
        status = (*operacion)(simply);
        if (status != SMP_RV_SUCCESS){
            if(status != SMP_RV_HALT){
                /*
		    fprintf(stdout, "%s\n", MSJ_COMIENZO_EJECUCION);
		    */
                return status;
            }
            break;
        }
    }
    /*
		    fprintf(stdout, "%s\n", MSJ_COMIENZO_EJECUCION);
		    */
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_leer(simpletron_t * simpletron){
    char buffer[MAX_STR];
    palabra_t palabra;
    char * pch;
    
    fprintf(stdout,"%s ",MSJ_INGRESO_PALABRA);
    if(fgets(buffer, MAX_STR, stdin) == NULL){
        return SMP_RV_PALABRA_NO_LEIDA;
    }
    palabra = strtol(buffer, &pch, 10);
    /*Se valida que el numero pueda ser representado en 16bits con signo*/
    if (pch == NULL || (*pch != '\n' && *pch != '\0'))
        return SMP_RV_PALABRA_NO_ES_ENTERO;
    if(palabra > MAX_PALABRA_BIN_SIGNED || palabra < MIN_PALABRA_BIN_SIGNED)
        return SMP_RV_PALABRA_FUERA_DE_RANGO;
    
    palabra = quitar_signo_palabra(palabra, MASK_PALABRA);
    
    VECTOR_guardar_entero(simpletron->memoria, simpletron->operando + 1, palabra);
    
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_escribir(simpletron_t * simpletron){
    palabra_t palabra;

    palabra = VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    palabra = aplicar_signo_palabra(palabra, MASK_PALABRA, MASK_MSB);
    
    fprintf(stdout,"%s %i: %i\n", MSJ_IMPRIMIR_PALABRA, simpletron->operando, palabra);
    return SMP_RV_SUCCESS;
} 
simply_retval_t lms_cargar(simpletron_t * simpletron){
    simpletron->acumulador = VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_guardar(simpletron_t * simpletron){
    VECTOR_guardar_entero(simpletron->memoria, simpletron->operando + 1, simpletron->acumulador);
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_pcargar(simpletron_t * simpletron){
    palabra_t puntero;
    /*Las funciones de TDA Vector empiezan a contar desde 1*/
    puntero = VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1) + 1;
    if(puntero > VECTOR_obtener_memoria_pedida(simpletron->memoria) || puntero < 1){
        return SMP_RV_SEGMENTATION_FAULT;
    }
    simpletron->acumulador = VECTOR_obtener_dato(simpletron->memoria, puntero);

    return SMP_RV_SUCCESS;
}
simply_retval_t lms_pguardar(simpletron_t * simpletron){
    palabra_t puntero;
    /*Las funciones de TDA Vector empiezan a contar desde 1*/
    puntero = VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1) + 1;
    if(puntero > VECTOR_obtener_memoria_pedida(simpletron->memoria) || puntero < 1){
        return SMP_RV_SEGMENTATION_FAULT;
    }
    VECTOR_guardar_entero(simpletron->memoria, puntero, simpletron->acumulador);
    
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_sumar(simpletron_t * simpletron){
    palabra_t resultado;
    
    resultado = simpletron->acumulador + VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    if(resultado > MAX_PALABRA_BIN || resultado < MIN_PALABRA_BIN){
        return SMP_RV_OVERFLOW;
    }
    simpletron->acumulador = resultado;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_restar(simpletron_t * simpletron){
    palabra_t resultado;
    /*Si dejo que el programa reste normalmente, me llena de ceros a la izquierda
     Resto a nivel de bit, en el campo de la palabra*/
    resultado = simpletron->acumulador - VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    
    resultado = quitar_signo_palabra(resultado, MASK_PALABRA);

    if(resultado > MAX_PALABRA_BIN || resultado < MIN_PALABRA_BIN){
        return SMP_RV_OVERFLOW;
    }
    simpletron->acumulador = resultado;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_dividir(simpletron_t * simpletron){
    palabra_t resultado;
    
    resultado = simpletron->acumulador / VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    if(resultado > MAX_PALABRA_BIN || resultado < MIN_PALABRA_BIN){
        return SMP_RV_OVERFLOW;
    }
    simpletron->acumulador = resultado;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_multiplicar(simpletron_t * simpletron){
    palabra_t resultado;
    
    resultado = simpletron->acumulador * VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    if(resultado > MAX_PALABRA_BIN || resultado < MIN_PALABRA_BIN){
        return SMP_RV_OVERFLOW;
    }
    simpletron->acumulador = resultado;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_jmp(simpletron_t * simpletron){
    simpletron->program_counter = simpletron->operando - 1;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_jmpneg(simpletron_t * simpletron){
    if(simpletron->acumulador & MASK_MSB)
        simpletron->program_counter = simpletron->operando - 1;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_jmpzero(simpletron_t * simpletron){
    if(!simpletron->acumulador)
        simpletron->program_counter = simpletron->operando - 1;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_jnz(simpletron_t * simpletron){
    if(simpletron->acumulador)
        simpletron->program_counter = simpletron->operando - 1;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_djnz(simpletron_t * simpletron){
    simpletron->acumulador--;
    if(simpletron->acumulador)
        simpletron->program_counter = simpletron->operando - 1;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_halt(simpletron_t * simpletron){
    return SMP_RV_HALT;
}
