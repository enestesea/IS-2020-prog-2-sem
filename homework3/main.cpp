#include "pugixml.h"
#include <string.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;
using namespace pugi;

struct Vertex {
    double x;
    double y;
    bool used = false;
};
struct MaxRoute{
    string name;
    double cost = -1;
};
double length(const Vertex& p1, const Vertex& p2)
{
    return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}
void longRoute(const unordered_map<string , vector<Vertex>>& graph, vector <MaxRoute>& max_path, const int ind){
    for(auto i : graph){
        int n = i.second.size();
        vector<double> dist(n, INT_MAX);
        dist[0] = 0;
        for(int j = 0; j < n; j++){
            int min_i = -1;
            for (int k = 0; k < n; k++)
                if (!i.second[k].used && (min_i == -1 || dist[k] > dist[min_i])) {
                    min_i = k;
                }
            i.second[min_i].used = true;
            for (int k = 0; k < n; k++)
                if (!i.second[k].used && length(i.second[min_i], i.second[k]) < dist[k])
                    dist[k] = length(i.second[min_i], i.second[k]);
        }
        double path = 0;
        for(double j : dist){
            path += j;
        }
        if (path > max_path[ind].cost) {
            max_path[ind].name = i.first;
            max_path[ind].cost = path;
        }
    }
}
void create_p(const string& temPoint, Vertex& tmpPoint ){
    string coordinate;
    for(int i = 0; i < temPoint.size(); i++){
        if(temPoint[i] == ','){
            tmpPoint.x = atof(coordinate.c_str());
            coordinate.erase(0);
        }
        else if(temPoint[i] != ',')
            coordinate += temPoint[i];
        if(i == temPoint.size()-1){
            tmpPoint.y = atof(coordinate.c_str());
            coordinate.erase(0);
        }
    }
}
void find_routes(const string& tempR, const xml_node& stat, vector<int>& maxTypes, Vertex& tmpPoint, vector<unordered_map <string, int>>& routes, vector<unordered_map<string , vector<Vertex>>>& graphs, vector<string>& maxR_name){
    string newr;
    const string tram = "Трамвай";
    const string troll = "Троллейбус";
    const string bus = "Автобус";
    for (int i = 0; i < tempR.size(); i++) {
        if (tempR[i] != ',' && tempR [i] != '.'){
            newr += tempR[i];
        }
        if (tempR[i] == ',' || tempR [i] == '.' || i == tempR.size()-1) {
            if (stat.child_value("type_of_vehicle") == tram){
                routes[0][newr] += 1;
                graphs[0][newr].push_back(tmpPoint);
                if (routes[0][newr] > maxTypes[0]){
                    maxTypes[0] = routes[0][newr];
                    maxR_name[0] = newr;
                }
            }
            else if (stat.child_value("type_of_vehicle") == troll){
                routes[1][newr] += 1;
                graphs[1][newr].push_back(tmpPoint);
                if (routes[1][newr] > maxTypes[1]){
                    maxTypes[1] = routes[1][newr];
                    maxR_name[1] = newr;
                }
            }
            else if (stat.child_value("type_of_vehicle") == bus){
                routes[2][newr] += 1;
                graphs[2][newr].push_back(tmpPoint);
                if (routes[2][newr] > maxTypes[2]){
                    maxTypes[2] = routes[2][newr];
                    maxR_name[2] = newr;
                }
            }
            newr.erase(0);
        }
    }
}

void find_street(const string& tempS, int& maxStreet, string& streetName, unordered_map <string, int>& streets){
    string newS;
    const char sh = 'ш';
    const char ul = 'л';
    const char pr = 'р';
    for (int i = 0; i < tempS.size(); i++){
        if (tempS[i] != ','){
            if (tempS[i] == '.'){
                if (tempS[i-1] == sh){
                    newS += "оссе";
                }
                if (tempS[i-1] == ul){
                    newS += "ица";
                }
                if (tempS[i-1] == pr){
                    newS += "оспект";
                }
            }
            else
                newS += tempS[i];
        }
        if (tempS[i] == ',' || i == tempS.size() - 1) {
            streets[newS] += 1;
            if (streets[newS] > maxStreet){
                maxStreet = streets[newS];
                streetName = newS;
            }
            newS.erase(0);
            i++;
        }
    }
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    xml_document doc;
    doc.load_file("data.xml");
    xml_node dataset = doc.child("dataset");

    vector<unordered_map<string , vector<Vertex>>> graphs(3);
    vector<unordered_map <string, int>> routes(3);
    unordered_map <string, int> streets;
    vector<int> maxTypes(3);
    vector<string> maxR_name(3);

    int maxStreet = 0;
    string streetName;

    for (xml_node stat = dataset.first_child(); stat; stat = stat.next_sibling())
    {
        Vertex tmpPoint;
        create_p(stat.child_value("coordinates"),tmpPoint);

        find_routes(stat.child_value("routes"), stat, maxTypes, tmpPoint, routes, graphs, maxR_name);

        find_street(stat.child_value("location"), maxStreet, streetName, streets );
    }
    vector <MaxRoute> max_path (3);
    longRoute (graphs[0], max_path, 0);
    longRoute (graphs[1], max_path, 1);
    longRoute (graphs[2], max_path, 2);
    cout << "1)Трамвайный маршрут с наибольшим количеством остановок: " << maxTypes[0] << ", маршрут номер " << maxR_name[0] << endl;
    cout << "Троллейбусный маршрут с наибольшим количеством остановок: " << maxTypes[1] << ", маршрут номер " << maxR_name[1] << endl;
    cout << "Автобусный маршрут с наибольшим количеством остановок: " << maxTypes[2] << ", маршрут номер " << maxR_name[2] << endl;
    cout << "2)Наиболее длинный трамвайный маршрут: " << max_path[0].name << endl;
    cout << "Наиболее длинный троллейбусный маршрут: " << max_path[1].name << endl;
    cout << "Наиболее длинный автобусный маршрут: " << max_path[2].name << endl;
    cout << "3)Улица с наибольшым количеством остановок: " << streetName <<" с " << maxStreet << " остановкой" << endl;
    return 0;
}
