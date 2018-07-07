#ifndef EJECUTAR_CODIGO__H
#define EJECUTAR_CODIGO__H

#define MAX_INGRESOS 5
#define MAX_INSTRICCIONES 5000
#define MSJ_COMIENZO_EJECUCION "******** INICIO DE EJECUCION DEL SIMPLETRON *******"
#define MSJ_FIN_EJECUCION "********* FIN DE EJECUCION DEL SIMPLETRON *********"
#define MSJ_INGRESO_PALABRA "Ingrese una palabra: "
#define MSJ_NUEVO_INGRESO "Ingrese nuevamente."
#define MSJ_IMPRIMIR_PALABRA "Contenido de la posición"

status_t ejecutar_codigo(simpletron_s * simpletron, params_s * params);
pfx_lms seleccionar_operacion (opcode_t op);
palabra_s* saltar_lista (palabra_s* nodo_inicial, palabra_s* nodo_actual, size_t desde,size_t hasta);
palabra_s* avanzar_lista_n (palabra_s* nodo, size_t n);
status_t lms_leer(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);
status_t lms_escribir(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);
status_t lms_cargar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);
status_t lms_guardar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);
status_t lms_pcargar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);
status_t lms_pguardar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);
status_t lms_sumar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);
status_t lms_restar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);
status_t lms_dividir(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);
status_t lms_multiplicar(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);
status_t lms_jmp(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);
status_t lms_jmpneg(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);
status_t lms_jmpzero(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);
status_t lms_jnz(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);
status_t lms_djnz(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);
status_t lms_halt(simpletron_s * simpletron, palabra_s * nodo_inicial, palabra_s * nodo_actual);

#endif
