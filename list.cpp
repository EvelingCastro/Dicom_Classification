#include <iostream>
#include <imebra/imebra.h>
#include <dirent.h>
#include <string>
#include <fstream>
#include <ncurses.h>

//using namespace std;

// Codes with information:
// StudyInstanceUID_0020_000D
// StudyID_0020_0010
// StudyDate_0008_0020
// StudyTime_0008_0030
// StudyDescription_0008_1030
// PatientSex_0010_0040
// PatientBirthDate_0010_0030
// PatientAge_0010_1010

int main(){/*
	std::wstring studies[3][6] = {
        //For PELVIS 0
        {L"PELVIS", L"Pelvis", L"pelvis", 0, 0, 0},
        //For TÓRAX 1
        {L"TÓRAX", L"TORAX", L"Tórax", L"Torax", L"tórax", L"torax"},
        //For CRÁNEO 2
        {L"CRÁNEO", L"CRANEO", L"Cráneo", L"Craneo", L"cráneo", L"craneo"}
    };*/

	std::ofstream outfile;
	outfile.open("list.csv");

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (".")) != NULL) {
  	/* print all the files and directories within directory */

		outfile << L"NAME;REGION;SEX;AGE" << std::endl;
		while ((ent = readdir (dir)) != NULL) {
			
			std::string str = ent->d_name;
			if(str.length() < 4)
				continue;
			std::string extension = str.substr(str.length() - 4);
			if(extension.compare(".dcm") == 0){
				//printf ("%s\n", ent->d_name);
				std::unique_ptr<imebra::DataSet> loadedDataSet(imebra::CodecFactory::load(ent->d_name));
				std::string patientInformation;
				try{
					for(int i = 0;i < 0xFFFEE0DD;i=i+1){
						try{
							patientInformation = loadedDataSet->getString(imebra::TagId((i>>16)&65535, i&65535),0);
							std::cout << i << std::endl;
							outfile << i << "->" << patientInformation << ";" << std::endl;
						}catch(imebra::MissingTagError e){
						}catch(imebra::MissingGroupError e){
						}catch(imebra::MissingBufferError e){
						}
					}
					//std::wcout << "Hello " << (std::wcscmp(patientInformation.data(),L"Tórax")) << std::endl;
					std::cout << patientInformation << std::endl;
				}catch(imebra::MissingTagError e){
				}catch(imebra::CodecWrongFormatError e){
				}
			}
		}
		closedir (dir);
	} else {
  	/* could not open directory */
		perror ("");
		return EXIT_FAILURE;
	}	
	outfile.close();
}