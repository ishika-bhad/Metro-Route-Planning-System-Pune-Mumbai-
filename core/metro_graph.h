#ifndef METRO_GRAPH_H
#define METRO_GRAPH_H

#include <string>
#include <vector>

/* ---------- Line Definition ---------- */
enum class Line
{
    // Pune
    PURPLE,
    AQUA,

    // Mumbai Metro
    MUM_METRO_1,
    MUM_METRO_2A,
    MUM_METRO_7,
    MUM_METRO_3,

    // Mumbai Local
    WESTERN,
    CENTRAL,
    HARBOUR,

    // Special
    INTERCHANGE
};

enum class Transport
{
    METRO,
    LOCAL
};

/* ---------- Helpers ---------- */
std::string lineToString(Line line);

/* ---------- Data Structures ---------- */
struct Station
{
    std::string name;
    std::string city;        // "Pune", "Mumbai"
    Transport transport;     // METRO or LOCAL
    std::vector<Line> lines; // Interchange if >1
};

struct Edge
{
    int to;
    int time;
    Line line;
};

/* ---------- Metro Graph Class ---------- */
class MetroGraph
{
private:
    std::vector<Station> stations;
    std::vector<std::vector<Edge>> graph;
    std::vector<int> cityStations(const std::string &city) const;

public:
    MetroGraph(); // constructor

    int stationCount() const;
    std::string getStationName(int id) const;
    std::string getRouteString(int src, int dest) const;
    std::string getRouteJSON(int src, int dest) const;
    std::vector<int> getStationsByCity(const std::string &city) const;
    std::string getRouteJSON(int src, int dest, const std::string &city) const;
};

#endif // METRO_GRAPH_H
