/*----------------------------------------------------------------------
+----------------------------------------------------------------------+
| @file knn.cpp                                                        |
| @author Lucas Fontes Buzuti                                          |
| @version V0.0.1                                                      |
| @created 01/08/2019                                                  |
| @modified 01/08/2019                                                 |
| @e-mail lucas.buzuti@outlook.com                                     |
+----------------------------------------------------------------------+
            Source file containing the implementation of the
                    k-Nearest Neighbors Algorithm
----------------------------------------------------------------------*/

#ifndef KNN_CPP
#define KNN_CPP

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h> 
#include "knn.h"

/*----------------------------------------------------------------------
                                kNN class
----------------------------------------------------------------------*/
//Default constructor (kNN class).
template <class Type>
kNN<Type>::kNN(int k){
  /*
  Param:
    int k  - `k` is the number of neighbors that will be taken into
             account to classify new data, it is recommended that it
             will be odd so there will not be tie.
  */
  if(k%2==0){
    throw "The k is even, change to odd.";
    exit(0);
  }
  if(k<0){
    throw "The k is negative, change to positive.";
    exit(0);
  }
  this->k = k;
}

//Destructor (kNN class).
template <class Type>
kNN<Type>::~kNN(){
  dataset.clear();
  attr_class.clear();
  classes.clear();
}

/*Function fit*/
template <class Type>
void kNN<Type>::fit(std::vector<std::vector<Type> >& dataset,
  std::vector<std::string>& attr_class){
  /*
  Param:
    vector<vector<Type> >  - Matrix of the dataset, where it contains
                             the numeric predictive attributes (feature)
                             of the dataset.
    vector<string>         - Vector of the dataset, where it contains
                             the class attributes of the dataset.
  */
  this->dataset = dataset;
  this->attr_class = attr_class;
}

/*The function returns the Euclidean distance
between two data.*/
template <class Type>
double kNN<Type>::euclidean_distance(std::vector<Type>& ind1,
  std::vector<Type>& ind2) {
  /*
  Param:
    vector<Type> - Vector with numeric predictive attributes (feature).
  Return: euclidean distance of tow elements.
  */
  typename std::vector<Type>::iterator it1, it2;
  double sum = 0.;

  it1=ind1.begin();
  it2=ind2.begin();
  while(it1!=ind1.end() && it2!=ind2.end()) {
    sum += pow((*it1 - *it2),2);
    it1++;
    it2++;
  }
  return sqrt(sum);
}

/*Detects all classes*/
template <class Type>
void kNN<Type>::set_classes(std::vector<std::string>& attr_class) {
  /*
  Param:
    vector<string> - Vector of the dataset, where it contains
                     the class attributes of the dataset.
  */
  std::set<std::string> classes(attr_class.begin(), attr_class.end());
  this->classes = classes;
}

/*Function predict*/
template <class Type>
std::string kNN<Type>::predict(std::vector<Type>& ind1) {
  /*
  Param:
    vector<Type>  -  Vector of the dataset, where it contains the
                     predictive numerical attributes (feature)
                     to be predicted.
  Return: string that it is prediction.
  */
  std::set<std::pair<double,int> > distances;
  std::set<std::pair<double,int> >::iterator it;

  for(int i=0; i<dataset.size(); i++) {
    double distance = kNN::euclidean_distance(dataset.at(i), ind1);
    distances.insert(std::make_pair(distance,i));
  }

  kNN::set_classes(attr_class);
  std::set<std::string>::iterator itclass;

  std::vector<int> count_classes(classes.size(),0);
  std::vector<int>::iterator itcount;

  //Counts number of class classify
  it = distances.begin();
  int max_k = 0;
  while(it!=distances.end() && max_k!=k) {
    itcount = count_classes.begin();
    itclass = classes.begin();
    while(itcount!=count_classes.end() && itclass!=classes.end()) {
      if(attr_class[it->second]==*itclass){
        (*itcount)++;
      }
      itcount++;
      itclass++;
    }
    max_k++;
    it++;
  }

  //determination of the class
  int p = 0;
  target_class = count_classes[0];
  for(int i=1; i<count_classes.size(); i++) {
    if(target_class<count_classes[i]) {
      target_class = count_classes[i];
      p = i;
    }
  }
  itclass = classes.begin();
  int c = 0;
	while(c!=p) {
		itclass++;
		c++;
	}

  return *itclass;
}

/*Return probability of class K for the example*/
template <class Type>
double kNN<Type>::score() {
  return (double)target_class / k;
}

#endif //KNN_CPP
