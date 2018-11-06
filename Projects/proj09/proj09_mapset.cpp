/*
Created by: Jude Jang
Created on: 3/24/2018
Section: 003

Project 09 - MapSet
Creates a combination data structure, MapSet, which combines a map and a set, 
without using either of their STL counterparts (map and set).
*/

#include<algorithm>
using std::lower_bound;

#include "proj09_mapset.h"

// Returns true if the element of the container is less than value_to_search_for.
bool binary_predicate(pair<string,long> pair, string key){
  return pair.first < key; 
}

// Returns an iterator to a pair<string,long>. 
vector<pair<string,long>>::iterator MapSet::find_key(string key){
  return lower_bound(v_.begin(), v_.end(), key, binary_predicate); 
}

// Takes each pair and places them in the vector.
MapSet::MapSet(initializer_list<pair<string,long>> il){
  for(auto pair:il)
    add(pair);
}

// Size of the MapSet.
size_t MapSet::size(){
  return v_.size();
}

// Returns a pair by key.
pair<string,long> MapSet::get(string key){
  if(find_key(key) != v_.end()){
    if(find_key(key)->first == key)
      return *find_key(key);
  }
  return {"", 0};
}

// Updates a keys value;
bool MapSet::update(string key, long val){
  if(find_key(key) != v_.end()){
    if(find_key(key)->first == key){
      find_key(key)->second = val;
      return true;
    }
  }
  return false;
}

// Removes a pair by key.
bool MapSet::remove(string key){
  if(find_key(key) != v_.end()){
    if(find_key(key)->first == key){
      v_.erase(find_key(key));
      return true;
    }
  }
  return false;
}

// Adds a pair by key.
bool MapSet::add(pair<string,long> pair){
  if(find_key(pair.first) != v_.end()){
    if(find_key(pair.first)->first == pair.first)
      return false;
  }
  v_.insert(find_key(pair.first), pair);
  return true;
}

// Compares two MapSets.
int MapSet::compare(MapSet& ms){
  int i = 0;
  while(i != size() && i != ms.size()){
    if(v_[i].first > ms.v_[i].first)
      return 1;
    else if(v_[i].first < ms.v_[i].first)
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

// Return a new MapSet that is a union of the two MapSets being called.
MapSet MapSet::mapset_union(MapSet& ms){
  MapSet new_ms;
  for(auto pair:v_)
    new_ms.add(pair);
  for(auto pair:ms.v_)
    new_ms.add(pair);
  return new_ms;
}

// Return a new MapSet that is the intersection of the two MapSets being called.
MapSet MapSet::mapset_intersection(MapSet& ms){
  MapSet new_ms;
  for(auto pair:v_){
    if(ms.find_key(pair.first) != ms.v_.end())
      if(ms.find_key(pair.first)->first == pair.first)
        new_ms.add(pair);
  }    
  return new_ms;
}  

// Returns the ostream after writing the MapSet to the ostream.
ostream& operator<<(ostream& os, MapSet& ms){
  for(auto i = ms.v_.begin(); i != ms.v_.end(); i++){
    if(i == ms.v_.begin())
      os << i->first << ":" << i->second;      
    else
      os << ", " << i->first << ":" << i->second;
  }
  return os;
}