#include <ros/ros.h>
#include <mavlink_phoenix/mavlink2ros.h>
#include <iostream>
#include <vector>
#include <string>
//#include <random>

ros::Publisher publisherCommand;
ros::Publisher publisherConfigParamSetBool;
ros::Publisher publisherConfigParamSetFloat;
ros::Publisher publisherConfigParamSetInt;
ros::Publisher publisherConfigRequestCount;
ros::Publisher publisherConfigRequestParams;
ros::Publisher publisherConfigRequest;
ros::Publisher publisherControlCommand;
ros::Publisher publisherControlLights;

std::vector<mavlink_phoenix::COMMAND*> messagesCommand;
std::vector<mavlink_phoenix::CONFIG_COUNT*> messagesConfigCount;
std::vector<mavlink_phoenix::CONFIG_PARAM_BOOL*> messagesConfigParamBool;
std::vector<mavlink_phoenix::CONFIG_PARAM_FLOAT*> messagesConfigParamFloat;
std::vector<mavlink_phoenix::CONFIG_PARAM_INT*> messagesConfigParamInt;
std::vector<mavlink_phoenix::CONFIG*> messagesConfig;
std::vector<mavlink_phoenix::DEBUG*> messagesDebug;
std::vector<mavlink_phoenix::HEARTBEAT*> messagesHeartbeat;
std::vector<mavlink_phoenix::IMU*> messagesImu;
std::vector<mavlink_phoenix::NOTIFICATION*> messagesNotification;
std::vector<mavlink_phoenix::ODOMETER_ABS*> messagesOdometerAbs;
std::vector<mavlink_phoenix::ODOMETER_DELTA_RAW*> messagesOdometerDeltaRaw;
std::vector<mavlink_phoenix::ODOMETER_DELTA*> messagesOdometerDelta;
std::vector<mavlink_phoenix::ODOMETER_RAW*> messagesOdometerRaw;
std::vector<mavlink_phoenix::ODOMETER*> messagesOdometer;
std::vector<mavlink_phoenix::PARKING_LOT*> messagesParkingLot;
std::vector<mavlink_phoenix::PROXIMITY*> messagesProximity;
std::vector<mavlink_phoenix::TELEMETRY*> messagesTelemetry;


void writeOptions()
{
	std::cout << "Please choose an option:\n";
	std::cout << "(1) Send a generic \"command\" message\n";
	std::cout << "(2) Send a generic \"config_param_set_bool\" message\n";
	std::cout << "(3) Send a generic \"config_param_set_float\" message\n";
	std::cout << "(4) Send a generic \"config_param_set_int\" message\n";
	std::cout << "(5) Send a generic \"config_request_count\" message\n";
	std::cout << "(6) Send a generic \"config_request_params\" message\n";
	std::cout << "(7) Send a generic \"config_request\" message\n";
	std::cout << "(8) Send a generic \"control_command\" message\n";
	std::cout << "(9) Send a generic \"control_lights\" message\n";
	std::cout << "(15) Print received messages\n";
	std::cout << "(20) Close Node\n";
	std::cout << "Your choice: ";
}

uint8_t getRand()
{
	return std::rand() % 256;
}

float getRandFloat()
{
	return (float)std::rand() / (float)RAND_MAX;
}

bool sendCommand()
{
	mavlink_phoenix::COMMAND msg;
	msg.sysid = getRand();
	msg.compid = getRand();
	msg.command = getRand();
	publisherCommand.publish(msg);
	std::cout << "Wrote \"Command\" Message: sysid: " << int(msg.sysid) << "; compid: " << int(msg.compid) << "; command:" << int(msg.command) << "\n";
}

bool sendConfigParamSetBool()
{
	mavlink_phoenix::CONFIG_PARAM_SET_BOOL msg;
	msg.sysid = getRand();
	msg.compid = getRand();
	msg.config_id = getRand();
	msg.param_id = getRand();
	msg.value = std::rand() % 2;
	publisherConfigParamSetBool.publish(msg);
	std::string val = (msg.value == 1) ? "true" : "false";
	std::cout << "Wrote \"Config_Param_Set_Bool\" Message: sysid: " << int(msg.sysid) << "; compid: " << int(msg.compid);
	std::cout << "; config_id: " << int(msg.config_id) << "; param_id" << int(msg.param_id);
	std::cout << "; value: " << val << "\n";
}

bool sendConfigParamSetFloat()
{
	mavlink_phoenix::CONFIG_PARAM_SET_FLOAT msg;
	msg.sysid = getRand();
	msg.compid = getRand();
	msg.config_id = getRand();
	msg.param_id = getRand();
	msg.value = getRandFloat();
	publisherConfigParamSetFloat.publish(msg);
	std::cout << "Wrote \"Config_Param_Set_Float\" Message: sysid: " << int(msg.sysid) << "; compid: " << int(msg.compid);
	std::cout << "; config_id: " << int(msg.config_id) << "; param_id: " << int(msg.param_id) << "; value: " << msg.value << "\n";
}

bool sendConfigParamSetInt()
{
	mavlink_phoenix::CONFIG_PARAM_SET_INT msg;
	msg.sysid = getRand();
	msg.compid = getRand();
	msg.config_id = getRand();
	msg.param_id = getRand();
	msg.value = std::rand();
	publisherConfigParamSetInt.publish(msg);
	std::cout << "Wrote \"Config_Param_Set_Int\" Message: sysid: " << int(msg.sysid) << "; compid: " << int(msg.compid);
	std::cout << "; config_id: " << int(msg.config_id) << "; param_id: " << int(msg.param_id) << "; value: " << msg.value << "\n";
}

bool sendConfigRequestCount()
{
	mavlink_phoenix::CONFIG_REQUEST_COUNT msg;
	msg.sysid = getRand();
	msg.compid = getRand();
	msg.dummy = getRand();
	publisherConfigRequestCount.publish(msg);
	std::cout << "Wrote \"Config_Request_Count\" Message: sysid: " << int(msg.sysid) << "; compid: " << int(msg.compid);
	std::cout << "; dummy: " << int(msg.dummy) << "\n";
}

bool sendConfigRequestParams()
{
	mavlink_phoenix::CONFIG_REQUEST_PARAMS msg;
	msg.sysid = getRand();
	msg.compid = getRand();
	msg.config_id = getRand();
	msg.param_id = getRand();
	publisherConfigRequestParams.publish(msg);
	std::cout << "Wrote \"Config_Request_Params\" Message: sysid: " << int(msg.sysid) << "; compid: " << int(msg.compid);
	std::cout << "; config_id: " << int(msg.config_id) << "; param_id: " << int(msg.param_id) << "\n";
}

bool sendConfigRequest()
{
	mavlink_phoenix::CONFIG_REQUEST msg;
	msg.sysid = getRand();
	msg.compid = getRand();
	msg.config_id = getRand();
	publisherConfigRequest.publish(msg);
	std::cout << "Wrote \"Config_Request\" Message: sysid: " << int(msg.sysid) << "; compid: " << int(msg.compid);
	std::cout << "; config_id: " << int(msg.config_id) << "\n";
}

bool sendControlCommand()
{
	mavlink_phoenix::CONTROL_COMMAND msg;
	msg.sysid = getRand();
	msg.compid = getRand();
	msg.velocity = getRandFloat();
	msg.steering_front = getRandFloat();
	msg.steering_rear = getRandFloat();
	msg.indicator_left = std::rand() % 2;
	msg.indicator_right = std::rand() % 2;
	publisherControlCommand.publish(msg);
	std::cout << "Wrote \"Control_Command\" Message: sysid: " << int(msg.sysid) << "; compid: " << int(msg.compid);
	std::cout << "; velocity: " << msg.velocity << "; steering_front: " << msg.steering_front << "; steering_rear: " << msg.steering_rear;
	std::cout << "; indicator_left: " << int(msg.indicator_left) << "; indicator_right: " << int(msg.indicator_right) << "\n";
}

bool sendControlLights()
{
	mavlink_phoenix::CONTROL_LIGHTS msg;
	msg.sysid = getRand();
	msg.compid = getRand();
	for(int i = 0; i < 15; i++)
	{
		msg.colors[i] = (std::rand() % (256*256*256)) * 256;
	}
	publisherControlLights.publish(msg);
	std::cout << "Wrote \"Control Lights\" Message: sysid: " << int(msg.sysid) << "; compid: " << int(msg.compid) << "\n";
	for(int i = 0; i < 15; i++)
	{
		int a = msg.colors[i] % 256;
		int b = (msg.colors[i] / 256) % 256;
		int g = (msg.colors[i] / (256 * 256)) % 256;
		int r = msg.colors[i] / (256 * 256 * 256);
 		std::cout << "color[" << i << "]: r:" << r << " g:" << g << " b:" << b << " a:" << a << "\n";
	}
	std::cout << " \n";
}

void receiveCommand(const mavlink_phoenix::COMMAND &msg)
{
	mavlink_phoenix::COMMAND *newMsg = new mavlink_phoenix::COMMAND();
	newMsg->sysid = msg.sysid;
	newMsg->compid = msg.compid;
	newMsg->command = msg.command;
	messagesCommand.push_back(newMsg);
}

void receiveConfigCount(const mavlink_phoenix::CONFIG_COUNT &msg)
{

}

void receiveConfigParamBool(const mavlink_phoenix::CONFIG_PARAM_BOOL &msg)
{

}

void receiveConfigParamFloat(const mavlink_phoenix::CONFIG_PARAM_FLOAT &msg)
{

}

void receiveConfigParamInt(const mavlink_phoenix::CONFIG_PARAM_INT &msg)
{

}

void receiveConfig(const mavlink_phoenix::CONFIG::ConstPtr &msg)
{

}

void receiveDebug(const mavlink_phoenix::DEBUG::ConstPtr &msg)
{

}

void receiveHeartbeat(const mavlink_phoenix::HEARTBEAT::ConstPtr &msg)
{

}

void receiveImu(const mavlink_phoenix::IMU::ConstPtr &msg)
{

}

void receiveNotification(const mavlink_phoenix::NOTIFICATION::ConstPtr &msg)
{

}

void receiveOdometerAbs(const mavlink_phoenix::ODOMETER_ABS::ConstPtr &msg)
{

}

void receiveOdometerDeltaRaw(const mavlink_phoenix::ODOMETER_DELTA_RAW::ConstPtr &msg)
{

}

void receiveOdometerDelta(const mavlink_phoenix::ODOMETER_DELTA::ConstPtr &msg)
{

}

void receiveOdometerRaw(const mavlink_phoenix::ODOMETER::ConstPtr &msg)
{

}

void receiveOdometer(const mavlink_phoenix::ODOMETER::ConstPtr &msg)
{

}

void receiveParkingLot(const mavlink_phoenix::PARKING_LOT::ConstPtr &msg)
{

}

void receiveProximity(const mavlink_phoenix::PROXIMITY::ConstPtr &msg)
{

}

void receiveTelemetry(const mavlink_phoenix::TELEMETRY::ConstPtr &msg)
{

}

void printReceivedMessages()
{
	std::cout << "No Messages Received. (Not implemented)\n";
}

void initPublisher(ros::NodeHandle &n)
{
	publisherCommand = n.advertise<mavlink_phoenix::COMMAND>("/to_mav_command", 10);
	publisherConfigParamSetBool = n.advertise<mavlink_phoenix::CONFIG_PARAM_SET_BOOL>("/to_mav_config_param_set_bool", 10);
	publisherConfigParamSetFloat = n.advertise<mavlink_phoenix::CONFIG_PARAM_SET_FLOAT>("/to_mav_config_param_set_float", 10);
	publisherConfigParamSetInt = n.advertise<mavlink_phoenix::CONFIG_PARAM_SET_INT>("/to_mav_config_param_set_int", 10);
	publisherConfigRequestCount = n.advertise<mavlink_phoenix::CONFIG_REQUEST_COUNT>("/to_mav_config_request_count", 10);
	publisherConfigRequestParams = n.advertise<mavlink_phoenix::CONFIG_REQUEST_PARAMS>("/to_mav_config_request_params", 10);
	publisherConfigRequest = n.advertise<mavlink_phoenix::CONFIG_REQUEST>("/to_mav_request", 10);
	publisherControlCommand = n.advertise<mavlink_phoenix::CONTROL_COMMAND>("/to_mav_control_command", 10);
	publisherControlLights = n.advertise<mavlink_phoenix::CONTROL_LIGHTS>("/to_mav_control_lights", 10);
}

void initSubscriber(ros::NodeHandle &n)
{
	ros::Subscriber subscriberCommand = n.subscribe("/to_mav_command", 10, receiveCommand);
	ros::Subscriber subscriberConfigCount = n.subscribe("/to_mav_config_count", 10, receiveConfigCount);
	ros::Subscriber subscriberConfigParamBool = n.subscribe("/to_mav_config_param_bool", 10, receiveConfigParamBool);
	ros::Subscriber subscriberConfigParamFloat = n.subscribe("/to_mav_config_param_float", 10, receiveConfigParamFloat);
	ros::Subscriber subscriberConfigParamInt = n.subscribe("/to_mav_config_param_int", 10, receiveConfigParamInt);
	ros::Subscriber subscriberConfig = n.subscribe("/to_mav_config", 10, receiveConfig);
	ros::Subscriber subscriberDebug = n.subscribe("/to_mav_debug", 10, receiveDebug);
	ros::Subscriber subscriberHeartbeat = n.subscribe("/to_mav_heartbeat", 10, receiveHeartbeat);
	ros::Subscriber subscriberImu = n.subscribe("/to_mav_imu", 10, receiveImu);
	ros::Subscriber subscriberNotification = n.subscribe("/to_mav_notification", 10, receiveNotification);
	ros::Subscriber subscriberOdometerAbs = n.subscribe("/to_mav_odometer_abs", 10, receiveOdometerAbs);
	ros::Subscriber subscriberOdometerDeltaRaw = n.subscribe("/to_mav_odometer_delta_raw", 10, receiveOdometerDeltaRaw);
	ros::Subscriber subscriberOdometerDelta = n.subscribe("/to_mav_odometer_delta", 10, receiveOdometerDelta);
	ros::Subscriber subscriberOdometerRaw = n.subscribe("/to_mav_odometer_raw", 10, receiveOdometerRaw);
	ros::Subscriber subscriberOdometer = n.subscribe("/to_mav_odometer", 10, receiveOdometer);
	ros::Subscriber subscriberParkingLot = n.subscribe("/to_mav_parking_lot", 10, receiveParkingLot);
	ros::Subscriber subscriberProximity = n.subscribe("/to_mav_proximity", 10, receiveProximity);
	ros::Subscriber subscriberTelemetry = n.subscribe("/to_mav_telemtry", 10, receiveTelemetry);
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "mavlink_phoenix_test_node");
	ros::NodeHandle n;
	ros::Rate loop_rate(100);
	initPublisher(n);
	initSubscriber(n);

	bool close = false;
	while(!close)
	{
		ros::spinOnce();

		writeOptions();
		int choice = 0;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			sendCommand();
			break;
		case 2:
			sendConfigParamSetBool();
			break;
		case 3:
			sendConfigParamSetFloat();
			break;
		case 4:
			sendConfigParamSetInt();
			break;
		case 5:
			sendConfigRequestCount();
			break;
		case 6:
			sendConfigRequestParams();
			break;
		case 7:
			sendConfigRequest();
			break;
		case 8:
			sendControlCommand();
			break;
		case 9:
			sendControlLights();
			break;
		case 15:
			printReceivedMessages();
			break;
		case 20:
			close = true;
			break;
		default:
			std::cout << "Invalid Choice: " << choice << "\n";
		}
		if(!close)
		{
			std::cout << "\n";
		}
	}

	return 0;
}
