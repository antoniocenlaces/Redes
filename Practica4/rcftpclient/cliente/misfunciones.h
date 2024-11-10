/****************************************************************************/
/* Plantilla para cabeceras de funciones del cliente (rcftpclient)          */
/* Plantilla $Revision$ */
/* Autor: González Almela, Antonio José */
/****************************************************************************/

/**
 * Obtiene la estructura de direcciones del servidor
 *
 * @param[in] dir_servidor String con la dirección de destino
 * @param[in] servicio String con el servicio/número de puerto
 * @param[in] f_verbose Flag para imprimir información adicional
 * @return Dirección de estructura con la dirección del servidor
 */
struct addrinfo* obtener_struct_direccion(char *dir_servidor, char *servicio, char f_verbose);

/**
 * Imprime una estructura sockaddr_in o sockaddr_in6 almacenada en sockaddr_storage
 *
 * @param[in] saddr Estructura de dirección
 */
void printsockaddr(struct sockaddr_storage * saddr);

/**
 * Configura el socket
 *
 * @param[in] servinfo Estructura con la dirección del servidor
 * @param[in] f_verbose Flag para imprimir información adicional
 * @return Descriptor del socket creado
 */
int initsocket(struct addrinfo *servinfo, char f_verbose);

/**
 * Verifica si versión y checksum de mensaje son válidos
 *
 * @param[in] recvbuffer Mensaje a comprobar
 * @return 1: es el esperado; 0: no es el esperado
 */
int mensajevalido(struct rcftp_msg recvbuffer);

/** 
 * enviar mensaje
 * 
 * @param[in] socket Descriptor del socket
 * @param[in] sendbuffer Mensaje a enviar
 * @param[in] servinfo Estructura con la dirección del servidor
 * @param[in/out] messageOrd Número secuencial del mensaje enviado
*/
void enviar(int socket,struct rcftp_msg sendbuffer, struct addrinfo *servinfo, int * messageOrd);

/**
 *  recibir
 * @param[out] buffer Espacio donde almacenar lo recibido
 * @param[in] buflen Longitud del buffer
 * @param[out] remote Dirección de la que hemos recibido
 * @param[out] remotelen Longitud de la dirección de la que hemos recibido
 * @return Tamaño del mensaje recibido
 */
ssize_t recibir(int socket, struct rcftp_msg *buffer, int buflen, struct sockaddr_storage *remote, socklen_t *remotelen);

/**
 * Algoritmo 1 del cliente
 *
 * @param[in] socket Descriptor del socket
 * @param[in] servinfo Estructura con la dirección del servidor
 */
void alg_basico(int socket, struct addrinfo *servinfo);


/**
 * Algoritmo 2 del cliente
 *
 * @param[in] socket Descriptor del socket
 * @param[in] servinfo Estructura con la dirección del servidor
 */
void alg_stopwait(int socket, struct addrinfo *servinfo);


/**
 * Algoritmo 3 del cliente
 *
 * @param[in] socket Descriptor del socket
 * @param[in] servinfo Estructura con la dirección del servidor
 * @param[in] window Tamaño deseado de la ventana deslizante
 */
void alg_ventana(int socket, struct addrinfo *servinfo,int window);


/**
 * Función que lee un número determinado de bytes de la entrada estandard
 *
 * @param[in] len número de bytes a leer
 */
char * leeDeEntradaEstandard(int len);