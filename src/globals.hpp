#ifndef GLOBALS_HPP
# define GLOBALS_HPP

extern std::string					color[NUM_OF_LINES];
extern metro_line					metro_lines[NUM_OF_LINES];
extern line_station					start_station;
extern line_station					end_station;
extern std::vector<short>			commom_lines;
extern short						commom_line;
extern short						start_line;
extern short						end_line;
extern short						next_line;
extern short						stop_counter;
extern short						candidate_counter;
extern std::vector<candidate>		candidates_list;
extern short						final_candidate;
extern short						minimal_stops;
extern short						minimal_transfers;
extern std::chrono::milliseconds	time_out;
extern std::chrono::milliseconds	time_in;

#endif