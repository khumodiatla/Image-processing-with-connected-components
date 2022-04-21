#ifndef __PGM__
#define __PGM_

#include <iostream>
#include <fstream>
#include <sstream>
#include "ConnectedComponent.h"

namespace MTLKHU004{
	class PGMimageProcessor{
		private:
			std::vector< std::unique_ptr<ConnectedComponent>> container;
			std::string inputPGMfile;
			unsigned char ** imageArray;
			int width, height;

		public:
			// Default Constructor declaration
			PGMimageProcessor();	
			
			// Destructor
			~PGMimageProcessor();
	
			// Copy Constructor
			PGMimageProcessor(const PGMimageProcessor & pgm);

			// Move Constructor
			PGMimageProcessor(PGMimageProcessor && pgm);

			// Copy Assignment Operator
			PGMimageProcessor & operator=(const PGMimageProcessor & pgm);
	
			// Move Assignment Operator
			PGMimageProcessor & operator=(PGMimageProcessor && pgm);
	
			// PGMimageProcessor constructor declaration
			PGMimageProcessor( std::string inputPGMfile);
		
			//  extractComponents function declaration
			int extractComponents(unsigned char threshold, int minValidSize);

			// filterComponentsBySize function declaration
			int filterComponentsBySize(int minSize, int maxSize);
		
			// writeComponents function declaration
			bool writeComponents(const std::string & outFileName);

			// getComponentCount function declaration
			int getComponentCount(void) const;

			// getLargestSize function declaration
			int getLargestSize(void) const;

			// getSmallestSize function declaration
			int getSmallestSize(void) const;

			// printComponentData function declaration
			void printComponentData(const ConnectedComponent & theComponent) const;

			// getWidth function declaration
			int getWidth() const;

			// getHeight function declaration
			int getHeight() const;

			// getInputPGMfile function declaration
			std::string getInputPGMfile() const;


	};
}

#endif

