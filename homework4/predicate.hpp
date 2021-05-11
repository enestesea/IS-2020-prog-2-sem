#ifndef PREDICATE_HPP
#define PREDICATE_HPP
#include <iostream>

using namespace std;

//all_of
template <typename Iterator, typename Predicate>
bool allOf(Iterator begin, Iterator end, Predicate pr){
    for(Iterator it = begin; it < end; it++){
        if(!pr(*it))
            return false;
    }
    return true;
}
//any_of
template <typename Iterator, typename Predicate>
bool anyOf(Iterator begin, Iterator end, Predicate pr){
    for(Iterator it = begin; it < end; it++){
        if(pr(*it))
            return true;
    }
    return false;
}
//none_of
template <typename Iterator, typename Predicate>
bool noneOf(Iterator begin, Iterator end, Predicate pr){
    return !anyOf(begin, end, pr);
}
//one_of
template <typename Iterator, typename Predicate>
bool oneOf(Iterator begin, Iterator end, Predicate pr){
    bool check = false;
    for(Iterator it = begin; it < end; it++){
        if(pr(*it)){
            if(check)
                return false;
            check = true;
        }
    }
    return true;
}
// is_sorted
template <typename Iterator, typename Predicate = less<>>
bool isSorted(Iterator begin, Iterator end, Predicate pr = Predicate()){
    for(Iterator it = begin; it < end - 1; it++){
        if(!pr(*it, *(it + 1)))
            return false;
    }
    return true;
}
//is_partitioned
template <typename Iterator, typename Predicate>
bool isPartitioned(Iterator begin, Iterator end, Predicate pr){
    bool it_ = pr(*begin);
    bool check = false;
    for(Iterator it = begin; it != end; it++){
        if(pr(*it) != it_){
            if(check)
               return false;
            check = true;
        }
    }
    return true;
}

//find_not
template <typename Iterator, typename Value>
Iterator findNot(Iterator begin, Iterator end, Value x){
    for(Iterator it = begin; it < end; it++){
        if(x != *it)
            return it;
    }
    return end;
}
//find_backward
template <typename Iterator, typename Value>
Iterator findBackward(Iterator begin, Iterator end, Value x){
    Iterator it_ = end;
    for(Iterator it = begin; it != end; it++){
        if(x == *it)
            it_ = it;
    }
    return it_;
}
//is_palindrome
template<typename Iterator, typename Predicate>
bool isPalindrome(Iterator begin, Iterator end, Predicate pr) {
    Iterator it_ = end;
    end--;
    while(begin != end && begin != it_){
        if(!pr(*begin, *end))
            return false;
        begin++;
        end--;
    }
    return true;
}

#endif

