#include "ros/ros.h"

#include <std_msgs/String.h>

#include "test_serial_arduino/Connexion.h"
#include "test_serial_arduino/DemandeContenant.h"

#include "MQTTClient.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "prog1");

  ros::NodeHandle n;

  ros::ServiceClient clientCoDistrib1 = n.serviceClient<test_serial_arduino::Connexion>("co_distrib_contenant");
  test_serial_arduino::Connexion srvCoDistrib1;

  ros::ServiceClient clientDemDistrib1 = n.serviceClient<test_serial_arduino::DemandeContenant>("dem_distrib_contenant");
  test_serial_arduino::DemandeContenant srvDemDistrib1;


  while (ros::ok())
  {

	std::string inputString;
    std::cout << "Give input ";

	int x;
    cin >> x ;

    if(x == 0)
    {
		ROS_INFO("Test dem");
      	if (clientDemDistrib1.call(srvDemDistrib1))
		{
		  ROS_INFO("Alors success : %d", srvDemDistrib1.response.success);
		  ROS_INFO("Alors code : %I64d", srvDemDistrib1.response.code);
		}
		else
		{
		  ROS_ERROR("Failed to call service connexion");
		}
    }
	else if(x == 1)
	{
		ROS_INFO("Test co");
      	if (clientCoDistrib1.call(srvCoDistrib1))
		{
		  ROS_INFO("Alors success : %d", srvDemDistrib1.response.success);
		}
		else
		{
		  ROS_ERROR("Failed to call service connexion");
		}
	}
	else
	{
		ROS_INFO("Sorry ...");
	}
	

	//ros::Duration(10).sleep();

  	ros::spinOnce();
  }
  

  

}



/*
#include "ros/ros.h"
#include "std_msgs/UInt16.h"

#include <sstream>

void testConnexion(ros::Publisher disCA);

void distribCallback(const std_msgs::UInt16::ConstPtr& msg)
{
  ROS_INFO("Incoming data from Distributeur de contenant : %d", msg->data);
}





int main(int argc, char **argv)
{

  ros::init(argc, argv, "prog1");

  ros::NodeHandle n;

  ros::Publisher dis_pub = n.advertise<std_msgs::UInt16>("distrib_sub",1);

  ros::Subscriber dis_sub = n.subscribe("distrib_pub", 1000, distribCallback);

  ros::Rate loop_rate(10);
  
  std_msgs::UInt16 msg;

  msg.data = 0;

  while (ros::ok())
  {
	ROS_INFO("We publish");

    testConnexion(dis_pub);

	ros::Duration(2).sleep();

  	ros::spinOnce();
  }

}

void testConnexion(ros::Publisher disCA)
{
  std_msgs::UInt16 msg;
  msg.data = 0;

  disCA.publish(msg);
}
*/
