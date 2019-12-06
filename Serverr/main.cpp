#include <iostream>
#include <enet/enet.h>

#include <glfw3.h>

//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <limits>
#include <glut.h>


using namespace std;









int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Server Window");
	
	/*
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("Server");

	glutMainLoop();
	*/



	if (enet_initialize() != 0)
	{
		cout << "Enet failed to initialise!" << "\n\n";
	}
	ENetAddress address;
	ENetHost* server;
	ENetEvent enetEvent;

	ENetPacket* dataPacket;


	address.host = ENET_HOST_ANY;
	address.port = 2222;

	server = enet_host_create(&address, 32, 2, 0, 0);

	if (server == NULL)
	{
		cout << "Server failed to initialise!" << "\n\n";
	}
 


		while (enet_host_service(server, &enetEvent, 0) > 0)
		{
			switch (enetEvent.type)
			{
			case ENET_EVENT_TYPE_CONNECT:

				cout << "A client connected from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << ".\n";


				//enetEvent.peer->data = "This is a client";

				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				cout << "The client from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << " disconnected \n";

				enetEvent.peer->data = NULL;

				break;
			}
		}
	


		
	return 0;

	enet_host_destroy(server);
	atexit(enet_deinitialize);
	

}
