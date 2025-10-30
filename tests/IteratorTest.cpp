#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/Bed.h"
#include "../include/Greenhouse.h"
#include "../include/PlantIterator.h"
#include "../include/PlantBedIterator.h"
#include "../include/GreenhouseIterator.h"

TEST_CASE("Basic Iterator Creation and Empty Collections") {
    SUBCASE("Bed creates PlantBedIterator") {
        Bed bed;
        auto iterator = bed.createIterator();
        CHECK(iterator != nullptr);
        CHECK(iterator->hasNext() == false);
        CHECK(iterator->currentIndex() == 0);
        delete iterator;
    }
    
    SUBCASE("Greenhouse creates GreenhouseIterator") {
        Greenhouse greenhouse;
        auto iterator = greenhouse.createIterator();
        CHECK(iterator != nullptr);
        CHECK(iterator->hasNext() == false);
        CHECK(iterator->currentIndex() == 0);
        delete iterator;
    }
}

TEST_CASE("Iterator Navigation Methods") {
    SUBCASE("PlantBedIterator navigation on empty bed") {
        Bed bed;
        PlantBedIterator iterator(bed);
        
        CHECK(iterator.hasNext() == false);
        CHECK(iterator.currentIndex() == 0);
        
        iterator.reset();
        CHECK(iterator.currentIndex() == 0);
    }
    
    SUBCASE("GreenhouseIterator navigation on empty greenhouse") {
        Greenhouse greenhouse;
        GreenhouseIterator iterator(greenhouse);
        
        CHECK(iterator.hasNext() == false);
        CHECK(iterator.currentIndex() == 0);
        
        iterator.reset();
        CHECK(iterator.currentIndex() == 0);
    }
}

TEST_CASE("Greenhouse with Beds Iteration") {
    SUBCASE("Single bed in greenhouse") {
        Greenhouse greenhouse;
        Bed* bed = new Bed();
        greenhouse.addBed(bed);
        
        auto iterator = greenhouse.createIterator();
        
        CHECK(iterator->hasNext() == true);
        CHECK(iterator->currentIndex() == 0);
        
        Bed* retrieved = iterator->next();
        CHECK(retrieved == bed);
        CHECK(iterator->hasNext() == false);
        CHECK(iterator->currentIndex() == 1);
        
        delete iterator;
        delete bed;
    }
    
    SUBCASE("Multiple beds in greenhouse") {
        Greenhouse greenhouse;
        Bed* bed1 = new Bed();
        Bed* bed2 = new Bed();
        
        greenhouse.addBed(bed1);
        greenhouse.addBed(bed2);
        
        auto iterator = greenhouse.createIterator();
        
        int count = 0;
        while (iterator->hasNext()) {
            Bed* bed = iterator->next();
            CHECK(bed != nullptr);
            count++;
        }
        
        CHECK(count == 2);
        CHECK(iterator->currentIndex() == 2);
        
        // Test reset
        iterator->reset();
        CHECK(iterator->currentIndex() == 0);
        CHECK(iterator->hasNext() == true);
        
        delete iterator;
        delete bed1;
        delete bed2;
    }
}

TEST_CASE("Iterator Pattern Integration") {
    SUBCASE("Nested iteration structure") {
        Greenhouse greenhouse;
        Bed* bed1 = new Bed();
        Bed* bed2 = new Bed();
        
        greenhouse.addBed(bed1);
        greenhouse.addBed(bed2);
        
        // Test that we can create iterators at both levels
        auto greenhouseIterator = greenhouse.createIterator();
        CHECK(greenhouseIterator != nullptr);
        
        while (greenhouseIterator->hasNext()) {
            Bed* currentBed = greenhouseIterator->next();
            auto plantIterator = currentBed->createIterator();
            CHECK(plantIterator != nullptr);
            delete plantIterator;
        }
        
        delete greenhouseIterator;
        delete bed1;
        delete bed2;
    }
}

TEST_CASE("Iterator Index Navigation") {
    SUBCASE("GreenhouseIterator goTo functionality") {
        Greenhouse greenhouse;
        Bed* beds[3];
        for (int i = 0; i < 3; i++) {
            beds[i] = new Bed();
            greenhouse.addBed(beds[i]);
        }
        
        GreenhouseIterator iterator(greenhouse);
        
        // Go to middle bed
        iterator.goTo(1);
        CHECK(iterator.currentIndex() == 1);
        CHECK(iterator.next() == beds[1]);
        
        // Go to first bed
        iterator.goTo(0);
        CHECK(iterator.currentIndex() == 0);
        CHECK(iterator.next() == beds[0]);
        
        // Cleanup
        for (int i = 0; i < 3; i++) {
            delete beds[i];
        }
    }
}