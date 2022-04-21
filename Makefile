CC=g++
name = Assignment3_MTLKHU004.tar


driver.exe: compile
	$(CC) driver.o PGMimageProcessor.o  ConnectedComponent.o -o driver.exe

compile: driver.cpp ConnectedComponent.cpp PGMimageProcessor.cpp 
	$(CC) -c driver.cpp ConnectedComponent.cpp PGMimageProcessor.cpp

run:
	./driver.exe -s 5000 7500 -t 200 -p -w chess-thresh.PGM chess.PGM

unitTest: compileTest
	$(CC) unitTest.o PGMimageProcessor.o ConnectedComponent.o -o unitTest.exe

compileTest: unitTest.cpp 
	$(CC) -c unitTest.cpp PGMimageProcessor.cpp ConnectedComponent.cpp

runUnitTest:
	./unitTest.exe
	
clean:
	rm *.o driver.exe unitTest.exe

package:
	tar -c -f $(name) * .git
	gzip $(name)
