
# Group Chat Application using C++ Sockets

This project implements a multi-client group chat application using C++ sockets. It allows several clients to connect to a server and exchange messages in real-time. The server listens for client connections, while each client can send and receive messages from other clients connected to the server.

## Features
- **Multi-client communication**: Several clients can connect and chat simultaneously.
- **Real-time messaging**: Clients can send and receive messages in real time.
- **Client-server architecture**: Centralized server manages all communications between clients.

## Prerequisites

### For Windows:
- **MinGW** or **Visual Studio**
- Winsock library (`ws2_32.lib`) for socket programming.

## Files

- **client.cpp**: The client-side application that connects to the server and sends/receives messages.
- **sockets.cpp**: The server-side application that listens for incoming client connections and relays messages between them.

## Compilation Instructions

### On Windows:
1. **Client Compilation**:
   ```bash
   g++ client.cpp -o client.exe -lws2_32
   ```

2. **Server Compilation**:
   ```bash
   g++ sockets.cpp -o server.exe -lws2_32
   ```

## Running the Application

### Step 1: Start the Server

Run the server before any clients to allow clients to connect.

#### On Windows:
```bash
server.exe
```

The server will start listening on port `11111` for incoming client connections.

### Step 2: Start the Clients

Once the server is running, start multiple clients to connect to the server.

#### On Windows:
```bash
client.exe
```

### Group Chat Usage
- After connecting, clients can send messages by typing and hitting `Enter`.
- Messages are broadcast to all other connected clients.
- Type `quit` to exit the chat session.

### Example Chat Session:
- **Client 1**: `Hello, how's everyone?`
- **Client 2**: `Doing great! What about you?`
- **Client 3**: `Excited to join the chat.`

## Notes
- The server must be running before clients can connect.
- All clients should connect using the same IP address and port (default: `127.0.0.1:11111`).

## Future Enhancements
- Adding client nickname support for easier identification.
- Handling message logging or history.
- Implementing file transfers between clients.

## License
This project is licensed under the MIT License - free to use and modify.
