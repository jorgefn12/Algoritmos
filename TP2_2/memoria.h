/*Prototipos y funciones primitivas para usar un TDA Vector (memoria del simpletron)*/

/*Aviso al usuario sobre la existencia de este tipo*/
typedef struct vector vector_t;
/********************Primitivas****************/
/*Crea un vector de n elementos inicializados en 0 y devuelve un puntero a la estructura. Si ocurre un fallo devuelve NULL.*/
vector_t * vector_crear(size_t n);
/*Destruye un TDA vector*/
void vector_destruir(vector_t **v);
/*Recibe v como un puntero a TDA vector, dato como un puntero al elemento a guardar. Guarda dato en la posicion i y retorna por el
* nombre un booleando de acuerdo a la operacion*/
bool_t vector_guardar(vector_t *v, int i, void * dato);

/*Redimiensiona el TDA vector apuntado por v con memoria para n elementos, retorna booleano segun la operacion*/
bool_t vector_redimensionar(vector_t *v, size_t n);

/*Recorre todo el TDA vector apuntado por v y aplica la función apuntada por func, cuyos argumentos serán el elemento de cada iteración
* y el argumento opcional arg. Si arg es NULL, la función no lo utiliza. Como se usa una funcion generica, las validaciones se deberían
* hacer afuera de esta primitiva.
*/
void vector_iterar(vector_t * v, void (*func)(void *,void *), void * arg);
