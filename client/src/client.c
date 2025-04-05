#include "client.h"
#include <readline/readline.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	log_info(logger, "Hola soy el log");

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	if ( !(config = iniciar_config()) ) 
	{
		log_info(logger, "Error al iniciar el programa");
		terminar_programa(conexion,logger, logger);
	}
	if (!(valor = config_get_string_value(config, "CLAVE")) || !(ip = config_get_string_value(config, "IP"))
	|| !(puerto = config_get_string_value(config, "PUERTO")) )
	{
		terminar_programa(conexion,logger, logger);
	}
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	
	// Loggeamos el valor de config
	log_info(logger, "IP: %s | Puerto: %s | Valor: %s", ip, puerto, valor);



	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("tp0.log", "Cliente", 1, LOG_LEVEL_DEBUG);
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("cliente.config");


	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;
	// La primera te la dejo de yapa
	leido = readline("> ");
	while (strcmp(leido, "") != 0)
	{
		log_info(logger, leido);
		
		free(leido);
		leido = readline("> ");
	}

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío


	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();

	leido = readline("> ");
	while (strcmp(leido, "") != 0)
	{
		agregar_a_paquete(paquete, leido, sizeof(leido));
		free(leido);
		leido = readline("> ");
	}
	free(leido);
	//agregar_a_paquete(paquete, '/0', sizeof(int));

	enviar_paquete(paquete, conexion);
	eliminar_paquete(paquete);

	// Leemos y esta vez agregamos las lineas al paquete

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	if (conexion) liberar_conexion(conexion);
	config_destroy(config);
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
