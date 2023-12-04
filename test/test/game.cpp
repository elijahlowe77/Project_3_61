// test.cpp : This file contains the 'main' function. Program execution begins and ends there.







#include "SFML/Graphics.hpp"
#include <set>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace sf;
class Button {
public:
	Color defaultColor; Color hoverColor; CircleShape circle; CircleShape circle2;
	bool Clicked;
	Button(float x, float y, float width, Color defaultColorr)
		: defaultColor(this->defaultColor)
	{
		circle.setPosition(x, y);
		circle.setRadius(width);
		circle.setFillColor(defaultColor);
		circle2.setPosition(x + 50, y);
		circle2.setRadius(width);
		circle2.setFillColor(defaultColor);
		Clicked = false;
	}
	bool mouseOver1(sf::RenderWindow& window) {

		Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
		return circle.getGlobalBounds().contains(mousePos);
	}
	bool mouseOver2(sf::RenderWindow& window) {

		Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
		return circle2.getGlobalBounds().contains(mousePos);
	}

	int update(RenderWindow& window) {
		window.draw(circle); window.draw(circle2);
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (mouseOver1(window)) {
				circle.setFillColor(Color::Blue);
				window.draw(circle);
				circle2.setFillColor(defaultColor);
				window.draw(circle2);
				return 1;
			}

			if (mouseOver2(window)) {
				circle2.setFillColor(Color::Blue);
				window.draw(circle2);
				circle.setFillColor(defaultColor);
				window.draw(circle);
				return 2;
			}

		}



		return -1;


	}





};
class Imagef {
public:
	Imagef(String state) {

		std::string def = "C:\\Users\\E\\source\\repos\\test\\test\\States";
		state = def + "\\" + state + ".png";
		if (!texture.loadFromFile(state)) {
			std::cout << "FAILED TO LOAD !!";
		}
		std::cout << "default";
		image.setTexture(texture);
		image.setPosition(500, 200);
		//image.setScale(0.35f, 0.35f);

	}


	Texture texture; Texture texture2;
	Sprite image;  Sprite image2;

	void set(std::string _state) {

		std::string def = "C:\\Users\\E\\source\\repos\\test\\test\\States";
		_state = def + "\\" + _state + ".png";
		if (!texture2.loadFromFile(_state)) {

			std::cout << "FAILED TO LOAD !!";
		}

		image2.setTexture(texture2);
		image2.setPosition(500, 200);
		image2.setScale(0.35f, 0.35f);

	} 
	void set(std::string _state,int x,int y) {

		std::string def = "C:\\Users\\E\\source\\repos\\test\\test\\States";
		_state = def + "\\" + _state + ".png";
		if (!texture2.loadFromFile(_state)) {

			std::cout << "FAILED TO LOAD !!";
		}

		image2.setTexture(texture2);
		image2.setPosition(x, y);
		image2.setScale(0.35f, 0.35f);

	}
	void set2(std::string _state, int x, int y, float s) {

		std::string def = "C:\\Users\\E\\source\\repos\\test\\test\\States";
		_state = def + "\\" + _state + ".png";
		if (!texture2.loadFromFile(_state)) {

			std::cout << "FAILED TO LOAD !!";
		}

		image2.setTexture(texture2);
		image2.setPosition(x, y);
		image2.setScale(s, s);

	}

};
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
	pair<string, float> getPair(string key) {
		for (int i = 0; i < drugmap.size(); i++) {
			if (drugmap[i].first == key) {
				return drugmap[i];
			}
		}
		return make_pair("FAIL",-1);
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
			if (hashedIndex >= map.size() - 1) { hashedIndex = 0; }
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
void insertData(HashMap &map, string filename, string state) {

	ifstream file("drugs.csv");
	string line;
	getline(file, line);
	string prev = "";
	while (getline(file, line)) {

		vector<string> values = splitline(line);
		if (state != values[0]) { continue; }

		if (stoi(values[1]) > 2009 && prev != values[1]) {
			cout << "State: " << values[0] << endl;
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


class Heap {
private:
	vector<pair<string, float>> heap;
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

	pair<string,float> getTop() { return heap[0]; }

	pair<string, float> extractTop() {
		pair<string,float> top = heap[0];
		heap[0] = heap[size - 1];
		heap.pop_back();
		size--;
		if (isMax)
			heapifyDown(0);
		else
			minHeapifyDown(0);
		return top;
	}

	void insert(string name, float val) {
		heap.push_back(make_pair(name,val));

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
			(heap[left].second > heap[index].second || (heap[left].second == heap[index].second && isMax)))
			largest = left;
		if (right < size && (heap[right].second > heap[largest].second ||
			(heap[right].second == heap[largest].second && isMax)))
			largest = right;
		if (largest != index) {
			pair<string,float> temp = heap[index];
			heap[index] = heap[largest];
			heap[largest] = temp;
			heapifyDown(largest);
		}
	}

	void heapifyUp(int index) {
		if (index == 0)
			return;
		int parent = (index - 1) / 2;
		if (heap[index].second > heap[parent].second || (heap[index].second == heap[parent].second && isMax)) {
			pair<string,float> temp = heap[index];
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

		if (left < size && heap[left].second < heap[index].second) {
			smallest = left;
		}
		if (right < size && heap[right].second < heap[smallest].second) {
			smallest = right;
		}
		if (smallest != index) {
			pair<string,float> temp = heap[index];
			heap[index] = heap[smallest];
			heap[smallest] = temp;
			minHeapifyDown(smallest);
		}
	}

	void minHeapifyUp(int index) {
		if (index == 0)
			return;
		int parent = (index - 1) / 2;
		if (heap[index].second < heap[parent].second) {
			pair<string,float> temp = heap[index];
			heap[index] = heap[parent];
			heap[parent] = temp;
			minHeapifyUp(parent);
		}
	}

	int getSize() { return this->size; }
};

void dataRankerHashMap(set<string>& iterators,  Heap& substanceRates, HashMap& test, bool marijuana, bool drug, bool alcohol, bool young, bool youngAdult, bool adult) {

	cout << "Weed " << marijuana << endl; 

	cout << "Drug " << drug << endl; 

	cout << "Alc " << alcohol << endl;
	if (!marijuana) {
		
		if (!young) {

			for (int i = 2010; i < 2018; i++) {

				string innerMapName = to_string(i) + "1217Marijuana";

				double rate = test.GetRate(innerMapName);

				substanceRates.insert(innerMapName, rate); 
				iterators.insert(innerMapName);
			}
		}
		if (!youngAdult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "1825Marijuana";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(innerMapName,rate); 
				iterators.insert(innerMapName);
			}
		}
		if (!adult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "26+Marijuana";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(innerMapName,rate); 
				iterators.insert(innerMapName);
			}
		}
	}
	if (!alcohol) { 
		
		if (!young) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "1217Alcohol";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(innerMapName, rate); 
				iterators.insert(innerMapName);
			}
		}
		if (!youngAdult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "1825Alcohol";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(innerMapName, rate); 
				iterators.insert(innerMapName);
			}
		}
		if (!adult) {
			for (int i = 2010; i < 2018; i++) { 
				
				string innerMapName = to_string(i) + "26+Alcohol";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(innerMapName, rate); 
				iterators.insert(innerMapName);
			}
		}
	}
	if (!drug) { 

		if (!young) {
			for (int i = 2010; i < 2018; i++) { 
				
				string innerMapName = to_string(i) + "1217IllicitDrugs";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(innerMapName, rate); 
				iterators.insert(innerMapName);
			}
		}
		if (!youngAdult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "1825IllicitDrugs";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(innerMapName, rate); 
				iterators.insert(innerMapName);
			}
		}
		if (!adult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "26+IllicitDrugs";
				double rate = test.GetRate(innerMapName);
				substanceRates.insert(innerMapName, rate); 
				iterators.insert(innerMapName);
			}
		}
	}

} 
void dataRankerMap(set<string>& iterators, Heap& substanceRates, Map& test, bool marijuana, bool drug, bool alcohol, bool young, bool youngAdult, bool adult) {

	cout << "Weed " << marijuana << endl;

	cout << "Drug " << drug << endl;

	cout << "Alc " << alcohol << endl;
	if (!marijuana) {

		if (!young) {

			for (int i = 2010; i < 2018; i++) {

				string innerMapName = to_string(i) + "1217Marijuana";

				double rate = test.get(innerMapName);

				substanceRates.insert(innerMapName, rate);
				iterators.insert(innerMapName);
			}
		}
		if (!youngAdult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "1825Marijuana";
				double rate = test.get(innerMapName);
				substanceRates.insert(innerMapName, rate);
				iterators.insert(innerMapName);
			}
		}
		if (!adult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "26+Marijuana";
				double rate = test.get(innerMapName);
				substanceRates.insert(innerMapName, rate);
				iterators.insert(innerMapName);
			}
		}
	}
	if (!alcohol) {

		if (!young) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "1217Alcohol";
				double rate = test.get(innerMapName);
				substanceRates.insert(innerMapName, rate);
				iterators.insert(innerMapName);
			}
		}
		if (!youngAdult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "1825Alcohol";
				double rate = test.get(innerMapName);
				substanceRates.insert(innerMapName, rate);
				iterators.insert(innerMapName);
			}
		}
		if (!adult) {
			for (int i = 2010; i < 2018; i++) {

				string innerMapName = to_string(i) + "26+Alcohol";
				double rate = test.get(innerMapName);
				substanceRates.insert(innerMapName, rate);
				iterators.insert(innerMapName);
			}
		}
	}
	if (!drug) {

		if (!young) {
			for (int i = 2010; i < 2018; i++) {

				string innerMapName = to_string(i) + "1217IllicitDrugs";
				double rate = test.get(innerMapName);
				substanceRates.insert(innerMapName, rate);
				iterators.insert(innerMapName);
			}
		}
		if (!youngAdult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "1825IllicitDrugs";
				double rate = test.get(innerMapName);
				substanceRates.insert(innerMapName, rate);
				iterators.insert(innerMapName);
			}
		}
		if (!adult) {
			for (int i = 2010; i < 2018; i++) {
				string innerMapName = to_string(i) + "26+IllicitDrugs";
				double rate = test.get(innerMapName);
				substanceRates.insert(innerMapName, rate);
				iterators.insert(innerMapName);
			}
		}
	}

}




int main(){
	vector<string> states = {
	   "Alabama", "Alaska", "Arizona", "Arkansas", "California",
	   "Colorado", "Connecticut", "Delaware", "Florida", "Georgia",
	   "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa",
	   "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland",
	   "Massachusetts", "Michigan", "Minnesota", "Mississippi", "Missouri",
	   "Montana", "Nebraska", "Nevada", "New Hampshire", "New Jersey",
	   "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio",
	   "Oklahoma", "Oregon", "Pennsylvania", "Rhode Island", "South Carolina",
	   "South Dakota", "Tennessee", "Texas", "Utah", "Vermont",
	   "Virginia", "Washington", "West Virginia", "Wisconsin", "Wyoming"
	};


	sf::RenderWindow window(sf::VideoMode(800, 800), "Test");
	sf::Event e;
	// texts  
	sf::Text ttext;  sf::Text state; sf::Text ask; sf::Text alc; sf::Text hard; sf::Text ask2; sf::Text za; sf::Text age;
	sf::Font font; sf::Text a1; sf::Text a2; sf::Text a3; sf::Text stateE;
	sf::Text go;

	//output string vector in order of 1: State, 2: Alcohol(1 or 0), 3: Cocaine, 4:Marijuana 5: 12-17, 6:1-25, 7: 25+
	vector<string> output(7);

	if (!font.loadFromFile("font.ttf")) {
		return -1;
	}



	ttext.setFont(font);
	ttext.setFillColor(sf::Color::White);

	ttext.setCharacterSize(20);
	ttext.setString("Is My State Addicted?");
	ttext.setFillColor(sf::Color::White);
	ttext.setPosition(250, 75);

	state.setFont(font);
	state.setFillColor(sf::Color::White);

	state.setCharacterSize(20);
	state.setString("STATE:");
	state.setFillColor(sf::Color::White);
	state.setPosition(75, 225);

	stateE.setFont(font);
	stateE.setFillColor(sf::Color::White);

	stateE.setCharacterSize(20);
	stateE.setFillColor(sf::Color::White);
	stateE.setPosition(175, 225);

	ask.setFont(font);
	ask.setFillColor(sf::Color::White);

	ask.setCharacterSize(30);
	ask.setString("Please Enter...");
	ask.setFillColor(sf::Color::White);
	ask.setPosition(75, 150);


	go.setFont(font);
	go.setFillColor(sf::Color::White);

	go.setCharacterSize(25);
	go.setString("Continue?");
	go.setFillColor(sf::Color::Red);
	go.setPosition(500, 740);


	ask2.setFont(font);
	ask2.setFillColor(sf::Color::White);

	ask2.setCharacterSize(30);
	ask2.setString("Please Select...  (y/n)");
	ask2.setFillColor(sf::Color::White);
	ask2.setPosition(75, 275);


	alc.setFont(font);
	alc.setFillColor(sf::Color::White);

	alc.setCharacterSize(20);
	alc.setString("Alcohol");
	alc.setFillColor(sf::Color::White);
	alc.setPosition(75, 350);
	Button alcButton(200, 345, 15, sf::Color::Green);

	hard.setFont(font);
	hard.setFillColor(sf::Color::White);

	hard.setCharacterSize(20);
	hard.setString("Cocaine");
	hard.setFillColor(sf::Color::White);
	hard.setPosition(75, 400);
	Button hardButton(200, 395, 15, sf::Color::Green);


	za.setFont(font);
	za.setFillColor(sf::Color::White);

	za.setCharacterSize(20);
	za.setString("Marijuana");
	za.setFillColor(sf::Color::White);
	za.setPosition(75, 450);
	Button zaButton(200, 445, 15, sf::Color::Green);

	age.setFont(font);
	age.setFillColor(sf::Color::White);

	age.setCharacterSize(30);
	age.setString("Age Group: (y/n)");
	age.setFillColor(sf::Color::White);
	age.setPosition(75, 490);

	a1.setFont(font);
	a1.setFillColor(sf::Color::White);

	a1.setCharacterSize(20);
	a1.setString("12-17");
	a1.setFillColor(sf::Color::White);
	a1.setPosition(75, 550);
	Button a1Button(200, 545, 15, sf::Color::Green);


	a2.setFont(font);
	a2.setFillColor(sf::Color::White);

	a2.setCharacterSize(20);
	a2.setString("18-25");
	a2.setFillColor(sf::Color::White);
	a2.setPosition(75, 590);
	Button a2Button(200, 585, 15, sf::Color::Green);

	a3.setFont(font);
	a3.setFillColor(sf::Color::White);

	a3.setCharacterSize(20);
	a3.setString("25+");
	a3.setFillColor(sf::Color::White);
	a3.setPosition(75, 630);
	Button a3Button(200, 625, 15, sf::Color::Green); 

	sf::Text maxS; sf::Text minS;

	maxS.setFont(font);
	maxS.setFillColor(sf::Color::White);

	maxS.setCharacterSize(20);
	maxS.setString("Greatest to Least");
	maxS.setFillColor(sf::Color::White);
	maxS.setPosition(25, 720); 

	minS.setFont(font);
	minS.setFillColor(sf::Color::White);

	minS.setCharacterSize(20);
	minS.setString("Least to Greatest");
	minS.setFillColor(sf::Color::White);
	minS.setPosition(345, 720);
	
	Button heapButton(245, 720, 15, sf::Color::Red);
	string heapName = ""; 

	bool isMap = false;
	sf::Text mapS; sf::Text hashS;

	mapS.setFont(font);
	mapS.setFillColor(sf::Color::White);

	mapS.setCharacterSize(20);
	mapS.setString("              Map");
	mapS.setFillColor(sf::Color::White);
	mapS.setPosition(25, 679);

	hashS.setFont(font);
	hashS.setFillColor(sf::Color::White);

	hashS.setCharacterSize(20);
	hashS.setString("Hash");
	hashS.setFillColor(sf::Color::White);
	hashS.setPosition(345, 679);

	Button structButton(245, 679, 15, sf::Color::Red);
	



	
	int order = 0;

	//button
	string inputString;
	int alcOpt = 1; int hardOpt = 1; int zaOpt = 1; int a1Opt = 1; int a2Opt = 1; int a3Opt = 1;

	Imagef statef("Ohio"); Imagef hardf("Ohio"); Imagef zaf("Ohio");
	Imagef a1f("Ohio"); Imagef a2f("Ohio"); Imagef a3f("Ohio"); Imagef alcs("Alc"); Imagef arrow("RedArrow");

	using namespace std;
	while (window.isOpen()) {


		while (window.pollEvent(e)) {

			if (e.type == sf::Event::Closed)
				window.close();
			if (order == 0)
			{
				auto iter = find(states.begin(), states.end(), inputString);

				if (e.type == sf::Event::TextEntered) {

					if (e.text.unicode < 126) {

						if (e.text.unicode == 8 && !inputString.empty()) // Backspace
						{
							cout << "Delete";
							inputString.pop_back();
						}
						else if (e.text.unicode == 13) {

							if (iter != states.end())
							{
								cout << "clicked entered: " << inputString << endl;
								output[0] = inputString;
								order++;

								statef.set(inputString);

							}

							//inputString.clear();
						}
						else {
							inputString += static_cast<char>(e.text.unicode);
						}

						stateE.setString(inputString);

					}

				}

			}
			int optA = alcButton.update(window);
			int optH = hardButton.update(window);
			int optZ = zaButton.update(window);
			int optA1 = a1Button.update(window);
			int optA2 = a2Button.update(window);
			int optA3 = a3Button.update(window);
			int isMax = heapButton.update(window); 
			int isHash = structButton.update(window);

			if (optA > 0) {
				alcOpt = optA - 1;
				if (alcOpt == 0)
					alcs.set2("Alc", 500, 500, 0.1);
				else alcs.set2("Bruh", 550, 530, 0.001); 
			}
			if (optH > 0) {
				hardOpt = optH - 1;
				if (hardOpt == 0)
					hardf.set2("Drugs", 550, 530, 0.1);
				else hardf.set2("Bruh", 550, 530, 0.001);
			}
			if (optZ > 0) {
				zaOpt = optZ - 1;
				if (zaOpt == 0)
					zaf.set2("Weed", 650, 500, 0.1);
				else zaf.set2("Bruh", 550, 530, 0.001);
			}
			if (optA1 > 0) {
				a1Opt = optA1 - 1;
				if (a1Opt == 0)
					a1f.set2("Teenager", 490, 600, 0.2);
				else a1f.set2("Bruh", 550, 530, 0.001);
			}
			if (optA2 > 0) {
				a2Opt = optA2 - 1;
				if (a2Opt == 0)
					a2f.set2("Adult", 570, 600, 0.2);
				else a2f.set2("Bruh", 550, 530, 0.001);
			}
			if (optA3 > 0) {
				a3Opt = optA3 - 1;
				if (a3Opt == 0)
					a3f.set2("Old", 660, 590, 0.15);
				else a3f.set2("Bruh", 550, 530, 0.001);
			}  
			if (isMax > 0) { 
				
				if ((isMax - 1) == 0) { 
					
					heapName = "max";
				}
				else {
			
					heapName = "min";
				}
			}
			if (isHash > 0) {
				if ((isHash - 1) == 0) { 
					isMap = true;
				}
				else { 
					
					isMap = false;
				}
			}
			

		}


		window.clear();
		window.draw(ttext); window.draw(state); window.draw(ask); window.draw(alc); window.draw(ask2); window.draw(hard);
		window.draw(za); window.draw(age); window.draw(a1); window.draw(a2); window.draw(a3); window.draw(stateE);
		window.draw(statef.image2); window.draw(hardf.image2); window.draw(zaf.image2);  window.draw(alcs.image2);
		window.draw(a1f.image2); window.draw(a2f.image2); window.draw(a3f.image2); 

		window.draw(maxS); window.draw(minS);
		window.draw(mapS); window.draw(hashS);

		alcButton.update(window);
		hardButton.update(window);
		zaButton.update(window);
		a1Button.update(window);
		a2Button.update(window);
		a3Button.update(window); 
		heapButton.update(window);
		structButton.update(window);

		arrow.set2("RedArrow", 650, 730, 0.03);

		window.draw(arrow.image2); window.draw(go);
		Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
		if (Mouse::isButtonPressed(Mouse::Left)) {
			std::cout << arrow.image2.getLocalBounds().left << " " << arrow.image2.getLocalBounds().top;
			if (arrow.image2.getGlobalBounds().contains(mousePos)) {
				window.close();
			}
		}


		//alcButton.draw(window);

		window.display();

	}

	sf::RenderWindow window2(sf::VideoMode(1600, 1300), "Showcase");
	sf::Event e2; sf::Text title;

	title.setFont(font);
	title.setFillColor(sf::Color::Black);

	title.setCharacterSize(30);
	title.setString(inputString);
	title.setFillColor(sf::Color::White);
	title.setPosition(730, 75);
	Imagef stateT("Ohio");  stateT.set(inputString,970,63);  


	//HashMap test(300, 0.5);
	HashMap test(300, 0.5); 
	insertData(test, "drugs.csv", inputString); 

	Map test2 = readcsv("drugs.csv");

	Heap substanceRates(heapName); 
	vector<sf::Text> displayer;  

	vector<sf::Text> A1217; 
	vector<sf::Text> A1825;
	vector<sf::Text> A26;  

	vector<sf::Text> C1217;
	vector<sf::Text> C1825;
	vector<sf::Text> C26;

	vector<sf::Text> M1217;
	vector<sf::Text> M1825;
	vector<sf::Text> M26;

	set<string> iterators; 
	if (!isMap) {
		dataRankerHashMap(iterators, substanceRates, test, zaOpt, hardOpt, alcOpt, a1Opt, a2Opt, a3Opt); //HashMap Implimentation 
	}
	else {
		dataRankerMap(iterators, substanceRates, test2, zaOpt, hardOpt, alcOpt, a1Opt, a2Opt, a3Opt); //Map Implimentation
	}
	

	set<string> added;
	while (substanceRates.getSize() != 0) { 

		for (auto &j : iterators) {  
				
				int hashedIndex = int(test.hash(j));     
				pair<string, float> i;
				if (!isMap)
				{
					i = test.map[hashedIndex]; 
					cout << "Hash" << endl;
				} 
				else {
					i = test2.getPair(j);  
					cout << "Map" << endl;
				}
				if (i.first == substanceRates.getTop().first && i.second == substanceRates.getTop().second) {
					
				
				sf::Text tempText;
				tempText.setFont(font);
				tempText.setFillColor(sf::Color::White);

				tempText.setCharacterSize(10);
				
				tempText.setFillColor(sf::Color::White);
				
				string year = i.first.substr(0, 4);
				string ageGroup = i.first.substr(4, 4);
				string substance = i.first.substr(8, i.first.size() - 8);   
				string rateS =  to_string(int(substanceRates.getTop().second));   
				string security = substance + ageGroup + year + rateS;
				//string rank = to_string(displayer.size() + 1); 
				
				
				if (substance == "Alcohol" || substance == "lcohol") {
					if (ageGroup == "1217")  
					{  
					
						string rank = to_string(A1217.size() + 1);
						string tempFinal = rank + ". Year: " + year + ", Percentage of Population Abuse: " + rateS + "%";
						tempText.setString(tempFinal); 
						  
						int sizePrev = added.size();
						added.insert(security);  
						if(sizePrev < added.size())
							A1217.push_back(tempText);
					} 
					if (ageGroup == "1825")  
					{
						string rank = to_string(A1825.size() + 1);
						string tempFinal = rank + ". Year: " + year + ", Percentage of Population Abuse: " + rateS + "%";
						tempText.setString(tempFinal);  
					
						int sizePrev = added.size();
						added.insert(security);
						if (sizePrev < added.size())
							A1825.push_back(tempText);
					} 
					if (ageGroup == "26+A")  
					{
						string rank = to_string(A26.size() + 1);
						string tempFinal = rank + ". Year: " + year + ", Percentage of Population Abuse: " + rateS + "%";
						tempText.setString(tempFinal); 
					
						int sizePrev = added.size();
						added.insert(security);
						if (sizePrev < added.size())
							A26.push_back(tempText);
					}
				} 
				else if (substance == "IllicitDrugs" || substance == "llicitDrugs") {
					
					if (ageGroup == "1217")
					{ 
						
						string rank = to_string(C1217.size() + 1);
						string tempFinal = rank + ". Year: " + year + ", Percentage of Population Abuse: " + rateS + "%";
						tempText.setString(tempFinal); 
					
						int sizePrev = added.size();
						added.insert(security);
						if (sizePrev < added.size())
							C1217.push_back(tempText); 
					}
					if (ageGroup == "1825")
					{
						string rank = to_string(C1825.size() + 1);
						string tempFinal = rank + ". Year: " + year + ", Percentage of Population Abuse: " + rateS + "%";
						tempText.setString(tempFinal); 
					
						int sizePrev = added.size();
						added.insert(security);
						if (sizePrev < added.size())
							C1825.push_back(tempText); 
					}
					if (ageGroup == "26+I")
					{
						string rank = to_string(C26.size() + 1);
						string tempFinal = rank + ". Year: " + year + ", Percentage of Population Abuse: " + rateS + "%";
						tempText.setString(tempFinal); 
					
						int sizePrev = added.size();
						added.insert(security);
						if (sizePrev < added.size())
							C26.push_back(tempText); 
					}
				} 
				else if (substance == "Marijuana" || substance == "arijuana") {
					if (ageGroup == "1217")
					{
						string rank = to_string(M1217.size() + 1);
						string tempFinal = rank + ". Year: " + year + ", Percentage of Population Abuse: " + rateS + "%";
						tempText.setString(tempFinal); 
						
						int sizePrev = added.size();
						added.insert(security);
						if (sizePrev < added.size())
							M1217.push_back(tempText);
					}
					if (ageGroup == "1825")
					{
						string rank = to_string(M1825.size() + 1);
						string tempFinal = rank + ". Year: " + year + ", Percentage of Population Abuse: " + rateS + "%";
						tempText.setString(tempFinal); 
					
						int sizePrev = added.size();
						added.insert(security);
						if (sizePrev < added.size())
							M1825.push_back(tempText);
					}
					if (ageGroup == "26+M")
					{
						string rank = to_string(M26.size() + 1);
						string tempFinal = rank + ". Year: " + year + ", Percentage of Population Abuse: " + rateS + "%";
						tempText.setString(tempFinal); 
						
						int sizePrev = added.size();
						added.insert(security);
						if (sizePrev < added.size())
							M26.push_back(tempText);
					}
				}

				}
				//string tempTotal = rank + ". Year: " + year + " Substance: " + substance + " Age group: " + ageGroup + " Rate: " + rateS;
				//cout << "TEMP TOTAL!! " <<tempTotal;
				//tempText.setString(tempTotal);
				//displayer.push_back(tempText); 
			
			}
		
		substanceRates.extractTop();
	}  
	

	sf::Sprite a1217f; sf::Sprite alc1217f;
	sf::Text youngDrinkers;  
	youngDrinkers.setFont(font);
	youngDrinkers.setFillColor(sf::Color::White);
	youngDrinkers.setCharacterSize(15);
	youngDrinkers.setFillColor(sf::Color::White); 
	youngDrinkers.setString("Proportion of 12-17 Year Olds Who Drink");
	youngDrinkers.setPosition(50,300); 

	sf::Sprite a1825f; sf::Sprite alc1825f;
	sf::Text adultDrinkers;
	adultDrinkers.setFont(font);
	adultDrinkers.setFillColor(sf::Color::White);
	adultDrinkers.setCharacterSize(15);
	adultDrinkers.setFillColor(sf::Color::White);
	adultDrinkers.setString("Proportion of 18-25 Year Olds Who Drink");
	adultDrinkers.setPosition(50, 650); 


	sf::Sprite a26f; sf::Sprite alc26f;
	sf::Text oldDrinkers;
	oldDrinkers.setFont(font);
	oldDrinkers.setFillColor(sf::Color::White);
	oldDrinkers.setCharacterSize(15);
	oldDrinkers.setFillColor(sf::Color::White);
	oldDrinkers.setString("Proportion of 26+ Year Olds Who Drink");
	oldDrinkers.setPosition(50, 650 + 350);

	sf::Sprite c1217f; sf::Sprite coc1217f;
	sf::Text youngHard;
	youngHard.setFont(font);
	youngHard.setFillColor(sf::Color::White);
	youngHard.setCharacterSize(15);
	youngHard.setFillColor(sf::Color::White);
	youngHard.setString("Proportion of 12-17 Year Olds Who Do Hard Drugs");
	youngHard.setPosition(50 + 530, 300);

	sf::Sprite c1825f; sf::Sprite coc1825f;
	sf::Text adultHard;
	adultHard.setFont(font);
	adultHard.setFillColor(sf::Color::White);
	adultHard.setCharacterSize(15);
	adultHard.setFillColor(sf::Color::White);
	adultHard.setString("Proportion of 18-25 Year Olds Who Do Hard Drugs");
	adultHard.setPosition(50 + 530, 650);


	sf::Sprite c26f; sf::Sprite coc26f;
	sf::Text oldHard;
	oldHard.setFont(font);
	oldHard.setFillColor(sf::Color::White);
	oldHard.setCharacterSize(15);
	oldHard.setFillColor(sf::Color::White);
	oldHard.setString("Proportion of 26+ Year Olds Who Do Hard Drugs");
	oldHard.setPosition(50 + 530, 650 + 350); 

	sf::Sprite m1217f; sf::Sprite mar1217f;
	sf::Text youngZa;
	youngZa.setFont(font);
	youngZa.setFillColor(sf::Color::White);
	youngZa.setCharacterSize(15);
	youngZa.setFillColor(sf::Color::White);
	youngZa.setString("Proportion of 12-17 Year Olds Who Smoke Weed");
	youngZa.setPosition(50 + 530*2, 300);

	sf::Sprite m1825f; sf::Sprite mar1825f;
	sf::Text adultZa;
	adultZa.setFont(font);
	adultZa.setFillColor(sf::Color::White);
	adultZa.setCharacterSize(15);
	adultZa.setFillColor(sf::Color::White);
	adultZa.setString("Proportion of 18-25 Year Olds Who Smoke Weed");
	adultZa.setPosition(50 + 530*2, 650);


	sf::Sprite m26f; sf::Sprite mar26f;
	sf::Text oldZa;
	oldZa.setFont(font);
	oldZa.setFillColor(sf::Color::White);
	oldZa.setCharacterSize(15);
	oldZa.setFillColor(sf::Color::White);
	oldZa.setString("Proportion of 26+ Year Olds Who Smoke Weed");
	oldZa.setPosition(50 + 530*2, 650 + 350);


	


	while (window2.isOpen()) { 
	
		
		//cout << "Hello";   
		window.clear();   
		int xPos = 50;
		int yPos = 330; 
		if(!alcOpt){ 
			if(!a1Opt){
			for (auto text : A1217) { 
				//cout << text.getString().toAnsiString() << endl; 

				//Teen Image 
				a1f.set2("Teenager", 100, 160, 0.2); 
				a1217f  = a1f.image2; 

				//Alc Image
				alcs.set2("Alc", 220, 180, 0.1);
				alc1217f = alcs.image2;


				text.setPosition(xPos, yPos); 
				yPos += 25; 
				window2.draw(text);
			}   
		} 
			
		yPos = 675;  
		if (!a2Opt) {
			for (auto text : A1825) { 

				//cout << text.getString().toAnsiString() << endl; 

				//Adult Image 
				a2f.set2("Adult", 100, 160 * 3.3, 0.2);
				a1825f = a2f.image2;

				//Alc Image
				alcs.set2("Alc", 220, 180 * 3, 0.1);
				alc1825f = alcs.image2;


				text.setPosition(xPos, yPos);
				yPos += 25;
				window2.draw(text);
			}
		}
		
		yPos = 1025;   
		cout << "sssssssssssssssssss" << yPos;
		if (!a3Opt) {
			for (auto text : A26) {
				//cout << text.getString().toAnsiString() << endl; 

				//Adult Image 
				a3f.set2("Old", 100, 160 * 5.5, 0.15);
				a26f = a3f.image2;

				//Alc Image
				alcs.set2("Alc", 220, 180 * 5, 0.1);
				alc26f = alcs.image2;


				text.setPosition(xPos, yPos);
				yPos += 25;
				window2.draw(text);
			}
		}
		
		}
		int shift2 = 7;
		int xPos2 = 600; 
		int yPos2 = 330;
		for (auto text : C1217) { 
			
			//cout << text.getString().toAnsiString() << endl; 

			//Teen Image 
			a1f.set2("Teenager", 100 * shift2, 160, 0.2);
			c1217f = a1f.image2;

			//Drug Image
			hardf.set2("Drugs", 220 * shift2/1.85, 200, 0.1);
			coc1217f = hardf.image2;

			
			text.setPosition(xPos2, yPos2);
			yPos2 += 25;
			window2.draw(text);
		}
		yPos2 = 675;
		for (auto text : C1825) {
			//cout << text.getString().toAnsiString() << endl; 

			//Adult Image 
			a2f.set2("Adult", 100 * shift2, 160 * 3.3, 0.2);
			c1825f = a2f.image2;

			//Drug Image
			hardf.set2("Drugs", 220 * shift2/1.85, 190 * 3.1, 0.1);
			coc1825f = hardf.image2;


			text.setPosition(xPos2, yPos2);
			yPos2 += 25;
			window2.draw(text);
		}
		yPos2 = 1025;

		for (auto text : C26) {
			//cout << text.getString().toAnsiString() << endl; 

			//Adult Image 
			a3f.set2("Old", 100 * shift2, 160 * 5.5, 0.15);
			c26f = a3f.image2;

			//Drug Image
			hardf.set2("Drugs", 220 * shift2/1.85, 187 *5, 0.1);
			coc26f = hardf.image2;


			text.setPosition(xPos2, yPos2);
			yPos2 += 25;
			window2.draw(text);
		} 
		int shift3 = 12;
		int xPos3 = 1130;
		int yPos3 = 330;
		for (auto text : M1217) {
			cout << text.getString().toAnsiString() << endl;

			//Teen Image 
			a1f.set2("Teenager", 100 * shift3, 160, 0.2);
			m1217f = a1f.image2;

			//Drug Image
			zaf.set2("Weed", 220 * shift3 / 2, 200, 0.1);
			mar1217f = zaf.image2;


			text.setPosition(xPos3, yPos3);
			yPos3 += 25;
			window2.draw(text);
		}
		yPos3 = 675;
		for (auto text : M1825) {
			cout << text.getString().toAnsiString() << endl;

			//Adult Image 
			a2f.set2("Adult", 100 * shift3, 160 * 3.3, 0.2);
			m1825f = a2f.image2;

			//Drug Image
			zaf.set2("Weed", 220 * shift3 / 2, 190 * 3.1, 0.1);
			mar1825f = zaf.image2;

		
			text.setPosition(xPos3, yPos3);
			yPos3 += 25;
			window2.draw(text);
		}
		yPos3 = 1025;

		for (auto text : M26) {
			cout << text.getString().toAnsiString() << endl;

			//Adult Image 
			a3f.set2("Old", 100 * shift3, 160 * 5.5, 0.15);
			m26f = a3f.image2;

			//Drug Image
			zaf.set2("Weed", 220 * shift3 / 2, 187 * 5, 0.1);
			mar26f = zaf.image2;


			text.setPosition(xPos3, yPos3);
			yPos3 += 25;
			window2.draw(text);
		}


		window2.draw(title);
		if(!alcOpt){ 
			if (!a1Opt) {
				window2.draw(a1217f); window2.draw(alc1217f); window2.draw(youngDrinkers);
			} 
			if (!a2Opt) {
				window2.draw(a1825f); window2.draw(alc1825f); window2.draw(adultDrinkers);
			} 
			if (!a3Opt) {
				window2.draw(a26f); window2.draw(alc26f); window2.draw(oldDrinkers);
			}
			
			
		} 
		if (!hardOpt) {
			if (!a1Opt) {
				window2.draw(c1217f); window2.draw(coc1217f); window2.draw(youngHard);
			}
			if (!a2Opt) {
				window2.draw(c1825f); window2.draw(coc1825f); window2.draw(adultHard);
			}
			if (!a3Opt) {
				window2.draw(c26f); window2.draw(coc26f); window2.draw(oldHard);
			}
		} 
		if (!zaOpt) {
			if (!a1Opt) {
				window2.draw(m1217f); window2.draw(mar1217f); window2.draw(youngZa);
			}
			if (!a2Opt) {
				window2.draw(m1825f); window2.draw(mar1825f); window2.draw(adultZa);
			}
			if (!a3Opt) {
				window2.draw(m26f); window2.draw(mar26f); window2.draw(oldZa);
			}
		}
		
		
		

		
		
		

		window2.draw(stateT.image2);

		window2.display();
	}


	std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
