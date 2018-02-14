# Rune Bergh 16Hbitsec

Har brukt kodesjekk.sh til å sjekke filene med valgrind og clang-tidy. 
scriptet passer argumentet 2 til siste fil, og tester det med dette. 


program 1 har en minnelekasje jeg ikke har funnet enda dessverre. 


output er lagret i en egen fil, res.txt. 

kompilert oblig1.c med gcc -Wall -o oblig1 oblig1.c

kompilert oblig1.2.c med gcc -Wall -o oblig1.2.c -pthread

kompilert oblig1.2.c med gcc -Wall oblig1.3.c -o oblig1.3 -pthread
