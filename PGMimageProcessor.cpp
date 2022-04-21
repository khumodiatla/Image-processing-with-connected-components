#include "PGMimageProcessor.h"

// Default Constructor Implementation
MTLKHU004::PGMimageProcessor::PGMimageProcessor(): height(0), width(0), inputPGMfile(""), imageArray(nullptr) {}

// Implememtation of the destructor, that frees up the imageArray memory
MTLKHU004::PGMimageProcessor::~PGMimageProcessor(){
	if( imageArray != nullptr){  // Check if imageArray is not nullptr
        	for(int i=0; i<height; ++i){
                	delete [] imageArray[i];
        	}
		delete [] imageArray;        	
	}
}

// Copy constructor implentation
MTLKHU004::PGMimageProcessor::PGMimageProcessor(const MTLKHU004::PGMimageProcessor & pgm): height(pgm.height), width(pgm.width), inputPGMfile(pgm.inputPGMfile){
	if( pgm.container.size() > 0){
		for(int i=0; i< pgm.container.size(); ++i){
			std::unique_ptr<MTLKHU004::ConnectedComponent> ptr(new MTLKHU004::ConnectedComponent);
			
			ptr->coordinates = pgm.container[i]->coordinates;
			ptr->numOfPixels = pgm.container[i]->numOfPixels;
			ptr->componentID = pgm.container[i]->componentID;

			container.push_back(std::move(ptr));
		}
	}
	if( imageArray != nullptr){
		for(int i=0; i< height; ++i){
			for(int j=0; j<width; ++j){
				imageArray[i][j] = pgm.imageArray[i][j];
			}
		}
	}
}

// Move constructor implentation
MTLKHU004::PGMimageProcessor::PGMimageProcessor(MTLKHU004::PGMimageProcessor && pgm){
	height = pgm.height; 
	width = pgm.width;

	inputPGMfile = std::move(pgm.inputPGMfile);  // Move the inputPGMfile 
	if( pgm.imageArray != nullptr){
		imageArray = std::move(pgm.imageArray);   // Move the imageArray containing the image data
	}
}

// Copy Assignment Operator implentation
MTLKHU004::PGMimageProcessor& MTLKHU004::PGMimageProcessor::operator=(const MTLKHU004::PGMimageProcessor & pgm){
	if( this !=  &pgm){
		height = pgm.height;  width = pgm.width;
		inputPGMfile = pgm.inputPGMfile;

		if( pgm.container.size() > 0){
			for(int i=0; i< pgm.container.size(); ++i){
				std::unique_ptr<MTLKHU004::ConnectedComponent> ptr(new MTLKHU004::ConnectedComponent);
				
				ptr->coordinates = pgm.container[i]->coordinates;
				ptr->numOfPixels = pgm.container[i]->numOfPixels;
				ptr->componentID = pgm.container[i]->componentID;

				container.push_back(std::move(ptr));
			}
		}
		if( imageArray != nullptr){
			for(int i=0; i< height; ++i){
				for(int j=0; j<width; ++j){
					imageArray[i][j] = pgm.imageArray[i][j];
				}
			}
		}

	}
	return *this;	
}

// Move Assignment Operator implentation
MTLKHU004::PGMimageProcessor& MTLKHU004::PGMimageProcessor::operator=(MTLKHU004::PGMimageProcessor && pgm){
	if( this !=  &pgm){
		height = pgm.height;  width = pgm.width;

		inputPGMfile = std::move(pgm.inputPGMfile);
		imageArray = std::move(pgm.imageArray);
		pgm.height = pgm.width = 0;
	}
	return *this;
}


// Parameterized Constructor implentation that sets the value of the inputPGMfile
MTLKHU004::PGMimageProcessor::PGMimageProcessor(std::string inputPGMfile): inputPGMfile(inputPGMfile) {}

// extractComponents implementation that extractComponents from the inputPGMfile and return number of components
int MTLKHU004::PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize){

	std::ifstream in(inputPGMfile, std::ios::binary); // Open the image
	std::string line;
	bool headerIdentified = false;

	if(in){
		while( getline(in, line)){
			std::istringstream iss(line);
			iss >> width;
			iss >> height;

			if(width != 0 && height != 0 ){
				getline(in, line);	

				// Allocate the heap memory for the input image
				imageArray = new unsigned char*[height];
				for(int i =0; i<height; ++i){
					imageArray[i] = new unsigned char[width];
				}			
				
				// Read image and store pixels in the imageArray
				while( !in.eof()){
					for(int i=0; i<height; ++i){
						for(int j=0; j<width; ++j){
							in >> imageArray[i][j];
						}
					}
				}
			}
	
		}
	}
	else{ // If an error occured
		std::cout << "Could not open the image" << "\n";
	}
	
	for(int i=0; i< height; ++i){
		for(int j=0; j<width; ++j){
			
			if( (float) imageArray[i][j] >= (float)threshold){  // Check if a pixel is a foreground pixel
				
				std::unique_ptr<MTLKHU004::ConnectedComponent> ptr(new MTLKHU004::ConnectedComponent);
				
				std::pair<int, int> coords;
				coords.first = i;
				coords.second = j;

				ptr->coordinates.push_back( coords );
				++ptr->numOfPixels;
	
				std::vector< std::pair<int, int>> cardinal;
				cardinal.push_back(coords);

				imageArray[ coords.first][coords.second] = (unsigned char)0;
								
				/** Loop infintely to check if the neighbours of the foreground pixel 
				  * Are also foreground pixels, and add their coordinates to the coordinates vector
				  * And change the pixels to black after adding their coordinates
				 */
				while(true){
					for(int i=0; i<cardinal.size(); ++i){
						if( (float) imageArray[ cardinal[i].first+1 ][ cardinal[i].second ] >= (float) threshold){
							coords.first = cardinal[i].first+1;
							coords.second = cardinal[i].second;
							
							++ptr->numOfPixels;  // Increment number of pixels
							ptr->coordinates.push_back(coords);

							cardinal.push_back(coords);
							imageArray[ coords.first ][ coords.second ] = (unsigned char)0; 
	
						}
						if( (float) imageArray[ cardinal[i].first-1][ cardinal[i].second ] >= (float) threshold){
							coords.first = cardinal[i].first-1;
							coords.second = cardinal[i].second;

							++ptr->numOfPixels;  // Increment number of pixels
							ptr->coordinates.push_back(coords);

							cardinal.push_back(coords);
							imageArray[ coords.first ][ coords.second ] = (unsigned char)0;
						}
						if( (float) imageArray[ cardinal[i].first ][ cardinal[i].second+1] >= (float) threshold){
							coords.first = cardinal[i].first;
							coords.second = cardinal[i].second+1;

							++ptr->numOfPixels; // Increment number of pixels
							ptr->coordinates.push_back(coords);

							cardinal.push_back(coords);
							imageArray[ coords.first ][ coords.second ] = (unsigned char)0;
						}
						if( (float) imageArray[ cardinal[i].first ][ cardinal[i].second-1 ] >= (float) threshold){
							coords.first = cardinal[i].first;
							coords.second = cardinal[i].second-1;

							++ptr->numOfPixels;  // Increment number of pixels
							ptr->coordinates.push_back(coords);

							cardinal.push_back(coords);
							imageArray[ coords.first ][ coords.second ] = (unsigned char)0;
						}
					}
					
					// Add the component to the container if it's size >= minValidSize
					if( ptr->numOfPixels >=  minValidSize){  
						container.push_back( std::move(ptr) );
					}

					break; 
				}
				
				
			}
		}
	}
	
	in.close();  // Close the input image
	
	return container.size();
}

/* filterComponentsBySize implementation that removes components  with size not within the given range 
 * and return number of components remaining
*/
int MTLKHU004::PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize){
	for( std::vector< std::unique_ptr< MTLKHU004::ConnectedComponent>>::const_iterator i= container.begin(); i != container.end(); ++i){
		if((*i)->numOfPixels <  minSize || (*i)->numOfPixels > maxSize){
			container.erase(i);
			--i;	
		}
	} 
	
	return container.size();
}

// writeComponents implementation that create a new PGM file which contains all current components
bool MTLKHU004::PGMimageProcessor::writeComponents(const std::string & outFileName){

	std::ofstream out(outFileName);
        out << "P5" << std::endl;
        out << width << " " << height << std::endl;
        out << 255 << std::endl;

	// Make imageArray contain only black pixels
	for(int i=0; i<height; ++i){
                for(int j=0; j<width; ++j){
                        imageArray[i][j] = (unsigned char)0;
                }
        }
	
	/** Change imageArray pixels to be white 
	  * At the coordinates of all components in the container
 	*/
	for( std::vector<std::unique_ptr<MTLKHU004::ConnectedComponent>>::const_iterator i= container.begin(); i != container.end(); ++i){
		for(int j=0; j < (*i)->coordinates.size(); ++j){
			int x = (*i)->coordinates[j].first;
			int y = (*i)->coordinates[j].second;
			imageArray[x][y] = (unsigned char)255;
		}
	}
	
	// Ouput all the imageArray pixels to the outFilename
        for(int i=0; i<height; ++i){
                for(int j=0; j<width; ++j){
                	out << imageArray[i][j];
                }
        }
	
	return true;
}

// getComponentCount implementation that return number of components
int MTLKHU004::PGMimageProcessor::getComponentCount(void) const{

	return container.size();
}


// getLargestSize implementation that return number of pixels in largest component
int MTLKHU004::PGMimageProcessor::getLargestSize(void) const{
	int largest = 0;
	
	for(int i=0; i<container.size(); ++i){
		if( container[i]->numOfPixels > largest){
			largest = container[i]->numOfPixels;
		}	
	}

	return largest;
}

// getSmallestSize implementation that return number of pixels in smallest component
int MTLKHU004::PGMimageProcessor::getSmallestSize(void) const{
	int smallest = container[0]->numOfPixels;

	for(int i=0; i<container.size(); ++i){
		if( container[i]->numOfPixels  < smallest){
			smallest = container[i]->numOfPixels;
		}
	}

	return smallest;
}

// printComponentData implementation that the data for a component to std::cout
void MTLKHU004::PGMimageProcessor::printComponentData(const MTLKHU004::ConnectedComponent & theComponent) const{
	std::cout <<"Component ID: " << theComponent.componentID << " : " << theComponent.numOfPixels  << " pixels"<< std::endl;
}

// getWidth implementation that returns the width
int MTLKHU004::PGMimageProcessor::getWidth() const{
	return width;
}

// getHeight implementation that returns the height
int MTLKHU004::PGMimageProcessor::getHeight() const{
	return height;
}

// getInputPGMfile function implementation that returns the inputPGMfile
std::string MTLKHU004::PGMimageProcessor::getInputPGMfile() const{
	return inputPGMfile;
}
