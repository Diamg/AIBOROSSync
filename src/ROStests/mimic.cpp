
#include <ros/ros.h>
#include <aibo_server/Joints.h>
#include <sensor_msgs/JointState.h>
#include "std_msgs/String.h"

ros::Publisher pub;
ros::Subscriber sub; 
aibo_server::Joints joi;

//define el callback de ROS
void callback(const aibo_server::Joints::ConstPtr& msg)
{
   joi.jointRF1=msg->jointRF1;
   joi.jointRF2=msg->jointRF2;
   joi.jointRF3=msg->jointRF3;
   joi.jointRH1=msg->jointRH1;
   joi.jointRH2=msg->jointRH2;
   joi.jointRH3=msg->jointRH3;
   joi.jointLF1=msg->jointLF1;
   joi.jointLF2=msg->jointLF2;
   joi.jointLF3=msg->jointLF3;
   joi.jointLH1=msg->jointLH1;
   joi.jointLH2=msg->jointLH2;
   joi.jointLH3=msg->jointLH3;
   joi.headPan=msg->headPan;
   joi.headNeck=msg->headNeck;
   joi.headTilt=msg->headTilt;
   joi.mouth=msg->mouth;
   joi.tailTilt=msg->tailTilt;
   joi.tailPan=msg->tailPan;
   
}
//publica en el topico
void publishJoint(){
	pub.publish(joi);
}

int main(int argc, char** argv)
{
	//inicia nodo de ROS
	ros::init(argc, argv, "aibo_tutorials");
	ros::NodeHandle n;
	//define frecuencia del loop de ROS
	ros::Rate r(10);
	
	std::string input, output;
	//define el publisher y el suscriber
	pub = n.advertise<aibo_server::Joints>("/ai2/aibo/subJoints", 1, false);
	sub = n.subscribe<aibo_server::Joints>("/ai1/aibo/joints", 1, callback);
	//bucle de ROS
	while (ros::ok())
	  {
		publishJoint();
		//revisa los callbacks	
		ros::spinOnce();
		r.sleep();	
	  }
	return(0);
}
