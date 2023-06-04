#include "sources/MagicalContainer.hpp"
#include "doctest.h"

using namespace ariel;

TEST_CASE("Magical container")
{
    SUBCASE("constructor")
    {
        CHECK_NOTHROW(MagicalContainer()); // check error not thrown
    }

    SUBCASE("add elements")
    {
        MagicalContainer container;

        CHECK_NOTHROW(container.addElement(9)); // positive
        CHECK_NOTHROW(container.addElement(-45)); // negative
        CHECK_NOTHROW(container.addElement(0)); // zero
    }

    SUBCASE("size function")
    {
        MagicalContainer container;
        CHECK(container.size() == 0);

        container.addElement(15);
        CHECK(container.size() == 1);
    }

    SUBCASE("remove elements")
    {
        MagicalContainer container;
        container.addElement(-20);
        container.addElement(0);
        container.addElement(15);

        CHECK_NOTHROW(container.removeElement(0));
        CHECK(container.size() == 2);

        CHECK_THROWS_AS(container.removeElement(44), std::runtime_error); // check if removing non existing number throws exception
    }
}

TEST_CASE("iterators")
{
    MagicalContainer container;
    container.addElement(0);
    container.addElement(15);
    container.addElement(127);
    container.addElement(8);
    container.addElement(3);

    MagicalContainer container_2; // same as container
    container_2.addElement(0);
    container_2.addElement(15);
    container_2.addElement(127);
    container_2.addElement(8);
    container_2.addElement(3);

    MagicalContainer container_3;
    container_3.addElement(1);

    SUBCASE("constructor iterators")
    {
        CHECK_NOTHROW(MagicalContainer::AscendingIterator it(container));
        CHECK_NOTHROW(MagicalContainer::PrimeIterator it(container));
        CHECK_NOTHROW(MagicalContainer::SideCrossIterator it(container));
    }

    MagicalContainer::AscendingIterator asc_itr(container);
    MagicalContainer::SideCrossIterator cross_itr(container);
    MagicalContainer::PrimeIterator prime_itr(container);

    MagicalContainer::AscendingIterator asc_itr_2(container);
    MagicalContainer::SideCrossIterator cross_itr_2(container);
    MagicalContainer::PrimeIterator prime_itr_2(container);

    MagicalContainer::AscendingIterator asc_itr_3(container_2);
    MagicalContainer::SideCrossIterator cross_itr_3(container_2);
    MagicalContainer::PrimeIterator prime_itr_3(container_2);

    MagicalContainer::AscendingIterator asc_itr_4(container_3);
    MagicalContainer::SideCrossIterator cross_itr_4(container_3);
    MagicalContainer::PrimeIterator prime_itr_4(container_3);

    SUBCASE("dereference operator")
    {
        CHECK(*asc_itr == 0);
        CHECK(*cross_itr == 0);
        CHECK(*prime_itr == 3);
    }

    SUBCASE("pre increment operator")
    {
        // ascending iterator
        CHECK(*asc_itr == 0);
        ++asc_itr;
        CHECK(*asc_itr == 3);
        ++asc_itr;
        CHECK(*asc_itr == 8);
        ++asc_itr;
        CHECK(*asc_itr == 15);
        ++asc_itr;
        CHECK(*asc_itr == 127);
        ++asc_itr; //end()
        CHECK_THROWS_AS(++asc_itr, std::runtime_error); // check error thrown when increment beyond boundaries
        // cross iterator
        CHECK(*cross_itr == 0);
        ++cross_itr;
        CHECK(*cross_itr == 127);
        ++cross_itr;
        CHECK(*cross_itr == 3);
        ++cross_itr;
        CHECK(*cross_itr == 15);
        ++cross_itr;
        CHECK(*cross_itr == 8);
        ++cross_itr; //end()
        CHECK_THROWS_AS(++cross_itr, std::runtime_error); // check error thrown when increment beyond boundaries
        // prime iterator
        CHECK(*prime_itr == 3);
        ++prime_itr;
        CHECK(*prime_itr == 127);
        ++prime_itr; //end()
        CHECK_THROWS_AS(++prime_itr, std::runtime_error); // check error thrown when increment beyond boundaries
    }

    SUBCASE("equality/inequality operator")
    {
        // check on iterator with the same container
        CHECK(asc_itr == asc_itr_2);
        CHECK(cross_itr == cross_itr_2);
        CHECK(prime_itr == prime_itr_2);

        ++cross_itr_2;
        ++asc_itr_2;
        ++prime_itr_2;

        CHECK(asc_itr != asc_itr_2);
        CHECK(cross_itr != cross_itr_2);
        CHECK(prime_itr != prime_itr_2);

        // check on iterator with same container from diffrent MagicalContainer instances
        CHECK(asc_itr == asc_itr_3);
        CHECK(cross_itr == cross_itr_3);
        CHECK(prime_itr == prime_itr_3);

        ++cross_itr_3;
        ++asc_itr_3;
        ++prime_itr_3;

        CHECK(asc_itr != asc_itr_3);
        CHECK(cross_itr != cross_itr_3);
        CHECK(prime_itr != prime_itr_3);

        // cant fine a way to compare it
        // check on iterator with different container
//        CHECK_THROWS_AS(asc_itr == asc_itr_4, std::runtime_error);
//        CHECK_THROWS_AS(cross_itr == cross_itr_4, std::runtime_error);
//        CHECK_THROWS_AS(prime_itr == prime_itr_4, std::runtime_error);

    }

    SUBCASE("comparison operators")
    {
        CHECK_FALSE(asc_itr < asc_itr_2);
        CHECK_FALSE(cross_itr < cross_itr_2);
        CHECK_FALSE(prime_itr < prime_itr_2);

        ++prime_itr_2;
        ++cross_itr_2;
        ++asc_itr_2;

        CHECK (asc_itr < asc_itr_2);
        CHECK (cross_itr < cross_itr_2);
        CHECK(prime_itr < prime_itr_2);

        // need to test compression with different containers
    }

    SUBCASE("assigment operator")
    {
        ++asc_itr_2;
        ++prime_itr_2;
        ++cross_itr_2;

        CHECK_NOTHROW(asc_itr=asc_itr_2);
        CHECK_NOTHROW(prime_itr=prime_itr_2);
        CHECK_NOTHROW(cross_itr=cross_itr_2);

        CHECK(asc_itr==asc_itr_2);
        CHECK(prime_itr==prime_itr_2);
        CHECK(cross_itr==cross_itr_2);

        // test assigment on diffrent MagicalContainer with same container
        ++asc_itr_3;
        ++prime_itr_3;
        ++cross_itr_3;

        CHECK_NOTHROW(asc_itr=asc_itr_3);
        CHECK_NOTHROW(prime_itr=prime_itr_3);
        CHECK_NOTHROW(cross_itr=cross_itr_3);

        CHECK(asc_itr==asc_itr_3);
        CHECK(prime_itr==prime_itr_3);
        CHECK(cross_itr==cross_itr_3);

        // test on diffrent containers
        CHECK_THROWS_AS(asc_itr=asc_itr_4, std::runtime_error);
        CHECK_THROWS_AS(prime_itr=prime_itr_4, std::runtime_error);
        CHECK_THROWS_AS(cross_itr=cross_itr_4, std::runtime_error);
    }
    SUBCASE("end begin functions")
    {
        ++asc_itr_4;
        ++cross_itr_4;

        CHECK(asc_itr_4 == asc_itr_4.end());
        CHECK(prime_itr_4 == prime_itr_4.end());
        CHECK(cross_itr_4 == cross_itr_4.end());

        CHECK(asc_itr == asc_itr.begin());
        CHECK(prime_itr == prime_itr.begin());
        CHECK(cross_itr == cross_itr.begin());
    }
}
