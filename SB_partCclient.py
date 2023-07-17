import socket

def main():
    clientsock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    servhost = '127.0.0.1'
    servport = 8888

    number = int(input("Enter a number to check if it's prime: "))

    clientsock.sendto(str(number).encode(), (servhost, servport))

    response, address = clientsock.recvfrom(1024)
    result = response.decode()

    print(f"The number {number} is {result}.")

    clientsock.close()

if __name__ == "__main__":
    main()