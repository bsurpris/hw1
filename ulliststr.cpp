#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val){
  
  //if list is empty
  if (head_ == NULL) 
  {
    Item* newItem = new Item();
    newItem->val[newItem->last] = val;
    newItem->last += 1;
    head_ = tail_ = newItem;
  }
  
  // To check if last item is full compare last index to ARRSIZE
  //Then create new item and set the first array spot to our new value, update the last variable
  //Attach to list and set the tail to this new item
  else if (tail_ -> last == ARRSIZE)
  {
    Item* newItem = new Item();
    newItem -> val[newItem -> first] = val;
    newItem -> last += 1;
    tail_ -> next = newItem;
    newItem -> prev = tail_;
    tail_ = newItem;

  }

  //If the last array isnt full we add our value onto the last spot
  else
  {
    tail_ -> val[tail_ -> last] = val;
    tail_ -> last += 1;
  }
  
  //update size
  size_ += 1;
}

void ULListStr::push_front(const std::string& val){

  //if list is empty
  if (head_ == NULL)
  {
    Item* newItem = new Item();
    newItem->val[newItem->first] = val;   
    newItem->last += 1;
    head_ = tail_ = newItem;
  }

  //if there's no room at the front of the head node (first == 0)
  //allocate a new head node and place the value at the BACK of its array
  //so future push_fronts have room to grow toward index 0
  else if (head_->first == 0)
  {
    Item* newItem = new Item();
    newItem->first = newItem->last = ARRSIZE;  // start empty at the back
    newItem->first -= 1;                        // make room at front
    newItem->val[newItem->first] = val;
    newItem->next = head_;
    head_->prev = newItem;
    head_ = newItem;
  }

  //there's room at the front of the head node
  else
  {
    head_->first -= 1;
    head_->val[head_->first] = val;
  }

  //update size
  size_ += 1;
}

void ULListStr::pop_back(){

  if (head_ == NULL)
  {
    return;
  }

  tail_ -> last -= 1;

  //remove tail if empty
  if (tail_ -> first == tail_ -> last)
  {
    //Store tail item in a temp variable
    Item* temp = tail_;

    //if it was the only node the list is empty
    if (head_ == tail_)
    {
      head_ = tail_ = NULL;
    }
    //change tail to the prev node
    else
    {
      tail_ = tail_ -> prev;
      tail_ -> next = NULL;
    }
    delete temp;
  }

  //update size
  size_ -= 1;
  
}

void ULListStr::pop_front(){

  if (head_ == NULL)
  {
    return;
  }

  head_ -> first += 1;

  //remove head if empty
  if (head_ -> first == head_ -> last)
  {
    //Store head item in a temp variable
    Item* temp = head_;

    //if it was the only node the list is empty
    if (head_ == tail_)
    {
      head_ = tail_ = NULL;
    }
    //change head to the next node
    else
    {
      head_ = head_ -> next;
      head_ -> prev = NULL;
    }
    delete temp;
  }

  //update size
  size_ -= 1;
  
}

std::string const & ULListStr::back() const
{
  return tail_ -> val[tail_ -> last - 1];
}

std::string const & ULListStr::front() const
{
  return head_ -> val[head_ -> first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const{

  Item* temp = head_;
  while (temp!= NULL)
  {
    size_t count = temp -> last -temp -> first;

    //if loc lands inside this node, return a pointer to that element
    if (loc < count)
    {
      return &(temp -> val[temp -> first + loc]);
    }

    //skip past this node and move only
    loc -= count;
    temp = temp -> next;
  }

  //location went past end of list
  return NULL;
}
void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
