import os


def compileCpp():
    os.system("cd cpp && g++ -o search search.cpp")
    os.system("cd ..")


def test(cars):
    os.system("python databaseFaker.py json " + str(cars))
    print("+= Python " + "=" * 10)
    os.system("python python/search.py")
    print("+= CPP " + "=" * 13)
    os.system("./cpp/search")
    print("+" * 15)
    os.system("rm fakedata.json")


if __name__ == "__main__":
    compileCpp()
    print("Cpp compiled !")
    print("Running tests . . .")
    n = [100, 1000, 10000]
    for i in n:
        test(i)
