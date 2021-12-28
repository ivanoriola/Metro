#ifndef DEFINES_HPP
# define DEFINES_HPP

# define MINS_PER_STOP	2
# define NUM_OF_LINES	12
# define MAX			1000 

# define TO_STR(x)		std::to_string(x)
# define FILE_NAME(x)	"metro_lines/line" + TO_STR(x) + ".txt"

# define RESET		"\033[0m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"

# define LINE_0_COLOR	"\033[37m"
# define LINE_1_COLOR	"\033[94m"
# define LINE_2_COLOR	RED
# define LINE_3_COLOR	YELLOW
# define LINE_4_COLOR	"\033[38;2;139;69;19m"
# define LINE_5_COLOR	"\033[38;2;50;205;50m"
# define LINE_6_COLOR	"\033[37m"
# define LINE_7_COLOR	"\033[38;2;255;140;0m"
# define LINE_8_COLOR	"\033[38;2;255;105;180m"
# define LINE_9_COLOR	"\033[38;2;128;0;128m"
# define LINE_10_COLOR	"\033[38;2;0;0;205m"
# define LINE_11_COLOR	GREEN

#endif