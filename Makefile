compile:
	@echo "Compiling..."
	@g++ src/cell.cpp src/register.cpp src/table.cpp src/datafile_manager.cpp src/database.cpp src/main.cpp -o main
	@echo "Done"

run:
	@echo "Running..."
	@./main
	@echo "Done"


