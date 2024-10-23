/**
 * @file servidorvocalesUDP.c
 *
 * Programa *servidorvocalesUDP* que cuenta vocales.
 *
 * Uso: servidorvocalesUDP puerto
 *
 * El programa crea un socket UDP en el puerto especificado, asocia el servidor
 * a ese puerto y atiende consecutivamente a los clientes UDP que envien mensajes.
 * Para cada cliente, recibe cadenas de texto, cuenta las vocales contenidas
 * y al acabar todas las recepciones envía al cliente el número total de
 * vocales contadas. El cliente señaliza el final de la transmisión enviado
 * un Byte con valor 4 (caracter ascii <EOT>)
 * 
 * Práctica 3 de Redes 2024-25
 * Autor: Antonio José González Almela
 * NIP: 143045
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include "comun.h"

// definición de constantes
#define BUFF_SIZE 1000 ///< Tamaño del buffer para las cadenas de texto.


/**
 * Función que crea la conexión y espera conexiones entrantes.
 *
 * @param servinfo Estructura de dirección local.
 * @param f_verbose Flag.
 * @return Descriptor de socket.
 */
int establecer_servicio(struct addrinfo *servinfo, char f_verbose)
{
    int sock = -1;

    printf("\nSe usará ÚNICAMENTE la primera dirección de la estructura\n");

    // crea un extremo de la comunicación y devuelve un descriptor
    if (f_verbose)
    {
        printf("Creando el socket (socket)... ");
        fflush(stdout);
    }
    sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (sock < 0)
    {
        perror("Error en la llamada socket: No se pudo crear el socket");
        // muestra por pantalla el valor de la cadena suministrada por el
        // programador, dos puntos y un mensaje de error que detalla la causa
        // del error cometido
        exit(1);
    }
    if (f_verbose) printf("hecho\n");

    // asocia el socket con un puerto
    if (f_verbose)
    {
        printf("Asociando socket a puerto (bind)... ");
        fflush(stdout);
    }
    if (bind(sock, (struct sockaddr*)servinfo->ai_addr, servinfo->ai_addrlen) < 0)
    {
        perror("Error asociando el socket");
        exit(1);
    }
    if (f_verbose) printf("hecho\n");

    // espera conexiones en un socket
    if (f_verbose)
    {
        printf("Servidor esperando recibir mensajes de cliente ... \n");
        fflush(stdout);
    }
    // En UDP no se hace listen desde el servidor
    return sock;
}

/**
 * Función que cuenta las vocales en una cadena de texto
 *
 * @param msg Cadena con el mensaje al que contar vocales.
 * @param s   Longitud del mensaje.
 * @return Número de vocales en msg[0..s].
 */
uint32_t countVowels(char msg[], size_t s)
{
    uint32_t result = 0;
    size_t i;
    for (i = 0; i < s; i++)
    {
        if (msg[i] == 'a' || msg[i] == 'A' ||
            msg[i] == 'e' || msg[i] == 'E' ||
            msg[i] == 'i' || msg[i] == 'I' ||
            msg[i] == 'o' || msg[i] == 'O' ||
            msg[i] == 'u' || msg[i] == 'U') result++;
    }
    return result;
}

/**
 * Programa principal
 *
 * @param argc Número de argumentos usados en la línea de comandos.
 * @param argv Vector de punteros a cadenas de caracteres. argv[0]
 *             apunta al nombre del programa, argv[1] al primer
 *             argumento y así sucesivamente.
 * @return 0 si todo ha ido bien, distinto de 0 si hay error.
 */
int main(int argc, char * argv[])
{   
    const char fin = 4;
    // declaración de variables propias del programa principal (locales a main)
    char f_verbose = 1;         // flag, 1: imprimir información extra
    struct addrinfo * servinfo = {0}; // dirección propia (servidor)
    int sock, endComm = 0;      // descriptor de socket y control de final comunicación del cliente
    char msg[BUFF_SIZE];        // espacio para almacenar los datos recibidos
    ssize_t readbytes;          // numero de bytes recibidos
    uint32_t num, netNum;       // contador de vocales en formato local y de red
    struct sockaddr_storage  caddr = {0}; // dirección del cliente con formato struct sockaddr_storage
                                          // que permite almacenar direcciones IPv4 e IPv6
    socklen_t clen;             // longitud de la dirección

    // verificación del número de parámetros:
    if (argc != 2)
    {
        printf("Número de parámetros incorrecto \n");
        printf("Uso: %s puerto\n", argv[0]);
        exit(1); // finaliza el programa indicando salida incorrecta (1)
    }

    // obtiene estructura de direccion para el servidor
    servinfo = obtener_struct_direccion(NULL, argv[1], f_verbose);

    // crea un extremo de la comunicación. Devuelve el descriptor del socket
    // sock contiene el identificador del socket abierto por el servidor
    sock = establecer_servicio(servinfo, f_verbose);

    // hay que liberar la memoria dinámica usada para la dirección
    // cuando ya no se necesite
    freeaddrinfo(servinfo);
    servinfo = NULL;
    // como ya se ha liberado ese bloque de memoria,
    // dejamos de apuntarlo para evitar acceder a ella por error.
    // Si referenciamos esta variable el programa abortará con
    // ERROR: SEGMENTATION FAULT

    // bucle infinito para atender conexiones una tras otra
    while (1)
    {
        // bucle de contar vocales
        num = 0;
        do {
            // servidor se bloquea en recvfrom() esperando recibir mensaje de algún cliente
            // una vez recibido recvfrom() nos deja en el caddr (struct sockaddr_storage)
            // la estructura de dirección del cliente que ha enviado el mensaje
            clen = sizeof caddr;
            if ((readbytes = recvfrom(sock, msg, BUFF_SIZE,0, (struct sockaddr *) &caddr, &clen)) < 0)
            {
                perror("Error de lectura en el socket");
                exit(1);
            }
            // En caso de lectura correcta y que el mensaje sea un byte de valor 4 se interrumpe bucle
            if (readbytes == 1 && msg[0] == fin) endComm = 1;
                else
                // caso contrario se imprime mensaje recibido y se cuentan las vocales
                {
                    printf("Mensaje recibido del cliente: "); fflush(stdout);
                    write(1, msg, readbytes);
                    // muestra en pantalla (salida estándar 1) el mensaje recibido
                    // evitamos usar printf por si lo recibido no es texto acabado con \0
                    num += countVowels(msg, readbytes);
                    printf("Vocales contadas hasta el momento: %d\n",num);
                }

        // condición de final: recibir byte de valor 4
        } while (endComm == 0);

        // No es necesario cerrar socket en UDP
        printf("Contadas %d vocales\n", num);  // muestra las vocales recibidas
        netNum = htonl(num);  // convierte el entero largo sin signo hostlong
        // desde el orden de bytes del host al de la red
        // envia al cliente el número de vocales recibidas:
        if (sendto(sock, &netNum, sizeof netNum, 0, (struct sockaddr *) &caddr, clen) < 0)
        {
            perror("Error de escritura en el socket");
            exit(1);
        }
        if (f_verbose) printf("Enviado número de vocales contadas al cliente\n");
        // Terminado el servicio a este cliente, no es necesario cerrar el canal con el cliente
        // en UDP no existe canal abierto
        // una vez atendido este cliente volvemos a esperar mensaje de otro cliente
    }

    // código inalcanzable.
    close(sock);
    exit(0);
}
