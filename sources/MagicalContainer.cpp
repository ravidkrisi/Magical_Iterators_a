#include "MagicalContainer.hpp"
namespace ariel
{
//----------- MagicalContainer class ---------------------------------------
    // **** define constructors ****
    /**
     * @brief default constructor
     */
    MagicalContainer::MagicalContainer() {}
     /**
      * @brief copy constructor
      * @param other reference to another MagicalContainer
      */
      MagicalContainer::MagicalContainer(ariel::MagicalContainer &other)
      {
          this->container_ = other.getContainer();
          this->asc_container_ = other.getAscContainer();
          this->prime_container_ = other.getPrimeContainer();
      }

      // **** define function ****
      /**
       * @brief function check for prime numbers
       * @param element number
       * @return bool that indicated if number is prime
       */
      bool MagicalContainer::isPrime_(int element)
      {
          if (element < 2) return false; // non prime
          if (element == 2) return true; // prime

          for (int i=2; i*i<=element; i++)
          {
              if (element % i == 0) return false; // optional divisor exist, non prime
          }
          return true; // no optional divisor, element is prime
      }

      /**
       * @brief function to add element to sorted container
       * @param element element to be added
       */
      void MagicalContainer::addSortedElement_(int element)
      {
          asc_container_.push_back(element); // add element to end of container
          for (std::size_t i = asc_container_.size()-1; i>0; --i) // sort container from end to beginning
          {
              // swap if element at index i-1 is bigger than element at index i
              if(asc_container_.at(i-1) > asc_container_.at(i)) swap(asc_container_.at(i-1), asc_container_.at(i));
          }
      }
    /**
     * @brief update primeContainer elements address
     */
    void MagicalContainer::updatePrimeAddress_()
    {
        // update prime numbersContainer addresses after insertion
        std::size_t j=0;
        for (std::size_t i = 0; i < asc_container_.size()-1; ++i)
        {
            if (isPrime_(asc_container_.at(i)))
            {
                prime_container_.at(j++) = &asc_container_.at(i);
            }
        }
    }
    /**
     * @brief add element address to primeContainer if element is prime. then sort primeContainer if needed
     * @param element
     */
    void MagicalContainer::addPrimeElement_(int element)
    {
        if (isPrime_(element))
        {
            prime_container_.push_back(&asc_container_.back());
        }
        updatePrimeAddress_();
    }
      /**
       * @brief function add element to all containers by
       * @param element int number that will be added to set
       */
      void MagicalContainer::addElement(int element)
      {
          container_.insert(element); // add element to elements set
          this->addSortedElement_(element); // add element to sorted container
          this->addPrimeElement_(element); // add element address to primeContainer if element is prime
      }

    /**
     * @brief remove element if exist from sortedContainer
     * @param element do be removed
     */
    void MagicalContainer::removeSortedElement_(int element)
    {
        auto it = std::find(asc_container_.begin(), asc_container_.end(), element); // find the element iterator if exist

        // check if iterator found, then delete from ascContainer
        if (it != asc_container_.end())
        {
            asc_container_.erase(it);
        }
    }

    /**
     * @brief remove element from primeContainer
     * @param element to be removed
     */
    void MagicalContainer::removePrimeElement_(int element)
    {
        // if element is prime remove one item from primeContainer
        if (isPrime_(element))
        {
            prime_container_.pop_back(); // remove last element
        }
        // update prime elements addresses
        updatePrimeAddress_();
    }

    /**
     * @brief function to erase element from all container if found
     * @param element to be deleted
     */
    void MagicalContainer::removeElement(int element)
    {
        // check if element exist in containers. then remove it. else throw runtime error
        if (container_.count(element) > 0) // element exit
        {
            container_.erase(element); // erase element from container
            removeSortedElement_(element); // remove element from sortedContainer
            removePrimeElement_(element); // remove element from primeContainer
        }
        else // element not exist
        {
            throw std::runtime_error("cant remove non-existing element");
        }
    }


//----------- AscendingIterator class ---------------------------------------

    // **** define constructors ****
    /**
     * @brief parameterized constructor
     * @param container reference for the magical container
     * @param index default=0. index for the iterator
     */
    MagicalContainer::AscendingIterator::AscendingIterator(ariel::MagicalContainer &container, std::size_t index): container_(container), index_(index) {}

    // **** define overload operators ****
    /**
     * @brief overload dereference operator
     * @return reference of element at index
     */
    int& MagicalContainer::AscendingIterator::operator*() {return container_.asc_container_.at(index_);}

    /**
     * @brief overload the ++ operator.
     * @return iterator after increment
     */
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++()
    {
        // throw exception if increment over boundaries
        if(end().index_ == index_) throw std::runtime_error("cant increment beyond boundaries");
        ++index_;
        return *this;
    }

    /**
     * @brief overload the equality operator
     * @param other reference to another iterator
     * @return bool that indicated if equality
     */
    bool MagicalContainer::AscendingIterator::operator==(const MagicalContainer::AscendingIterator &other) const
    {
        return (index_ == other.index_);
    }

     /**
     * @brief overload the inequality operator
     * @param other reference to another iterator
     * @return bool that indicated if inequality
     */
    bool MagicalContainer::AscendingIterator::operator!=(const MagicalContainer::AscendingIterator &other) const
    {
        return !(*this == other);
    }

    /**
     * @brief overload < comparison
     * @param other reference for another iterator
     * @return bool that indicate comparison
     */
    bool MagicalContainer::AscendingIterator::operator<(const MagicalContainer::AscendingIterator &other) const
    {
        return (this->index_ < other.index_);
    }

    /**
     * @brief overload < comparison
     * @param other reference for another iterator
     * @return bool that indicate comparison
     */
    bool MagicalContainer::AscendingIterator::operator>(const MagicalContainer::AscendingIterator &other) const
    {
        return (this->index_ > other.index_);
    }

    /**
     * @brief assign iterator overload
     * @param other reference for another itertator
     * @return
     */
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const MagicalContainer::AscendingIterator &other)
    {
        // check if containers are equal
        if (container_.container_ != other.container_.container_) throw std::runtime_error("cant assign iterator on different container");

        // containers are equal so assign index
        index_ = other.index_;
        return *this;
    }

    // **** define function ****
    /**
     * @brief set iterator index at zero
     * @return the iterator after set index at 0
     */
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const
    {
        return MagicalContainer::AscendingIterator(this->container_);
    }

    /**
     * set iterator index at end of the container
     * @return
     */
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const
    {
        return MagicalContainer::AscendingIterator(this->container_, this->container_.getAscContainer().size());
    }

//----------- SideCrossIterator class ---------------------------------------
    // **** define constructors ****
    /**
     * @brief SideCrossIterator parameterized constructor
     * @param container reference for the magical container
     * @param index index of the iterator. default 0
     */
    MagicalContainer::SideCrossIterator::SideCrossIterator(ariel::MagicalContainer& container, std::size_t index): container_(container), index_(index) {}

    // **** define overload operators ***
    /**
     * @brief dereference overload operator
     * @return element reference at index
     */
    int& MagicalContainer::SideCrossIterator::operator*() {return container_.asc_container_.at(index_);}

    /**
     * @brief increment the iterator. overload ++ pre operator
     * @return iterator after increment
     */
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++()
    {
        // throw exception if increment over boundaries
        if(end().index_ == index_) throw std::runtime_error("cant increment beyond boundaries");

        std::size_t mid_index = container_.getAscContainer().size()/2;
        if (mid_index == index_) // if mid_index equal to index icrement to end index
        {
            index_ = container_.getAscContainer().size();
        }
        else if (index_<mid_index) // if index is on the left side from mid_index
        {
            index_ = (container_.getAscContainer().size()-1) - index_;
        }
        else if (index_ > mid_index) // if index is on the right side from mid_index
        {
            index_ = (container_.getAscContainer().size()) - index_;
        }
        return *this;
    }

     /**
     * @brief overload the equality operator
     * @param other reference to another iterator
     * @return bool that indicated if equality
     */
    bool MagicalContainer::SideCrossIterator::operator==(const MagicalContainer::SideCrossIterator &other) const
    {
        return (index_ == other.index_);
    }

    /**
    * @brief overload the inequality operator
    * @param other reference to another iterator
    * @return bool that indicated if inequality
    */
    bool MagicalContainer::SideCrossIterator::operator!=(const MagicalContainer::SideCrossIterator &other) const
    {
        return (!(*this == other));
    }

    /**
     * @brief overload < comparison
     * @param other reference for another iterator
     * @return bool that indicate comparison
     */
    bool MagicalContainer::SideCrossIterator::operator<(const MagicalContainer::SideCrossIterator &other) const
    {
        return (this->index_ < other.index_);
    }

    /**
     * @brief overload < comparison
     * @param other reference for another iterator
     * @return bool that indicate comparison
     */
    bool MagicalContainer::SideCrossIterator::operator>(const MagicalContainer::SideCrossIterator &other) const
    {
        return (this->index_ > other.index_);
    }


    /**
     * @brief assign iterator overload
     * @param other reference for another itertator
     * @return
     */
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const MagicalContainer::SideCrossIterator &other)
    {
        // check if containers are equal
        if (container_.container_ != other.container_.container_) throw std::runtime_error("cant assign iterator on different container");

        // containers are equal so assign index
        index_ = other.index_;
        return *this;
    }


    // **** define function ****
    /**
     * @brief set iterator index at zero
     * @return iterator of the beginning of the container
     */
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const
    {
        return MagicalContainer::SideCrossIterator(this->container_);
    }

    /**
     * @brief set iterator index at nid index of the container
     * @return iterator of the beginning of the container
     */
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const
    {
        return MagicalContainer::SideCrossIterator(this->container_, this->container_.getAscContainer().size());
    }


//----------- PrimeIterator class ---------------------------------------
    // **** define constructors ****
    /**
     * @brief constructor
     * @param container reference for the Magical Container
     * @param index index of the iterator
     */
    MagicalContainer::PrimeIterator::PrimeIterator(ariel::MagicalContainer &container, std::size_t index): container_(container), index_(index) {}

    // **** define overload operators ***
    /**
     * @brief overload dereference operator
     * @return reference for the element at index
     */
    int& MagicalContainer::PrimeIterator::operator*()
    {
        return *container_.prime_container_.at(index_);
    }

    /**
     * @brief overload the pre increment operator
     * @return object of the iterator at incremented index
     */
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        // throw exception if increment over boundaries
        if(end().index_ == index_) throw std::runtime_error("cant increment beyond boundaries");

        ++index_;
        return *this;
    }

    /**
     * @brief overload equality operator
     * @param other reference for other primeIterator
     * @return bool that indicated if iterator at the same index
     */
    bool MagicalContainer::PrimeIterator::operator==(const MagicalContainer::PrimeIterator &other) const
    {
        return (this->index_ == other.index_);
    }

    /**
     * @brief overload inequality operator
     * @param other reference for other primeIterator
     * @return bool that indicated if iterator not at the same index
     */
    bool MagicalContainer::PrimeIterator::operator!=(const MagicalContainer::PrimeIterator &other) const
    {
        return !(*this == other);
    }

    /**
     * @brief overload < comparison
     * @param other reference for another iterator
     * @return bool that indicate comparison
     */
    bool MagicalContainer::PrimeIterator::operator<(const MagicalContainer::PrimeIterator &other) const
    {
        return (this->index_ < other.index_);
    }

    /**
     * @brief overload < comparison
     * @param other reference for another iterator
     * @return bool that indicate comparison
     */
    bool MagicalContainer::PrimeIterator::operator>(const MagicalContainer::PrimeIterator &other) const
    {
        return (this->index_ > other.index_);
    }

    /**
     * @brief assign iterator overload
     * @param other reference for another itertator
     * @return
     */
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const MagicalContainer::PrimeIterator &other)
    {
        // check if containers are equal
        if (container_.container_ != other.container_.container_) throw std::runtime_error("cant assign iterator on different container");

        // containers are equal so assign index
        index_ = other.index_;
        return *this;
    }

    /**
     * create instance of iterator at 0 index
     * @return instance of iterator at index 0
     */
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const
    {
        return MagicalContainer::PrimeIterator(this->container_);
    }

    /**
     * create instance of iterator at last index
     * @return instance of iterator at index last
     */
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const
    {
        return MagicalContainer::PrimeIterator(this->container_, this->container_.prime_container_.size());
    }

}
