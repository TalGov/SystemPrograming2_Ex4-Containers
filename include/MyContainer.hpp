//talgov44@gmail.com

#ifndef MYCONTAINER_HPP
#define MYCONTAINER_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <stdexcept>

namespace ariel
{
    template <typename T = int>

    class MyContainer
    {
        private:
            std::vector<T> container; // The container

        public:
            void addElement(const T& item);
            void removeElement(const T& item);
            int size() const;
            void print() const;

        // Ascending Order
        class AscendingOrder
        {
            private:
                std::vector<T> sorted_container; // A sorted copy of the container elements
                size_t index; // The current index in the container
                const MyContainer<T>* parent_container_ptr; // Pointer to the parent container for identity check

            public:
            /**
            Constructor
            Parameters:
                og_container - the original container to sort
                start - start index
                parent - pointer to the parent MyContainer instance
            Returns:
                -
            */
            AscendingOrder(const std::vector<T>& og_container, const MyContainer<T>* parent, size_t start = 0)
                : sorted_container(og_container), index(start), parent_container_ptr(parent)
            {
                std::sort(sorted_container.begin(), sorted_container.end()); // Sorting
            }
            
            /**
            This function returns the container's current size
            Parameters:
                none
            Returns:
                int - the size
            */
            int getContainerSize() const
            {
                return sorted_container.size();
            }

            /**
            This function checks if the index is not the given one
            *Const function
            Parameters:
                other - the second iterator to check the index from
            Returns:
                bool - if not the index of the given iterator
            */
            bool operator!=(const AscendingOrder& other) const
            {
                return (parent_container_ptr != other.parent_container_ptr) || (index != other.index);
            }

            /**
            This function checks if the index is equal to the given one
            *Const function
            Parameters:
                other - the second iterator to check the index from
            Returns:
                bool - if equal to the index of the given iterator
            */
            bool operator==(const AscendingOrder& other) const
            {
                return (parent_container_ptr == other.parent_container_ptr) && (index == other.index);
            }

            /**
            This function returns an item from its reference
            *Const function
            Parameters:
                none
            Returns:
                const T& - the item's value
            */
            const T& operator*() const
            {
                if (index >= sorted_container.size()) // Exception
                {
                    throw std::out_of_range("Invalid AscendingOrder dereference");
                }

                return sorted_container[index];
            }

            /**
            This function increases the current index by one
            Parameters:
                none
            Returns:
                AscendingOrder& - this iterator's reference
            */
            AscendingOrder& operator++()
            {
                ++index;
                return *this;
            }
        };

        /**
        This function returns an iterator to the first element of ascending order
        *Const function
        Parameters:
            none
        Returns:
            AscendingOrder - the iterator
        */
        AscendingOrder begin_ascending_order() const
        {
            return AscendingOrder(container, this);
        }

        /**
        This function returns an iterator to the last element of ascending order
        *Const function
        Parameters:
            none
        Returns:
            AscendingOrder - the iterator
        */
        AscendingOrder end_ascending_order() const
        {
            return AscendingOrder(container, this, container.size());
        }


        // Descending Order
        class DescendingOrder
        {
            private:
                std::vector<T> sorted_container; // A sorted copy of the container elements
                size_t index; // The current index in the container
                const MyContainer<T>* parent_container_ptr; // Pointer to the parent container for identity check

            public:
                /**
                Constructor
                Parameters:
                    og_container - the original container to sort
                    start - start index
                    parent - pointer to the parent MyContainer instance
                Returns:
                    -
                */
            DescendingOrder(const std::vector<T>& og_container, const MyContainer<T>* parent, size_t start = 0)
                : sorted_container(og_container), index(start), parent_container_ptr(parent)
            {
                std::sort(sorted_container.begin(), sorted_container.end(), std::greater<T>()); // Sorting
            }

            /**
            This function returns the container's current size
            Parameters:
                none
            Returns:
                int - the size
            */
            int getContainerSize() const
            {
                return sorted_container.size();
            }

            /**
            This function checks if the index is not the given one
            *Const function
            Parameters:
                other - the second iterator to check the index from
            Returns:
                bool - if not the index of the given iterator
            */
            bool operator!=(const DescendingOrder& other) const
            {
                return (parent_container_ptr != other.parent_container_ptr) || (index != other.index);
            }
            
            /**
            This function checks if the index is equal to the given one
            *Const function
            Parameters:
                other - the second iterator to check the index from
            Returns:
                bool - if equal to the index of the given iterator
            */
            bool operator==(const DescendingOrder& other) const
            {
                return (parent_container_ptr == other.parent_container_ptr) && (index == other.index);
            }

            /**
            This function returns an item from its reference
            *Const function
            Parameters:
                none
            Returns:
                const T& - the item's value
            */
            const T& operator*() const
            {
                if (index >= sorted_container.size()) // Exception
                {
                    throw std::out_of_range("Invalid DescendingOrder dereference");
                }

                return sorted_container[index];
            }

            /**
            This function increases the current index by one
            Parameters:
                none
            Returns:
                DescendingOrder& - this iterator's reference
            */
            DescendingOrder& operator++()
            {
                ++index;
                return *this;
            }
        };

        /**
        This function returns an iterator to the first element of descending order
        *Const function
        Parameters:
            none
        Returns:
            DescendingOrder - the iterator
        */
        DescendingOrder begin_descending_order() const
        {
            return DescendingOrder(container, this);
        }
        
        /**
        This function returns an iterator to the last element of descending order
        *Const function
        Parameters:
            none
        Returns:
            DescendingOrder - the iterator
        */
        DescendingOrder end_descending_order() const
        {
            return DescendingOrder(container, this, container.size());
        }


        // Side-Cross Order
        class SideCrossOrder
        {
            private:
                std::vector<T> sorted_container; // A sorted copy of the container elements
                size_t index; // The current index in the container
                const MyContainer<T>* parent_container_ptr; // Pointer to the parent container for identity check

            public:
                /**
                Constructor
                Parameters:
                    og_container - the original container to sort
                    parent - pointer to the parent MyContainer instance
                    is_end - if to put the iterator at the end of the container
                Returns:
                    -
                */
            SideCrossOrder(const std::vector<T>& og_container, const MyContainer<T>* parent, bool is_end = false)
                : index(0), parent_container_ptr(parent)
            {
                // Copying and sorting in ascending sort:
                std::vector<T> sorted = og_container;
                std::sort(sorted.begin(), sorted.end());

                size_t left = 0;
                size_t right = sorted.size() ? sorted.size() - 1 : 0;

                while (left <= right && left < sorted.size()) // Has more elements to check
                {
                    if (left == right) // One more element to add
                    {
                        sorted_container.push_back(sorted[left]);
                        break;
                    }

                    // Adding two elements (left and right) to the cotainer:
                    sorted_container.push_back(sorted[left]);
                    sorted_container.push_back(sorted[right]);
                    ++left;
                    --right;
                }

                if (is_end) // Put the iterator at the end of the container
                {
                    index = sorted_container.size();
                }
            }

            /**
            This function returns the container's current size
            Parameters:
                none
            Returns:
                int - the size
            */
            int getContainerSize() const
            {
                return sorted_container.size();
            }

            /**
            This function checks if the index is not the given one
            *Const function
            Parameters:
                other - the second iterator to check the index from
            Returns:
                bool - if not the index of the given iterator
            */
            bool operator!=(const SideCrossOrder& other) const
            {
                return (parent_container_ptr != other.parent_container_ptr) || (index != other.index);
            }

            /**
            This function checks if the index is equal to the given one
            *Const function
            Parameters:
                other - the second iterator to check the index from
            Returns:
                bool - if equal to the index of the given iterator
            */
            bool operator==(const SideCrossOrder& other) const
            {
                return (parent_container_ptr == other.parent_container_ptr) && (index == other.index);
            }
            
            /**
            This function returns an item from its reference
            *Const function
            Parameters:
                none
            Returns:
                const T& - the item's value
            */
            const T& operator*() const
            {
                if (index >= sorted_container.size()) // Exception
                {
                    throw std::out_of_range("Invalid SideCrossOrder dereference");
                }
                return sorted_container[index];
            }

            /**
            This function increases the current index by one
            Parameters:
                none
            Returns:
                SideCrossOrder& - this iterator's reference
            */
            SideCrossOrder& operator++()
            {
                ++index;
                return *this;
            }
        };

        /**
        This function returns an iterator to the first element of side-cross order
        *Const function
        Parameters:
            none
        Returns:
            SideCrossOrder - the iterator
        */
        SideCrossOrder begin_side_cross_order() const
        {
            return SideCrossOrder(container, this);
        }

        /**
        This function returns an iterator to the last element of side-cross order
        *Const function
        Parameters:
            none
        Returns:
            SideCrossOrder - the iterator
        */
        SideCrossOrder end_side_cross_order() const
        {
            return SideCrossOrder(container, this, true);
        }


        // Reverse Order
        class ReverseOrder
        {
            private:
                const std::vector<T>& og_container_ref; // A refrence to the originar container (const to block changes)
                size_t current_index; // The current index in the container
                const MyContainer<T>* parent_container_ptr; // Pointer to the parent container for identity check

            public:
                /**
                Constructor for begin (sets the iterator at the first element)
                Parameters:
                    og_container - the original container to sort
                    parent - pointer to the parent MyContainer instance
                Returns:
                    -
                */
            ReverseOrder(const std::vector<T>& og_container, const MyContainer<T>* parent)
                : og_container_ref(og_container), parent_container_ptr(parent)
            {
                current_index = og_container.empty() ? 0 : og_container.size() - 1;
            }

            /**
            Constructor for end (sets the iterator at the last element)
            Parameters:
                og_container - the original container to sort
                parent - pointer to the parent MyContainer instance
                bool - dummy to differ the constructors
            Returns:
                -
            */
            ReverseOrder(const std::vector<T>& og_container, const MyContainer<T>* parent, bool)
                : og_container_ref(og_container), current_index(og_container.size()), parent_container_ptr(parent) {}

            /**
            This function returns the container's current size
            Parameters:
                none
            Returns:
                int - the size
            */
            int getContainerSize() const
            {
                return og_container_ref.size();
            }
            
            /**
            This function checks if the index is not the given one
            *Const function
            Parameters:
                other - the second iterator to check the index from
            Returns:
                bool - if not the index of the given iterator
            */
            bool operator!=(const ReverseOrder& other) const
            {
                return (parent_container_ptr != other.parent_container_ptr) || (current_index != other.current_index);
            }
            
            /**
            This function checks if the index is equal to the given one
            *Const function
            Parameters:
                other - the second iterator to check the index from
            Returns:
                bool - if equal to the index of the given iterator
            */
            bool operator==(const ReverseOrder& other) const
            {
                return (parent_container_ptr == other.parent_container_ptr) && (current_index == other.current_index);
            }
            
            /**
            This function returns an item from its reference
            *Const function
            Parameters:
                none
            Returns:
                const T& - the item's value
            */
            const T& operator*() const
            {
                if (current_index >= og_container_ref.size()) // Exception
                {
                    throw std::out_of_range("Invalid ReverseOrder dereference");
                }

                return og_container_ref[current_index];
            }

            /**
            This function increases the current index by one
            Parameters:
                none
            Returns:
                ReverseOrder& - this iterator's reference
            */
            ReverseOrder& operator++()
            {
                if (og_container_ref.empty() || current_index == 0)
                    current_index = og_container_ref.size();
                else
                    --current_index;
                return *this;
            }
        };

        /**
        This function returns an iterator to the first element of reverse order
        *Const function
        Parameters:
            none
        Returns:
            ReverseOrder - the iterator
        */
        ReverseOrder begin_reverse_order() const
        {
            return ReverseOrder(container, this);
        }

        /**
        This function returns an iterator to the last element of reverse order
        *Const function
        Parameters:
            none
        Returns:
            ReverseOrder - the iterator
        */
        ReverseOrder end_reverse_order() const
        {
            return ReverseOrder(container, this, true);
        }


        // Regular Order (Itaration with no change)
        class Order
        {
            private:
                const std::vector<T>& og_container_ref; // A refrence to the originar container (const to block changes)
                size_t index; // The current index in the container
                const MyContainer<T>* parent_container_ptr; // Pointer to the parent container for identity check

            public:
                /**
                Constructor
                Parameters:
                    og_container - the original container
                    start - start index
                    parent - pointer to the parent MyContainer instance
                Returns:
                    -
                */
            Order(const std::vector<T>& og_container, const MyContainer<T>* parent, size_t start = 0)
                : og_container_ref(og_container), index(start), parent_container_ptr(parent) {}

            /**
            This function returns the container's current size
            Parameters:
                none
            Returns:
                int - the size
            */
            int getContainerSize() const
            {
                return og_container_ref.size();
            }

            /**
            This function checks if the index is not the given one
            *Const function
            Parameters:
                other - the second iterator to check the index from
            Returns:
                bool - if not the index of the given iterator
            */
            bool operator!=(const Order& other) const
            {
                return (parent_container_ptr != other.parent_container_ptr) || (index != other.index);
            }

            /**
            This function checks if the index is equal to the given one
            *Const function
            Parameters:
                other - the second iterator to check the index from
            Returns:
                bool - if equal to the index of the given iterator
            */
            bool operator==(const Order& other) const
            {
                return (parent_container_ptr == other.parent_container_ptr) && (index == other.index);
            }

            /**
            This function returns an item from its reference
            *Const function
            Parameters:
                none
            Returns:
                const T& - the item's value
            */
            const T& operator*() const
            {
                if (index >= og_container_ref.size()) // Exception
                {
                    throw std::out_of_range("Invalid Order dereference");
                }

                return og_container_ref[index];
            }

            /**
            This function increases the current index by one
            Parameters:
                none
            Returns:
                Order& - this iterator's reference
            */
            Order& operator++()
            {
                ++index;
                return *this;
            }
        };

        /**
        This function returns an iterator to the first element of regular order
        *Const function
        Parameters:
            none
        Returns:
            Order - the iterator
        */
        Order begin_order() const
        {
            return Order(container, this);
        }

        /**
        This function returns an iterator to the last element of regular order
        *Const function
        Parameters:
            none
        Returns:
            Order - the iterator
        */
        Order end_order() const
        {
            return Order(container, this, container.size());
        }

        /**
        This function overrides the default for loop begin (element : vector)
        *Const function
        Parameters:
            none
        Returns:
            Order - an iterator of the first element
        */
        Order begin() const
        {
            return begin_order();
        }

        /**
        This function overrides the default for loop begin (element : vector)
        *Const function
        Parameters:
            none
        Returns:
            Order - an iterator of the last element
        */
        Order end() const
        {
            return end_order();
        }


        // Middle-Out Order
        class MiddleOutOrder
        {
            private:
                std::vector<T> sorted_container; // A sorted copy of the container elements
                size_t index; // The current index in the container
                const MyContainer<T>* parent_container_ptr; // Pointer to the parent container for identity check

            public:
                /**
                Constructor
                Parameters:
                    og_container - the original container to sort
                    parent - pointer to the parent MyContainer instance
                    start - start index
                Returns:
                    -
                */
            MiddleOutOrder(const std::vector<T>& og_container, const MyContainer<T>* parent, size_t start = 0)
                : index(start), parent_container_ptr(parent)
            {
                std::vector<T> sorted = og_container;
                std::sort(sorted.begin(), sorted.end());

                if (sorted.empty()) // Empty
                {
                    return;
                }

                if (sorted.size() % 2 != 0) // Odd number of elements
                { 
                    int mid_idx = sorted.size() / 2;
                    sorted_container.push_back(sorted[mid_idx]);

                    for (int offset = 1; ; ++offset) 
                    {
                        bool added = false;
                        if (mid_idx - offset >= 0) 
                        {
                            sorted_container.push_back(sorted[mid_idx - offset]);
                            added = true;
                        }

                        if (mid_idx + offset < static_cast<int>(sorted.size())) 
                        {
                            sorted_container.push_back(sorted[mid_idx + offset]);
                            added = true;
                        }

                        if (!added) break;
                    }
                }
                else // Even number of elements
                { 
                    int mid_right_idx = sorted.size() / 2;
                    int mid_left_idx = mid_right_idx - 1;
                    
                    sorted_container.push_back(sorted[mid_left_idx]);
                    sorted_container.push_back(sorted[mid_right_idx]);

                    for (int offset = 1; ; ++offset) 
                    {
                        bool added = false;

                        if (mid_left_idx - offset >= 0) 
                        {
                            sorted_container.push_back(sorted[mid_left_idx - offset]);
                            added = true;
                        }

                        if (mid_right_idx + offset < static_cast<int>(sorted.size())) 
                        {
                            sorted_container.push_back(sorted[mid_right_idx + offset]);
                            added = true;
                        }

                        if (!added) break;
                    }
                }
            }

            /**
            This function returns the container's current size
            Parameters:
                none
            Returns:
                int - the size
            */
            int getContainerSize() const
            {
                return sorted_container.size();
            }

            /**
            This function checks if the index is not the given one
            *Const function
            Parameters:
                other - the second iterator to check the index from
            Returns:
                bool - if not the index of the given iterator
            */
            bool operator!=(const MiddleOutOrder& other) const
            {
                return (parent_container_ptr != other.parent_container_ptr) || (index != other.index);
            }

            /**
            This function checks if the index is equal to the given one
            *Const function
            Parameters:
                other - the second iterator to check the index from
            Returns:
                bool - if equal to the index of the given iterator
            */
            bool operator==(const MiddleOutOrder& other) const
            {
                return (parent_container_ptr == other.parent_container_ptr) && (index == other.index);
            }

            /**
            This function returns an item from its reference
            *Const function
            Parameters:
                none
            Returns:
                const T& - the item's value
            */
            const T& operator*() const
            {
                if (index >= sorted_container.size()) // Exception
                {
                    throw std::out_of_range("Invalid MiddleOutOrder dereference");
                }

                return sorted_container[index];
            }

            /**
            This function increases the current index by one
            Parameters:
                none
            Returns:
                MiddleOutOrder& - this iterator's reference
            */
            MiddleOutOrder& operator++()
            {
                ++index;
                return *this;
            }
        };

        /**
        This function returns an iterator to the first element of middle-out order
        *Const function
        Parameters:
            none
        Returns:
            MiddleOutOrder - the iterator
        */
        MiddleOutOrder begin_middle_out_order() const
        {
            return MiddleOutOrder(container, this);
        }

        /**
        This function returns an iterator to the last element of middle-out order
        *Const function
        Parameters:
            none
        Returns:
            MiddleOutOrder - the iterator
        */
        MiddleOutOrder end_middle_out_order() const
        {
            MiddleOutOrder temp(container, this);
            return MiddleOutOrder(container, this, temp.getContainerSize());
        }
    };

    /**
    This function adds an element to the container
    Parameters:
        item - the element
    Returns:
        none
    */
    template <typename T>
    void MyContainer<T>::addElement(const T& item)
    {
        container.push_back(item);
    }

    /**
    This function removes an element from the container
    Parameters:
        item - the element
    Returns:
        none
    */
    template <typename T>
    void MyContainer<T>::removeElement(const T& item)
    {
        auto new_end = std::remove(container.begin(), container.end(), item);

        if (new_end == container.end() && std::find(container.begin(), container.end(), item) == container.end()) // Exception
        {
            throw std::invalid_argument("No such item in the container");
        }

        container.erase(new_end, container.end());
    }

    /**
    This function returns the size of the container
    Parameters:
        none
    Returns:
        int - the size
    */
    template <typename T>
    int MyContainer<T>::size() const
    {
        return container.size();
    }

    /**
    This function prints the container
    Parameters:
        none
    Returns:
        none
    */
    template <typename T>
    void MyContainer<T>::print() const
    {
        for (size_t i = 0; i < container.size(); ++i)
        {
            if (i != 0)
            {
                std::cout << " ";
            }
            
            std::cout << container[i];
        }

        std::cout << std::endl;
    }

}

#endif