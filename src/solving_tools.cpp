#include "metro.hpp"

short	get_commom_line(line_station station_1, line_station station_2)
{
	short	distance = 0;
	short	minimal_distance = MAX;
	short	shortest_commom_line = -1;
	short	position_1;
	short	position_2;

	commom_lines.clear();

	for (short station_1_lines = 0; station_1_lines < station_1.lines.size(); station_1_lines++)
	{
		for (short station_2_lines = 0; station_2_lines < station_2.lines.size(); station_2_lines++)
		{
			if (station_1.lines[station_1_lines] == station_2.lines[station_2_lines])
				commom_lines.push_back(station_1.lines[station_1_lines]);
		}
	}
	for (short line = 0; line < commom_lines.size(); line++)
	{
		position_1 = get_position_in_line(station_1, commom_lines[line]);
		position_2 = get_position_in_line(station_2, commom_lines[line]);
		distance = abs(position_2 - position_1);
		if (distance < minimal_distance)
		{
			minimal_distance = distance;
			shortest_commom_line = commom_lines[line];
		}
	}
	return shortest_commom_line;
}

short get_commom_transfer(short line1, short line2)
{
	short	target_line1;
	short	target_line2;

	for (short line1_transfer = 0; line1_transfer < metro_lines[line1].transfers.size(); line1_transfer++)
	{
		target_line1 = metro_lines[line1].transfers[line1_transfer].target_line;
		if (target_line1 == line2)
			return target_line1;
	}
	for (short line2_transfer = 0; line2_transfer < metro_lines[line1].transfers.size(); line2_transfer++)
	{
		target_line2 = metro_lines[line2].transfers[line2_transfer].target_line;
		if (target_line2 == line1)
			return target_line2;
	}
	for (short line2_transfer = 0; line2_transfer < metro_lines[line2].transfers.size(); line2_transfer++)
	{
		for (short line1_transfer = 0; line1_transfer < metro_lines[line1].transfers.size(); line1_transfer++)
		{
			target_line1 = metro_lines[line1].transfers[line1_transfer].target_line;
			target_line2 = metro_lines[line2].transfers[line2_transfer].target_line;
			if (target_line1 == target_line2)
				return target_line1;
		}
	}
	return -1;
}

short get_position_in_line(line_station ext_station, short line)
{
	for (short station = 0; station < metro_lines[line].stations.size(); station++)
	{
		if (metro_lines[line].stations[station].name == ext_station.name)
			return station;
	}
	return -1;
}

void get_lines_transfers(void)
{
	line_transfer new_transfer;
	for (short line = 0; line < NUM_OF_LINES; line++)
	{
		for(short station = 0; station< metro_lines[line].stations.size(); station++)
		{
			for (short station_line = 0; station_line <  metro_lines[line].stations[station].lines.size(); station_line++)
			{
				if (metro_lines[line].stations[station].lines[station_line] != line)
				{
					new_transfer.position = station;
					new_transfer.target_line = metro_lines[line].stations[station].lines[station_line];
					metro_lines[line].transfers.push_back(new_transfer);
				}
			}
		}
	}
}

void	count_same_line(line_station station1, line_station station2)
{
	short station1_position;
	short station2_position;

	station1_position = get_position_in_line(station1, commom_line);
	station2_position = get_position_in_line(station2, commom_line);

	if (station1_position < station2_position)
	{
		for (short station = station1_position; station <= station2_position; station++)
			stop_counter++;
	}
	else
	{
		for (short station = station1_position; station >= station2_position; station--)
			stop_counter++;
	}
}

void	transfers_between_lines(short line1, short line2, short candidate)
{
	short	commom_transfer;

	commom_transfer = get_commom_transfer(line1, line2);
	if (commom_transfer != -1)
	{
		candidates_list[candidate].transfer_list.push_back(line1);
		candidates_list[candidate].transfer_list.push_back(commom_transfer);
		if (!is_in_destiny(commom_transfer))
			candidates_list[candidate].transfer_list.push_back(line2);
	}
}

bool	is_in_destiny(short line)
{
	for (short destiny_line = 0; destiny_line < end_station.lines.size(); destiny_line++)
	{
		if (line == end_station.lines[destiny_line])
			return true;
	}
	return false;
}

line_station	closest_transfer(line_station station, short line_from, short line_to)
{
	short	distance = 0;
	short	minimal_distance = MAX;
	short	closest_transfer;

	for (short transfer = 0; transfer < metro_lines[line_from].transfers.size(); transfer++)
	{
		if (metro_lines[line_from].transfers[transfer].target_line == line_to)
		{
			distance = abs(metro_lines[line_from].transfers[transfer].position - get_position_in_line(station, line_from));
			if (distance < minimal_distance)
			{
				minimal_distance = distance;
				closest_transfer =  metro_lines[line_from].transfers[transfer].position;
			}
		}
	}
	return metro_lines[line_from].stations[closest_transfer];
}