#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct Flight {
    std::string destination;
    int distance;
    int cost;
};

struct Airport {
    std::string code;
    std::vector<Flight> outgoing;
};

struct Graph {
    std::vector<Airport> airports;
    int flight_count = 0;
};

// Split a row into six fields. A comma inside double quotes is part of a field.
// Reject malformed rows according to this week's instructions.
std::vector<std::string> parse_row(const std::string& row) {
    (void)row;
    throw std::logic_error("TODO: implement CSV parsing and validation");
}

// Find an airport by code; return its index or -1 when it is absent.
int find_airport(const Graph& graph, const std::string& code) {
    (void)graph;
    (void)code;
    throw std::logic_error("TODO: implement airport lookup");
}

// Add both endpoint vertices if needed, then add ONE directed flight.
void add_flight(Graph& graph, const std::vector<std::string>& fields) {
    (void)graph;
    (void)fields;
    throw std::logic_error("TODO: validate and add the directed flight");
}

// Open the named file, read the header and rows, and build the graph.
Graph load_graph(const std::string& filename) {
    (void)filename;
    throw std::logic_error("TODO: implement file loading");
}

// Display destination, distance and cost for every outgoing flight.
// Report an unknown code without ending the program.
void show_outgoing(const Graph& graph, const std::string& code) {
    (void)graph;
    (void)code;
    throw std::logic_error("TODO: display outgoing flights");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: airport_project <data.csv>\n";
        return 1;
    }
    try {
        Graph graph = load_graph(argv[1]);
        std::cout << "Airports: " << graph.airports.size() << '\n';
        std::cout << "Flights: " << graph.flight_count << '\n';
        std::string code;
        while (std::cout << "Airport code (or quit): " && std::cin >> code) {
            if (code == "quit") break;
            show_outgoing(graph, code);
        }
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
