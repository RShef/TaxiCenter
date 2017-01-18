all: client server

client: ClientMain.o Client.o Bfs.o Driver.o Grid.o GridPoint.o LuxuryCab.o Passenger.o Point.o StandardCab.o TaxiCenter.o Trip.o Socket.o Tcp.o Clock.o
	g++  -o client.out ClientMain.o Client.o Bfs.o Driver.o Grid.o GridPoint.o LuxuryCab.o Passenger.o Point.o StandardCab.o TaxiCenter.o Trip.o Socket.o Tcp.o Clock.o -lboost_serialization -std=c++11 -pthread

server: ServerMain.o Server.o Bfs.o Driver.o Grid.o GridPoint.o LuxuryCab.o Passenger.o Point.o StandardCab.o TaxiCenter.o Trip.o Socket.o Tcp.o Clock.o
	g++  -o server.out ServerMain.o Server.o Bfs.o Driver.o Grid.o GridPoint.o LuxuryCab.o Passenger.o Point.o StandardCab.o TaxiCenter.o Trip.o Socket.o Tcp.o Clock.o -lboost_serialization -std=c++11 -pthread

ServerMain.o: MainFlow/ServerMain.cpp
	g++ -c MainFlow/ServerMain.cpp -lboost_serialization -std=c++11

Server.o: MainFlow/Server.cpp
	g++ -c MainFlow/Server.cpp -lboost_serialization -std=c++11

ClientMain.o: MainFlow/ClientMain.cpp
	g++ -c MainFlow/ClientMain.cpp -lboost_serialization -std=c++11

Client.o: MainFlow/Client.cpp
	g++ -c MainFlow/Client.cpp -lboost_serialization -std=c++11

Socket.o: Socketing/Socket.cpp Socketing/Socket.h
	g++ -c Socketing/Socket.cpp Socketing/Socket.h -std=c++11

Tcp.o: Socketing/Tcp.cpp Socketing/Tcp.h
	g++ -c Socketing/Tcp.cpp Socketing/Tcp.h -std=c++11

Bfs.o: World/Bfs.cpp World/Bfs.h
	g++ -c World/Bfs.cpp

Driver.o: TaxiStation/Driver.cpp TaxiStation/Driver.h
	g++ -c TaxiStation/Driver.cpp -std=c++11

Grid.o: World/Grid.cpp World/Grid.h World/Map.h
	g++ -c World/Grid.cpp

GridPoint.o: World/GridPoint.cpp World/GridPoint.h
	g++ -c World/GridPoint.cpp

LuxuryCab.o: TaxiStation/Vehicles/LuxuryCab.cpp TaxiStation/Vehicles/LuxuryCab.h TaxiStation/Vehicles/Cab.h
	g++ -c TaxiStation/Vehicles/LuxuryCab.cpp

Passenger.o: TaxiStation/Passenger.cpp TaxiStation/Passenger.h
	g++ -c TaxiStation/Passenger.cpp

Point.o: World/Point.cpp World/Point.h
	g++ -c World/Point.cpp

StandardCab.o: TaxiStation/Vehicles/StandardCab.cpp TaxiStation/Vehicles/StandardCab.h TaxiStation/Vehicles/Cab.h
	g++ -c TaxiStation/Vehicles/StandardCab.cpp

TaxiCenter.o: TaxiStation/TaxiCenter.cpp TaxiStation/TaxiCenter.h
	g++ -c TaxiStation/TaxiCenter.cpp -std=c++11

Trip.o: TaxiStation/Trip.cpp TaxiStation/Trip.h
	g++ -c TaxiStation/Trip.cpp -std=c++11

Clock.o: World/Clock.cpp World/Clock.h
	g++ -c World/Clock.cpp

clean:
	rm -f *.o a.out client.out server.out

