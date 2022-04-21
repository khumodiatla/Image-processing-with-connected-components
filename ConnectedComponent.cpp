#include "ConnectedComponent.h"

// Default Constructor implementation that sets the default values for the class members
MTLKHU004::ConnectedComponent::ConnectedComponent(): numOfPixels(0), componentID(0){}

// Destructor
MTLKHU004::ConnectedComponent::~ConnectedComponent(){}

// Copy Constructor implementation
MTLKHU004::ConnectedComponent::ConnectedComponent(const MTLKHU004::ConnectedComponent & c): numOfPixels(c.numOfPixels), componentID(c.componentID){
    if( c.coordinates.size() > 0){
        for(int i=0; i< c.coordinates.size(); ++i){
            std::pair<int, int> p;
            p.first = c.coordinates[i].first;
            p.second = c.coordinates[i].second;
            coordinates.push_back(p);
        }
    }
}

// Move Constrcutor implemtation
MTLKHU004::ConnectedComponent::ConnectedComponent( MTLKHU004::ConnectedComponent && c): numOfPixels(c.numOfPixels), componentID(c.componentID){
    coordinates = std::move( c.coordinates);
    c.numOfPixels = c.componentID = 0;
}

// Copy Assignment Operator implementation
MTLKHU004::ConnectedComponent& MTLKHU004::ConnectedComponent::operator=(const MTLKHU004::ConnectedComponent & c){
    if( this != &c){
        numOfPixels = c.numOfPixels;
        componentID = c.componentID;

        if( c.coordinates.size() > 0){
            for(int i=0; i< c.coordinates.size(); ++i){
              std::pair<int, int> p;
              p.first = c.coordinates[i].first;
              p.second = c.coordinates[i].second;
              coordinates.push_back(p);
            }
        }
    }
	  return *this;
}

// Move Assignment Operator implementation
MTLKHU004::ConnectedComponent& MTLKHU004::ConnectedComponent::operator=(MTLKHU004::ConnectedComponent && c){
    if(this != &c){
        numOfPixels = c.numOfPixels;
        componentID = c.componentID;
        coordinates = std::move( c.coordinates);
        c.numOfPixels = c.componentID = 0;
    }
  	return *this;
}