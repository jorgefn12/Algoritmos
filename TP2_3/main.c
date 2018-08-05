

int main(int argc, char** argv){
    status_t st;
    params_t argumentos;
    size_t i, j;
    simpletron_t * simply;
    lista_t lista = NULL;
    
    validacion_cla(argc,argv, &argumentos);
    for(i = 0; i < argumentos.cant_archivos; i++){
        simply = SIMPLETRON_crear();
        leer_archivo(&simply->memoria, &argumentos.archivo_entrada[i], argumentos.cant_memoria);
        LISTA_insertar_al_final(&lista,simply);
    }
    LISTA_aplicar(lista, SIMPLETRON_ejecutar);
    LISTA_recorrer(lista, imprimir_dump, argumentos.archivo_salida);
    LISTA_destruir(&lista, SIMPLETRON_destruir);
    
    return EXIT_SUCCESS;
}
