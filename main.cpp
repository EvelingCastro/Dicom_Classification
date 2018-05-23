#include <iostream>
#include <imebra/imebra.h>
#include <dirent.h>
#include <string>
#include <fstream>
#include <ncurses.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

using namespace std;

// Codes with information:
// StudyInstanceUID_0020_000D
// StudyID_0020_0010
// StudyDate_0008_0020
// StudyTime_0008_0030
// StudyDescription_0008_1030
// PatientSex_0010_0040
// PatientBirthDate_0010_0030
// PatientAge_0010_1010

int row,col,width,first,percent;
static volatile sig_atomic_t interrupted = 0;

void term(int signum){
    interrupted = 1;
}

void clearLine(int l){
	attron(COLOR_PAIR(1));
	for(int i=0;i<col;i++){
		move(l,i);
		addch(' ');
	}
}

void writeTitle(string title){
	const char *temp = title.c_str();
	mvprintw(row/2-7,(col-title.length())/2," %s ",temp);
}

void writeStatus(string name){
	char *temp = new char [name.length()+1];
	strcpy(temp, name.c_str());
	char other[width];
	int t = 1;
	for(int i=0;(i<(width-7)) && temp[i];i++){
		other[i] = temp[i];
		t = i;
	}
	for(int i=t;i<(width-7);i++){
		other[i] = ' ';
	}
	bool cent = percent/100 != 0;
	other[width-7] = ' ';
	other[width-6] = ' ';
	other[width-5] = ' ';
	other[width-4] = (cent)?'1':' ';
	other[width-3] = (cent)?'0':((percent%100)/10 + '0' == '0')?' ':(percent%100)/10 + '0';
	other[width-2] = percent%10 + '0';
	other[width-1] = '%';
	other[width] = '\0';
	attron(COLOR_PAIR(1));

	clearLine(row/2-3);
	mvprintw(row/2-3,first,"%s",other);
	attron(COLOR_PAIR(2));
	move(row/2-1,first-1);
	addch('[');
	for(int i=first;i<(width*percent/100+first);i++){
		move(row/2-1,i);
		addch(' ');
	}
	move(row/2-1,width+first);
	addch(']');
}


int main(){
	signal(SIGINT, term);

	std::ofstream outfile;
	outfile.open("list.csv");

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (".")) != NULL) {
  	/* print all the files and directories within directory */

		unsigned int mili = 1; 
		char mesg[]="Just a string";
		initscr();
		//raw();
		noecho();
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		init_pair(2, COLOR_BLACK, COLOR_WHITE);
		curs_set(0);
		getmaxyx(stdscr,row,col);

		width = col*9/10;
		first = (col - width)/2;

		attron(COLOR_PAIR(2));
		//mvprintw(1,(col-strlen(mesg))/2,"%s",mesg);
		percent = 0;
		
		outfile << "NAME;REGION;SEX;AGE" << std::endl;
		int total = 0;
		int count = 0;
		while ((ent = readdir (dir)) != NULL){
			writeTitle("Counting images");
			refresh();
			total++;
		}
		dir = opendir (".");
		//mvprintw(0,0,"%i",total);
		
		while ((ent = readdir (dir)) != NULL) {
			count++;
			writeTitle("Analizing all images");
			refresh();
			std::string str = ent->d_name;
			if(str.length() < 4)
				continue;
			std::string extension = str.substr(str.length() - 4);
			if(extension.compare(".dcm") == 0){
				//printf ("%s\n", ent->d_name);
				std::unique_ptr<imebra::DataSet> loadedDataSet(imebra::CodecFactory::load(ent->d_name));
				std::string patientInformation;
				try{
					patientInformation = loadedDataSet->getString(imebra::TagId(imebra::tagId_t::StudyDescription_0008_1030), 0);
					//std::wcout << "Hello " << (std::wcscmp(patientInformation.data(),L"Tórax")) << std::endl;
					outfile << patientInformation << ";";
					//std::cout << patientInformation << std::endl;
					writeStatus(patientInformation);
					refresh();
					
				}catch(imebra::MissingTagError e){
				}catch(imebra::CodecWrongFormatError e){
				}catch(imebra::StreamEOFError e){
				}
			}
			percent = count*100/total;
			if (interrupted){
		        clear();
		        mvprintw((row-1)/2,(col-24)/2,"A SIGNAL WAS ENCOUNTERED");
		        refresh();
		        sleep(1);
				closedir (dir);
				clrtoeol();
				getch();
		        endwin();
				outfile.close();
		        exit(0);
		    }
		}
		closedir (dir);
		clrtoeol();
		getch();
		endwin();
	} else {
  	/* could not open directory */
		perror ("");
		return EXIT_FAILURE;
	}	
	outfile.close();
}