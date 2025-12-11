compile:
	@echo "Compiling..."
	@g++ cell.cpp register.cpp table.cpp database.cpp main.cpp -o main
	@echo "Done"

run:
	@echo "Running..."
	@./main
	@echo "Done"


