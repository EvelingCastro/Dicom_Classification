#include <iostream>
#include <imebra/imebra.h>
#include <dirent.h>
#include <string>
#include <fstream>
#include <ncurses.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <chrono>

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
char a='|';
string zones[100000];
int limit = 0;
static volatile sig_atomic_t interrupted = 0;

void term(int signum){
    interrupted = 1;
}

bool isHere(string name){
	for(int i=0;i<limit;i++)
		if(zones[i].compare(name) == 0)
			return true;
	return false;
}

void put(string name){
	zones[limit++] = name;
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

void wait(){
	if(a == '|'){
		a = '\\';
	}else if(a == '\\'){
		a = '-';
	}else if(a == '-'){
		a = '/';
	}else if(a == '/'){
		a = '|';
	}
	mvprintw(row/2-5,(col-3)/2," %c ",a);
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
	for(int i=t+1;i<(width-7);i++){
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
	attron(COLOR_PAIR(1));
	addch('[');
	attron(COLOR_PAIR(2));
	for(int i=first;i<(width*percent/100+first);i++){
		move(row/2-1,i);
		addch(' ');
	}
	move(row/2-1,width+first);
	attron(COLOR_PAIR(1));
	addch(']');
	attron(COLOR_PAIR(2));
}


int main(){
	auto start = chrono::high_resolution_clock::now();
	signal(SIGINT, term);

	std::ofstream outfile;
	outfile.open("list.csv");

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (".")) != NULL) {
  	/* print all the files and directories within directory */

		initscr();
		//raw();
		noecho();
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		init_pair(2, COLOR_BLACK, COLOR_WHITE);
		init_pair(3, COLOR_WHITE, COLOR_RED);
		curs_set(0);
		getmaxyx(stdscr,row,col);

		width = col*9/10;
		first = (col - width)/2;

		attron(COLOR_PAIR(2));
		percent = 0;
		
		outfile << "NAME;REGION;SEX;AGE" << std::endl;
		int total = 0;
		int count = 0;
		while ((ent = readdir (dir)) != NULL){
			writeTitle("Counting images");
			wait();
			refresh();
			std::string str = ent->d_name;
			if(str.length() < 4)
				continue;
			std::string extension = str.substr(str.length() - 4);
			if(extension.compare(".dcm") == 0){
				total++;
			}
		}
		clearLine(row/2-5);
		dir = opendir (".");
		
		while ((ent = readdir (dir)) != NULL) {
			wait();
			writeTitle("Analyzing images");
			refresh();
			std::string str = ent->d_name;
			writeStatus(str);
			refresh();
			if(str.length() < 4)
				continue;
			std::string extension = str.substr(str.length() - 4);
			if(extension.compare(".dcm") == 0){
				count++;
				//printf ("%s\n", ent->d_name);
				std::unique_ptr<imebra::DataSet> loadedDataSet(imebra::CodecFactory::load(ent->d_name));
				std::string patientInformation;
				try{
					patientInformation = loadedDataSet->getString(imebra::TagId(imebra::tagId_t::StudyDescription_0008_1030), 0);
					if(patientInformation.empty())
						patientInformation = loadedDataSet->getString(imebra::TagId(imebra::tagId_t::SeriesDescription_0008_103E), 0);
					outfile << patientInformation.c_str() << ";" << endl;
					
					if(!isHere(patientInformation)){
						put(patientInformation);
					}

				}catch(imebra::MissingTagError e){
					patientInformation = loadedDataSet->getString(imebra::TagId(imebra::tagId_t::SeriesDescription_0008_103E), 0);
					outfile << patientInformation.c_str() << ";" << endl;
				}catch(imebra::MissingGroupError e){
				}catch(imebra::CodecWrongFormatError e){
				}catch(imebra::StreamEOFError e){
				}
			}
			percent = count*100/total;
			if (interrupted){
		        clear();
		        attron(COLOR_PAIR(3));
				auto stop = chrono::high_resolution_clock::now();
		        mvprintw((row-1)/2,(col-26)/2," A SIGNAL WAS ENCOUNTERED ");
				mvprintw((row-1)/2+2,(col-18)/2," Time: %d ms", chrono::duration_cast<chrono::milliseconds>(stop-start).count());
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
		clear();
		percent = 0;
		total = limit;
		count = 0;
		while(count < limit){
			count++;
			wait();
			writeTitle("Creating folders");
			refresh();
			stringstream s;
			s << "./" << zones[count];
			string path = s.str();
			int status;
			writeStatus(path);
			refresh();
			sleep(1);
			char *temp = new char [path.length()+1];
			strcpy(temp, path.c_str());
			status = mkdir(temp, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

			percent = count*100/total;
			if (interrupted){
		        clear();
		        attron(COLOR_PAIR(3));
				auto stop = chrono::high_resolution_clock::now();
		        mvprintw((row-1)/2,(col-26)/2," A SIGNAL WAS ENCOUNTERED ");
				mvprintw((row-1)/2+2,(col-18)/2," Time: %d ms", chrono::duration_cast<chrono::milliseconds>(stop-start).count());
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
		clear();
		percent = 0;
		while ((ent = readdir (dir)) != NULL){
			writeTitle("Counting images");
			wait();
			refresh();
			std::string str = ent->d_name;
			if(str.length() < 4)
				continue;
			std::string extension = str.substr(str.length() - 4);
			if(extension.compare(".dcm") == 0){
				total++;
			}
		}
		count = 0;
		dir = opendir (".");
		
		while ((ent = readdir (dir)) != NULL){
			wait();
			writeTitle("Moving images");
			refresh();
			std::string str = ent->d_name;
			writeStatus(str);
			refresh();
			if(str.length() < 4)
				continue;
			std::string extension = str.substr(str.length() - 4);
			if(extension.compare(".dcm") == 0){
				count++;
				//printf ("%s\n", ent->d_name);
				std::unique_ptr<imebra::DataSet> loadedDataSet(imebra::CodecFactory::load(ent->d_name));
				std::string patientInformation;
				try{
					patientInformation = loadedDataSet->getString(imebra::TagId(imebra::tagId_t::StudyDescription_0008_1030), 0);
					if(patientInformation.empty())
						patientInformation = loadedDataSet->getString(imebra::TagId(imebra::tagId_t::SeriesDescription_0008_103E), 0);
					outfile << patientInformation.c_str() << ";" << endl;


					char *temp = new char [str.length()+1];
					strcpy(temp, str.c_str());
					char *temp1 = new char [patientInformation.length()+1];
					strcpy(temp1, patientInformation.c_str());
					stringstream s;
					s << temp1 << "/" << str;
					string path = s.str();
					char *temp2 = new char [path.length()+1];
					strcpy(temp2, path.c_str());
					rename( temp, temp2 );
					
					if(!isHere(patientInformation)){
						put(patientInformation);
					}

				}catch(imebra::MissingTagError e){
					patientInformation = loadedDataSet->getString(imebra::TagId(imebra::tagId_t::SeriesDescription_0008_103E), 0);
					outfile << patientInformation.c_str() << ";" << endl;
				}catch(imebra::MissingGroupError e){
				}catch(imebra::CodecWrongFormatError e){
				}catch(imebra::StreamEOFError e){
				}
			}
			percent = count*100/total;
			if(percent > 100)
				percent = 100;
			if (interrupted){
		        clear();
		        attron(COLOR_PAIR(3));
				auto stop = chrono::high_resolution_clock::now();
		        mvprintw((row-1)/2,(col-26)/2," A SIGNAL WAS ENCOUNTERED ");
				mvprintw((row-1)/2+2,(col-18)/2," Time: %d ms", chrono::duration_cast<chrono::milliseconds>(stop-start).count());
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
		clear();
        attron(COLOR_PAIR(1));
        mvprintw((row-1)/2,(col-19)/2," Finished process. ");
        mvprintw((row-1)/2+1,(col-16)/2," Press any key. ");
		auto stop = chrono::high_resolution_clock::now();
		mvprintw((row-1)/2+2,(col-18)/2," Time: %d ms", chrono::duration_cast<chrono::milliseconds>(stop-start).count());
        sleep(2);
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