import socket
import threading

HOST = '127.0.0.1'
PORT = 1234
LISTENER_LIMIT = 5

def main():
    #SOCK_STREAM uses TCP
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        server.bind((HOST, PORT))
        print(f"Running the server on host {HOST} and port {PORT}")
    except:
        print(f"Unable to bind to host {HOST} and port {PORT}")

    #Server limit
    server.listen(LISTENER_LIMIT)

    while True:

        client, address = server.accept()
        print(f"Successfully connected to client {address[0], address[1]}")


if __name__ == '__main__':
    main()

