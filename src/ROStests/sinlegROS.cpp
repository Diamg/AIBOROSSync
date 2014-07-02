#include <ros/ros.h>
#include <aibo_server/Joints.h>
#include <sensor_msgs/JointState.h>
#include "std_msgs/String.h"

ros::Publisher pub;
ros::Subscriber sub; 
aibo_server::Joints joi;
float angle=0;

//publica el el mensage de tipo Joints
void publishJoint(){
	pub.publish(joi);
}

  
int main(int argc, char** argv)
{
	//inicializa el objeto joints
	joi.jointRF2=73.74736;
	joi.jointRF3=32.0;
	joi.jointRH1=0;
	joi.jointRH2=0;
	joi.jointRH3=0;
	joi.jointLF1=0;
	joi.jointLF2=0;
	joi.jointLF3=0;
	joi.jointLH1=0;
	joi.jointLH2=0;
	joi.jointLH3=0;
	joi.headPan=0;
	joi.headNeck=0;
	joi.headTilt=0;
	joi.mouth=0;
	joi.tailTilt=0;
	joi.tailPan=0;

	//inicia el nodo de ROS
	ros::init(argc, argv, "sinlegROS");
	ros::NodeHandle n;
	//define la frecuencia del loop
	ros::Rate r(10);
	
	std::string input, output;
	//define el publisher
	pub = n.advertise<aibo_server::Joints>("/aibo_server/aibo/subJoints", 1, false);
	
	//loop de ROS
	while (ros::ok())
	  {
		float l=50*sin(angle*2*M_PI/360) + 85;
		angle+=10;
		joi.jointRF1=l;
		publishJoint();
		r.sleep();	
	  }
	return(0);
}

