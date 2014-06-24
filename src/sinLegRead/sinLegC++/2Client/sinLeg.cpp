
#include <urbi/uobject.hh>
#include <urbi/uclient.hh>
#include <urbi/usyncclient.hh>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <math.h>


std::ofstream f;
std::ofstream f2;
float angle=0;

urbi::UClient* client;
urbi::UClient* client2;

//guarda el tiempo
void getTime(double& tim)
{
	struct timespec tsp;
	clock_gettime(CLOCK_REALTIME, &tsp);   
	tim = (double)(tsp.tv_sec+ tsp.tv_nsec*0.000000001);
	return;
}
//escribe los datos de salida
void saveData( double tim,double value, std::string tag){
	
	char command[100];
	sprintf (command,"%f \t %f",tim, value);
	f << command << std::endl;
	
	return;
}
//escribe los datos de entrada
void saveData2( double tim,double value, std::string tag){
	
	char command[100];
	sprintf (command,"%f \t %f",tim, value);
	f2 << command << std::endl;
	
	return;
}
//Bucle de envio
void *move(void*)
{
	while(true){
		
		float l=50*sin(angle*2*M_PI/360) + 85;
		char command[100];
		sprintf (command,"legLF1.val=%f time: 100,",l);
		client2->send(command);
		angle+=10;
		double tim;
		getTime(tim);
		
		saveData2(tim,l, "LF1");
		usleep(100000);
		
	}
	return NULL;
}
//Callback de URBI
urbi::UCallbackAction onJointSensor(const urbi::UMessage &msg) 
  {
	double value = (double)msg.value->val;
	std::cout.precision(18);		
	if (msg.tag=="legLF1"){
		double tim;
		getTime(tim);
		saveData(tim,value, msg.tag);
		
	}	

	return urbi::URBI_CONTINUE;
  }
int main(int argc, char** argv)
{
	//inicia clientes URBI
	client = new urbi::UClient(argv[1], 54000);
	client2 = new urbi::UClient(argv[1], 54000);
	//Inicia callback de URBI para cada tag
	client->setCallback (urbi::callback(onJointSensor),"legRF1");
	client->setCallback (urbi::callback(onJointSensor),"legRF2");
	client->setCallback (urbi::callback(onJointSensor),"legRF3");
	client->setCallback (urbi::callback(onJointSensor),"legRH1");
	client->setCallback (urbi::callback(onJointSensor),"legRH2");
	client->setCallback (urbi::callback(onJointSensor),"legRH3");
	client->setCallback (urbi::callback(onJointSensor),"legLF1");
	client->setCallback (urbi::callback(onJointSensor),"legLF2");
	client->setCallback (urbi::callback(onJointSensor),"legLF3");
	client->setCallback (urbi::callback(onJointSensor),"legLH1");
	client->setCallback (urbi::callback(onJointSensor),"legLH2");
	client->setCallback (urbi::callback(onJointSensor),"legLH3");
	client->setCallback (urbi::callback(onJointSensor),"mouth");
	client->setCallback (urbi::callback(onJointSensor),"headNeck");
	client->setCallback (urbi::callback(onJointSensor),"headPan");
	client->setCallback (urbi::callback(onJointSensor),"headTilt");
	client->setCallback (urbi::callback(onJointSensor),"tailTilt");
	client->setCallback (urbi::callback(onJointSensor),"tailPan");
	client2->send("motors on;");
	//define el modo de resolver conflictos
	client2->send("legLF1.val->blend = cancel;");
	//demanda del loop
	client->send("loop legRF1 << legRF1.val & loop legRF2 << legRF2.val & loop legRF3 << legRF3.val & loop legRH1 << legRH1.val & loop legRH2 << legRH2.val & loop legRH3 << legRH3.val & loop legLF1 << legLF1.val & loop legLF2 << legLF2.val & loop legLF3 << legLF3.val & loop legLH1 << legLH1.val & loop legLH2 << legLH2.val & loop legLH3 << legLH3.val & loop neck << neck.val & loop headTilt << headTilt.val & loop headPan << headPan.val & loop tailPan << tailPan.val & loop tailTilt << tailTilt.val & loop mouth << mouth.val;");
	//Abre el archivo de datos de salida
	f.open ("DataOut.txt");
	f.precision(15);
	//Abre el archivo de datos de entrada
	f2.open ("DataIn.txt");
	f2.precision(15);
	// crea thread para el envio
	pthread_t t1;
	pthread_create(&t1, NULL, &move,NULL);
	pthread_join(t1,NULL);
	//Bucle de URBI
	urbi::execute();
	//cierra archivos
	f.close();
	f2.close();

	return(0);
}

