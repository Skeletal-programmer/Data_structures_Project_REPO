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
    if (fields.size() != 6) { //Checks vector for 6 fields
        throw std::runtime_error("Invalid flight row");
    }
    
    std::string origin = fields[0]; //Extract airport codes
    std::string destination = fields[1];
    
    if (origin.empty() || destination.empty()) { //Validate airport codes
        throw std::runtime_error("Airport code cannot be empty");
    }
    
    int distance = std::stoi(fields[4]); //Extract distance/cost
    int cost = std::stoi(fields[5]);
    
    if (distance <= 0 || cost <= 0) { //Validate distance and cost
        throw std::runtime_error("Distance and cost must be positive");
    }
    int origin_index = find_airport(graph, origin); //Search for origin airport

    if (origin_index == -1) { //Check if missing
        Airport new_airport; //Make new airport if missing
        new_airport.code = origin;
        graph.airports.push_back(new_airport); //Add new airport to graph
        origin_index = static_cast<int>(graph.airports.size() - 1); //Retieves new airports index
    }
    int destination_index = find_airport(graph, destination); //Search for dest

    if (destination_index == -1) { //Check if index missing
        Airport new_airport; //Create new airport
        new_airport.code = destination;
        graph.airports.push_back(new_airport); //Add to the graph
    }
    Flight flight; //Creates actual flight

    flight.destination = destination;
    flight.distance = distance;
    flight.cost = cost;
    graph.airports[origin_index].outgoing.push_back(flight); //Adds flight to graph
    graph.flight_count++; //Increment flight count
}

// Open the named file, read the header and rows, and build the graph.
Graph load_graph(const std::string& filename) {

    std::ifstream file(filename); //Opens CSV

    if (!file.is_open()) { //Checks whether file open
        throw std::runtime_error("Could not open file: " + filename);
    }

    Graph graph;
    std::string line;

    // Read CSV header
    if (!std::getline(file, line)) { //Read one line
        throw std::runtime_error("CSV file is empty");
    }

    std::vector<std::string> expected_header = {"Origin_airport","Destination_airport","Origin_city","Destination_city","Distance","Cost"}; //6 Expected headers

    if (parse_row(line) != expected_header) { //Seperates 6 fields
        throw std::runtime_error("Invalid CSV header");
    }

    int line_number = 1;

    // Read remaning CSV rows
    while (std::getline(file, line)) {

        line_number++;

        // Ignore blank lines
        if (line.find_first_not_of(" \t\r\n") == std::string::npos) {
            continue;
        }

        try {
            std::vector<std::string> fields = parse_row(line);
            add_flight(graph, fields);
        }
        catch (const std::exception& error) {
            throw std::runtime_error(
                "Error on line " + std::to_string(line_number)
                + ": " + error.what()
            );
        }
    }

    if (file.bad()) {
        throw std::runtime_error("Error reading CSV file");
    }
    return graph;
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
