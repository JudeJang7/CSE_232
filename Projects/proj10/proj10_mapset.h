/*
Created by: Jude Jang
Created on: 4/5/2018
Section: 003

Project 10 - MapSet (dynamic arrays)
Creates a combination data structure, MapSet, which combines a map and a set, 
using dynamic arrays.
*/

#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream; using std::endl;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<algorithm>
using std::sort; using std::lower_bound; using std::find;
#include<sstream>
using std::ostringstream;
#include<iterator>
using std::distance;

//
// Node
//
template<typename K, typename V>
struct Node {
  K first;
  V second;
  Node() = default;
  Node(K,V);
  bool operator<(const Node&) const;
  bool operator==(const Node&) const;

  // Prints key:value
  friend ostream& operator<<(ostream &out, const Node &n){
    out << n.first << ":" << n.second;
    return out;
  }
};

// Initializes data members
template<typename K, typename V>
Node<K,V>::Node(K key, V value){
  first = key; 
  second = value;
}

// Compares two Node instances based on the first values
template<typename K, typename V>
bool Node<K,V>::operator<(const Node &n) const{
  return n.first < first;
}

// Compares two Node instances based on the first values
template<typename K, typename V>
bool Node<K,V>::operator==(const Node &n) const{
  return first == n.first;
}

//
// MapSet
// 
template<typename K, typename V>
class MapSet{
 private:
  Node<K,V>* ary_;
  size_t last_;
  size_t capacity_;
  Node<K,V>* find_key(K);
  void grow ();
 public:
  MapSet(int sz = 2);
  MapSet(initializer_list< Node<K,V> >);
  MapSet (const MapSet&);
  MapSet operator=(MapSet);
  ~MapSet();
  size_t size();
  bool remove (K);  
  bool add(Node<K,V>);
  Node<K,V> get(K);
  bool update(K,V);  
  int compare(MapSet&);
  MapSet mapset_union (MapSet&);
  MapSet mapset_intersection(MapSet&);

  // Prints MapSet
  friend ostream& operator<<(ostream &out, const MapSet &ms){
    for(auto itr = ms.ary_; itr < ms.ary_ + ms.last_; ++itr)
      if(itr != ms.ary_ + ms.last_ -1)
        out << *itr << ", ";
      else
        out << *itr;
    return out; 
  }
};

// Initializes data members
template<typename K, typename V>
MapSet<K,V>::MapSet(int capacity){
  ary_ = new Node<K,V>[capacity];
  capacity_ = capacity;
  last_ = 0;
}

// Initializes an array
template<typename K, typename V>
MapSet<K,V>::MapSet(initializer_list< Node<K,V> > il){
  capacity_ = il.size();
  ary_ = new Node<K,V>[capacity_];
  last_ = 0;
  for(auto n:il)
    add(n);  
}

// Copies MapSets data members
template<typename K, typename V>
MapSet<K,V>::MapSet(const MapSet &ms){
  last_ = ms.last_;
  capacity_ = ms.capacity_;
  ary_ = new Node<K,V>[ms.last_];
  copy(ms.ary_, ms.ary_+ms.last_, ary_);
}

// Copy and swap
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::operator=(MapSet<K,V> ms){
  swap(ary_, ms.ary_);
  last_ = ms.last_;
  capacity_ = ms.capacity_;
  return *this;
}

// Destructor
template<typename K, typename V>
MapSet<K,V>::~MapSet(){
  delete [] ary_;
}

// Size of MapSet
template<typename K, typename V>
size_t MapSet<K,V>::size(){
  return last_;
}

// Doubles the capacity of the underlying array
template<typename K, typename V>
void MapSet<K,V>::grow(){
  Node<K,V>* new_ary;
  new_ary = new Node<K,V>[capacity_ * 2];
  copy(ary_, ary_+last_, new_ary);
  swap(new_ary, ary_);
  delete [] new_ary;
}

// Returns a pointer to a Node<K,V>
template<typename K, typename V>
Node<K,V>* MapSet<K,V>::find_key(K key){
  auto lower = lower_bound(ary_, ary_ + last_, key, [](Node<K,V> ptr, K key){return ptr.first <key;});
  if(lower > ary_ + last_){
    return nullptr;
  }
  return lower; 
}

// Creates a Node and inserts the new pair into the array
template<typename K, typename V>
bool MapSet<K,V>::add(Node<K,V> n){
  if(capacity_ == last_)
    grow();
  if(find_key(n.first) != nullptr){
    if(find_key(n.first)->first == n.first)
      return false;
    else{
      auto d = distance(ary_, find_key(n.first));
      Node<K,V>* new_ary = new Node<K,V>[capacity_+1];
      copy(ary_, ary_ + d, new_ary);
      new_ary[d] = n;
      copy(ary_ + d, ary_+last_, new_ary + d + 1);
      swap(ary_, new_ary);
      last_++;
      delete [] new_ary;
      return true;
    } 
  }  
  ary_[last_] = n;
  last_++;
  return true;   
}

//  If the key is in the MapSet, remove the associated Node
template<typename K, typename V>
bool MapSet<K,V>::remove(K key){
  if(find_key(key) != nullptr && find_key(key)->first == key){
    auto d = distance(ary_, find_key(key));
    Node<K,V>* new_ary = new Node<K,V>[capacity_-1];
    copy(ary_, ary_ + d, new_ary);
    copy(ary_ + d + 1, ary_ + last_, new_ary + d);
    swap(ary_, new_ary);
    last_--;
    delete [] new_ary;
    return true;
  }
  return false;
}

// Returns a Node<K,V>
template<typename K, typename V>
Node<K,V> MapSet<K,V>::get(K key){
  if(find_key(key) != nullptr && find_key(key)->first == key)
    return *find_key(key);
  return {"", 0};
}

// Update the key-value pair to the value
template<typename K, typename V>
bool MapSet<K,V>::update(K key, V value){
  if(find_key(key) != nullptr && find_key(key)->first == key){
    find_key(key)->second = value;
    return true;
  }
  return false;
}

// Compares the two MapSets lexicographically
template<typename K, typename V>
int MapSet<K,V>::compare(MapSet &ms){
  int i = 0;
  while(i != size() && i != ms.size()){
    if(ary_[i].first > ms.ary_[i].first)
      return 1;
    else if(ary_[i].first < ms.ary_[i].first)
      return -1;
    i++;
    if((i == size() && i != ms.size()) || (i != size() && i == ms.size()))
      break;
  }
  if(size() > ms.size())
    return 1;
  else if(size() < ms.size())
    return -1;
  else
    return 0;
}

// Returns a new MapSet that is a union of the two MapSets being called
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_union(MapSet<K,V> &ms){
  MapSet new_ms(*this);
  for(auto itr = ms.ary_; itr != ms.ary_ + ms.last_; ++itr){
    new_ms.add(*itr);
  }
  return new_ms;
}

// Return a new MapSet that is the intersection of the two MapSets being called
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_intersection(MapSet<K,V> &ms){
  MapSet new_ms;
  for(auto itr = ary_; itr != ary_ + last_; ++itr){
    if(ms.find_key(itr->first)->first == itr->first)
      new_ms.add(*itr);
  }    
  return new_ms;
}

#endif
  