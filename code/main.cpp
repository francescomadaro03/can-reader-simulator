#include "parser/DCBParser.cpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {

    const std::string dbcPath =  ".\\code\\dbc_data.dbc";
    std::ifstream inputFile(dbcPath);
    if (!inputFile) {
        std::cerr << "Unable to open DBC file: " << dbcPath << '\n';
        return 1;
    }
    inputFile.close();

    DCBParser parser;
    parser.loadFile(dbcPath);

    DCBTable table;
    parser.createEntries(table);

    std::vector<const DCBEntry*> entries;
    entries.reserve(table.DCBTableData.size());
    for (const auto& item : table.DCBTableData) {
        entries.push_back(&item.second);
    }
    std::sort(entries.begin(), entries.end(), [](const DCBEntry* left, const DCBEntry* right) {
        return left->id < right->id;
    });

    std::cout << "Parsed " << entries.size() << " message(s)\n";
    for (const DCBEntry* entry : entries) {
        std::cout << "\nMessage " << entry->id << ": " << entry->name
                  << " (" << entry->signalDefList.size() << " signal(s))\n";
        for (const SignalDef& signal : entry->signalDefList) {
            std::cout << "  - " << signal.name
                      << ": bits " << static_cast<unsigned int>(signal.startingBit)
                      << '-' << static_cast<unsigned int>(signal.endingBit)
                      << ", unit=\"" << signal.unit << "\"\n";
        }
    }

    return 0;
}
