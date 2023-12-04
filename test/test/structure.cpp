
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Map {
public:
	vector<pair<string, float>> drugmap;
	void put(string key, float value) {
		pair<string, float> p(key, value);
		for (int i = 0; i < drugmap.size(); i++) {
			if (drugmap[i].first == key) {
				drugmap[i].second = value;
				return;
			}
		}
		drugmap.push_back(p);
	};
	float get(string key) {
		for (int i = 0; i < drugmap.size(); i++) {
			if (drugmap[i].first == key) {
				return drugmap[i].second;
			}
		}
		return -1;
	}
};

vector<string> splitline(string line) {
	vector<string> values;
	int position = line.find(",", 0);
	while (position != -1) {
		string value = line.substr(1, position - 2);
		values.push_back(value);
		line = line.substr(position + 1, line.size() - position - 1);
		position = line.find(",", 0);
	}
	return values;
}

Map readcsv(string filename) {
	ifstream file(filename);
	Map drugmap;
	string line;
	getline(file, line);
	string prev = "";
	while (getline(file, line)) {
		vector<string> values = splitline(line);
		if (stoi(values[1]) > 2010 && prev != values[1]) {
			string key1 = values[1] + "1217Alcohol";

			drugmap.put(key1, stof(values[8]));

			drugmap.put(values[1] + "1825Alcohol", stof(values[9]));
			drugmap.put(values[1] + "26+Alcohol", stof(values[10]));
			drugmap.put(values[1] + "1217IllicitDrugs", stof(values[26]));
			drugmap.put(values[1] + "1825IllicitDrugs", stof(values[27]));
			drugmap.put(values[1] + "26+IllicitDrugs", stof(values[28]));
			drugmap.put(values[1] + "1217Marijuana", stof(values[44]));
			drugmap.put(values[1] + "1825Marijuana", stof(values[45]));
			drugmap.put(values[1] + "26+Marijuana", stof(values[46]));
			prev = values[1];
		}
	}
	return drugmap;
}

class HashMap {

public:
	int size;
	int capacity;
	float loadFactor;
	vector<pair<string, float>> map; // pair of key amd value
	// seperate chaining based on addition of ascii values
	HashMap(int _capacity, float _loadFactor) {
		loadFactor = _loadFactor;
		capacity = _capacity;
		for (int i = 0; i < capacity; i++) {
			map.push_back(make_pair("", -99.0f));
		}
	}
	int hash(string input) {

		int sum = 1;

		for (char c : input) {
			sum += static_cast<int>(c) + 7;
		}

		return sum % capacity;
	}
	void insert(string year, string item, float rate) {

		string total = year + item;

		int mappedIndex = hash(total);
		// cout << mappedIndex << endl;
		int index1 = 3;
		int index2 = 3;
		while (map[mappedIndex].second > -1) {
			mappedIndex += index1;
			index1 *= index1;
			if (mappedIndex >= map.size()) {
				mappedIndex = 0;
			}
		}

		map[mappedIndex] = make_pair(total, rate);
		size++;

		// REHASHING
		if (loadFactor <= ((1.0f * size) / (1.0f * capacity))) {
			cout << "Size: " << size << endl << "Capacity: " << capacity << endl;

			capacity *= 1.5;
			vector<pair<string, float>> mapNew;
			for (int i = 0; i < capacity; i++) {
				mapNew.push_back(make_pair("", -99.0f));
			}
			for (int i = 0; i < capacity / 1.5; i++) {

				if (map[i].second < 0) {
					continue;
				}

				int mappedIndex = hash(map[i].first);

				while (mapNew[mappedIndex].second > 0) {
					// cout << "BRUH";
					mappedIndex += index2;
					index2 *= index2;

					if (mappedIndex > mapNew.size() - 1) {
						mappedIndex = 0;
					}
				}
				mapNew[mappedIndex] = make_pair((map[i].first), (map[i].second));
			}

			map = mapNew;
		}
	}
	float GetRate(string key) {
		int hashedIndex = hash(key);
		int index1 = 3;

		while (map[hashedIndex].first != key) {
			hashedIndex += index1;
			index1 *= index1;
		}
		return map[hashedIndex].second;
	}
	void print() {
		for (auto c : map) {
			cout << c.first << " " << c.second << endl;
		}
	}
};
// "C:\Users\E\Downloads\drugs.csv"
void insertData(HashMap &map, string filename) {

	ifstream file("C:\\Users\\E\\Downloads\\drugs.csv");
	string line;
	getline(file, line);
	string prev = "";
	while (getline(file, line)) {

		vector<string> values = splitline(line);

		if (stoi(values[1]) > 2010 && prev != values[1]) {
			map.insert(values[1], "1217Alcohol", stoi(values[8]));
			map.insert(values[1], "1825Alcohol", stoi(values[9]));
			map.insert(values[1], "26+Alcohol", stoi(values[10]));
			map.insert(values[1], "1217IllicitDrugs", stoi(values[26]));
			map.insert(values[1], "1825IllicitDrugs", stoi(values[27]));
			map.insert(values[1], "26+IllicitDrugs", stoi(values[28]));
			map.insert(values[1], "1217Marijuana", stoi(values[44]));
			map.insert(values[1], "1825Marijuana", stoi(values[8]));
			map.insert(values[1], "26+Marijuana", stoi(values[8]));
			prev = values[1];
		}
	}
}

/*
unordered_map<string, map<string, float>> readhashcsv(string filename) {
  ifstream file(filename);
  map<string, map<string, float>> drugmap;
  string line;
  getline(file, line);
  while (getline(file, line)) {
  vector<string> values = splitline(line);
  string key1 = values[0] + values[1];
  map <string, float> rates;
  rates["1217Alcohol"] = stof(values[8]);
  rates["1825Alcohol"] = stof(values[9]);
  rates["26+Alcohol"] = stof(values[10]);
  rates["1217IllicitDrugs"] = stof(values[26]);
  rates["1825IllicitDrugs"] = stof(values[27]);
  rates["26+IllicitDrugs"] = stof(values[28]);
  rates["1217Marijuana"] = stof(values[44]);
  rates["1825Marijuana"] = stof(values[45]);
  rates["26+Marijuana"] = stof(values[46]);

  drugmap[key1] = rates;
  }
  return drugmap;
}
*/
class Heap {
private:
	vector<double> heap;
	string type;
	bool isMax;
	int size;

public:
	Heap(string type) {
		heap = {};
		this->type = type;
		size = 0;

		if (type == "max")
			isMax = true;
		else
			isMax = false;
	}

	double getTop() { return heap[0]; }

	double extractTop() {
		double top = heap[0];
		heap[0] = heap[size - 1];
		heap.pop_back();
		size--;
		if (isMax)
			heapifyDown(0);
		else
			minHeapifyDown(0);
		return top;
	}

	void insert(double val) {
		heap.push_back(val);
		size++;
		if (isMax)
			heapifyUp(size - 1);
		else
			minHeapifyUp(size - 1);
	}

	void heapifyDown(int index) {
		int left, right, largest;

		left = 2 * index + 1;
		right = 2 * index + 2;
		largest = index;

		if (left < size &&
			(heap[left] > heap[index] || (heap[left] == heap[index] && isMax)))
			largest = left;
		if (right < size && (heap[right] > heap[largest] ||
			(heap[right] == heap[largest] && isMax)))
			largest = right;
		if (largest != index) {
			double temp = heap[index];
			heap[index] = heap[largest];
			heap[largest] = temp;
			heapifyDown(largest);
		}
	}

	void heapifyUp(int index) {
		if (index == 0)
			return;
		int parent = (index - 1) / 2;
		if (heap[index] > heap[parent] || (heap[index] == heap[parent] && isMax)) {
			double temp = heap[index];
			heap[index] = heap[parent];
			heap[parent] = temp;
			heapifyUp(parent);
		}
	}

	void minHeapifyDown(int index) {
		int left, right, smallest;

		left = 2 * index + 1;
		right = 2 * index + 2;
		smallest = index;

		if (left < size && heap[left] < heap[index]) {
			smallest = left;
		}
		if (right < size && heap[right] < heap[smallest]) {
			smallest = right;
		}
		if (smallest != index) {
			double temp = heap[index];
			heap[index] = heap[smallest];
			heap[smallest] = temp;
			minHeapifyDown(smallest);
		}
	}

	void minHeapifyUp(int index) {
		if (index == 0)
			return;
		int parent = (index - 1) / 2;
		if (heap[index] < heap[parent]) {
			double temp = heap[index];
			heap[index] = heap[parent];
			heap[parent] = temp;
			minHeapifyUp(parent);
		}
	}

	int getSize() { return this->size; }
};

int main() {

	HashMap test(300, 0.5);
	insertData(test, "drugs.csv");
	test.print();
	/*
	bool marijuana = true;
	bool drug = true;
	bool alcohol = true;
	bool young = true;
	bool youngAdult = false;
	bool adult = true;

	/* Example
	 * State: Alabama
	 * Substance: Alcohol, Marijuana
	 * Age: 12-17, 26+
	 * Heapifies based on the entire set of values given (64 total)
	 *

	Heap substanceRates("max");

	// different type of substance inputs
	if (marijuana) {
		if (young) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "1217Marijuana";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(rate);
			}
		}
		if (youngAdult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "1825Marijuana";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(rate);
			}
		}
		if (adult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "26+Marijuana";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(rate);
			}
		}
	}
	if (alcohol) {
		if (young) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "1217Alcohol";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(rate);
			}
		}
		if (youngAdult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "1825Alcohol";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(rate);
			}
		}
		if (adult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "26+Alcohol";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(rate);
			}
		}
	}
	if (drug) {
		if (young) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "1217IllicitDrugs";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(rate);
			}
		}
		if (youngAdult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "1825IllicitDrugs";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(rate);
			}
		}
		if (adult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "26+IllicitDrugs";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(rate);
			}
		}
	}

	// prints out everything
	while (substanceRates.getSize() != 0) {
		for (auto &i : test.map) {
			if (i.second == substanceRates.getTop()) {
				string year = i.first.substr(0, 4);
				string ageGroup = i.first.substr(4, 4);
				string substance = i.first.substr(8, i.first.size() - 8);
				cout << "Year: " << year << " Substance: " << substance
					<< " Age group: " << ageGroup
					<< " Rate: " << substanceRates.getTop() << endl;
				break;
			}
		}
		substanceRates.extractTop();
	}
	*/
	return 0;
}

;