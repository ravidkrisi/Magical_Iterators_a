#include <vector>
#include <set>
#include <iostream>
#include <stdexcept>

using namespace std;
namespace ariel {
//----------- MagicalContainer class ---------------------------------------
    class MagicalContainer
    {
    private:
        // **** declare attributes ****
        std::set<int> container_; // store all element
        std::vector<int> asc_container_; // store all element in ascending order
        std::vector<int *> prime_container_; // store all prime element in insert order

        static bool isPrime_(int element); // check if element is prime for prime container
        void addSortedElement_(int element); // add element to sorted container
        void addPrimeElement_(int element); // add element pointer if its prime
        void removeSortedElement_(int element); // add element to sorted container
        void removePrimeElement_(int element); // add element pointer if its prime
        void updatePrimeAddress_(); // update primeContainer elements addresses

    public:
        // **** declare & define constructors ****
        MagicalContainer(); // default constructor
        MagicalContainer(MagicalContainer &other); // copy constructor
        ~MagicalContainer(){}; // destructor

        // **** declare & define getters ****
        std::set<int> getContainer() const {return this->container_;} // return the elements container
        std::vector<int> getAscContainer() const {return this->asc_container_;} // return the elements asc container
        std::vector<int *> getPrimeContainer() const {return this->prime_container_;} // return the elements prime container
        std::size_t size() const {return container_.size();} // return the size of the container

        // **** declare functions ****
        void removeElement(int element); // remove element to all containers
        void addElement(int element); // add element to all containers

//----------- AscendingIterator class ---------------------------------------
        class AscendingIterator
        {
        private:
            // **** declare attributes ****
            MagicalContainer& container_;
            std::size_t index_;

        public:
            // **** declare & define constructors ****
            AscendingIterator(MagicalContainer& container, std::size_t index=0); // initialize iterator

            // **** overload operators ****
            int& operator*(); // overload the dereference operator
            MagicalContainer::AscendingIterator& operator++ (); // overload the ++ operator
            bool operator !=(const MagicalContainer::AscendingIterator& other) const; // overload inequality operator
            bool operator ==(const MagicalContainer::AscendingIterator& other) const; // overload equality operator
            bool operator <(const MagicalContainer::AscendingIterator& other) const; // overload comparison operator
            bool operator >(const MagicalContainer::AscendingIterator& other) const; // overload comparison operator
            MagicalContainer::AscendingIterator& operator =(const MagicalContainer::AscendingIterator& other); // overload assigment operator


            // **** declare functions ****
            MagicalContainer::AscendingIterator begin() const; // return asc_iterator that point to the beginning of the container
            MagicalContainer::AscendingIterator end() const; // return asc_iterator that point to the end of the container

        };

//----------- SideCrossIterator class ---------------------------------------
        class SideCrossIterator
        {
        private:
            // **** declare attributes ****
            MagicalContainer& container_;
            std::size_t index_;

        public:
            // **** declare constructors ****
            SideCrossIterator(MagicalContainer& container, std::size_t index=0); // constructor

            // **** overload operators ****
            int& operator*(); // overload the dereference operator
            MagicalContainer::SideCrossIterator& operator++ (); // overload the ++ operator
            bool operator !=(const MagicalContainer::SideCrossIterator& other) const; // overload inequality operator
            bool operator ==(const MagicalContainer::SideCrossIterator& other) const; // overload equality operator
            bool operator <(const MagicalContainer::SideCrossIterator& other) const; // overload comparison operator
            bool operator >(const MagicalContainer::SideCrossIterator& other) const; // overload comparison operator
            MagicalContainer::SideCrossIterator& operator =(const MagicalContainer::SideCrossIterator& other); // overload assigment operator


            // **** declare functions ****
            MagicalContainer::SideCrossIterator begin() const; // return asc_iterator that point to the beginning of the container
            MagicalContainer::SideCrossIterator end() const; // return asc_iterator that point to the end of the container


        };

        class PrimeIterator
        {
        private:
            // **** declare attributes ****
            MagicalContainer& container_;
            std::size_t index_;

        public:
            // **** declare constructors ****
            PrimeIterator(MagicalContainer& container, std::size_t index=0); // parameterized constructor

            // **** overload operators ****
            int& operator*(); // overload the dereference operator
            MagicalContainer::PrimeIterator& operator++ (); // overload the ++ operator
            bool operator !=(const MagicalContainer::PrimeIterator& other) const; // overload inequality operator
            bool operator ==(const MagicalContainer::PrimeIterator& other) const; // overload equality operator
            bool operator <(const MagicalContainer::PrimeIterator& other) const; // overload comparison operator
            bool operator >(const MagicalContainer::PrimeIterator& other) const; // overload comparison operator
            MagicalContainer::PrimeIterator& operator =(const MagicalContainer::PrimeIterator& other); // overload assigment operator

            // **** declare functions ****
            MagicalContainer::PrimeIterator begin() const; // return asc_iterator that point to the beginning of the container
            MagicalContainer::PrimeIterator end() const; // return asc_iterator that point to the end of the container
        };

    };
}