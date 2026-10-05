

#include "DCBEntry.h"
#include "DCBEntry.h"
#include "SignalDef.h"
#include "IParser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <optional>


class DCBParser : public IParser {

    public:
        void loadFile(const std::string pathname) override {
            loadDcbFile(pathname);
        }

        void createEntries(DCBTable& table) override {
            createDCBEntries(table);
        }


    private:
        std::fstream dbcfile;

        void loadDcbFile(const std::string pathname){
            dbcfile.open(pathname);
            if(!dbcfile.is_open()){
                std::cout << "DBC file not found" << std::endl;
            }

            return;
        }

        void createDCBEntries(DCBTable& table){
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

                if(partial == "BO_"){
                    if(currentEntry != std::nullopt && currentEntry.has_value()){
                        table.DCBTableData.emplace(currentEntry -> id, currentEntry.value());
                        currentEntry = std::nullopt;
                    }
                    DCBEntry entry;
                    if(ss >> partial){
                        entry.id = std::stoi(partial);
                    }
                    else {
                        std::cerr << "Error in DBC file, no suitable code";
                    }

                    ss >> partial;
                    entry.name = partial;
                    ss >> partial;
                    entry.dlc = std::stoi(partial);
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
                        ss >> partial;
                    } 
                    else if (partial[0] == 'm') {
                        signal.muxType = MultiplexType::Multiplexed;
                        signal.muxValue = std::stoi(partial.substr(1));
                        ss >> partial;
                    }

                    ss >> partial;

                    size_t pipePos = partial.find('|');
                    size_t atPos = partial.find('@');
                    if (pipePos != std::string::npos && atPos != std::string::npos){
                        std::string startingBit = partial.substr(0, pipePos);
                        signal.startingBit = std::stoi(startingBit);

                        std::string length = partial.substr(pipePos + 1, atPos - pipePos -1);
                        signal.endingBit = std::stoi(startingBit) + std::stoi(length);

                        std::string formatStr = partial.substr(atPos + 1);
                        formatStr[0] == '1' ? signal.endianess = true : signal.endianess = false;
                        formatStr[1] == '+' ? signal.isSigned = false : signal.isSigned = true;

                    }

                    ss >> partial;

                    size_t separateScaleAndWeight = partial.find(',');
                    if(separateScaleAndWeight != std::string::npos){
                        signal.weight = std::stof(partial.substr(1, separateScaleAndWeight));
                        signal.scale = std::stof(partial.substr(separateScaleAndWeight+1, partial.length() -1 ));
                    }


                    ss >> partial;

                    size_t separateMaxAndMin = partial.find('|');
                    if(separateMaxAndMin != std::string::npos){
                        signal.min = std::stof(partial.substr(1, separateMaxAndMin));
                        signal.max = std::stof(partial.substr(separateMaxAndMin+1, partial.length() -1 ));
                    }
                    ss >> partial;
                    signal.unit = partial;

                    while(ss >> partial){
                        size_t posComma = partial.find(',');
                        if(posComma != std::string::npos){
                            signal.nodes.push_back(partial.substr(0, posComma));
                        }
                        else {
                        signal.nodes.push_back(partial);
                        }
                    }

                    currentEntry -> signalDefList.push_back(signal);

                    



                }


            }

            if(currentEntry.has_value()){
                table.DCBTableData.emplace(currentEntry -> id, currentEntry.value());
                currentEntry = std::nullopt;

            }


        }





};

