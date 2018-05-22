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

	std::ios_base::sync_with_stdio(false);
	std::wcout.imbue(std::locale("en_US.UTF-8"));
	std::wofstream outfile("list.csv");
	outfile.imbue(std::locale("en_US.UTF-8"));

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
				std::wstring patientInformation;
				try{
					patientInformation = loadedDataSet->getUnicodeString(imebra::TagId(imebra::tagId_t::StudyInstanceUID_0020_000D), 0);
					//std::wcout << "Hello " << (std::wcscmp(patientInformation.data(),L"Tórax")) << std::endl;
					outfile << patientInformation << L";";
					std::wcout << patientInformation << std::endl;
				}catch(imebra::MissingTagError e){
					outfile << L"--;";
				}catch(imebra::CodecWrongFormatError e){
					outfile << L"--;";
				}

				try{
					patientInformation = loadedDataSet->getUnicodeString(imebra::TagId(imebra::tagId_t::StudyDescription_0008_1030), 0);
					outfile << patientInformation << L";";
				}catch(imebra::MissingTagError e){
					outfile << L"--;";
				}catch(imebra::CodecWrongFormatError e){
					outfile << L"--;";
				}

				try{
					patientInformation = loadedDataSet->getUnicodeString(imebra::TagId(imebra::tagId_t::PatientSex_0010_0040), 0);
					outfile << patientInformation << L";";
				}catch(imebra::MissingTagError e){
					outfile << L"--;";
				}catch(imebra::CodecWrongFormatError e){
					outfile << L"--;";
				}

				try{
					patientInformation = loadedDataSet->getUnicodeString(imebra::TagId(imebra::tagId_t::PatientAge_0010_1010), 0);
					outfile << patientInformation << std::endl;
				}catch(imebra::MissingTagError e){
					outfile << L"--" << std::endl;
				}catch(imebra::CodecWrongFormatError e){
					outfile << L"--;";
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