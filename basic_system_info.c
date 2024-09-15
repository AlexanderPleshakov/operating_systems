#include <stdio.h> // for work with files and console
#include <unistd.h> // for getting system info
#include <sys/utsname.h> // for getting os and machine information
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>


void print_user_and_computer() {
	printw("\nComputer name and user name (Task 1)\n");
        char computer_name[65];
        if (gethostname(computer_name, sizeof(computer_name)) == 0) {
                printw("Computer name: %s\n", computer_name);
        } else {
                printw("Computer name printing error");
        }

        char user_name[257];
        if (getlogin_r(user_name, sizeof(user_name)) == 0) {
                printw("User name: %s\n", user_name);
        } else {
                printw("User name printin error");
        }
}

void print_os_version() {
	printw("\n OS Version (Task 2)\n");
	struct utsname system_info;
	if (uname(&system_info) == 0) {
		printw("OS core version: %s\n", system_info.release);
		printw("OS version: %s\n", system_info.version);
		printw("OS name: %s\n", system_info.sysname);
	} else {
		printw("OS versiono printing error");
	}
}

void print_system_metrics() {
	printw("\nSystem metrics (Task 3)\n");
	printw("Processors count: %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
	printw("RAM: %ld Mb\n", (sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE)) / (1024 * 1024));
	printw("Max hostname lenght: %ld\n", sysconf(_SC_HOST_NAME_MAX));
	printw("Max login name lenght: %ld\n", sysconf(_SC_LOGIN_NAME_MAX));
}

void print_time_functions() {
	printw("\n Time functions (Task 4)\n");
	time_t current_time = time(NULL);
	struct tm *local_time = localtime(&current_time);
	printw("Local time: %s", asctime(local_time));

	struct tm *gmt_time = gmtime(&current_time);
	printw("UTC time: %s", asctime(gmt_time));
}

void print_additional_api_functions() {
	printw("\nAdditional information (Task 5)\n");
	char *home_dir = getenv("HOME");
	
	// Home dir
	if (home_dir) {
		printw("Home catalog: %s\n", home_dir);
	} else {
		printw("Home is invalid");
	}

	// CPU frequency

	FILE *file = fopen("/proc/cpuinfo", "r");

	if (file == NULL) {
		perror("Ошибка при открытии файла");
	}

	char line[256];
	while (fgets(line, sizeof(line), file)) {
		if (strstr(line, "cpu MHz") != NULL) {
        	printw("%s", line);
        	break;
		}
	}

	fclose(file);

	// Other
	
	printw("User id: %d\n", getuid());
	printw("Effective user id: %d\n", geteuid());
}

int main() {
	initscr();
	start_color();

	if (has_colors() == FALSE) {
		endwin();
		printw("colors don't support");
		return 1;
	}

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);

	attron(COLOR_PAIR(1));
	print_user_and_computer();
	attroff(COLOR_PAIR(1));
	refresh();
	
	attron(COLOR_PAIR(2));
	print_os_version();
	attroff(COLOR_PAIR(1));
	refresh();

	attron(COLOR_PAIR(3));
	print_system_metrics();
	attroff(COLOR_PAIR(3));
        refresh();

	print_time_functions();
	print_additional_api_functions();

	getch();

	endwin();

	return 0;
}
