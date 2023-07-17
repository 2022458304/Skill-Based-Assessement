import threading

class FibonacciThread(threading.Thread):
    def run(self):
        print("For the Fibonacci Series:")
        x, y = 0, 1
        while x <= 10000:
            print(x, end=' ')
            x, y = y, x + y
        print()

class SquareThread(threading.Thread):
    def run(self):
        print("Square Numbers:")
        for numP in range(1, 10001):
            print(numP * numP, end=' ')
        print()

class CubeThread(threading.Thread):
    def run(self):
        print("Cube Numbers:")
        for numP in range(1, 10001):
            print(numP * numP * numP, end=' ')
        print()

def main():
    print("Please Select the option:")
    print("1. Fibonacci")
    print("2. Square")
    print("3. Cube")
    print("Enter Option")

    choice = int(input())

    if choice == 1:
        fib_thread = FibonacciThread()
        fib_thread.start()
        fib_thread.join()
    elif choice == 2:
        square_thread = SquareThread()
        square_thread.start()
        square_thread.join()
    elif choice == 3:
        cube_thread = CubeThread()
        cube_thread.start()
        cube_thread.join()
    else:
        print("Invalid option. Please select the correct option: 1, 2, or 3.")

if __name__ == "__main__":
    main()
