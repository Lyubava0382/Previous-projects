main: main.o Player.o Heal.o Box.o Teleport.o Smonster.o Mmonster.o Lmonster.o Cellule.o CelluleView.o Field.o FieldView.o Game.o
	g++ main.o Player.o Heal.o Box.o Teleport.o Smonster.o Mmonster.o Lmonster.o Cellule.o CelluleView.o Field.o FieldView.o Game.o -o main
main.o: main.cpp
	g++ -c main.cpp
Player.o: Player.cpp
	g++ -c Player.cpp
Heal.o: Heal.cpp
	g++ -c Heal.cpp
Box.o: Box.cpp
	g++ -c Box.cpp
Teleport.o: Teleport.cpp
	g++ -c Teleport.cpp
Smonster.o: Smonster.cpp
	g++ -c Smonster.cpp
Mmonster.o: Mmonster.cpp
	g++ -c Mmonster.cpp
Lmonster.o: Lmonster.cpp
	g++ -c Lmonster.cpp
Cellule.o: Cellule.cpp
	g++ -c Cellule.cpp
CelluleView.o: CelluleView.cpp
	g++ -c CelluleView.cpp
Field.o: Field.cpp
	g++ -c Field.cpp
FieldView.o: FieldView.cpp
	g++ -c FieldView.cpp
Game.o: Game.cpp
	g++ -c Game.cpp
clean:
	rm *.o main
