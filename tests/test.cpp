//talgov44@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "MyContainer.hpp"

#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <sstream>

using namespace std;

/*
This function converts MyContainer to vector for easy comparison
Parameters:
    container - the container
Returns:
    vector<T> - the new vector
*/
template <typename T>
vector<T> containerToVector(const ariel::MyContainer<T>& container)
{
    vector<T> vec;

    for (const T& item : container)
    {
        vec.push_back(item);
    }

    return vec;
}

/*
This function convert an iterator range to vector for easy comparison
Parameters:
    begin_it - the beginning iterator
    end_it - the ending iterator
Returns:
    vector<T> - the new vector
*/
template <typename IteratorType, typename T>
vector<T> iteratorToVector(IteratorType begin_it, IteratorType end_it)
{
    vector<T> vec;

    for (IteratorType it = begin_it; it != end_it; ++it)
    {
        vec.push_back(*it);
    }

    return vec;
}


TEST_CASE("MyContainer<int> Core Operations")
{
    ariel::MyContainer<int> intContainer;

    SUBCASE("addElement_EmptyContainer")
    {// Checking if the array is empty
        intContainer.addElement(10);
        CHECK(intContainer.size() == 1);// Checking container size after adding one element
        CHECK(containerToVector(intContainer) == vector<int>{10});// Checking content after adding one element
    }

    SUBCASE("addElement_MultipleElements")
    {// Checking if multiple elements can be added
        intContainer.addElement(1);
        intContainer.addElement(2);
        intContainer.addElement(3);
        CHECK(intContainer.size() == 3);// Checking container size after adding multiple elements
        CHECK(containerToVector(intContainer) == vector<int>{1, 2, 3});// Checking content after adding multiple elements
    }

    SUBCASE("addElement_DuplicateElements")
    {// Checking if duplicate elements can be added
        intContainer.addElement(5);
        intContainer.addElement(10);
        intContainer.addElement(5);
        CHECK(intContainer.size() == 3);// Checking container size with duplicates
        CHECK(containerToVector(intContainer) == vector<int>{5, 10, 5});// Checking content with duplicates
    }

    SUBCASE("addElement_LargeNumberOfElements")
    {// Checking if a large number of elements can be added
        for (int i = 0; i < 1000; ++i) {
            intContainer.addElement(i);
        }
        CHECK(intContainer.size() == 1000);// Checking size after adding 1000 elements
        vector<int> expected(1000);
        for (int i = 0; i < 1000; ++i) {
            expected[i] = i;
        }
        CHECK(containerToVector(intContainer) == expected);// Checking content after adding 1000 elements
    }

    SUBCASE("removeElement_OnlyElement")
    {// Checking if the only element can be removed
        intContainer.addElement(100);
        intContainer.removeElement(100);
        CHECK(intContainer.size() == 0);// Checking size after removing the only element
        CHECK(containerToVector(intContainer).empty());// Checking if container is empty
    }

    SUBCASE("removeElement_FirstElement")
    {// Checking if the first element can be removed
        intContainer.addElement(1);
        intContainer.addElement(2);
        intContainer.addElement(3);
        intContainer.removeElement(1);
        CHECK(intContainer.size() == 2);// Checking size after removing first element
        CHECK(containerToVector(intContainer) == vector<int>{2, 3});// Checking content after removing first element
    }

    SUBCASE("removeElement_LastElement")
    {// Checking if the last element can be removed
        intContainer.addElement(1);
        intContainer.addElement(2);
        intContainer.addElement(3);
        intContainer.removeElement(3);
        CHECK(intContainer.size() == 2);// Checking size after removing last element
        CHECK(containerToVector(intContainer) == vector<int>{1, 2});// Checking content after removing last element
    }

    SUBCASE("removeElement_MiddleElement")
    {// Checking if a middle element can be removed
        intContainer.addElement(1);
        intContainer.addElement(2);
        intContainer.addElement(3);
        intContainer.removeElement(2);
        CHECK(intContainer.size() == 2);// Checking size after removing middle element
        CHECK(containerToVector(intContainer) == vector<int>{1, 3});// Checking content after removing middle element
    }

    SUBCASE("removeElement_MultipleOccurrences")
    {// Checking if multiple occurrences of an element can be removed
        intContainer.addElement(1);
        intContainer.addElement(2);
        intContainer.addElement(1);
        intContainer.addElement(3);
        intContainer.addElement(1);
        intContainer.removeElement(1);
        CHECK(intContainer.size() == 2);// Checking size after removing multiple occurrences
        CHECK(containerToVector(intContainer) == vector<int>{2, 3});// Checking content after removing multiple occurrences
    }

    SUBCASE("removeElement_FromEmptyContainerThrows")
    {// Checking if removing from an empty container throws an exception
        CHECK(intContainer.size() == 0);// Checking initial empty size
        CHECK_THROWS_AS(intContainer.removeElement(5), invalid_argument);// Checking if invalid_argument is thrown
    }

    SUBCASE("removeElement_NonExistentElementThrows")
    {// Checking if removing a non-existent element throws an exception
        intContainer.addElement(1);
        intContainer.addElement(2);
        CHECK_THROWS_AS(intContainer.removeElement(99), invalid_argument);// Checking if invalid_argument is thrown for non-existent element
        CHECK(intContainer.size() == 2);// Checking that container size is unchanged
        CHECK(containerToVector(intContainer) == vector<int>{1, 2});// Checking that container content is unchanged
    }

    SUBCASE("removeElement_RemoveAllElements")
    {// Checking if all elements can be removed
        intContainer.addElement(1);
        intContainer.addElement(2);
        intContainer.addElement(3);
        intContainer.removeElement(1);
        intContainer.removeElement(2);
        intContainer.removeElement(3);
        CHECK(intContainer.size() == 0);// Checking size after all elements are removed
        CHECK(containerToVector(intContainer).empty());// Checking if container is empty
    }

    SUBCASE("size_AfterAddsAndRemoves")
    {// Checking container size after various operations
        CHECK(intContainer.size() == 0);// Checking initial empty size
        intContainer.addElement(10);
        CHECK(intContainer.size() == 1);// Checking size after 1 add
        intContainer.addElement(20);
        intContainer.addElement(30);
        CHECK(intContainer.size() == 3);// Checking size after 3 adds
        intContainer.removeElement(20);
        CHECK(intContainer.size() == 2);// Checking size after 1 remove
        intContainer.removeElement(10);
        intContainer.removeElement(30);
        CHECK(intContainer.size() == 0);// Checking size after all removed
    }

    SUBCASE("print_EmptyContainer")
    {// Checking print for an empty container
        stringstream ss;
        streambuf* oldCout = cout.rdbuf(); // Save old cout buffer
        cout.rdbuf(ss.rdbuf()); // Redirect cout to stringstream

        intContainer.print();
        cout.rdbuf(oldCout); // Restore old cout buffer
        CHECK(ss.str() == "\n");//Expect just a newline for empty container print
    }

    SUBCASE("print_SingleElementContainer")
    {// Checking print for a single element container
        intContainer.addElement(123);
        stringstream ss;
        streambuf* oldCout = cout.rdbuf();
        cout.rdbuf(ss.rdbuf());

        intContainer.print();
        cout.rdbuf(oldCout);
        CHECK(ss.str() == "123\n");//Expect single element followed by newline
    }

    SUBCASE("print_MultiElementContainer")
    {// Checking print for a multi-element container
        intContainer.addElement(1);
        intContainer.addElement(2);
        intContainer.addElement(3);
        stringstream ss;
        streambuf* oldCout = cout.rdbuf();
        cout.rdbuf(ss.rdbuf());

        intContainer.print();
        cout.rdbuf(oldCout);
        CHECK(ss.str() == "1 2 3\n");//Expect space-separated elements followed by newline
    }
}

TEST_CASE("MyContainer<int> Iterator Edge Cases")
{
    SUBCASE("AscendingOrder_EmptyContainer")
    {// Checking AscendingOrder iterator for an empty container
        ariel::MyContainer<int> emptyContainer;
        auto it = emptyContainer.begin_ascending_order();
        auto end_it = emptyContainer.end_ascending_order();
        CHECK(it == end_it);// Checking if begin equals end for empty container
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing begin() of empty container throws
        CHECK(it.getContainerSize() == 0); // Check getContainerSize for empty container
    }

    SUBCASE("AscendingOrder_SingleElement")
    {// Checking AscendingOrder iterator for a single element container
        ariel::MyContainer<int> container;
        container.addElement(50);
        auto it = container.begin_ascending_order();
        auto end_it = container.end_ascending_order();
        CHECK(*it == 50);// Checking value of the single element
        CHECK(it.getContainerSize() == 1); // Check getContainerSize for single element
        ++it;
        CHECK(it == end_it);// Checking if iterator reaches end after increment
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing past-the-end throws
    }

    SUBCASE("AscendingOrder_MultipleElements")
    {// Checking AscendingOrder iterator for multiple elements
        ariel::MyContainer<int> container;
        container.addElement(30);
        container.addElement(10);
        container.addElement(20);
        vector<int> expected = {10, 20, 30};
        CHECK(iteratorToVector<ariel::MyContainer<int>::AscendingOrder, int>(container.begin_ascending_order(), container.end_ascending_order()) == expected);// Checking full ascending order
        CHECK(container.begin_ascending_order().getContainerSize() == 3); // Check getContainerSize
    }

    SUBCASE("AscendingOrder_WithDuplicates")
    {// Checking AscendingOrder iterator with duplicate elements
        ariel::MyContainer<int> container;
        container.addElement(5);
        container.addElement(1);
        container.addElement(5);
        container.addElement(2);
        vector<int> expected = {1, 2, 5, 5};
        CHECK(iteratorToVector<ariel::MyContainer<int>::AscendingOrder, int>(container.begin_ascending_order(), container.end_ascending_order()) == expected);// Checking ascending order with duplicates
    }

    SUBCASE("DescendingOrder_EmptyContainer")
    {// Checking DescendingOrder iterator for an empty container
        ariel::MyContainer<int> emptyContainer;
        auto it = emptyContainer.begin_descending_order();
        auto end_it = emptyContainer.end_descending_order();
        CHECK(it == end_it);// Checking if begin equals end for empty container
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing begin() of empty container throws
        CHECK(it.getContainerSize() == 0); // Check getContainerSize for empty container
    }

    SUBCASE("DescendingOrder_SingleElement")
    {// Checking DescendingOrder iterator for a single element container
        ariel::MyContainer<int> container;
        container.addElement(50);
        auto it = container.begin_descending_order();
        auto end_it = container.end_descending_order();
        CHECK(*it == 50);// Checking value of the single element
        CHECK(it.getContainerSize() == 1); // Check getContainerSize for single element
        ++it;
        CHECK(it == end_it);// Checking if iterator reaches end after increment
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing past-the-end throws
    }

    SUBCASE("DescendingOrder_MultipleElements")
    {// Checking DescendingOrder iterator for multiple elements
        ariel::MyContainer<int> container;
        container.addElement(30);
        container.addElement(10);
        container.addElement(20);
        vector<int> expected = {30, 20, 10};
        CHECK(iteratorToVector<ariel::MyContainer<int>::DescendingOrder, int>(container.begin_descending_order(), container.end_descending_order()) == expected);// Checking full descending order
        CHECK(container.begin_descending_order().getContainerSize() == 3); // Check getContainerSize
    }

    SUBCASE("DescendingOrder_WithDuplicates")
    {// Checking DescendingOrder iterator with duplicate elements
        ariel::MyContainer<int> container;
        container.addElement(5);
        container.addElement(1);
        container.addElement(5);
        container.addElement(2);
        vector<int> expected = {5, 5, 2, 1};
        CHECK(iteratorToVector<ariel::MyContainer<int>::DescendingOrder, int>(container.begin_descending_order(), container.end_descending_order()) == expected);// Checking descending order with duplicates
    }

    SUBCASE("SideCrossOrder_EmptyContainer")
    {// Checking SideCrossOrder iterator for an empty container
        ariel::MyContainer<int> emptyContainer;
        auto it = emptyContainer.begin_side_cross_order();
        auto end_it = emptyContainer.end_side_cross_order();
        CHECK(it == end_it);// Checking if begin equals end for empty container
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing begin() of empty container throws
        CHECK(it.getContainerSize() == 0); // Check getContainerSize for empty container
    }

    SUBCASE("SideCrossOrder_SingleElement")
    {// Checking SideCrossOrder iterator for a single element container
        ariel::MyContainer<int> container;
        container.addElement(50);
        auto it = container.begin_side_cross_order();
        auto end_it = container.end_side_cross_order();
        CHECK(*it == 50);// Checking value of the single element
        CHECK(it.getContainerSize() == 1); // Check getContainerSize for single element
        ++it;
        CHECK(it == end_it);// Checking if iterator reaches end after increment
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing past-the-end throws
    }

    SUBCASE("SideCrossOrder_EvenNumberOfElements")
    {// Checking SideCrossOrder iterator for an even number of elements
        ariel::MyContainer<int> container;
        container.addElement(10);
        container.addElement(40);
        container.addElement(20);
        container.addElement(30);
        // Sorted: 10, 20, 30, 40
        // Expected side-cross: 10, 40, 20, 30
        vector<int> expected = {10, 40, 20, 30};
        CHECK(iteratorToVector<ariel::MyContainer<int>::SideCrossOrder, int>(container.begin_side_cross_order(), container.end_side_cross_order()) == expected);// Checking side-cross order for even elements
        CHECK(container.begin_side_cross_order().getContainerSize() == 4); // Check getContainerSize
    }

    SUBCASE("SideCrossOrder_OddNumberOfElements")
    {// Checking SideCrossOrder iterator for an odd number of elements
        ariel::MyContainer<int> container;
        container.addElement(50);
        container.addElement(10);
        container.addElement(40);
        container.addElement(20);
        container.addElement(30);
        // Sorted: 10, 20, 30, 40, 50
        // Expected side-cross: 10, 50, 20, 40, 30
        vector<int> expected = {10, 50, 20, 40, 30};
        CHECK(iteratorToVector<ariel::MyContainer<int>::SideCrossOrder, int>(container.begin_side_cross_order(), container.end_side_cross_order()) == expected);// Checking side-cross order for odd elements
        CHECK(container.begin_side_cross_order().getContainerSize() == 5); // Check getContainerSize
    }

    SUBCASE("SideCrossOrder_WithDuplicates")
    {// Checking SideCrossOrder iterator with duplicate elements
        ariel::MyContainer<int> container;
        container.addElement(5);
        container.addElement(1);
        container.addElement(5);
        container.addElement(2);
        // Sorted: 1, 2, 5, 5
        // Expected side-cross: 1, 5, 2, 5
        vector<int> expected = {1, 5, 2, 5};
        CHECK(iteratorToVector<ariel::MyContainer<int>::SideCrossOrder, int>(container.begin_side_cross_order(), container.end_side_cross_order()) == expected);// Checking side-cross order with duplicates
    }

    SUBCASE("ReverseOrder_EmptyContainer")
    {// Checking ReverseOrder iterator for an empty container
        ariel::MyContainer<int> emptyContainer;
        auto it = emptyContainer.begin_reverse_order();
        auto end_it = emptyContainer.end_reverse_order();
        CHECK(it == end_it);// Checking if begin equals end for empty container
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing begin() of empty container throws
        CHECK(it.getContainerSize() == 0); // Check getContainerSize for empty container
    }

    SUBCASE("ReverseOrder_SingleElement")
    {// Checking ReverseOrder iterator for a single element container
        ariel::MyContainer<int> container;
        container.addElement(50);
        auto it = container.begin_reverse_order();
        auto end_it = container.end_reverse_order();
        CHECK(*it == 50);// Checking value of the single element
        CHECK(it.getContainerSize() == 1); // Check getContainerSize for single element
        ++it;
        CHECK(it == end_it);// Checking if iterator reaches end after increment
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing past-the-end throws
    }

    SUBCASE("ReverseOrder_MultipleElements")
    {// Checking ReverseOrder iterator for multiple elements
        ariel::MyContainer<int> container;
        container.addElement(10);
        container.addElement(20);
        container.addElement(30);
        vector<int> expected = {30, 20, 10}; // Original order reversed
        CHECK(iteratorToVector<ariel::MyContainer<int>::ReverseOrder, int>(container.begin_reverse_order(), container.end_reverse_order()) == expected);// Checking full reverse order
        CHECK(container.begin_reverse_order().getContainerSize() == 3); // Check getContainerSize
    }

    SUBCASE("ReverseOrder_WithDuplicates")
    {// Checking ReverseOrder iterator with duplicate elements
        ariel::MyContainer<int> container;
        container.addElement(1);
        container.addElement(2);
        container.addElement(1);
        container.addElement(3);
        vector<int> expected = {3, 1, 2, 1}; // Original order reversed
        CHECK(iteratorToVector<ariel::MyContainer<int>::ReverseOrder, int>(container.begin_reverse_order(), container.end_reverse_order()) == expected);// Checking reverse order with duplicates
    }

    SUBCASE("Order_EmptyContainer")
    {// Checking Order iterator for an empty container
        ariel::MyContainer<int> emptyContainer;
        auto it = emptyContainer.begin_order();
        auto end_it = emptyContainer.end_order();
        CHECK(it == end_it);// Checking if begin equals end for empty container
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing begin() of empty container throws
        CHECK(it.getContainerSize() == 0); // Check getContainerSize for empty container
    }

    SUBCASE("Order_SingleElement")
    {// Checking Order iterator for a single element container
        ariel::MyContainer<int> container;
        container.addElement(50);
        auto it = container.begin_order();
        auto end_it = container.end_order();
        CHECK(*it == 50);// Checking value of the single element
        CHECK(it.getContainerSize() == 1); // Check getContainerSize for single element
        ++it;
        CHECK(it == end_it);// Checking if iterator reaches end after increment
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing past-the-end throws
    }

    SUBCASE("Order_MultipleElements")
    {// Checking Order iterator for multiple elements
        ariel::MyContainer<int> container;
        container.addElement(10);
        container.addElement(20);
        container.addElement(30);
        vector<int> expected = {10, 20, 30}; // Original insertion order
        CHECK(iteratorToVector<ariel::MyContainer<int>::Order, int>(container.begin_order(), container.end_order()) == expected);// Checking full original order
        CHECK(container.begin_order().getContainerSize() == 3); // Check getContainerSize
    }

    SUBCASE("Order_WithDuplicates")
    {// Checking Order iterator with duplicate elements
        ariel::MyContainer<int> container;
        container.addElement(1);
        container.addElement(2);
        container.addElement(1);
        container.addElement(3);
        vector<int> expected = {1, 2, 1, 3}; // Original insertion order
        CHECK(iteratorToVector<ariel::MyContainer<int>::Order, int>(container.begin_order(), container.end_order()) == expected);// Checking original order with duplicates
    }

    SUBCASE("MiddleOutOrder_EmptyContainer")
    {// Checking MiddleOutOrder iterator for an empty container
        ariel::MyContainer<int> emptyContainer;
        auto it = emptyContainer.begin_middle_out_order();
        auto end_it = emptyContainer.end_middle_out_order();
        CHECK(it == end_it);// Checking if begin equals end for empty container
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing begin() of empty container throws
        CHECK(it.getContainerSize() == 0); // Check getContainerSize for empty container
    }

    SUBCASE("MiddleOutOrder_SingleElement")
    {// Checking MiddleOutOrder iterator for a single element container
        ariel::MyContainer<int> container;
        container.addElement(50);
        auto it = container.begin_middle_out_order();
        auto end_it = container.end_middle_out_order();
        CHECK(*it == 50);// Checking value of the single element
        CHECK(it.getContainerSize() == 1); // Check getContainerSize for single element
        ++it;
        CHECK(it == end_it);// Checking if iterator reaches end after increment
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing past-the-end throws
    }

    SUBCASE("MiddleOutOrder_EvenNumberOfElements")
    {// Checking MiddleOutOrder iterator for an even number of elements
        ariel::MyContainer<int> container;
        container.addElement(10);
        container.addElement(40);
        container.addElement(20);
        container.addElement(30);
        // Sorted: 10, 20, 30, 40
        // Expected middle-out: 20, 30, 10, 40
        vector<int> expected = {20, 30, 10, 40};
        CHECK(iteratorToVector<ariel::MyContainer<int>::MiddleOutOrder, int>(container.begin_middle_out_order(), container.end_middle_out_order()) == expected);// Checking middle-out order for even elements
        CHECK(container.begin_middle_out_order().getContainerSize() == 4); // Check getContainerSize
    }

    SUBCASE("MiddleOutOrder_OddNumberOfElements")
    {// Checking MiddleOutOrder iterator for an odd number of elements
        ariel::MyContainer<int> container;
        container.addElement(50);
        container.addElement(10);
        container.addElement(40);
        container.addElement(20);
        container.addElement(30);
        // Sorted: 10, 20, 30, 40, 50
        // Middle is 30. Output: 30, 20, 40, 10, 50
        vector<int> expected = {30, 20, 40, 10, 50};
        CHECK(iteratorToVector<ariel::MyContainer<int>::MiddleOutOrder, int>(container.begin_middle_out_order(), container.end_middle_out_order()) == expected);// Checking middle-out order for odd elements
        CHECK(container.begin_middle_out_order().getContainerSize() == 5); // Check getContainerSize
    }

    SUBCASE("MiddleOutOrder_WithDuplicates")
    {// Checking MiddleOutOrder iterator with duplicate elements
        ariel::MyContainer<int> container;
        container.addElement(5);
        container.addElement(1);
        container.addElement(5);
        container.addElement(2);
        // Sorted: 1, 2, 5, 5
        // Middle is between 2 and 5 (first 5). Output: 2, 5, 1, 5
        vector<int> expected = {2, 5, 1, 5};
        CHECK(iteratorToVector<ariel::MyContainer<int>::MiddleOutOrder, int>(container.begin_middle_out_order(), container.end_middle_out_order()) == expected);// Checking middle-out order with duplicates
    }
}

TEST_CASE("MyContainer<double> Iterator Edge Cases")
{
    double epsilon = numeric_limits<double>::epsilon(); // For floating point comparisons

    SUBCASE("AscendingOrder_EmptyContainer_Double")
    {// Checking AscendingOrder iterator for an empty double container
        ariel::MyContainer<double> emptyContainer;
        auto it = emptyContainer.begin_ascending_order();
        auto end_it = emptyContainer.end_ascending_order();
        CHECK(it == end_it);// Checking if begin equals end for empty double container
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing begin() of empty double container throws
        CHECK(it.getContainerSize() == 0); // Check getContainerSize for empty double container
    }

    SUBCASE("AscendingOrder_SingleElement_Double")
    {// Checking AscendingOrder iterator for a single double element container
        ariel::MyContainer<double> container;
        container.addElement(3.14);
        auto it = container.begin_ascending_order();
        auto end_it = container.end_ascending_order();
        CHECK(*it == doctest::Approx(3.14).epsilon(epsilon));// Checking value of the single double element
        CHECK(it.getContainerSize() == 1); // Check getContainerSize for single double element
        ++it;
        CHECK(it == end_it);// Checking if iterator reaches end after increment
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing past-the-end throws
    }

    SUBCASE("AscendingOrder_MultipleElements_Double")
    {// Checking AscendingOrder iterator for multiple double elements
        ariel::MyContainer<double> container;
        container.addElement(2.2);
        container.addElement(1.1);
        container.addElement(3.3);
        vector<double> expected = {1.1, 2.2, 3.3};
        vector<double> actual = iteratorToVector<ariel::MyContainer<double>::AscendingOrder, double>(container.begin_ascending_order(), container.end_ascending_order());
        CHECK(actual.size() == expected.size());// Checking size of actual vs expected
        for (size_t i = 0; i < actual.size(); ++i) {
            CHECK(actual[i] == doctest::Approx(expected[i]).epsilon(epsilon));// Checking individual elements with approx
        }
        CHECK(container.begin_ascending_order().getContainerSize() == 3); // Check getContainerSize
    }

    SUBCASE("DescendingOrder_EmptyContainer_Double")
    {// Checking DescendingOrder iterator for an empty double container
        ariel::MyContainer<double> emptyContainer;
        auto it = emptyContainer.begin_descending_order();
        auto end_it = emptyContainer.end_descending_order();
        CHECK(it == end_it);// Checking if begin equals end for empty double container
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing begin() of empty double container throws
        CHECK(it.getContainerSize() == 0); // Check getContainerSize for empty double container
    }

    SUBCASE("DescendingOrder_SingleElement_Double")
    {// Checking DescendingOrder iterator for a single double element container
        ariel::MyContainer<double> container;
        container.addElement(1.0);
        auto it = container.begin_descending_order();
        auto end_it = container.end_descending_order();
        CHECK(*it == doctest::Approx(1.0).epsilon(epsilon));// Checking value of the single double element
        CHECK(it.getContainerSize() == 1); // Check getContainerSize for single double element
        ++it;
        CHECK(it == end_it);// Checking if iterator reaches end after increment
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing past-the-end throws
    }

    SUBCASE("DescendingOrder_MultipleElements_Double")
    {// Checking DescendingOrder iterator for multiple double elements
        ariel::MyContainer<double> container;
        container.addElement(2.2);
        container.addElement(1.1);
        container.addElement(3.3);
        vector<double> expected = {3.3, 2.2, 1.1};
        vector<double> actual = iteratorToVector<ariel::MyContainer<double>::DescendingOrder, double>(container.begin_descending_order(), container.end_descending_order());
        CHECK(actual.size() == expected.size());// Checking size of actual vs expected
        for (size_t i = 0; i < actual.size(); ++i) {
            CHECK(actual[i] == doctest::Approx(expected[i]).epsilon(epsilon));// Checking individual elements with approx
        }
        CHECK(container.begin_descending_order().getContainerSize() == 3); // Check getContainerSize
    }

    SUBCASE("SideCrossOrder_EmptyContainer_Double")
    {// Checking SideCrossOrder iterator for an empty double container
        ariel::MyContainer<double> emptyContainer;
        auto it = emptyContainer.begin_side_cross_order();
        auto end_it = emptyContainer.end_side_cross_order();
        CHECK(it == end_it);// Checking if begin equals end for empty double container
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing begin() of empty double container throws
        CHECK(it.getContainerSize() == 0); // Check getContainerSize for empty double container
    }

    SUBCASE("SideCrossOrder_SingleElement_Double")
    {// Checking SideCrossOrder iterator for a single double element container
        ariel::MyContainer<double> container;
        container.addElement(7.7);
        auto it = container.begin_side_cross_order();
        auto end_it = container.end_side_cross_order();
        CHECK(*it == doctest::Approx(7.7).epsilon(epsilon));// Checking value of the single double element
        CHECK(it.getContainerSize() == 1); // Check getContainerSize for single double element
        ++it;
        CHECK(it == end_it);// Checking if iterator reaches end after increment
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing past-the-end throws
    }

    SUBCASE("SideCrossOrder_EvenNumberOfElements_Double")
    {// Checking SideCrossOrder iterator for an even number of double elements
        ariel::MyContainer<double> container;
        container.addElement(4.4);
        container.addElement(1.1);
        container.addElement(3.3);
        container.addElement(2.2);
        // Sorted: 1.1, 2.2, 3.3, 4.4
        // Expected side-cross: 1.1, 4.4, 2.2, 3.3
        vector<double> expected = {1.1, 4.4, 2.2, 3.3};
        vector<double> actual = iteratorToVector<ariel::MyContainer<double>::SideCrossOrder, double>(container.begin_side_cross_order(), container.end_side_cross_order());
        CHECK(actual.size() == expected.size());// Checking size of actual vs expected
        for (size_t i = 0; i < actual.size(); ++i) {
            CHECK(actual[i] == doctest::Approx(expected[i]).epsilon(epsilon));// Checking individual elements with approx
        }
        CHECK(container.begin_side_cross_order().getContainerSize() == 4); // Check getContainerSize
    }

    SUBCASE("SideCrossOrder_OddNumberOfElements_Double")
    {// Checking SideCrossOrder iterator for an odd number of double elements
        ariel::MyContainer<double> container;
        container.addElement(5.5);
        container.addElement(1.1);
        container.addElement(4.4);
        container.addElement(2.2);
        container.addElement(3.3);
        // Sorted: 1.1, 2.2, 3.3, 4.4, 5.5
        // Expected side-cross: 1.1, 5.5, 2.2, 4.4, 3.3
        vector<double> expected = {1.1, 5.5, 2.2, 4.4, 3.3};
        // Corrected: Use SideCrossOrder iterators
        vector<double> actual = iteratorToVector<ariel::MyContainer<double>::SideCrossOrder, double>(container.begin_side_cross_order(), container.end_side_cross_order());
        CHECK(actual.size() == expected.size());// Checking size of actual vs expected
        for (size_t i = 0; i < actual.size(); ++i) {
            CHECK(actual[i] == doctest::Approx(expected[i]).epsilon(epsilon));// Checking individual elements with approx
        }
        CHECK(container.begin_side_cross_order().getContainerSize() == 5); // Check getContainerSize
    }

    SUBCASE("ReverseOrder_EmptyContainer_Double")
    {// Checking ReverseOrder iterator for an empty double container
        ariel::MyContainer<double> emptyContainer;
        auto it = emptyContainer.begin_reverse_order();
        auto end_it = emptyContainer.end_reverse_order();
        CHECK(it == end_it);// Checking if begin equals end for empty double container
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing begin() of empty double container throws
        CHECK(it.getContainerSize() == 0); // Check getContainerSize for empty double container
    }

    SUBCASE("ReverseOrder_SingleElement_Double")
    {// Checking ReverseOrder iterator for a single double element container
        ariel::MyContainer<double> container;
        container.addElement(9.9);
        auto it = container.begin_reverse_order();
        auto end_it = container.end_reverse_order();
        CHECK(*it == doctest::Approx(9.9).epsilon(epsilon));// Checking value of the single double element
        CHECK(it.getContainerSize() == 1); // Check getContainerSize for single double element
        ++it;
        CHECK(it == end_it);// Checking if iterator reaches end after increment
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing past-the-end throws
    }

    SUBCASE("ReverseOrder_MultipleElements_Double")
    {// Checking ReverseOrder iterator for multiple double elements
        ariel::MyContainer<double> container;
        container.addElement(1.0);
        container.addElement(2.0);
        container.addElement(3.0);
        vector<double> expected = {3.0, 2.0, 1.0}; // Original order reversed
        vector<double> actual = iteratorToVector<ariel::MyContainer<double>::ReverseOrder, double>(container.begin_reverse_order(), container.end_reverse_order());
        CHECK(actual.size() == expected.size());// Checking size of actual vs expected
        for (size_t i = 0; i < actual.size(); ++i) {
            CHECK(actual[i] == doctest::Approx(expected[i]).epsilon(epsilon));// Checking individual elements with approx
        }
        CHECK(container.begin_reverse_order().getContainerSize() == 3); // Check getContainerSize
    }

    SUBCASE("Order_EmptyContainer_Double")
    {// Checking Order iterator for an empty double container
        ariel::MyContainer<double> emptyContainer;
        auto it = emptyContainer.begin_order();
        auto end_it = emptyContainer.end_order();
        CHECK(it == end_it);// Checking if begin equals end for empty double container
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing begin() of empty double container throws
        CHECK(it.getContainerSize() == 0); // Check getContainerSize for empty double container
    }

    SUBCASE("Order_SingleElement_Double")
    {// Checking Order iterator for a single double element container
        ariel::MyContainer<double> container;
        container.addElement(1.23);
        auto it = container.begin_order();
        auto end_it = container.end_order();
        CHECK(*it == doctest::Approx(1.23).epsilon(epsilon));// Checking value of the single double element
        CHECK(it.getContainerSize() == 1); // Check getContainerSize for single double element
        ++it;
        CHECK(it == end_it);// Checking if iterator reaches end after increment
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing past-the-end throws
    }

    SUBCASE("Order_MultipleElements_Double")
    {// Checking Order iterator for multiple double elements
        ariel::MyContainer<double> container;
        container.addElement(1.1);
        container.addElement(3.3);
        container.addElement(2.2);
        vector<double> expected = {1.1, 3.3, 2.2}; // Original insertion order
        vector<double> actual = iteratorToVector<ariel::MyContainer<double>::Order, double>(container.begin_order(), container.end_order());
        CHECK(actual.size() == expected.size());// Checking size of actual vs expected
        for (size_t i = 0; i < actual.size(); ++i) {
            CHECK(actual[i] == doctest::Approx(expected[i]).epsilon(epsilon));// Checking individual elements with approx
        }
        CHECK(container.begin_order().getContainerSize() == 3); // Check getContainerSize
    }

    SUBCASE("MiddleOutOrder_EmptyContainer_Double")
    {// Checking MiddleOutOrder iterator for an empty double container
        ariel::MyContainer<double> emptyContainer;
        auto it = emptyContainer.begin_middle_out_order();
        auto end_it = emptyContainer.end_middle_out_order();
        CHECK(it == end_it);// Checking if begin equals end for empty double container
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing begin() of empty double container throws
        CHECK(it.getContainerSize() == 0); // Check getContainerSize for empty double container
    }

    SUBCASE("MiddleOutOrder_SingleElement_Double")
    {// Checking MiddleOutOrder iterator for a single double element container
        ariel::MyContainer<double> container;
        container.addElement(8.8);
        auto it = container.begin_middle_out_order();
        auto end_it = container.end_middle_out_order();
        CHECK(*it == doctest::Approx(8.8).epsilon(epsilon));// Checking value of the single double element
        CHECK(it.getContainerSize() == 1); // Check getContainerSize for single double element
        ++it;
        CHECK(it == end_it);// Checking if iterator reaches end after increment
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing past-the-end throws
    }

    SUBCASE("MiddleOutOrder_EvenNumberOfElements_Double")
    {// Checking MiddleOutOrder iterator for an even number of double elements
        ariel::MyContainer<double> container;
        container.addElement(4.0);
        container.addElement(1.0);
        container.addElement(3.0);
        container.addElement(2.0);
        // Sorted: 1.0, 2.0, 3.0, 4.0
        // Expected middle-out: 2.0, 3.0, 1.0, 4.0
        vector<double> expected = {2.0, 3.0, 1.0, 4.0};
        // Corrected: Use MiddleOutOrder iterators
        vector<double> actual = iteratorToVector<ariel::MyContainer<double>::MiddleOutOrder, double>(container.begin_middle_out_order(), container.end_middle_out_order());
        CHECK(actual.size() == expected.size());// Checking size of actual vs expected
        for (size_t i = 0; i < actual.size(); ++i) {
            CHECK(actual[i] == doctest::Approx(expected[i]).epsilon(epsilon));// Checking individual elements with approx
        }
        CHECK(container.begin_middle_out_order().getContainerSize() == 4); // Check getContainerSize
    }

    SUBCASE("MiddleOutOrder_OddNumberOfElements_Double")
    {// Checking MiddleOutOrder iterator for an odd number of double elements
        ariel::MyContainer<double> container;
        container.addElement(5.0);
        container.addElement(1.0);
        container.addElement(4.0);
        container.addElement(2.0);
        container.addElement(3.0);
        // Sorted: 1.0, 2.0, 3.0, 4.0, 5.0
        // Expected middle-out: 3.0, 2.0, 4.0, 1.0, 5.0
        vector<double> expected = {3.0, 2.0, 4.0, 1.0, 5.0};
        vector<double> actual = iteratorToVector<ariel::MyContainer<double>::MiddleOutOrder, double>(container.begin_middle_out_order(), container.end_middle_out_order());
        CHECK(actual.size() == expected.size());// Checking size of actual vs expected
        for (size_t i = 0; i < actual.size(); ++i) {
            CHECK(actual[i] == doctest::Approx(expected[i]).epsilon(epsilon));// Checking individual elements with approx
        }
        CHECK(container.begin_middle_out_order().getContainerSize() == 5); // Check getContainerSize
    }
}

TEST_CASE("MyContainer Iterators - Iterator Comparison and Dereference Errors")
{
    ariel::MyContainer<int> container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(3);

    SUBCASE("AscendingOrder_DereferencePastEndThrows")
    {// Checking AscendingOrder dereference past end throws
        auto it = container.end_ascending_order();
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing end iterator throws out_of_range
    }

    SUBCASE("DescendingOrder_DereferencePastEndThrows")
    {// Checking DescendingOrder dereference past end throws
        auto it = container.end_descending_order();
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing end iterator throws out_of_range
    }

    SUBCASE("SideCrossOrder_DereferencePastEndThrows")
    {// Checking SideCrossOrder dereference past end throws
        auto it = container.end_side_cross_order();
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing end iterator throws out_of_range
    }

    SUBCASE("ReverseOrder_DereferencePastEndThrows")
    {// Checking ReverseOrder dereference past end throws
        auto it = container.end_reverse_order();
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing end iterator throws out_of_range
    }

    SUBCASE("Order_DereferencePastEndThrows")
    {// Checking Order dereference past end throws
        auto it = container.end_order();
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing end iterator throws out_of_range
    }

    SUBCASE("MiddleOutOrder_DereferencePastEndThrows")
    {// Checking MiddleOutOrder dereference past end throws
        auto it = container.end_middle_out_order();
        CHECK_THROWS_AS(*it, out_of_range);//Dereferencing end iterator throws out_of_range
    }

    SUBCASE("IteratorComparison_DifferentTypes")
    {// Checking iterator comparison with different types (should not compile or be false)
        ariel::MyContainer<int> c;
        c.addElement(1);
        c.addElement(2);
        // This is a compile-time check, not a runtime check, but demonstrating intent.
        // CHECK(c.begin_ascending_order() == c.begin_descending_order()); // This would be a compile error
        // The iterators are distinct types, so direct comparison is not allowed by C++ rules.
        // We can only check equality/inequality for iterators of the *same* type.
        CHECK(true); //Placeholder to ensure test case passes compilation
    }

    SUBCASE("IteratorComparison_SameTypeDifferentContainers")
    {// Checking iterator comparison with same type but different containers
        ariel::MyContainer<int> c1;
        c1.addElement(1);
        ariel::MyContainer<int> c2;
        c2.addElement(1);
        // Iterators from different containers should not compare equal, even if values are same.
        CHECK_FALSE(c1.begin_ascending_order() == c2.begin_ascending_order());// Checking inequality for iterators from different containers
        CHECK(c1.begin_ascending_order() != c2.begin_ascending_order());// Checking inequality for iterators from different containers
    }

    SUBCASE("IteratorComparison_EmptyContainerBeginEnd") {
        ariel::MyContainer<int> empty_mc;
        CHECK(empty_mc.begin_ascending_order() == empty_mc.end_ascending_order()); //
        CHECK_FALSE(empty_mc.begin_ascending_order() != empty_mc.end_ascending_order()); //
        CHECK(empty_mc.begin_descending_order() == empty_mc.end_descending_order()); //
        CHECK(empty_mc.begin_side_cross_order() == empty_mc.end_side_cross_order()); //
        CHECK(empty_mc.begin_reverse_order() == empty_mc.end_reverse_order()); //
        CHECK(empty_mc.begin_order() == empty_mc.end_order()); //
        CHECK(empty_mc.begin_middle_out_order() == empty_mc.end_middle_out_order()); //
    }

    SUBCASE("IteratorComparison_MultiElementBeginEnd") {
        ariel::MyContainer<int> mc;
        mc.addElement(1);
        mc.addElement(2);
        CHECK_FALSE(mc.begin_ascending_order() == mc.end_ascending_order()); //
        CHECK(mc.begin_ascending_order() != mc.end_ascending_order()); //
        CHECK_FALSE(mc.begin_descending_order() == mc.end_descending_order()); //
        CHECK_FALSE(mc.begin_side_cross_order() == mc.end_side_cross_order()); //
        CHECK_FALSE(mc.begin_reverse_order() == mc.end_reverse_order()); //
        CHECK_FALSE(mc.begin_order() == mc.end_order()); //
        CHECK_FALSE(mc.begin_middle_out_order() == mc.end_middle_out_order()); //
    }
}

TEST_CASE("MyContainer - Const Correctness and Read-Only Access")
{
    ariel::MyContainer<int> mc;
    mc.addElement(10);
    mc.addElement(20);
    mc.addElement(30);

    const ariel::MyContainer<int>& const_mc = mc;

    SUBCASE("ConstContainer_Size")
    {// Checking size on a const container
        CHECK(const_mc.size() == 3);// Checking size via const reference
    }

    SUBCASE("ConstContainer_Print")
    {// Checking print on a const container
        stringstream ss;
        streambuf* oldCout = cout.rdbuf();
        cout.rdbuf(ss.rdbuf());

        const_mc.print();
        cout.rdbuf(oldCout);
        CHECK(ss.str() == "10 20 30\n");// Checking print output via const reference
    }

    SUBCASE("ConstContainer_AscendingOrder")
    {// Checking AscendingOrder iterator on a const container
        vector<int> expected = {10, 20, 30};
        sort(expected.begin(), expected.end()); // Ensure sorted
        CHECK(iteratorToVector<ariel::MyContainer<int>::AscendingOrder, int>(const_mc.begin_ascending_order(), const_mc.end_ascending_order()) == expected);// Checking ascending order via const reference
    }

    SUBCASE("ConstContainer_DescendingOrder")
    {// Checking DescendingOrder iterator on a const container
        vector<int> expected = {10, 20, 30};
        sort(expected.begin(), expected.end(), greater<int>()); // Ensure sorted descending
        CHECK(iteratorToVector<ariel::MyContainer<int>::DescendingOrder, int>(const_mc.begin_descending_order(), const_mc.end_descending_order()) == expected);// Checking descending order via const reference
    }

    SUBCASE("ConstContainer_SideCrossOrder")
    {// Checking SideCrossOrder iterator on a const container
        vector<int> sorted_copy = {10, 20, 30};
        sort(sorted_copy.begin(), sorted_copy.end());
        vector<int> expected;
        size_t left = 0;
        size_t right = sorted_copy.size() - 1;
        while (left <= right) {
            if (left == right) {
                expected.push_back(sorted_copy[left]);
                break;
            }
            expected.push_back(sorted_copy[left]);
            expected.push_back(sorted_copy[right]);
            ++left;
            --right;
        }
        CHECK(iteratorToVector<ariel::MyContainer<int>::SideCrossOrder, int>(const_mc.begin_side_cross_order(), const_mc.end_side_cross_order()) == expected);// Checking side-cross order via const reference
    }

    SUBCASE("ConstContainer_ReverseOrder")
    {// Checking ReverseOrder iterator on a const container
        vector<int> expected = {10, 20, 30};
        reverse(expected.begin(), expected.end());
        CHECK(iteratorToVector<ariel::MyContainer<int>::ReverseOrder, int>(const_mc.begin_reverse_order(), const_mc.end_reverse_order()) == expected);// Checking reverse order via const reference
    }

    SUBCASE("ConstContainer_Order")
    {// Checking Order iterator on a const container
        vector<int> expected = {10, 20, 30};
        CHECK(iteratorToVector<ariel::MyContainer<int>::Order, int>(const_mc.begin_order(), const_mc.end_order()) == expected);// Checking original order via const reference
    }
}