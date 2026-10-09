#include "headers/IReader.h"
#include "headers/TranslatedRawMessage.h"
#include <vector>
#include <string_view>
#include <algorithm>
#include <charconv>





class SocketCANReader : public IReader {

    private:
        std::vector<std::string> supportedInterfaces = {"vcan0"}; 
        bool checkSupportedInterfaces(std::string interface) override {
            auto it = std::find(supportedInterfaces.begin(), supportedInterfaces.end(), interface);
            bool result;

            // Controllo se è stato trovato
            (it != supportedInterfaces.end()) ? result = true : result = false;

            return result;
        }

        TranslatedRawMessage computeTranslationFromRaw(std::string_view rawMessage){
            bool errorFound = false;
            size_t endTimestamp = rawMessage.find(')');
            size_t endId = rawMessage.find('#');
            endTimestamp == std::string_view::npos ? errorFound = true : errorFound = false;
            endId == std::string_view::npos ? errorFound = true : errorFound = false;
            for(int i = 0 && !errorFound; i<supportedInterfaces.size(); i++){
                size_t interface = rawMessage.find(supportedInterfaces[i]);
                (interface == std::string_view::npos) ? errorFound = true : errorFound = false;
            }

            TranslatedRawMessage toBeDelivered;
            // IF THERE ARE ERROR FORMATS, NO INTERRUPTION THE SOFTWARE DOESN'T FAIL BUT IT JUST RETURN AN INVALID MESSAGE AND GOES FURTHER 
            if(errorFound){toBeDelivered.id = -1; return toBeDelivered;} 


            //EXTRACTION OF THE TIMESTAMP, FALLBACK TO INVALID ID MESSAGE IF THERE IS AN ERROR WITH THE SAVING OF THE TIMESTAMP INTO THE TRANSLATED MESSAGE
            auto [ptr, ec] = std::from_chars(rawMessage.data() + 1, rawMessage.data() + endTimestamp, toBeDelivered.id);
            if(ec != std::errc()){toBeDelivered.id = -1; return toBeDelivered;}

            //EXTRACTION OF THE MESSAGE ID, FALLBACK TO INVALID ID MESSAGE IF THERE ARE PROBLEMS WITH THE CONVERSION OF THE ID 
            auto [ptr, ec] = std::from_chars(rawMessage.data() + endTimestamp, rawMessage.data() + endId, toBeDelivered.id);
            if(ec != std::errc()){toBeDelivered.id == -1; return toBeDelivered;}

            //EXTRACTION OF RAW DATA
            size_t readCharsFromRawMessage = ptr - rawMessage.data();
            rawMessage.remove_prefix(readCharsFromRawMessage);
            toBeDelivered.rawData = rawMessage.data();

            return toBeDelivered;


        }
        

    public:
        
        int ComputeRawTranslationAndSend(std::string_view rawMessage) override {
            computeTranslationFromRaw(rawMessage);
            return 0;
            
        }


};