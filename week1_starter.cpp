#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <cctype>

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
    
    std::vector<std::string> fields;
    std::string field;
    bool quoted = false;
    for (size_t i = 0; i < row.length(); i++) {
        char ch = row[i];
        if (ch == '"') { //Checks for quotation marks
            quoted = !quoted; //If qouted is false = true and if quoted is true=false
        }
        else if (ch == ',' && !quoted) { //Checks and accounts for commas
            fields.push_back(field);
            field.clear();
        }
        else{
            field += ch; //Saves ordfinary characters to the field
        }
    }
    fields.push_back(field); //Ensueres final field is still grabbed despite lacking comma
    if (quoted) {
        throw std::runtime_error("Unclosed quotation");
    }

    if (fields.size() != 6) {
        throw std::runtime_error("CSV row must have exactly six fields");
    }
    return fields;
}

// Find an airport by code; return its index or -1 when it is absent.
int find_airport(const Graph& graph, const std::string& code){ //Search evry airport

    for (size_t i = 0; i < graph.airports.size(); i++) {

        if (graph.airports[i].code == code) { //Chack airport code if matches requested code
            return static_cast<int>(i);
        }
    }

    return -1; //Airport doesn't exist
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
