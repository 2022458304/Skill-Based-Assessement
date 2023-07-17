import socket

def is_prime(numP):
    if numP < 2:
        return False
    for x in range(2, int(numP**0.5) + 1):
        if numP % x == 0:
            return False
    return True

def main():
    servsock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    servhost = '127.0.0.1'
    servport = 8888

    servsock.bind((servhost, servport))

    print("The Server is currently listening on {}:{}".format(servhost, servport))

    try:
        while True:
            data, address = servsock.recvfrom(1024)
            number = int(data.decode())

            if is_prime(number):
                result = "Prime"
            else:
                result = "Not Prime"

            servsock.sendto(result.encode(), address)

    except KeyboardInterrupt:
        print("Server is terminated by user.")
        servsock.close()

if __name__ == "__main__":
    main()