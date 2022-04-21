#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "PGMimageProcessor.h"

TEST_CASE("PGMimageProcessor Class Unit Test"){
	SECTION("extractComponents method"){
		MTLKHU004::PGMimageProcessor pgm("chess.PGM");

		int numOfComp = pgm.extractComponents(200, 1000);
		REQUIRE( numOfComp == 6);
	}

	SECTION("filterComponentsBySize method"){
		MTLKHU004::PGMimageProcessor pgm("chess.PGM");
		pgm.extractComponents(200, 1000);

		int remainingComp = pgm.filterComponentsBySize(4000,7000);
		REQUIRE(remainingComp == 3);

	}
	SECTION("writeComponents method"){
		MTLKHU004::PGMimageProcessor pgm("chess.PGM");
		pgm.extractComponents(200, 500);

		bool file = pgm.writeComponents("unitTestFile.PGM");
		REQUIRE( file == true );
	}
	SECTION("getComponentCount method"){
		MTLKHU004::PGMimageProcessor pgm("chess.PGM");
		pgm.extractComponents(200, 800);

		int count = pgm.getComponentCount();
		REQUIRE( count == 6 );
	}
	SECTION("getLargestSize method"){
		MTLKHU004::PGMimageProcessor pgm("chess.PGM");
		pgm.extractComponents(200, 800);

		int largest = pgm.getLargestSize();
		REQUIRE( largest == 7898 );
	}
	SECTION("getSmallestSize method"){
		MTLKHU004::PGMimageProcessor pgm("chess.PGM");
		pgm.extractComponents(200, 800);

		int smallest = pgm.getSmallestSize();
		REQUIRE( smallest == 4252 );
	}
	SECTION("printComponentData method"){
		MTLKHU004::PGMimageProcessor pgm("chess.PGM");
		MTLKHU004::ConnectedComponent component;
		pgm.printComponentData(component);
	}
	SECTION("Default Constructor"){
		MTLKHU004::PGMimageProcessor pgm;

		REQUIRE( pgm.getHeight() == 0);
		REQUIRE( pgm.getWidth() == 0);
		REQUIRE( pgm.getInputPGMfile() == "" );	
	}
	SECTION("Copy Constructor"){
		MTLKHU004::PGMimageProcessor pgm("chess.PGM");
	
	}
	SECTION("Move Constructor"){
		MTLKHU004::PGMimageProcessor pgm("chess.PGM");
	
	}
	SECTION("Copy Assignment Operator"){
		MTLKHU004::PGMimageProcessor pgm("chess.PGM");

	}
	SECTION("Move Assignment Operator"){
		MTLKHU004::PGMimageProcessor pgm("chess.PGM");

	}
}

TEST_CASE("ConnectedComponent Class Unit Test"){
	SECTION("Default Constructor"){
		MTLKHU004::ConnectedComponent component;  // Default Constructor Invoked 

		REQUIRE(component.numOfPixels == 0);
		REQUIRE(component.componentID == 0);
		REQUIRE(component.coordinates.size() == 0);
	}
	SECTION("Copy Constructor"){
		MTLKHU004::ConnectedComponent component;
		MTLKHU004::ConnectedComponent component2(component);  // Copy Constructor Invoked 

		REQUIRE(component.numOfPixels == component2.numOfPixels);
		REQUIRE(component.componentID == component2.componentID);
		REQUIRE(component.coordinates.size() == component2.coordinates.size());
	}
	SECTION("Move Constructor"){
		MTLKHU004::ConnectedComponent component;
		MTLKHU004::ConnectedComponent component2(std::move(component)); // Move Constructor Invoked 

		REQUIRE(component2.numOfPixels == 0);
		REQUIRE(component2.componentID == 0);
		REQUIRE(component2.coordinates.size() == 0);
	}
	SECTION("Copy Assignment Operator"){
		MTLKHU004::ConnectedComponent component;
		MTLKHU004::ConnectedComponent component2(component);
		MTLKHU004::ConnectedComponent component3;
		component3 = component2;  // Copy Assignment Operator Invoked

		REQUIRE(component3.numOfPixels == component2.numOfPixels);
		REQUIRE(component3.componentID == component2.componentID);
		REQUIRE(component3.coordinates.size() == component2.coordinates.size());
	}
	SECTION("Move Assignment Operator"){
		MTLKHU004::ConnectedComponent component;
		MTLKHU004::ConnectedComponent component2(component);
		MTLKHU004::ConnectedComponent component3;
		component3 = std::move(component2);  // Move Assignment Operator Invoked

		REQUIRE(component3.numOfPixels == component.numOfPixels);
		REQUIRE(component3.componentID == component.componentID);
		REQUIRE(component3.coordinates.size() == component.coordinates.size());
	}
}