
Network Application Project



Project Structure



project/
│
├── CMakeLists.txt          
├── client/
│   └── client.cpp 
│   └── CMakeLists.txt       
└── server/
    └── server.cpp              
    └── CMakeLists.txt

CMakeLists.txt: The main CMake file that configures the build system.
client/client.cpp: Contains the implementation of the client-side application.
server/server.cpp: Contains the implementation of the server-side application.



Prerequisites



Before building the project, ensure you have the following installed on your system:

CMake (version 3.10 or higher)
C++ compiler (GCC, Clang, or another modern compiler)
pthread library (for Unix-based systems)



Running the Application



Starting the Server

To start the server, run the following command from the build directory:

./server/server <port_number>

Running the Client

To connect the client to the server, run the following command:

./client/client <server_ip> <port_number>

