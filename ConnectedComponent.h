#ifndef __Component__
#define __Component__

#include <string>
#include <vector>
#include <memory>
#include <utility>

namespace MTLKHU004{
	class ConnectedComponent{
		private:
			std::unique_ptr<ConnectedComponent> ptr;
		public:
			int numOfPixels;
			int componentID;
			std::vector< std::pair<int, int > > coordinates;

			// Default constructor declaration
			ConnectedComponent();

			// Destructor 
			~ConnectedComponent();
		
			// Copy Constructor
			ConnectedComponent(const ConnectedComponent & c);

			// Move Constructor
			ConnectedComponent( ConnectedComponent && c);

			// Copy Assignment Operator
			ConnectedComponent & operator=(const ConnectedComponent & c);

			// Move Assignment Operator
			ConnectedComponent & operator=(ConnectedComponent && c);
	
	};
}

#endif
