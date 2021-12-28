#include "metro.hpp"

void load_stations(void)
{
	std::string file_name;
	std::string input_line;
	short divider_position;
	std::string station_lines_string;
	short station_lines_length;
	char *station_lines_char;
	char *token;

	for (short line = 0; line < NUM_OF_LINES; line++)
	{
		file_name = FILE_NAME(line);
		std::ifstream file_read(file_name.c_str());
		metro_line new_line;

		while (getline(file_read, input_line))
		{
			line_station new_station;

			divider_position = input_line.find('#');
			new_station.name = input_line.substr(0, divider_position);
			station_lines_length = input_line.length() - new_station.name.length() - 1;
			station_lines_string = input_line.substr(divider_position + 1, station_lines_length);

			station_lines_char = &(station_lines_string.at(0));
			token = strtok(station_lines_char, ",");
			while (token)
			{
				new_station.lines.push_back(atoi(token));
				token = strtok(NULL, ",");
			}
			new_line.line_number = line;
			new_line.stations.push_back(new_station);
		}
		metro_lines[line] = new_line;
	}
}

void get_user_stations(void)
{
	do
	{
		start_station.name = input(RESET "Estación de ORIGEN: ");
	} while (!is_valid_station(&start_station));

	do
	{
		end_station.name = input(RESET "Estación de DESTINO: ");
	} while (!is_valid_station(&end_station));
}

bool is_valid_station(line_station *input_station)
{
	for (short line = 0; line < NUM_OF_LINES; line++)
	{
		for (short station = 0; station < metro_lines[line].stations.size(); station++)
		{
			if (!strcasecmp(input_station->name.c_str(), metro_lines[line].stations[station].name.c_str()))
			{
				input_station->lines = metro_lines[line].stations[station].lines;
				input_station->name = metro_lines[line].stations[station].name;
				print(GREEN "✓ " RESET " [ " + input_station->name + RESET " ] ");
				for (int i = 0; i < (metro_lines[line].stations[station].lines.size()); i++)
				{
					print(color[metro_lines[line].stations[station].lines[i]] + " L"
						+ TO_STR(metro_lines[line].stations[station].lines[i]) + RESET);
				}
				print("\n\n");
				return true;
			}
		}
	}
	print(RED "✘" RESET "  \"" + input_station->name + RESET "\" no se encuentra.\n\n");
	return false;
}