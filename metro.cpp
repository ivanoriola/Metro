#include "metro.hpp"

std::string					color[NUM_OF_LINES];
metro_line					metro_lines[NUM_OF_LINES];
line_station				start_station;
line_station				end_station;
std::vector<short>			commom_lines;
short						commom_line;
short						start_line;
short						end_line;
short						next_line;
short						stop_counter;
short						candidate_counter;
std::vector<candidate>		candidates_list;
short						final_candidate;
short						minimal_stops;
short						minimal_transfers;
std::chrono::milliseconds	time_out;
std::chrono::milliseconds	time_in;

int main(void)
{
	#if defined _WIN32
		SetConsoleOutputCP(65001);
		SetConsoleCP(1252);
	#endif

	color[0] = LINE_0_COLOR;
	color[1] = LINE_1_COLOR;
	color[2] = LINE_2_COLOR;
	color[3] = LINE_3_COLOR;
	color[4] = LINE_4_COLOR;
	color[5] = LINE_5_COLOR;
	color[6] = LINE_6_COLOR;
	color[7] = LINE_7_COLOR;
	color[8] = LINE_8_COLOR;
	color[9] = LINE_9_COLOR;
	color[10] = LINE_10_COLOR;
	color[11] = LINE_11_COLOR;

	std::string choice;

	load_stations();
	while (true) {

		clear_screen();
		print_metro_logo();

		print("[" YELLOW "1" RESET "] Calcular un trayecto\n");
		print("[" YELLOW "2" RESET "] Mostrar una línea de metro\n");
		print("[" YELLOW "0" RESET "] Salir\n");

		choice = input("\nSelecciona una opción: ");

		if (choice.length() != 1)
		{
			print(RED "\n✘" RESET "  \"" + choice + "\" no es una opción valida.\n\n");
			print("\n");
			print("Presione ENTER para continuar ... \n");
			std::cin.get();
			continue;
		}

		switch (choice.at(0))
		{
			case '0':
				print("\n¡Adiós!\n\n");
				exit(0);
				break;
			case '1':
				print("\n");
				get_user_stations();
				solve();
				print_final_data();
				break;
			case '2':
				print("\n");
				select_line_to_print();
				break;
			default:
				print(RED "\n✘" RESET "  \"" + choice + "\" no es una opción valida.\n\n");
				print("\n");
				print("Presione ENTER para continuar ... \n");
				std::cin.get();
				break;
		}
	}

	return 0;
}