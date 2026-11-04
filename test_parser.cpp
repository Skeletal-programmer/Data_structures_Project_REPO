#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>


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

int main() {
    std::string test = "ABC,BCD,\"Allentown, PA\",City B,1,2";

    try {
        std::vector<std::string> fields = parse_row(test);

        for (size_t i = 0; i < fields.size(); i++) {
            std::cout << "Field " << i + 1
                      << ": " << fields[i] << '\n';
        }
    }
    catch (const std::exception& error) {
        std::cout << "Error: " << error.what() << '\n';
    }

    return 0;
}
