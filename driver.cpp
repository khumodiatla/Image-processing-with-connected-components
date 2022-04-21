#include <iostream>
#include "PGMimageProcessor.h"

int main(int argc, char * argv[]){
	
	int minValue, maxValue, threshold; 
	std::string outPGMfile, inputPGMfile = argv[argc-1];
	bool print = false;

	for(int i=0; i<argc; ++i){
		if( std::string (argv[i]) == "-s"){
			minValue = std::stoi(argv[i+1]);
			maxValue = std::stoi(argv[i+2]);
		}
		if( std::string (argv[i]) == "-t"){
			threshold = std::stoi (argv[i+1]);
		}
		if( std::string (argv[i]) == "-p"){
			print = true;
		}
		if( std::string (argv[i]) == "-w"){
			outPGMfile = std::string (argv[i+1]);
        }
	}
	
	MTLKHU004::PGMimageProcessor processor(inputPGMfile);  // Invoke the PGMimageProcessor parameterized constructor
	processor.extractComponents((unsigned char) threshold, 1000);  // Invoke the extractComponents function
	processor.filterComponentsBySize(minValue, maxValue);  // Invoke the filterComponentsBySize function
	processor.writeComponents(outPGMfile);  // Invoke the writeComponents function
	
	std::cout << "Number of components: " << processor.getComponentCount() << std::endl;	
	std::cout << "Largest componenet: " << processor.getLargestSize() << std::endl;
	std::cout << "Smallest component: " << processor.getSmallestSize() << std::endl;

	//std::vector< std::unique_ptr< MTLKHU004::ConnectedComponent>> c;// = processor.getContainer();
	//processor.printComponentData( processor.getContainer()[0] );

}
