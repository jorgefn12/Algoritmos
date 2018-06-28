typedef long palabra_t;

typedef struct archivo{
    char* nombre_archivo;
    /*formato y tipo*/
    palabra_t *palabra;
}archivos_s;

typedef struct {
    size_t largo;
    palabra_t acumulador;
    size_t program_counter;
    archivos_s archivo;
    simpletron_s *sig;
} simpletron_s;