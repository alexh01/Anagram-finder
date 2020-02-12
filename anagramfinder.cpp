/*******************************************************************************
 * Name        : Alexander Heifler
 * The goal of this assignment was to find all the greatest number of words that were anagrams of each other within any given text file with the best time complexity possible O(n lg n)
 ******************************************************************************/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <unordered_map>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct hash_pair {
	template <class N1, class N2> 
	size_t operator()(const pair<N1, N2>& p) const
	{
		auto h1 = hash<N1>{}(p.first);
		auto h2 = hash<N2>{}(p.second);
		return h1 ^ h2;
	}
};
void vector_printer(vector<string> a)
{
	for(int i=0;i<(int)a.size()-1;i++)
		cout<<a[i]<<"\n";
	if(a.size()-1>=0)
		cout<<a[a.size()-1];
}
void vector_printer(vector<vector<string>> a)
{
	for(int i=0;i<(int)a.size()-1;i++)
	{
		vector_printer(a[i]);
		cout<<"\n";
		cout<<"\n";
	}
	if(a.size()-1>=0)
		vector_printer(a[a.size()-1]);
}
int main (int argc, char *argv[]) {
	if(argc!=2) {
		cout<<"Usage: ./anagramfinder <dictionary file>\n";
		return 1;
	}
	unordered_map<pair<unsigned long long int,unsigned long long int>, vector<string>, hash_pair> enchillada;
	string filename=argv[1];
	ifstream myfile(filename.c_str());
	if (myfile.is_open()) {
		for(string line; getline(myfile, line);) {
			unsigned long long int key1=0;
			unsigned long long int key2=0;
			pair<unsigned long long int, unsigned long long int> key;
			bool useit=true;
			for(size_t i=0;i<line.length();i++) {
				int asciin=(int)line[i];
				if((asciin>=97&&asciin<=122)||(asciin>=65&&asciin<=90)) {
					if((asciin>=65&&asciin<=90))
						asciin+=32;
					if(asciin>109)
						key2+=1<<((asciin-110)*5);
					else
						key1+=1<<((asciin-97)*5);
				}
				else {
					if(asciin==13)
						break;
					useit=false;
					while(i<line.length()) 
						i++;
				}
			}
			if(useit) {
				key=make_pair(key1,key2);
				if(enchillada.find(key)==enchillada.end()) {
					vector<string> this_is_new;
					this_is_new.push_back(line);
					enchillada.insert({key,this_is_new});
				}
				else {
					enchillada.at(key).push_back(line);
				}
			}
		}
		
		myfile.close();
	}
	else{
		cerr << "Error: File '"<<argv[1]<<"' not found.\n";
		return 1;
	}
	vector<vector<string>> answer;
	size_t greatest=0;
	for (auto &i: enchillada) {
        if(i.second.size()>greatest) {
			greatest=i.second.size();
			answer.clear();
			answer.push_back(i.second);
		}
		else if(i.second.size()==greatest)
			answer.push_back(i.second);
    }
	if(greatest<2)
	{
		cout<<"No anagrams found.\n";
		return 1;
	}
	cout<<"Max anagrams: "<<greatest<<"\n";
	
	for(int i=0;i<(int)answer.size();i++)
	{
		sort(answer[i].begin(), answer[i].end());
	}
	sort(answer.begin(), answer.end());
	vector_printer(answer);
	
	return 0;
}
