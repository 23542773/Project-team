#include "PlantBedIterator.h"
#include "Bed.h"
#include "Plant.h"
#include "PlantBedMemento.h"

PlantBedIterator::PlantBedIterator(Bed& b) : bed(b), Index(0) {

    memento = bed.createMemento(); 
    snapshot = memento->getSnapshot();

 }

PlantBedIterator::~PlantBedIterator() {
    delete memento;
 }

Plant*& PlantBedIterator::next() {
    return snapshot[Index++];
}

bool PlantBedIterator::hasNext() {
    return Index < snapshot.size();
}

void PlantBedIterator::goTo(size_t index) {
    if (index < bed.getPlants().size())
        Index = index;
}

void PlantBedIterator::reset() {
    Index = 0;
}

size_t PlantBedIterator::currentIndexValue() const {
    return Index;
}


