#include <iostream>
#include <cassert>
#include "Plant.h"
#include "Bed.h"
#include "Greenhouse.h"
#include "PlantStateIterator.h"
#include "PlantBedIterator.h"

// Dummy Flyweight Implementation
/**
 * @class DummyFlyweight
 * @brief Test implementation of PlantFlyweight for testing purposes.
 */
class DummyFlyweight : public PlantFlyweight {
public:
    std::string getSku() override { return "SKU1"; }
    std::string getName() override { return "Plant"; }
    std::string getBiome() override { return "Forest"; }
    int getCost() override { return 10; }
};

// Utility test helpers
/**
 * @brief Prints a separator with title for test output.
 * @param title The title to display in the separator.
 */
void separator(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

/**
 * @brief Main test function for iterator implementations.
 * @return 0 on success, non-zero on failure.
 */
int main() {
    DummyFlyweight fly;

    // ---------- TEST 1: Empty Bed Iterator ----------
    separator("TEST 1: Empty Bed Iterator");
    Bed emptyBed;
    PlantIterator<Plant*>* emptyIter = emptyBed.createIterator();
    assert(!emptyIter->hasNext() && "Empty bed should have no plants");
    std::cout << " Passed empty bed hasNext() test.\n";
    delete emptyIter;

    // ---------- TEST 2: Bed iteration correctness ----------
    separator("TEST 2: Bed Iteration Order");
    Plant p1("p1", "green", &fly, nullptr, nullptr, nullptr, nullptr);
    Plant p2("p2", "red", &fly, nullptr, nullptr, nullptr, nullptr);
    Bed bed;
    bed.addPlant(&p1);
    bed.addPlant(&p2);

    PlantIterator<Plant*>* bedIter = bed.createIterator();
    size_t count = 0;
    while (bedIter->hasNext()) {
        Plant* p = bedIter->next();
        std::cout << "  " << p->id() << " " << p->getColour() << "\n";
        if (count == 0) assert(p == &p1);
        if (count == 1) assert(p == &p2);
        ++count;
    }
    assert(count == 2 && "Expected 2 plants in bed");
    std::cout << " Passed bed iteration order test.\n";
    delete bedIter;

    // ---------- TEST 3: Greenhouse Iteration ----------
    separator("TEST 3: Greenhouse Iteration");
    Plant p3("p3", "yellow", &fly, nullptr, nullptr, nullptr, nullptr);
    Bed bed2;
    bed2.addPlant(&p3);
    Greenhouse gh;
    gh.addBed(&bed);
    gh.addBed(&bed2);

    PlantIterator<Plant*>* ghIter = gh.createIterator();
    std::vector<Plant*> seen;
    while (ghIter->hasNext()) {
        Plant* p = ghIter->next();
        seen.push_back(p);
        std::cout << "  " << p->id() << " " << p->getColour() << "\n";
    }
    assert(seen.size() == 3 && "Expected 3 total plants in greenhouse");
    assert(seen[0] == &p1 && seen[1] == &p2 && seen[2] == &p3);
    std::cout << " Passed greenhouse iteration order test.\n";
    delete ghIter;

    // ---------- TEST 4: goTo() and currentIndex() ----------
    separator("TEST 4: goTo() and currentIndex()");
    PlantIterator<Plant*>* bedIter2 = bed.createIterator();
    bedIter2->goTo(1);
    Plant* current = bedIter2->next();
    assert(current == &p2 && "goTo(1) should move iterator to p2");
    std::cout << " currentIndex() after goTo(1): " << bedIter2->currentIndex() << "\n";
    delete bedIter2;

    // ---------- TEST 5: Multiple Iterators ----------
    separator("TEST 5: Multiple Iterators");
    PlantIterator<Plant*>* iterA = bed.createIterator();
    PlantIterator<Plant*>* iterB = bed.createIterator();
    assert(iterA->next() == &p1);
    assert(iterB->next() == &p1);
    std::cout << " Iterators can operate independently.\n";
    delete iterA;
    delete iterB;

    // ---------- TEST 6: Const Greenhouse Iteration ----------
    separator("TEST 6: Const Greenhouse Iteration");
    const Greenhouse& constGh = gh;
    PlantIterator<Plant*>* constIter = const_cast<Greenhouse&>(constGh).createIterator();
    assert(constIter->hasNext());
    delete constIter;
    std::cout << " Passed const greenhouse iterator test.\n";

    // ---------- TEST 7: Stress Test ----------
    separator("TEST 7: Stress Test with Many Plants");
    Bed bigBed;
    std::vector<Plant*> many;
    for (int i = 0; i < 100; ++i)
        many.push_back(new Plant("id" + std::to_string(i), "green", &fly, nullptr, nullptr, nullptr, nullptr));
    for (auto* p : many) bigBed.addPlant(p);
    PlantIterator<Plant*>* bigIter = bigBed.createIterator();
    size_t bigCount = 0;
    while (bigIter->hasNext()) {
        bigIter->next();
        bigCount++;
    }
    assert(bigCount == 100 && "Expected 100 plants in big bed");
    std::cout << " Passed stress test.\n";
    for (auto* p : many) delete p;
    delete bigIter;

    std::cout << "\n ALL TESTS PASSED SUCCESSFULLY \n";
    return 0;
}
