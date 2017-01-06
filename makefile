all: client server

client: ClientMain.o Bfs.o Driver.o Grid.o GridPoint.o LuxuryCab.o Passenger.o Point.o StandardCab.o TaxiCenter.o Trip.o Socket.o Udp.o Clock.o
	g++  -o client.out ClientMain.o Bfs.o Driver.o Grid.o GridPoint.o LuxuryCab.o Passenger.o Point.o StandardCab.o TaxiCenter.o Trip.o Socket.o Udp.o Clock.o -lboost_serialization

server: ServerMain.o Bfs.o Driver.o Grid.o GridPoint.o LuxuryCab.o Passenger.o Point.o StandardCab.o TaxiCenter.o Trip.o Socket.o Udp.o Clock.o
	g++  -o server.out ServerMain.o Bfs.o Driver.o Grid.o GridPoint.o LuxuryCab.o Passenger.o Point.o StandardCab.o TaxiCenter.o Trip.o Socket.o Udp.o Clock.o -lboost_serialization

ServerMain.o: TaxiStation/ServerMain.cpp
	g++ -c TaxiStation/ServerMain.cpp -lboost_serialization

ClientMain.o: TaxiStation/ClientMain.cpp
	g++ -c TaxiStation/ClientMain.cpp -lboost_serialization

Socket.o: Socketing/Socket.cpp Socketing/Socket.h
	g++ -c Socketing/Socket.cpp Socketing/Socket.h

Udp.o: Socketing/Udp.cpp Socketing/Udp.h
	g++ -c Socketing/Udp.cpp Socketing/Udp.h

Bfs.o: TaxiStation/Bfs.cpp TaxiStation/Bfs.h
	g++ -c TaxiStation/Bfs.cpp

Driver.o: TaxiStation/Driver.cpp TaxiStation/Driver.h
	g++ -c TaxiStation/Driver.cpp

Grid.o: TaxiStation/Grid.cpp TaxiStation/Grid.h TaxiStation/Map.h
	g++ -c TaxiStation/Grid.cpp

GridPoint.o: TaxiStation/GridPoint.cpp TaxiStation/GridPoint.h
	g++ -c TaxiStation/GridPoint.cpp

LuxuryCab.o: TaxiStation/LuxuryCab.cpp TaxiStation/LuxuryCab.h TaxiStation/Cab.h
	g++ -c TaxiStation/LuxuryCab.cpp

Passenger.o: TaxiStation/Passenger.cpp TaxiStation/Passenger.h
	g++ -c TaxiStation/Passenger.cpp

Point.o: TaxiStation/Point.cpp TaxiStation/Point.h
	g++ -c TaxiStation/Point.cpp

StandardCab.o: TaxiStation/StandardCab.cpp TaxiStation/StandardCab.h TaxiStation/Cab.h
	g++ -c TaxiStation/StandardCab.cpp

TaxiCenter.o: TaxiStation/TaxiCenter.cpp TaxiStation/TaxiCenter.h
	g++ -c TaxiStation/TaxiCenter.cpp

Trip.o: TaxiStation/Trip.cpp TaxiStation/Trip.h
	g++ -c TaxiStation/Trip.cpp

Clock.o: TaxiStation/Clock.cpp TaxiStation/Clock.h
	g++ -c TaxiStation/Clock.cpp

clean:
	rm -f *.o a.out client.out server.out
# to work.