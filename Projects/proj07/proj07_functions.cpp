/*
Created by: Jude Jang
Created on: 3/8/2018
Section: 003

Project 07
Manages a list of computer servers.
Adds and disconnects users from servers as well as balances the server load.
*/

#include "proj07_functions.h"
using ServerData = std::map<std::string, std::set<std::string>>;
using UserName = const std::string &;
using ServerName = const std::string &;
#include <string>
using std::string;
#include <fstream>
using std::ifstream;
#include <sstream>
using std::stringstream;
#include <stdexcept>
using std::invalid_argument; using std::domain_error;
#include <set>
using std::set;
#include <algorithm>
using std::set_symmetric_difference;
#include <iterator>
#include <vector>
using std::vector;

// Connects a user to a server
bool AddConnection(ServerData &sd, ServerName sn, UserName un){
  if (sd.find(sn) == sd.end()){
    sd[sn].insert(un);
    return true;
  }  
  else {
    if (sd[sn].find(un) == sd[sn].end()){
      sd[sn].insert(un);
      return true;
    }
    else
      return false;
  } 
}

// Disconnects a user from a server
bool DeleteConnection(ServerData &sd, ServerName sn, UserName un){
  if (sd[sn].find(un) == sd[sn].end())
    return false;
  else
    sd[sn].erase(un);
  return true;
}

// Parses through a file to connect and disconnect users from servers
ServerData ParseServerData(const std::string &fname){
  ServerData sd;
  ifstream file(fname);
  string line, un, action, sn;
  if (!file.is_open())
    throw invalid_argument("Invalid File Name.");
  while (getline(file, line)){
    stringstream ss(line);
    ss >> un >> action >> sn;
    if (action == "join")
      AddConnection(sd, sn, un);
    else if (action == "leave")
      DeleteConnection(sd, sn, un);
    else 
      throw domain_error("Invalid Action.");
  }    
  return sd;
}

// Prints servers with its users
void PrintAll(std::ostream &out, const ServerData &sd){
  for (auto pair:sd){
    out << pair.first << " :";
    for (auto un:pair.second)
      out << " " << un ;
      out << "\n";
  }  
}

// Returns set of all servers
set<string> AllServers(const ServerData &sd){
  set<string> all_servers;
  for (auto pair:sd)
    all_servers.insert(pair.first);
  return all_servers;
}

// Returns set of all users
set<string> AllUsers(const ServerData &sd){
  set<string> all_users;
    for (auto pair:sd)
      for (auto un:pair.second)
        all_users.insert(un);
  return all_users;
}

// Returns set of servers that user is connected to
set<string> HasConnections(const ServerData &sd, UserName un){
  set<string> active_servers;
  for (auto pair:sd)
    if (pair.second.find(un) != pair.second.end())
      active_servers.insert(pair.first);
  return active_servers;
}

// Returns set of users that a server has
set<string> HasUsers(const ServerData &sd, ServerName sn){
  set<string> active_users;
  if (sd.find(sn) != sd.end())
    for (auto pair:sd)
      if (pair.first == sn)     
        for (auto un:pair.second)
          active_users.insert(un);
  return active_users;  
}

// Balances servers by moving users to different servers
void BalanceServers(ServerData &sd, ServerName sn1, ServerName sn2){
  set<string> sn1_un = HasUsers(sd, sn1);
  set<string> sn2_un = HasUsers(sd, sn2);
  set<string> sym_diff;
  int i;

  set_symmetric_difference(
        sn1_un.begin(), sn1_un.end(),
        sn2_un.begin(), sn2_un.end(),
        inserter(sym_diff, sym_diff.begin()));

  for (auto un:sym_diff){
    sn1_un.erase(un);
    sn2_un.erase(un);
    DeleteConnection(sd, sn1, un);
    DeleteConnection(sd, sn2, un);
  }  
  
  if (sym_diff.size() % 2 == 1)     
    i = sym_diff.size() / 2 + 1;
  else
    i = sym_diff.size() / 2 ;

    for (int j = 0; j != i; j++){
      std::set<string>::iterator it = sym_diff.begin();
      std::advance(it, j);
      string un = *it;
      sn1_un.insert(un);
      AddConnection(sd, sn1, un);
    }

    for (auto un:sn1_un)
      sym_diff.erase(un);

    for (auto un:sym_diff)
      AddConnection(sd, sn2, un);  
}

// Removes duplicate users and distribute users alphabetically
void CleanAndBalance(ServerData &sd){
  set<string> a_uns = AllUsers(sd);
  set<string> uns;
  set<string> sns = AllServers(sd);

  for (auto sn:sns){
    uns = HasUsers(sd, sn);
    for (auto un:uns)
      DeleteConnection(sd, sn, un);
  }    

  int sn_count = 0;
  vector<string> un_v;
  vector<string> sn_v;

  for (auto un:a_uns)
    un_v.push_back(un);
  for (auto sn:sns)
    sn_v.push_back(sn);

  while (un_v.size() != 0){
    sd[sn_v[sn_count]].insert(un_v[0]);
    sn_count++;
    un_v.erase(un_v.begin());
    if(sn_count == sn_v.size())
      sn_count = 0;
  } 
}   