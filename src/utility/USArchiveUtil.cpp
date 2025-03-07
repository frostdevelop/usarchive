#include "usarchive.h"
#include "stringtools.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>
#include <vector>
#include <fstream>
#define PINFO "USArchive Command Line Utility"
#define PVERSION "Version: 1.0"

//class usarchive;

int main(int argc, char* argv[]){
	switch(argc){
	case 1:{
		std::cout << PINFO << '\n' << PVERSION;
		std::string command;
		std::vector<std::string> files;
		std::vector<usarchive> archives;
		std::string temp;
		int_fast16_t index = 0;
		while(true){
			std::cout << '\n'+(files.size() > 0 && index >= 0 ? files[index] : "")+'>';
			std::cin >> command;
			command = stringtools::toLower(command);
			//std::cout << "PROCESS...";
			if(command == "exit"){
				break;
			}else if(command == "size"){
		        std::cout << "ROGER Size";
			    std::cout << std::endl << files.size();
			}else{
				//std::istringstream csplit(command);
				//std::string verb;
				//csplit >> verb;
				if(command == "create"){
					std::cin >> temp;
					index = files.size();
			        std::cout << "ROGER Creating "+temp;
					files.push_back(temp);
					archives.push_back(usarchive());
				}else if(command == "open"){
				    std::cin >> temp;
			        std::cout << "ROGER Opening "+temp;
			        usarchive archive(temp);
			        switch(archive.error()){
		        	case 0:
			        	index = files.size();
			        	archives.push_back(archive);
			        	files.push_back(temp);
			        	break;
	        		default:
	        			std::cout << "\nERROR Opening " << archive.error();
	        			break;
			        }
				}else if(command == "list"){
			        std::cout << "ROGER Listing";
				    for(size_t i=0;i<files.size();i++){
				        std::cout << std::endl << i+1 << ". "+files[i];
				    }
				}else if(command == "switch"){
				    std::cin >> temp;
				    bool found = false;
			        std::cout << "ROGER Switching "+temp;
				    for(size_t i=0;i<files.size();i++){
				        if(files[i] == temp){
				            found = true;
				            index = i;
				            break;
				        }
				    }
				    if(found){
				        std::cout << "\nSUCCESS Switching";
				    }else{
				        std::cout << "\nERROR Switching: Archive not found: "+temp;
				    }
				}else if(command == "home"){
				    std::cout << "ROGER Home";
				    index = -1;
			    }else if(command == "info"){
			        std::cout << "ROGER Info";
			        std::cout << std::endl << PINFO << std::endl << PVERSION;
			    }else if(command == "version"){
			        std::cout << "ROGER Version";
			        std::cout << std::endl << PVERSION;
			    }else if(command == "help"){
			        std::cout << "ROGER Help";
			        std::cout << "\nUSArchive Command Line Utility Help\nSCOPE: GLOBAL\n  create [name]: Creates an archive of name [name].\n  open [file]: Opens the archive [file]\n  list: Lists available archives\n  switch [name]: Switches context to the archive [name]\n  home: Switches context to null\n  info: Echoes app info\n  version: Echoes app version\nSCOPE: ARCHIVE\n  write [file]: Writes archive to [file]\n  discard: Discards the archive\n  add [file]: Adds [file] to archive\n  dump: Lists files of the archive\n  extract [dir]: Extracts the archive to [dir]\n  extfile [file]: Extracts [file] from archive to working directory\n  extracth: Extracts archive to working directory";
			    }else if(files.size() > 0){
				    if(command == "write"){
				        std::string filename;
				        std::cin >> filename;
				        std::cout << "ROGER Writing "+filename;
				        archives[index].writeTo(filename);
				        switch(archives[index].error()){
	        			case 0:
		        			std::cout << "\nSUCCESS Writing";
		        			break;
        				default:
        					std::cout << "\nERROR Writing " << archives[index].error(); 
        					break;
		        		}
				    }else if(command == "discard"){
				        std::cout << "ROGER Discarding";
			            files.erase(files.begin()+index);
			            archives.erase(archives.begin()+index);
			            index = -1;
				    }else if(command == "add"){
				        std::string filename;
				        std::cin >> filename;
				        std::cout << "ROGER Adding "+filename;
				        archives[index].addFile(filename);
				        switch(archives[index].error()){
	        			case 0:
		        			std::cout << "\nSUCCESS Adding";
		        			break;
        				default:
        					std::cout << "\nERROR Adding " << archives[index].error(); 
        					break;
		        		}
				    }else if(command == "dump"){
				    	std::cout << "ROGER Dumping";
				    	for(size_t i=0;i<archives[index].size();i++){
				    		usa::file archivefile = archives[index].getFile(i);
				    		std::string afilename(reinterpret_cast<char*>(archivefile.name),archivefile.namesize);
				    		std::cout << std::endl << i << ". NAME:"+afilename+" SIZE:" << archivefile.size;
				    	}
				    }else if(command == "extract"){
				        std::string dirname;
				        std::cin >> dirname;
				    	std::cout << "ROGER Extracting "+dirname;
				    	archives[index].unArchive(dirname);
				    	switch(archives[index].error()){
	        			case 0:
		        			std::cout << "\nSUCCESS Extracting";
		        			break;
        				default:
        					std::cout << "\nERROR Extracting " << archives[index].error(); 
        					break;
		        		}
				    }else if(command == "extfile"){
				        std::string filename;
				        std::cin >> filename;
				    	std::cout << "ROGER Extract file " + filename;
				    	bool written = false;
				    	for(size_t i=0;i<archives[index].size();i++){
				    		usa::file archivefile = archives[index].getFile(i);
				    		std::string afilename(reinterpret_cast<char*>(archivefile.name),archivefile.namesize);
				    		if(afilename == filename){
				    			std::ofstream wafile(afilename,std::ios::binary);
				    			if(!wafile.is_open()){
				    				std::cout << "\nERROR Extract file ";
				    			}else{
				    				wafile.write(reinterpret_cast<char*>(archivefile.data),archivefile.size);
				    				written = true;
				    			}
				    			wafile.close();
				    			break;
				    		}
				    	}
				    	if(written){
				    		std::cout << "\nSUCCESS Extract file";
				    	}else{
				    		std::cout << "\nERROR Extract file not written.";
				    	}
				    }else if(command == "extracth"){
				    	std::cout << "ROGER Extracthere";
				    	archives[index].unArchive("./");
				    	switch(archives[index].error()){
	        			case 0:
		        			std::cout << "\nSUCCESS Extracting";
		        			break;
        				default:
        					std::cout << "\nERROR Extracting " << archives[index].error(); 
        					break;
		        		}
				    }else{
				        std::cout << "INVALID: "+command;
				    }
				}else{
				    std::cout << "INVALID: "+command;
				}
			}
		}
		break;
	}
	case 2:{
	    //std::cout << "Processing 2 args";
		const std::string cmd(argv[1]);
	    if(cmd == "help" || cmd == "-h" || cmd == "--help"){
	    	std::cout << "USArchive cli help\nhelp, -h, --help: Show help\nextract [file] ?[dir]: Extract an archive to dir or here.\ninfo, -i, --info: Show info\nversion, -v, --version: Show version" << std::endl;
	    }else if(cmd == "info" || cmd == "-i" || cmd == "--info"){
	    	std::cout << PINFO << std::endl << PVERSION << std::endl;
	    }else if(cmd == "version" || cmd == "-v" || cmd == "--version"){
	    	std::cout << PVERSION << std::endl;
	    }else{
	    	std::cout << "INVALID: " + cmd << std::endl;
    	}
		break;
	}
	case 3:{
	    const std::string cmd(argv[1]);
	    if(cmd == "extract"){
	    	const std::string filename(argv[2]);
	        std::cout << "ROGER Extraction " << filename << std::endl;
	        usarchive archive(filename);
	        archive.unArchive("./");
	        switch(archive.error()){
        	case 0:
        		std::cout << "SUCCESS Extraction" << std::endl;
	        	break;
        	default:
        		std::cout << "ERROR " << archive.error() << std::endl;
        		break;
	        }
	    }else{
	        std::cout << "INVALID: " + cmd << std::endl;
	    }
		break;
	}
	case 4:{
	    const std::string cmd(argv[1]);
	    if(cmd == "extract"){
	        const std::string filename(argv[2]);
	        const std::string exPath(argv[3]);
	        std::cout << "ROGER Extraction " + filename + " to " + exPath << std::endl;
	        usarchive archive(filename);
	        archive.unArchive(exPath);
	        switch(archive.error()){
        	case 0:
        		std::cout << "SUCCESS Extraction" << std::endl;
	        	break;
        	default:
        		std::cout << "ERROR " << archive.error() << std::endl;
        		break;
	        }
	    }else{
	        std::cout << "INVALID: " + cmd << std::endl;
	    }
	}
	}
	return 0;
}