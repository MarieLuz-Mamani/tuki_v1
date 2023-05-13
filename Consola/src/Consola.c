
#include "consola.h"

t_config* iniciar_config(char* path_codigo)
{
	t_config *config ;

	//config=config_create(path_codigo);



	if( (config=config_create(path_codigo)) == NULL) {
		puts("No se pudo leer la configuracion \n ");
		exit(2);
	}


	return config;
}

t_log* iniciar_logger(void)
{
	t_log* logger;

	 if((logger=log_create("consola.log","Consola",1,LOG_LEVEL_INFO))== NULL){
		printf("No se pudo crear log");
		exit(1);
	}


	return logger;
}

void leer_lista(char* path_inst){


	t_list* lista=list_create();

	FILE *archivo;
	int max=100;

	if ((archivo = fopen(path_inst, "r")) == NULL)
	{
		puts ( " Error en la apertura. Es posible que el fichero no exista \n ");
	}

	char** instruccion =string_array_new();

	instruccion_ inst_consola;
	inst_consola.instruccion=string_new();
	inst_consola.parametros=string_array_new();
/*
	instruccion_ *z;
	z->instruccion=string_new();
	z->parametros=string_array_new();
*/
	char* buffer=string_new();
	while(fgets(buffer,max,archivo)){
		instruccion_ * inst;
		strtok(buffer,"\n");
		//ahora en buffer tenemos la instruccion y sus parametros
		printf("%s \n",buffer);
		if(string_contains(buffer," ") || !string_is_empty(buffer)){

			//divide entre instrucciones y parametros
			instruccion=string_n_split(buffer,2," ");

			// -- comprueba si cuarda cuando no hay nada en los demas espacios
			//printf("Guardado en instruccion %s \n",instruccion[1]);
			inst_consola.instruccion=instruccion[0];
			//z->instruccion=instruccion[0];

			if(instruccion[1] != NULL){
				printf("no vacio param\n");
				inst_consola.parametros=string_split(instruccion[1]," ");
				//z->parametros=string_split(instruccion[1]," ");
			}

			else{
				printf("vacio param \n");
				inst_consola.parametros=string_array_new();

			}

			//cargamos la lista de instrucciones a enviar a kernel
			//inst->instruccion=inst_consola.instruccion;
			//inst->parametros=inst_consola.parametros;

			//inst->instruccion=&inst_consola.instruccion;
			//inst->parametros=string_array_new();

			list_add(lista,&inst_consola);
			//void *list_get(t_list *, int index)

		}
	}
	instruccion_ *x;
	x=list_get(lista,0); // solo marca el EXIT ultimo de la lista
	printf("\n  lei de lista %s \n",x->instruccion);
	printf("\n  Largo de lista %i \n",list_size(lista));
	fclose(archivo);

}

void terminar_programa(int conexion, t_log* logger, t_config* config/*,t_list* lista_inst*/)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config)
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	log_destroy(logger);
	/*
	 if(logger != NULL){
		log_destroy(logger);
	}
	 */

	if(config != NULL){
		config_destroy(config);
	}
/*
	if(lista_inst != NULL){
		list_destroy(lista_inst);
	}
*/
	//close(conexion);

}

// int main(int argc, char** argv){
// no me deja ingresar los parametros por main
//-- investigar como en eclipse
int main(void) {

	int conexion=0;
	char* ip_kernel;
	int puerto_kernel;

	//t_list* lista_instrucciones=list_create();
	leer_lista("/home/utnso/cooder_v1/Consola/pseudocodigo.txt");
	//pasa por argumento
	/*
	if(argc<2){
		return EXIT_FAILURE;
	}
  */
	t_log* logger;
	logger=iniciar_logger();

	/* t_config* config=iniciar_config(argv[1]); */

	t_config* config_consola=iniciar_config("consola.config");


	 ip_kernel=config_get_string_value(config_consola,"IP_KERNEL");
	 puerto_kernel=config_get_int_value(config_consola,"PUERTO_KERNEL");

	printf("!!!Soy la Consola !!! ip:%s   puerto:%d  ",ip_kernel,puerto_kernel); /* prints !!!Hello World!!! */


	terminar_programa(conexion,logger,config_consola);
}
