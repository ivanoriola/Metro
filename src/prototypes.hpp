#ifndef PROTOTYPES_HPP
# define PROTOTYPES_HPP

// console_tools.cpp
void			clear_screen();
void			print(std::string text);
std::string		input(std::string text);

// data_print.cpp
void			print_metro_logo(void);
void			select_line_to_print(void);
void			print_metro_line(short line);
void			print_station(short line, short station);
void 			print_final_data(void);

// initial_processes.cpp
void			load_stations(void);
void			get_user_stations(void);
bool			is_valid_station(line_station *input_station);

// solving_processes.cpp
void			solve(void);
void			solve_same_station(void);
void			solve_same_line (line_station station1, line_station station2);
void			solve_different_line (void);

// solving_tools.cpp
short			get_commom_line(line_station start_station, line_station end_station);
short			get_commom_transfer(short line1, short line2);
short			get_position_in_line(line_station ext_station, short line);
void			get_lines_transfers(void);
void			count_same_line(line_station station1, line_station station2);
void			transfers_between_lines(short line1, short line2, short candidate);
bool			is_in_destiny(short line);
line_station	closest_transfer(line_station station, short line_from, short line_to);

#endif