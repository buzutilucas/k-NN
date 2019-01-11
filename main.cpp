#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <stdlib.h>
#include "knn.h"

using namespace std;

void load_data(vector<vector<double> >* feature, vector<string>* classes, string* path_to_dataset, int attr, int num);

int main(int argc, char *argv[]) {
  int attr = 5; //number of attribute
  string path_dataset = "./dataset/iris.data";
  int num_data = 147; //number of data
  string path_data_test = "./dataset/iris_test.data";
  int num_data_test = 4; //number of data test

  vector<vector<double> > feature;
  vector<string> classes;
  vector<vector<double> > feature_test;
  vector<string> classes_test;

  load_data(&feature, &classes, &path_dataset, attr, num_data); //Load Dataset Training
  load_data(&feature_test, &classes_test, &path_data_test, attr, num_data_test); //Load Dataset testing

  int k = 5; // K
  kNN<double> knn(k);
  knn.fit(feature,classes);
  for(int i=0; i<feature_test.size(); i++) {
    string prediction = knn.predict(feature_test[i]);
    cout << "Class: " << classes_test[i] << endl;
    cout << "Prediction: " << prediction << endl;
    cout << "Score: " << knn.score() << "\n\n";
  }

  return 0;
}

void load_data(vector<vector<double> >* feature, vector<string>* classes, string* path_to_dataset, int attr, int num) {
  ifstream read(*path_to_dataset);

  vector<string> temp_vet;
  string line;
  string temp;

  if(read.fail()) {
    cout << "Failure to open a file." << endl;
    cout << "File: " << *path_to_dataset << endl;
    exit(0);
  }

  while (getline(read, line)) {
    istringstream iss(line); //string stream
    while(getline(iss, temp, ',')) {
      temp_vet.push_back(temp);
    }
  }

  read.close();

  int k = 0;
  for(int i=0; i<num; i++) {
    vector<double> myvector;
    for(int j=0; j<attr; j++) {
      if(isalpha(temp_vet[k].c_str()[0]))
        classes->push_back(temp_vet[k]);
      else
        myvector.push_back(atof(temp_vet[k].c_str()));
      k++;
    }
    feature->push_back(myvector);
  }
}
