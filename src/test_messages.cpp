#include <ros/ros.h>
#include <mavlink_phoenix/mavlink2ros.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>


ros::Publisher publisherCommand;
ros::Publisher publisherConfigParamSetBool;
ros::Publisher publisherConfigParamSetFloat;
ros::Publisher publisherConfigParamSetInt;
ros::Publisher publisherConfigRequestCount;
ros::Publisher publisherConfigRequestParams;
ros::Publisher publisherConfigRequest;
ros::Publisher publisherControlCommand;
ros::Publisher publisherControlLights;


void writeOptions()
{
    std::cout << "Please choose an option:\n";
    std::cout << "(1) Send a random \"config_param_set_bool\" message\n";
    std::cout << "(2) Send a random \"config_param_set_float\" message\n";
    std::cout << "(3) Send a random \"config_param_set_int\" message\n";
    std::cout << "(4) Send a random \"config_request_count\" message\n";
    std::cout << "(5) Send a random \"config_request_params\" message\n";
    std::cout << "(6) Send a random \"config_request\" message\n";
    std::cout << "(7) Send a random \"control_command\" message\n";
    std::cout << "(8) Send a random \"control_lights\" message\n";
    std::cout << "(0) Close Node\n";
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
    if(msg.velocity < 0.5) msg.velocity = msg.velocity - 1;
    msg.steering_front = getRandFloat() * 2 - 1;
    msg.steering_rear = getRandFloat()  * 2 - 1;
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

void initPublisher(ros::NodeHandle &n)
{
	publisherConfigParamSetBool = n.advertise<mavlink_phoenix::CONFIG_PARAM_SET_BOOL>("/to_mav_config_param_set_bool", 10);
	publisherConfigParamSetFloat = n.advertise<mavlink_phoenix::CONFIG_PARAM_SET_FLOAT>("/to_mav_config_param_set_float", 10);
	publisherConfigParamSetInt = n.advertise<mavlink_phoenix::CONFIG_PARAM_SET_INT>("/to_mav_config_param_set_int", 10);
	publisherConfigRequestCount = n.advertise<mavlink_phoenix::CONFIG_REQUEST_COUNT>("/to_mav_config_request_count", 10);
	publisherConfigRequestParams = n.advertise<mavlink_phoenix::CONFIG_REQUEST_PARAMS>("/to_mav_config_request_params", 10);
	publisherConfigRequest = n.advertise<mavlink_phoenix::CONFIG_REQUEST>("/to_mav_request", 10);
	publisherControlCommand = n.advertise<mavlink_phoenix::CONTROL_COMMAND>("/to_mav_control_command", 10);
	publisherControlLights = n.advertise<mavlink_phoenix::CONTROL_LIGHTS>("/to_mav_control_lights", 10);
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "mavlink_phoenix_test_node");
	ros::NodeHandle n;
	ros::Rate loop_rate(100);
    initPublisher(n);

    std::vector<int> choices;
    int pos = -2;

	bool close = false;
	while(!close)
	{
		ros::spinOnce();

		if(pos == -2)
		{
			writeOptions();
		}
        int choice = -1;
        char buffer[10];
        system ("/bin/stty raw");
        choice = getchar();
        system ("/bin/stty cooked");
        int c;
        //std::cout << "\n" << int(choice) << "\n";
        if(choice == 3 || choice == 4 || choice == 26)
        {
        	std::cout << "\n";
        	return 0;
        }
        if(choice == 27)
        {
        	int c = getchar();
        	std::cout << int(c) << "\n";
        	if(c == 91)
        	{
        		int d = getchar();
        		std::cout << int(d) << "\n";
				if(d == 65)
				{
					if(pos == -2)
					{
						pos = choices.size() - 1;
					}
					else if(pos == -1 && choices.size() > 0)
					{
						pos = 0;
					}
					else
					{
						pos--;
					}
					if(pos != -1)
					{
						std::cout << "\n";
						writeOptions();
						std::cout << int(choices[pos]);
					}

				}
				else if(d == 66)
				{
					if(pos == -2)
					{
						pos = 0;
					}
					else
					{
						pos++;
					}
					if(pos == choices.size() && choices.size() > 0)
					{
						pos = choices.size() -1;
					}
					if(pos < choices.size())
					{
						std::cout << "\n";
						writeOptions();
						std::cout << int(choices[pos]);
					}
				}
        	}
        }
        else
        {
            std::cout << "\n";
            if(pos != -2)
            {
                choice = choices[pos];
                pos = -2;
            }
            if(choice > 47) choice -= 48;
            choices.push_back(choice);

            switch (choice)
            {
            case 1:
                sendConfigParamSetBool();
                break;
            case 2:
                sendConfigParamSetFloat();
                break;
            case 3:
                sendConfigParamSetInt();
                break;
            case 4:
                sendConfigRequestCount();
                break;
            case 5:
                sendConfigRequestParams();
                break;
            case 6:
                sendConfigRequest();
                break;
            case 7:
                sendControlCommand();
                break;
            case 8:
                sendControlLights();
                break;
            case 0:
                close = true;
                break;
            default:
                std::cout << "Invalid Choice: ";
                std::cout << choice;
                std::cout << "\n";
            }
            if(!close)
            {
                std::cout << "\n";
            }
        }
	}

	return 0;
}
