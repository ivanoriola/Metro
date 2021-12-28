#include "metro.hpp"

void print_metro_logo(void)
{
	print("\n");
	print("\t" RED "╔═══════════════════════════════════════════════════╗\n");
	print("\t║                                                   ║\n");
	print("\t║  " BLUE "██     ██ ████████ ████████ ████████   ███████   " RED "║\n");
	print("\t║  " BLUE "███   ███ ██          ██    ██     ██ ██     ██  " RED "║\n");
	print("\t║  " BLUE "██ ███ ██ ██████      ██    ████████  ██     ██  " RED "║\n");
	print("\t║  " BLUE "██     ██ ██          ██    ██   ██   ██     ██  " RED "║\n");
	print("\t║  " BLUE "██     ██ ████████    ██    ██     ██  ███████   " RED "║\n");
	print("\t║                                                   ║\n");
	print("\t╚══════════════  " RESET "Cálculo de trayectos" RED "  ═════════════╝\n" RESET);
	print("\n");
	print("\n");
}

void	select_line_to_print(void)
{
	short	line;

	print(RESET "Selecciona una línea: \n");
	for (short line_number = 0; line_number < NUM_OF_LINES; line_number++)
		print(color[line_number] + "[" + TO_STR(line_number) + "] ");
	print("\n");

	do
	{
		line = stoi(input(RESET ""));
	} while (line < 0 || line >= NUM_OF_LINES);
	
	print_metro_line(line);
}

void print_metro_line(short line)
{
	print("\n");
	if (line == 0)
		print(color[line] + "\t Ramal Opera - Ppe. Pio\n");	
	else
		print(color[line] + "\t Linea " + TO_STR(line) + "\n");
	print("\t════════════════════════\n" RESET);
	for (short station = 0; station < metro_lines[line].stations.size(); station++)
	{
		print("\t" + metro_lines[line].stations[station].name);
		for (int i = 0; i < (metro_lines[line].stations[station].lines.size()); i++)
		{
			if (metro_lines[line].stations[station].lines[i] != line)
				print(color[metro_lines[line].stations[station].lines[i]] + " L"
					+ TO_STR(metro_lines[line].stations[station].lines[i]) + RESET);
			else if (metro_lines[line].stations[station].lines.size() != 1)
				print(RESET " ->");
		}
		print("\n");
	}
	print(color[line] + "\t════════════════════════\n\n\n" RESET);

	print("\n");
	print("Presione ENTER para continuar ... \n");
	std::cin.get();
}

void print_station(short line, short station)
{
	print(RESET "\t├ " + color[line] + "L" + TO_STR(line) + "" RESET " - ");
	print(metro_lines[line].stations[station].name + "\n");
}

void print_final_data(void)
{
	int		minutes;
	short	transfer_counter;


	if (!candidates_list.empty())
	{
		stop_counter = minimal_stops;
		transfer_counter = candidates_list[final_candidate].transfer_list.size() - 1;
		stop_counter -= transfer_counter;
	}
	else
		transfer_counter = 0;

	minutes = (stop_counter + transfer_counter) * MINS_PER_STOP;
	
	print("\n");
	if (stop_counter != 1)
		print(RESET "Son " YELLOW + TO_STR(stop_counter) + RESET " paradas ");
	else
		print(RESET "Es " YELLOW + TO_STR(stop_counter) + RESET " parada ");

	if (transfer_counter > 1)
		print("con " YELLOW + TO_STR(transfer_counter) + RESET " transbordos.\n");
	else if (transfer_counter == 1)
		print("con " YELLOW + TO_STR(transfer_counter) + RESET " transbordo.\n");
	else
		print("sin transbordos.\n");

	print(RESET "Duración (aproximada) del trayecto: " YELLOW + TO_STR(minutes) + RESET " mins.\n");
	print(RESET "Tiempo de búsqueda: " YELLOW + TO_STR(time_out.count() - time_in.count()) + RESET " ms.\n\n");
	print("\n");
	print("Presione ENTER para continuar ... \n");
	std::cin.get();
}