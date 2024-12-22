/*************************************************************************************************************
 * INCLUDE
*************************************************************************************************************/
#include <iostream>
#include <string.h>
#include <sstream>
#include <unistd.h>

#include <pthread.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*************************************************************************************************************
 * DEFINE
*************************************************************************************************************/
using namespace std;

#define APP_USER_CMD_BUFF_SIZE      100
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

/*************************************************************************************************************
 * VARIABLES
*************************************************************************************************************/
int socket_port_number;

typedef struct {
    string address;
    string port;
} client_thread_data;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static int data_ready = 0;
static string MessageToServer;


/*************************************************************************************************************
 * FUNCTIONS
*************************************************************************************************************/

/***
 * Display the initial GUI
 */
void display_chatApplicationUI(void)
{
    std::cout << "***************************************************************************************\n";
    std::cout << "********************************** Chat Application ***********************************\n";
    std::cout << "***************************************************************************************\n\n";

    std::cout << "Use the commands below:\n";
    std::cout << "1. help                               : display user interface options\n";
    std::cout << "2. myip                               : display IP address of this app\n";
    std::cout << "3. myport                             : display listening port of this app\n";
    std::cout << "4. connect <destination> <port no>    : connect to the app of another computer\n";
    std::cout << "5. list                               : list all the connections of this app\n";
    std::cout << "6. terminate <connection id>          : terminate a connection\n";
    std::cout << "7. send <connection id> <message>     : send a message to a connection\n";
    std::cout << "8. exit                               : close all connections & terminate the app\n\n";
    std::cout << "***************************************************************************************\n";
}

static void *tcp_client_handler(void *args)
{
    client_thread_data *data = (client_thread_data *)args;
    int portno;
    int server_fd;
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0',sizeof(serv_addr));

    portno = stoi(data->port);

    // Server addressing
    serv_addr.sin_family = AF_INET; //ipv4 protocol
    serv_addr.sin_port   = htons(portno);
    if (inet_pton(AF_INET, (data->address).c_str(), &serv_addr.sin_addr) == -1) 
        handle_error("inet_pton()");

    // Socket create
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
        handle_error("socket()");

    // Connect to server
    if (connect(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        handle_error("connect()");

    cout << "Connected successfully. Ready for data tranmission " << endl;

    pthread_mutex_lock(&mutex);
    while (1)
    {
        pthread_cond_wait(&cond, &mutex);
        if (data_ready == 1)
        {
            cout << "Send " << MessageToServer << " to Server" << endl;
            data_ready = 0;
        }
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}
static void *user_command_handler(void *args)
{
    while (1)
    {
        string userCommand;

        cout << "Enter your command: ";
        getline(cin, userCommand);

        // Parse the command
        istringstream stream(userCommand);

        string Command;
        // Split string command
        stream >> Command;

        if (Command == "help")
        {
            cout << Command << " handler()" << endl;
        }
        else if (Command == "myip")
        {
            cout << Command << " handler()" << endl;
        }
        else if (Command == "myport")
        {
            cout << Command << " handler()" << endl;
        }
        else if (Command == "connect")
        {
            int ret;
            pthread_t tcpClient_thread;
            string address, port;

            stream >> address;
            stream >> port;

            client_thread_data data;
            data.address = address;
            data.port = port;

            // Threads creating
            if (ret = pthread_create(&tcpClient_thread, NULL, &tcp_client_handler, &data))
            {
                handle_error("pthread_create()");
                exit(EXIT_FAILURE);
            }

            pthread_join(tcpClient_thread, NULL);
        }
        else if (Command == "list")
        {
            cout << Command << " handler()" << endl;
        }
        else if (Command == "terminate")
        {
            cout << Command << " handler()" << endl;
        }
        else if (Command == "send")
        {
            cout << Command << " handler()" << endl;

            string connect_id, message;

            pthread_mutex_lock(&mutex);
            stream >> connect_id;
            stream >> MessageToServer;
            data_ready = 1;
            cout << "Send " << MessageToServer << " to " << connect_id << endl;
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mutex);
        }
        else if (Command == "exit")
        {
            cout << Command << " handler()" << endl;
            exit(EXIT_SUCCESS);
        }
        else
        {
            cout << Command << "Unknown command" << endl;
        }
    }
    return 0;
}

static void *tcp_server_handler(void *args)
{
    //TODO: initialize TCP socket server, creat a subject for it
    int server_fd, new_socket_fd;
    int opt;
    int len;
    struct sockaddr_in serv_addr, client_addr;

    // Socket create
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
        handle_error("socket()");

    // Prevent: “address already in use”
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        handle_error("setsockopt()");

    // Server initial
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(socket_port_number);
    serv_addr.sin_addr.s_addr =  INADDR_ANY;

    // Binding socket with server address
    if (bind(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        handle_error("bind()");

    // Listen to 5 connection
    if (listen(server_fd, 50) == -1)
        handle_error("listen()");

    // Get client's information
    len = sizeof(client_addr);

    while (1)
    {
        // listening for connection
        new_socket_fd  = accept(server_fd, (struct sockaddr*)&client_addr, (socklen_t *)&len);
        if (new_socket_fd == -1)
        {
            handle_error("accept()");
        }
        
        string client_ip(INET_ADDRSTRLEN, '\0');

        inet_ntop(AF_INET, &client_addr.sin_addr, &client_ip[0], INET_ADDRSTRLEN);
        cout << "\nAccepted a new connection from address: " << client_ip << ", set up at port: " << ntohs(serv_addr.sin_port) << endl;
    }
}

int main(int argc, char *argv[])
{
    int ret;

    pthread_t tcpServer_thread, userCommand_thread;

    if (argc < 2)
    {
        cout << "No port provided\ncommand: ./chat <port number>" << endl;
        exit(EXIT_FAILURE);
    }

    socket_port_number = atoi(argv[1]);

    // GUI display
    display_chatApplicationUI();

    cout << "Application is listening on port: " << socket_port_number << "\n\n";

    // Threads creating
    if (ret = pthread_create(&tcpServer_thread, NULL, &tcp_server_handler, NULL))
    {
        handle_error("pthread_create()");
        exit(EXIT_FAILURE);
    }

    if (ret = pthread_create(&userCommand_thread, NULL, &user_command_handler, NULL))
    {
        handle_error("pthread_create()");
        exit(EXIT_FAILURE);
    }

    pthread_join(tcpServer_thread, NULL);
    pthread_join(userCommand_thread, NULL);

    return 0;
}
