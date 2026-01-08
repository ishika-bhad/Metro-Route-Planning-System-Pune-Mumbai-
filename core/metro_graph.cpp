#include "metro_graph.h"
#include <iostream>
#include <queue>
#include <climits>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>
#include <utility>

static const int METRO_LOCAL_TRANSFER = 8; // minutes
static const int METRO_METRO_TRANSFER = 3; // minutes

std::string lineToString(Line line)
{
    switch (line)
    {
    case Line::PURPLE:
        return "Purple Line";
    case Line::AQUA:
        return "Aqua Line";

    case Line::MUM_METRO_1:
        return "Mumbai Metro Line 1";
    case Line::MUM_METRO_2A:
        return "Mumbai Metro Line 2A";
    case Line::MUM_METRO_7:
        return "Mumbai Metro Line 7";
    case Line::MUM_METRO_3:
        return "Mumbai Metro Line 3";

    case Line::WESTERN:
        return "Western Line";
    case Line::CENTRAL:
        return "Central Line";
    case Line::HARBOUR:
        return "Harbour Line";

    case Line::INTERCHANGE:
        return "Interchange";
    default:
        return "Unknown Line";
    }
}

MetroGraph::MetroGraph()
{
    stations = {
        {"PCMC", "Pune", Transport::METRO, {Line::PURPLE}},
        {"Sant Tukaram Nagar", "Pune", Transport::METRO, {Line::PURPLE}},
        {"Bhosari", "Pune", Transport::METRO, {Line::PURPLE}},
        {"Kasarwadi", "Pune", Transport::METRO, {Line::PURPLE}},
        {"Shivajinagar", "Pune", Transport::METRO, {Line::PURPLE}},
        {"Civil Court", "Pune", Transport::METRO, {Line::PURPLE, Line::AQUA}},
        {"Swargate", "Pune", Transport::METRO, {Line::PURPLE}},
        {"Vanaz", "Pune", Transport::METRO, {Line::AQUA}},
        {"Ideal Colony", "Pune", Transport::METRO, {Line::AQUA}},
        {"Nal Stop", "Pune", Transport::METRO, {Line::AQUA}},
        {"PMC", "Pune", Transport::METRO, {Line::AQUA}},
        {"Ruby Hall Clinic", "Pune", Transport::METRO, {Line::AQUA}}};

    graph.resize(stations.size());

    // ---------------- MUMBAI METRO ----------------

    // Line 1: Versova – Andheri W – Ghatkopar
    int M_VERSOVA = stations.size();
    stations.push_back({"Versova", "Mumbai", Transport::METRO, {Line::MUM_METRO_1}});

    int M_ANDHERI_W = stations.size();
    stations.push_back({"Andheri West", "Mumbai", Transport::METRO, {Line::MUM_METRO_1, Line::MUM_METRO_2A}});

    int M_GHATKOPAR = stations.size();
    stations.push_back({"Ghatkopar", "Mumbai", Transport::METRO, {Line::MUM_METRO_1}});

    // Line 2A: Andheri W – Oshiwara – Goregaon W – Malad W
    int M_OSHIWARA = stations.size();
    stations.push_back({"Oshiwara", "Mumbai", Transport::METRO, {Line::MUM_METRO_2A}});

    int M_GOREGAON_W = stations.size();
    stations.push_back({"Goregaon West", "Mumbai", Transport::METRO, {Line::MUM_METRO_2A}});
    int M_MALAD_W = stations.size();
    stations.push_back({"Malad West", "Mumbai", Transport::METRO, {Line::MUM_METRO_2A}});

    // Line 7: Andheri E – Jogeshwari E – Goregaon E – Malad E
    int M_ANDHERI_E = stations.size();
    stations.push_back({"Andheri East", "Mumbai", Transport::METRO, {Line::MUM_METRO_7}});

    int M_JOGESHWARI_E = stations.size();
    stations.push_back({"Jogeshwari East", "Mumbai", Transport::METRO, {Line::MUM_METRO_7}});
    int M_GOREGAON_E = stations.size();
    stations.push_back({"Goregaon East", "Mumbai", Transport::METRO, {Line::MUM_METRO_7}});

    int M_MALAD_E = stations.size();
    stations.push_back({"Malad East", "Mumbai", Transport::METRO, {Line::MUM_METRO_7}});

    // ---------------- MUMBAI LOCAL ----------------

    // Western Line
    int L_CHURCHGATE = stations.size();
    stations.push_back({"Churchgate", "Mumbai", Transport::LOCAL, {Line::WESTERN}});

    int L_DADAR_W = stations.size();
    stations.push_back({"Dadar (W)", "Mumbai", Transport::LOCAL, {Line::WESTERN}});

    int L_ANDHERI_WL = stations.size();
    stations.push_back({"Andheri (W)", "Mumbai", Transport::LOCAL, {Line::WESTERN}});

    int L_BORIVALI = stations.size();
    stations.push_back({"Borivali", "Mumbai", Transport::LOCAL, {Line::WESTERN}});

    // Central Line
    int L_CSMT = stations.size();
    stations.push_back({"CSMT", "Mumbai", Transport::LOCAL, {Line::CENTRAL}});

    int L_DADAR_C = stations.size();
    stations.push_back({"Dadar (C)", "Mumbai", Transport::LOCAL, {Line::CENTRAL}});

    int L_KURLA = stations.size();
    stations.push_back({"Kurla", "Mumbai", Transport::LOCAL, {Line::CENTRAL, Line::HARBOUR}});

    int L_THANE = stations.size();
    stations.push_back({"Thane", "Mumbai", Transport::LOCAL, {Line::CENTRAL}});

    // Harbour Line
    int L_WADALA = stations.size();
    stations.push_back({"Wadala", "Mumbai", Transport::LOCAL, {Line::HARBOUR}});

    int L_VASHI = stations.size();
    stations.push_back({"Vashi", "Mumbai", Transport::LOCAL, {Line::HARBOUR}});

    int L_PANVEL = stations.size();
    stations.push_back({"Panvel", "Mumbai", Transport::LOCAL, {Line::HARBOUR}});

    graph.resize(stations.size());

    auto addEdge = [&](int u, int v, int t, Line l)
    {
        graph[u].push_back({v, t, l});
        graph[v].push_back({u, t, l});
    };

    addEdge(0, 1, 4, Line::PURPLE);
    addEdge(1, 2, 3, Line::PURPLE);
    addEdge(2, 3, 4, Line::PURPLE);
    addEdge(3, 4, 5, Line::PURPLE);
    addEdge(4, 5, 2, Line::PURPLE);
    addEdge(5, 6, 4, Line::PURPLE);

    addEdge(7, 8, 3, Line::AQUA);
    addEdge(8, 9, 3, Line::AQUA);
    addEdge(9, 10, 2, Line::AQUA);
    addEdge(10, 5, 2, Line::AQUA);
    addEdge(5, 11, 4, Line::AQUA);
    // ---------------- MUMBAI METRO EDGES ----------------

    // Line 1
    addEdge(M_VERSOVA, M_ANDHERI_W, 5, Line::MUM_METRO_1);
    addEdge(M_ANDHERI_W, M_GHATKOPAR, 7, Line::MUM_METRO_1);

    // Line 2A
    addEdge(M_ANDHERI_W, M_OSHIWARA, 3, Line::MUM_METRO_2A);
    addEdge(M_OSHIWARA, M_GOREGAON_W, 4, Line::MUM_METRO_2A);
    addEdge(M_GOREGAON_W, M_MALAD_W, 4, Line::MUM_METRO_2A);

    // Line 7
    addEdge(M_ANDHERI_E, M_JOGESHWARI_E, 3, Line::MUM_METRO_7);
    addEdge(M_JOGESHWARI_E, M_GOREGAON_E, 4, Line::MUM_METRO_7);
    addEdge(M_GOREGAON_E, M_MALAD_E, 4, Line::MUM_METRO_7);

    // ---------------- MUMBAI LOCAL EDGES ----------------

    // Western Line
    addEdge(L_CHURCHGATE, L_DADAR_W, 10, Line::WESTERN);
    addEdge(L_DADAR_W, L_ANDHERI_WL, 12, Line::WESTERN);
    addEdge(L_ANDHERI_WL, L_BORIVALI, 15, Line::WESTERN);

    // Central Line
    addEdge(L_CSMT, L_DADAR_C, 12, Line::CENTRAL);
    addEdge(L_DADAR_C, L_KURLA, 10, Line::CENTRAL);
    addEdge(L_KURLA, L_THANE, 15, Line::CENTRAL);

    // Harbour Line
    addEdge(L_CSMT, L_WADALA, 12, Line::HARBOUR);
    addEdge(L_WADALA, L_VASHI, 15, Line::HARBOUR);
    addEdge(L_VASHI, L_PANVEL, 25, Line::HARBOUR);
    // Dadar Western ↔ Central
    addEdge(L_DADAR_W, L_DADAR_C, 5, Line::INTERCHANGE);

    // Kurla Central ↔ Harbour
    addEdge(L_KURLA, L_WADALA, 6, Line::INTERCHANGE);

    // ---------------- METRO ↔ LOCAL INTERCHANGES ----------------

    // Andheri West Metro ↔ Andheri (W) Local
    addEdge(
        M_ANDHERI_W,
        L_ANDHERI_WL,
        METRO_LOCAL_TRANSFER,
        Line::INTERCHANGE);

    // Ghatkopar Metro ↔ Kurla Local
    addEdge(
        M_GHATKOPAR,
        L_KURLA,
        METRO_LOCAL_TRANSFER,
        Line::INTERCHANGE);

    // Andheri East Metro ↔ Andheri (W) Local (skywalk / bridge)
    addEdge(
        M_ANDHERI_E,
        L_ANDHERI_WL,
        METRO_LOCAL_TRANSFER,
        Line::INTERCHANGE);
}

int MetroGraph::stationCount() const
{
    return stations.size();
}

std::string MetroGraph::getStationName(int id) const
{
    return stations[id].name;
}

std::string MetroGraph::getRouteString(int src, int dest) const
{
    int n = stations.size();
    std::vector<int> dist(n, INT_MAX), parent(n, -1);
    std::vector<Line> usedLine(n);

    std::priority_queue<
        std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>>
        pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (auto &e : graph[u])
        {
            if (stations[u].city != stations[e.to].city)
                continue;

            if (dist[u] + e.time < dist[e.to])
            {
                dist[e.to] = dist[u] + e.time;
                parent[e.to] = u;
                usedLine[e.to] = e.line;
                pq.push({dist[e.to], e.to});
            }
        }
    }

    if (dist[dest] == INT_MAX)
        return "No route available";

    std::vector<int> path;
    for (int v = dest; v != -1; v = parent[v])
        path.push_back(v);

    std::reverse(path.begin(), path.end());

    std::string output;
    Line currentLine = (path.size() > 1) ? usedLine[path[1]] : stations[src].lines[0];

    output += stations[path[0]].name +
              " (" + lineToString(usedLine[path[1]]) + ")\n";

    for (size_t i = 1; i < path.size(); i++)
    {
        if (usedLine[path[i]] != currentLine)
        {
            output += "Change to " + lineToString(usedLine[path[i]]) + "\n";
            currentLine = usedLine[path[i]];
        }
        output += "  ↓ " + stations[path[i]].name +
                  " (" + lineToString(usedLine[path[i]]) + ")\n";
    }

    output += "\nTotal Time: " + std::to_string(dist[dest]) + " minutes";
    return output;
}
std::string MetroGraph::getRouteJSON(int src, int dest) const
{
    int n = stations.size();
    std::vector<int> dist(n, INT_MAX), parent(n, -1);
    std::vector<Line> usedLine(n);

    std::priority_queue<
        std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>>
        pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (const auto &e : graph[u])
        {
            if (dist[u] + e.time < dist[e.to])
            {
                dist[e.to] = dist[u] + e.time;
                parent[e.to] = u;
                usedLine[e.to] = e.line;
                pq.push({dist[e.to], e.to});
            }
        }
    }

    if (dist[dest] == INT_MAX)
    {
        return R"({"error":"No route available"})";
    }

    std::vector<int> path;
    for (int v = dest; v != -1; v = parent[v])
        path.push_back(v);
    std::reverse(path.begin(), path.end());

    std::string json = "{\n";
    json += "  \"total_time\": " + std::to_string(dist[dest]) + ",\n";
    json += "  \"route\": [\n";

    for (size_t i = 0; i < path.size(); i++)
    {
        Line line;

        if (i == 0)
        {
            if (usedLine[path[1]] == Line::INTERCHANGE)
                line = stations[path[0]].lines[0];
            else
                line = usedLine[path[1]];
        }
        else
        {
            line = usedLine[path[i]];
        }

        json += "    { ";
        json += "\"id\": " + std::to_string(path[i]) + ", ";
        json += "\"station\": \"" + stations[path[i]].name + "\", ";
        json += "\"line\": \"" + lineToString(usedLine[path[i]]) + "\" }";

        if (i + 1 < path.size())
            json += ",";
        json += "\n";
    }

    json += "  ]\n";
    json += "}";

    return json;
}
std::vector<int> MetroGraph::getStationsByCity(const std::string &city) const
{
    std::vector<int> ids;
    for (int i = 0; i < stations.size(); ++i)
    {
        if (stations[i].city == city)
            ids.push_back(i);
    }
    return ids;
}
