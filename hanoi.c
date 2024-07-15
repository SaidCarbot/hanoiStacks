/*
18-jun-24
19-jun-24
25-jun-24 ya quedo chido todo

PASOS PARA EJECUTAR
1) compilar con make hanoi
2) gaurdar movimeinto con ./hanoi > movi.txt
3) python gui.py
4) meter en los botones el nuemro de discos y el movi.txt
    si se hace .txt para pares entonces los nones temrinaran en B

MOVIMIENTOS
T(1)=1
T(2)=3
T(3)=7
T(4)=15
T(5)=31
T(6)=63
T(7)=127
T(8)=255
Entonces, si usara solo un puntero estaria modificando la 
pila pero como una pila a veces poeude ser auxiliar o a veces destino
entonces perdería el track de las pilas, cierto? o sea con un puntero
solo accedo a la ubicación de la pila pero con dos punteros puedo seguir
la pila por si se mueve, cierto? Sí, por la realocada, es decir el cambio de aux 
y destino variable;
Puntero único (stackDS*): Puedes modificar el contenido de la pila,
pero no su referencia.
Doble puntero (stackDS**): Puedes modificar tanto el contenido de la pila como su referencia.
*/

#include <stdio.h>
#include <stdlib.h>

// A) Global variables
typedef int element;                                                // A.1

typedef struct stackNodeD                                           // A.2
{
    element elemento;
    struct stackNodeD* next;
    int numeroPalito;
}
stackDS;

// Para almacenar movimiento y que .py los pueda usar para GUI
typedef struct                                                      // A.3
{
    int origen;
    int destino;
} listaMovimiento;

// B) Prototypes
void initializeDS(stackDS** ds);                                    // B.1
element isEmptyDS(stackDS* ds);                                     // B.2
stackDS* pushDS(stackDS** ds, element elemento);                    // B.3
element popDS(stackDS** ds);                                        // B.4
void deleteDS(stackDS** ds);                                        // B.5

    // Seccion de hanoi
void agregarMovimiento(listaMovimiento* movimientos,
    int* contador, int origen, int destino);                        // B.6

int primeMove(stackDS** origen, stackDS** destino,
    listaMovimiento* movimientos, int* contador,
    int origen_id, int destino_id);                                 // B.7
    

void hanoiRe(int n, stackDS** A, stackDS** C,
    stackDS** B,listaMovimiento* movimientos,
    int* contador,int A_id, int C_id, int B_id);                    // B.8


// C) Main
int main()
{
    // 1 de 5::Del número de discos
    int n;
    // printf("Ingrese el número de discos (hasta 8): ");
    scanf("%d", &n);
    if (n < 1 || n > 8)//MODIFICABLE PARA AUMENTAR
    {
        printf("Número de discos no válido. Ingrese un número entre 1 y 8.\n");
        return 1;
    }

    // 2 de 5:: De incilizar los tres stacks
    stackDS* origen;
    stackDS* auxiliar;
    stackDS* destino;

    initializeDS(&origen);                                      // B.1
    initializeDS(&auxiliar);                                    // B.1
    initializeDS(&destino);                                     // B.1

    // 3 de 5:: De poner los n discos en el stack origen
    for (int i = n; i >= 1; i--)
    {
        pushDS(&origen, i);                                     // B.3
    }

    // Inicializar los movimientos y el contador
    listaMovimiento movimientos[256]; // para maximo 255 movimientos
                                      // de 8 discos MODIFICABLE PARA AUMENTAR
    int contador = 0; // Par air avanzando en el struct o todos en el mismo "i"

    // 4 de 5::De mover de un palito a otro                     // B.8
    hanoiRe(n, &origen, &destino, &auxiliar, movimientos, &contador, 1, 3, 2);

    // 5 de 5::De Liberar la memoria
    // printf("En palito final\n");
    deleteDS(&destino);                                        // B.5

    return 0;
}

// D Funcions
// D.1) Inicializar pila-DINAMICA :/ O(1)
void initializeDS(stackDS** head)
{
    *head = NULL;
}

// D.2) Revisar si esta vacia-DINAMICA :/ O(1)
element isEmptyDS(stackDS* ds) 
{
    return ds == NULL;
}

// D.3) Crear nodo dinamico stack (PUSH)-DINAMICA :/ O(1)
stackDS* pushDS(stackDS** ds, element elemento)
{
    if (ds == NULL)
    {
        printf("Error: el puntero a la pila dinamica es nulo.\n");
        exit(1);
    }

    stackDS* new = (stackDS*)malloc(sizeof(stackDS));
    if (new == NULL)
    {
        printf("Error: No se pudo asignar memoria para el nuevo nodo.\n");
        exit(1);
    }
    new->elemento = elemento;
    new->next = *ds;
    *ds = new;
    return new;
}

// D.4) Eliminar nodo dinamico stack (POP)-DINAMICA :/ O(1)
element popDS(stackDS** ds)
{
    if (isEmptyDS(*ds))                                        // B.2
    {
        printf("Error: la pila está vacía. No se puede hacer POP\n");
        exit(EXIT_FAILURE);
    }
    stackDS* temp = *ds;
    element elemento = temp->elemento;
    *ds = temp->next;
    free(temp);
    return elemento;
}

// D.5) Eliminar toda a lista usando POP-TOTAL-DINAMICA :/ O(n)
void deleteDS(stackDS** ds) 
{
    element elemento;
    while (!isEmptyDS(*ds))                                 // B.2
    {
        elemento = popDS(ds);                               // B.4
        // printf("Borrando disco... %d\n",elemento);
    }
}

// De resolver hanoi y mover
// D.6 Llenar lista para que .py lo lea :/ O(1)
void agregarMovimiento(listaMovimiento* movimientos, int* contador,
                        int origen, int destino)
{
    movimientos[*contador].origen = origen; // Podria ser tambien con globarlVar el *contador
    printf("%d ", origen);//para exportar al movi.txt
    movimientos[*contador].destino = destino;// recuerda desreferenciar *regresa lo que hay
    printf("%d\n", destino);
    (*contador)++;
}
// D.7 del primer movimiento base, de A hasta C, :/O(1) // MODIFICABLE 
int primeMove(stackDS** origen, stackDS** destino,
              listaMovimiento* movimientos, int* contador,
              int origenId, int destinoId)
    {
        if (isEmptyDS(*origen))                             // B.2
        {
            printf("Error: el origen está vacío. No se puede mover un disco.\n");
            return -1;// se supone nunc anetraria por la validacion de python y aquí
        }
            element diskMovido = popDS(origen);             // B.4
            pushDS(destino, diskMovido);                    // B.3
            agregarMovimiento(movimientos, contador,                   
                origenId, destinoId);//registrar movimiento // B.6
    return diskMovido; // no es necesario regresar algo, lo deje porque asi era con ctypes
}

// D.8 de resolver la torre
// [1]Luis J. Aguilas & Ignacio Z. Martinez,
// "Estructuras de datos en Java",2008, McGrawHill.
void hanoiRe(int n, stackDS** A, stackDS** C, stackDS** B,
    listaMovimiento* movimientos, int* contador, int A_id,
    int C_id, int B_id)
    {       // Cuantos discos, VariInicial, VariFinal, VariCentral,..
            //..,almacer Movimientos,contador,iD VariInicial,...
            //...,iD VariFinal,iD VariCentral

    // En donde termina es a donde debe ser el primer movimiento
        if (n == 1)
        {
            primeMove(A, C, movimientos, contador,
              A_id, C_id);                                            // B.7
            return;// es para terminar la funcion dentro de otra
        }
        hanoiRe(n - 1, A, B, C, movimientos, contador, A_id, B_id, C_id);
        primeMove(A, C, movimientos, contador, A_id, C_id);         // B.7
        hanoiRe(n - 1, B, C, A, movimientos, contador, B_id, C_id, A_id);
    }

// Por Said Carbot et all.
// México-IPN-ESCOM,junio 2024
