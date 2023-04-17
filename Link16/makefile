CC=g++
FLAG=-c

Link16:Link16.o interface.o HeaderWord.o InitialWord.o ExtendWord.o ContinueWord.o global.o STDPMsg.o AES.o
	${CC} Link16.o interface.o HeaderWord.o InitialWord.o ExtendWord.o ContinueWord.o global.o STDPMsg.o AES.o -o Link16 -fpermissive

Link16.o:Link16.cpp
	${CC} ${FLAG} Link16.cpp -o Link16.o -fpermissive

interface.o:interface.cpp
	${CC} ${FLAG} interface.cpp -o interface.o -fpermissive

HeaderWord.o:HeaderWord.cpp
	${CC} ${FLAG} HeaderWord.cpp -o HeaderWord.o -fpermissive

InitialWord.o:InitialWord.cpp
	${CC} ${FLAG} InitialWord.cpp -o InitialWord.o -fpermissive

ExtendWord.o:ExtendWord.cpp
	${CC} ${FLAG} ExtendWord.cpp -o ExtendWord.o -fpermissive

ContinueWord.o:ContinueWord.cpp
	${CC} ${FLAG} ContinueWord.cpp -o ContinueWord.o -fpermissive

global.o:global.cpp
	${CC} ${FLAG} global.cpp -o global.o -fpermissive

STDPMsg.o:STDPMsg.cpp
	${CC} ${FLAG} STDPMsg.cpp -o STDPMsg.o -fpermissive

AES.o:AES.cpp
	${CC} ${FLAG} AES.cpp -o AES.o -fpermissive

clean:
	rm -r Link16
	rm -r Link16.o interface.o HeaderWord.o InitialWord.o ExtendWord.o ContinueWord.o global.o STDPMsg.o AES.o
