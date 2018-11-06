/*
Created by: Jude Jang
Created on: 4/12/2018
Section: 003

Project 11 - MapSet (linked list)
Creates a combination data structure, MapSet, which combines a map and a set, 
using a linked list.
*/

#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream;
#include<string>
using std::string;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<sstream>
using std::ostringstream;

//
// Node
//
template<typename K, typename V>
struct Node {
  K first;
  V second;
  Node *next = nullptr;
  
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

// Initializes data members key and value
template<typename K, typename V>
Node<K,V>::Node(K key, V value){
  first = key; 
  second = value;
}

// Checks to see if a key of a node is greater than a key of another node
template<typename K, typename V>
bool Node<K,V>::operator<(const Node &n) const{
  return n.first < first;
}

// Checks to see if the key of two nodes are equal
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
  Node<K,V>* head_ = nullptr;
  Node<K,V>* tail_ = nullptr;  
  size_t sz_ = 0;
  Node<K,V>* find_key(K);

 public:
  MapSet()=default;
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
    ostringstream oss;
    for(Node<K,V>* ptr = ms.head_; ptr != nullptr; ptr = ptr->next)
      oss << *ptr << ", ";
    string s = oss.str();
    out << s.substr(0,s.size()-2);
    return out;
  }  
};

// Initializes data members for a linked list
template<typename K, typename V>
MapSet<K,V>::MapSet(initializer_list< Node<K,V> > il){
  head_ = nullptr;
  tail_ = nullptr;  
  sz_ = 0;
  for(auto n:il)
    add(n);
}

// Creates a copy of mapset
template<typename K, typename V>
MapSet<K,V>::MapSet(const MapSet &ms){
  if(ms.head_ == nullptr){
    head_ = nullptr;
    tail_ = nullptr;
  }
  else{
    head_ = new Node<K,V>(ms.head_->first, ms.head_->second);
    tail_ = head_;
    Node<K,V>* ms_ptr = ms.head_->next;
    Node<K,V>* new_node;
	  while(ms_ptr != nullptr){
      new_node = new Node<K,V>(ms_ptr->first, ms_ptr->second);
      tail_->next = new_node;
      ms_ptr = ms_ptr->next;
      tail_ = new_node;
	  }
  }
}

// Swaps
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::operator=(MapSet ms){
  swap(head_, ms.head_);
  swap(tail_, ms.tail_);
  return *this;
}	

// walk down the list, moving head_ but remember it in to_del
// delete each node in turn, the set head_ and tail_
template<typename K, typename V>
MapSet<K,V>::~MapSet(){
  Node<K,V>* to_del = head_;
  while(to_del != nullptr){
    head_ = head_->next;
    delete to_del;
    to_del = head_;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

// Size of MapSet
template<typename K, typename V>
size_t MapSet<K,V>::size(){
  return sz_;
}

// Returns a pointer to a Node in the MapSet
template<typename K, typename V>
Node<K,V>* MapSet<K,V>::find_key(K key){
  Node<K,V>* result = nullptr;
  for(Node<K,V>* n = head_; n != nullptr; n = n->next)
    if(n->first <= key)
      result = n;
  return result;    
}  

// Adds a Node to the MapSet
template<typename K, typename V>
bool MapSet<K,V>::add(Node<K,V> n){
  Node<K,V>* n_n = new Node<K,V>(n.first, n.second);
  Node<K,V>* ptr = find_key(n.first);
  if(ptr != nullptr){
    if(ptr->first != n.first){
      n_n->next = ptr->next;
      ptr->next = n_n;
      if(ptr == tail_)
        tail_ = n_n;    
      sz_++;
      return true;      
    }
    delete n_n;
    return false;
  }
  else{
    if(head_ != nullptr){
      n_n ->next = head_;
      head_ = n_n;
    }
    else if(tail_ != nullptr){
      tail_->next = n_n;
      tail_ = n_n;
    }
    else{
      head_ = n_n;
      tail_ = n_n;
    }
    sz_++;
    return true;
  }
}    

// Removes a Node to the MapSet
template<typename K, typename V>
bool MapSet<K,V>::remove(K key){
  Node<K,V>* itr = find_key(key);
  Node<K,V>* i;
  Node<K,V>* j;
  if(itr != nullptr){
    if(head_->first == key){
      head_ = head_->next;
      sz_--;
      return true;
    }
    else if(key == itr->first){
      for(i = head_, j = tail_; i != nullptr && j != nullptr; i = i-> next){
        if(i->next == j){
          tail_ = i;
          i->next = nullptr;
          sz_--;
          return true;
        }
        else if(i-> next == itr){
          i->next = i->next->next;
          sz_--;
          return true;
        }  
      }
    }
  }
  return false;
}

// Returns the pair in the mapset with the found key
template<typename K, typename V>
Node<K,V> MapSet<K,V>::get(K key){
  if(find_key(key) != nullptr && find_key(key)->first == key)
    return *find_key(key);
  return {"", 0};
}

// Updates a pair's value in the mapset
template<typename K, typename V>
bool MapSet<K,V>::update(K key, V value){
  if(find_key(key) != nullptr && find_key(key)->first == key){
    find_key(key)->second = value;
    return true;
  }
  return false;
}

// Compares two MapSets lexicographically
template<typename K, typename V>
int MapSet<K,V>::compare(MapSet &ms){
  Node<K,V>* ptr = head_;
  Node<K,V>* ms_ptr = ms.head_;
  while(ptr != nullptr && ms_ptr != nullptr){
    if(ptr->first > ms_ptr->first)
      return 1;
    else if(ptr->first < ms_ptr->first)
      return -1;
    ptr = ptr->next;
    ms_ptr = ms_ptr->next;
    if((ptr == nullptr && ms_ptr != nullptr) || (ptr != nullptr && ms_ptr == nullptr))
      break;
  }
  if(sz_ > ms.sz_)
    return 1;
  else if(sz_ < ms.sz_)
    return -1;
  else
    return 0;
}

// Returns a new MapSet that is a union of two MapSets
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_union(MapSet<K,V> &ms){
  MapSet new_ms(*this);
  for(auto itr = ms.head_; itr != nullptr; itr = itr->next){
    new_ms.add(*itr);
  }
  return new_ms;
}

// Returns a new MapSet that is the intersection of two MapSets
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_intersection(MapSet<K,V> &ms){
  MapSet new_ms;
  for(auto itr = head_; itr != nullptr; itr = itr->next){
    if(ms.find_key(itr->first)->first == itr->first)
      new_ms.add(*itr);
  }    
  return new_ms; 
}

#endif