#include "metro.hpp"

void solve(void)
{
	time_in = std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch());

	stop_counter = -1;
	candidates_list.clear();
	commom_line = get_commom_line(start_station, end_station);

	if (start_station.name == end_station.name)
		solve_same_station();
	else if (commom_line != -1)
		solve_same_line(start_station, end_station);
	else
		solve_different_line();

	time_out = std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch());
}

void	solve_same_station(void)
{
	print(RESET "\n");
	print("\n\t┌─");
	print("\n\t├ ");
	for (short line = 0; line < commom_lines.size(); line++)
		print(color[commom_lines[line]] + " L" + TO_STR(commom_lines[line]) + "");
	print(RESET " - " + start_station.name);
	print("\n\t└─");
	stop_counter++;

	print("\n");
}

void	solve_same_line(line_station station1, line_station station2)
{
	short station1_position;
	short station2_position;

	station1_position = get_position_in_line(station1, commom_line);
	station2_position = get_position_in_line(station2, commom_line);

	if (station1_position < station2_position)
	{
		print("\n");
		print(RESET "\t┌─\n");
		for (short station = station1_position; station <= station2_position; station++)
		{
			print_station(commom_line, station);
			stop_counter++;
		}
		print(RESET "\t└─\n");
	}
	else
	{
		print("\n");
		print(RESET "\t┌─\n");
		for (short station = station1_position; station >= station2_position; station--)
		{
			print_station(commom_line, station);
			stop_counter++;
		}
		print(RESET "\t└─\n");
	}
}

void solve_different_line(void)
{
	line_station	prev_station;
	line_station	next_station;
	short			line1;
	short			line2;

	get_lines_transfers();

	candidate_counter = 0;
	for (short station1_line = 0; station1_line < start_station.lines.size(); station1_line++)
	{
		line1 = start_station.lines[station1_line];
		for (short station2_line = 0; station2_line < end_station.lines.size(); station2_line++)
		{
			candidate		new_candidate;
			line2 = end_station.lines[station2_line];
			stop_counter = -1;
			candidates_list.push_back(new_candidate);
			transfers_between_lines(line1, line2, candidate_counter);
			candidate_counter++;
		}
	}

	minimal_stops = MAX;
	minimal_transfers = MAX;
	for (short candidate = 0; candidate < candidates_list.size(); candidate++)
	{
		stop_counter = -1;
		next_station = start_station;

		for (short transfer = 0; transfer < candidates_list[candidate].transfer_list.size() - 1; transfer++)
		{
			prev_station = next_station;
			next_station = 
				closest_transfer(prev_station,
					candidates_list[candidate].transfer_list[transfer],
					candidates_list[candidate].transfer_list[transfer + 1]);
			commom_line = get_commom_line(prev_station, next_station);
			count_same_line(prev_station, next_station);
		}

		prev_station = next_station;
		next_station = end_station;
		commom_line = get_commom_line(prev_station, next_station);
		count_same_line(prev_station, next_station);

		if (stop_counter <= minimal_stops)
		{
			minimal_stops = stop_counter;
			if (candidates_list[candidate].transfer_list.size() < minimal_transfers)
			{
				minimal_transfers = candidates_list[candidate].transfer_list.size();
				final_candidate = candidate;
			}
		}
	}

	stop_counter = -1;
	next_station = start_station;

	for (short transfer = 0; transfer < candidates_list[final_candidate].transfer_list.size() - 1; transfer++)
	{
		prev_station = next_station;
		next_station = 
			closest_transfer(prev_station,
				candidates_list[final_candidate].transfer_list[transfer],
				candidates_list[final_candidate].transfer_list[transfer + 1]);
		commom_line = get_commom_line(prev_station, next_station);
		solve_same_line(prev_station, next_station);
	}

	prev_station = next_station;
	next_station = end_station;
	commom_line = get_commom_line(prev_station, next_station);
	solve_same_line(prev_station, next_station);
}