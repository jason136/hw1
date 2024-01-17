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

void ULListStr::push_back(const std::string& val) {
  if (tail_ == NULL) {
    tail_ = new Item();
    tail_->val[0] = val;
    tail_->last = 1;
    head_ = tail_;
  } else if (tail_->last < ARRSIZE) {
    tail_->val[tail_->last++] = val;
  } else {
    tail_->next = new Item();
    tail_->next->prev = tail_;
    tail_ = tail_->next;
    tail_->val[0] = val;
    tail_->last = 1;
  }

  size_++;
}

void ULListStr::push_front(const std::string& val) {
  if (head_ == NULL) {
    head_ = new Item();
    head_->last = ARRSIZE;
    head_->first = ARRSIZE - 1;
    head_->val[head_->first] = val;
    tail_ = head_;
  } else if (head_->first > 0) {
    head_->val[--head_->first] = val;
  } else {
    head_->prev = new Item();
    head_->prev->next = head_;
    head_ = head_->prev;
    head_->last = ARRSIZE;
    head_->first = ARRSIZE - 1;
    head_->val[head_->first] = val;
  }

  size_++;
}

void ULListStr::pop_back() {
  if (tail_ == NULL) return;

  if (tail_->last - tail_->first > 1) {
    tail_->last--;
  } else if (head_ == tail_) {
    delete head_;
    head_ = tail_ = NULL;
  } else {
    Item *temp = tail_->prev;
    delete tail_;
    tail_ = temp;
    tail_->next = NULL;
  }

  size_--;
}

void ULListStr::pop_front() {
  if (head_ == NULL) return;

  if (head_->last - head_->first > 1) {
    head_->first++;
  } else if (head_ == tail_) {
    delete head_;
    head_ = tail_ = NULL;
  } else {
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
    head_->prev = NULL;
  }

  size_--;
}

std::string const & ULListStr::back() const {
  return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const {
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const {
  if (loc >= size_) return NULL;

  if (head_ == NULL) return NULL;

  Item *temp = head_;
  if (loc < head_->last - head_->first) {
    return &head_->val[head_->first + loc];
  } else {
    loc -= head_->last - head_->first;
    temp = temp->next;
  }

  while (loc >= ARRSIZE) {
    loc -= ARRSIZE;
    temp = temp->next;
  }

  return &temp->val[temp->first + loc];
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
