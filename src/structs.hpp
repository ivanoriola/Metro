#ifndef STRUCTS_HPP
# define STRUCTS_HPP

typedef struct{
	std::vector<short>	transfer_list;
}	candidate;

typedef struct{
	short	target_line;
	short	position;
}	line_transfer;

typedef struct{
	std::string			name;
	std::vector<short>	lines;
}	line_station;

typedef struct{
	short						line_number;
	std::vector<line_station>	stations;
	std::vector<line_transfer>	transfers;
}	metro_line;

#endif