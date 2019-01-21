[![Build Status](https://travis-ci.org/buzutilucas/k-NN.svg?branch=master)](https://travis-ci.org/buzutilucas/k-NN)

# k-NN (k-Nearest Neighbors)
C++ implementation of K-nearest neighbors. The k-NN is one of the simplest machine learning algorithms, moreover, it is considered supervised learning.

### How to use
When instantiate the object, choose the type of data that this object will be, but it takes into account the type of data (e.g. `kNN<double> knn`). After instantiating the object, we use the fit function for carrying the vector feature and the vector class. Finally, we use the predict function for predicting new examples.

```C++
kNN<double> knn;
knn.fit(feature,classes);
for(int i=0; i<feature_test.size(); i++) {
  string prediction = knn.predict(feature_test[i]);
  cout << "Class: " << classes_test[i] << endl;
  cout << "Prediction: " << prediction << endl;
  cout << "Score: " << knn.score() << "\n\n";
}
```

But to use the k-NN implemented by me, you must use just letters without digits in class names and it can be anywhere in the data.

```
either
5.1,3.5,1.4,0.2,Iris-setosa
or
Iris-setosa,5.1,3.5,1.4,0.2
or
5.1,3.5,Iris-setosa,1.4,0.2
...
```

To access other datasets, you need to modify some variables in `main.cpp`. See below:

```C++
int attr = 5; //number of attribute
string path_dataset = "./dataset/iris.data";
int num_data = 147; //number of data
string path_data_test = "./dataset/iris_test.data";
int num_data_test = 4; //number of data test
```
Moreover, you can modify the variable **K** too in `main.cpp` in variable `int k`.

*The codes are all commented.*

### Used data set
To do testing in the k-NN implemented in C++, we use a famous data set, named Iris.

### Compile (linux)
**How to run:**
```
cd your_path_to_knn
make
./main
```
