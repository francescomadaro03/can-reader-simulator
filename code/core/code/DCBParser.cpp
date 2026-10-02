#include <DCBEntry.h>
#include <DCBTable.h>
#include <SignalDef.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <optional>


class DCBParser {
    private:
        std::fstream dbcfile;

        void loadDcbFile(){
            dbcfile.open("core\\dbc_data.dbc");
            if(!dbcfile.is_open()){
                std::cout << "DBC file not found" << std::endl;
            }

            return;
        }

        void createDCBEntries(DCBTable table){
            std::string line;
            std::optional<DCBEntry> currentEntry = std::nullopt;

            while(std::getline(dbcfile, line)){
                
                if(line.empty()) continue;
                if (!line.empty() && line.back() == '\r') {
                    line.pop_back();
                }

                std::stringstream ss(line);
                std::string partial;
                
                ss >> partial;

                if(partial == "B0_"){
                    if(currentEntry != std::nullopt){
                        table.DCBTableData.emplace(currentEntry -> id, currentEntry);
                        currentEntry = std::nullopt;
                    }
                    DCBEntry entry;
                    if(ss >> partial){
                        //correctful parsing of the entry
                    }
                    else {
                        std::cerr << "Error in DBC file, no suitable code";
                    }

                    ss >> partial;
                    entry.name = partial;
                    currentEntry = entry;
                    
                }

                if(partial == "SG_"){
                    SignalDef signal;
                    ss >> partial;
                    signal.name = partial;
                    ss >> partial;

                    if (partial == ":") {
                        signal.muxType = MultiplexType::Standard;
                    } 
                    else if (partial == "M") {
                        signal.muxType = MultiplexType::Switch;
                    } 
                    else if (partial[0] == 'm') {
                        signal.muxType = MultiplexType::Multiplexed;
                        signal.muxValue = std::stoi(partial.substr(1)); 
                    }

                    ss >> partial;

                    signal.startingBit = std::stoi(partial.substr(0));
                    signal.endingBit = std::stoi(partial.substr(1)) + signal.startingBit;
                    signal.endianess = std::stoi(partial.substr(2));
                    partial.substr(3) == "+" ? signal.isSigned = false : signal.isSigned = true;

                    ss >> partial;
                    signal.weight = std::stoi(partial.substr(1));
                    signal.scale = std::stoi(partial.substr(3));

                    ss >> partial;
                    signal.min = std::stoi(partial.substr(1));
                    signal.max = std::stoi(partial.substr(3));

                    ss >> partial;
                    signal.unit = partial;

                    while(ss >> partial){
                        signal.nodes.push_back(partial);
                    }

                    currentEntry -> signalDefList.push_back(signal);

                    



                }


            }
        }





};

