#include "esphome/core/log.h"
#include "custom_rfid_reader.h"

namespace esphome
{
    namespace custom_rfid_reader
    {

        static const char *TAG = "custom_rfid_reader.text_sensor";

        void CustomRFIDReader::setup()
        {
        }

        int readline(int readch, char *buffer, int len)
        {
            static int pos = 0;
            int rpos;

            if (readch > 0)
            {
                switch (readch)
                {
                case '\n':
                case '\r':           // Return on CR or newline
                    buffer[pos] = 0; // Just to be sure, set last character 0
                    rpos = pos;
                    pos = 0; // Reset position index ready for next time
                    return rpos;
                default:
                    if ((pos < len - 1) && (readch < 127))
                    { // Filter on <127 to make sure it is a character
                        buffer[pos++] = readch;
                        buffer[pos] = 0;
                    }
                    else
                    {
                        buffer[pos] = 0; // Just to be sure, set last character 0
                        rpos = pos;
                        pos = 0; // Reset position index ready for next time
                        return rpos;
                    }
                }
            }
            // No end of line has been found, so return -1.
            return -1;
        }

        void CustomRFIDReader::loop()
        {
            const int max_line_length = 80;
            static char buffer[max_line_length];
            while (available())
            {
                if (readline(read(), buffer, max_line_length) > 0)
                {
                    std::string s = std::string(buffer);
                    if (s == "NONE")
                        this->current_state_ = ReaderState::NoTag;
                    else if (s.substr(0, 5) == "VALID")
                        this->current_state_ = ReaderState::ValidTag;
                    else if (s.substr(0, 4) == "INIT")
                    {
                        this->current_state_ = ReaderState::NoTag;
                        std::string s2 = "Reader detected:";
                        std::strcat(s2, s.substr(5));
                        ESP_LOGI(TAG, s2);
                    }
                    else
                        this->current_state_ = ReaderState::InvalidTag;

                    if (this->current_state_ == ReaderState::ValidTag && this->last_state_ != ReaderState::ValidTag)
                    {
                        ESP_LOGI(TAG, "A valid tag detected!");
                        publish_state(s.substr(6));
                    }
                    else if (this->current_state_ == ReaderState::NoTag && this->last_state_ != ReaderState::NoTag)
                    {
                        ESP_LOGI(TAG, "A valid tag not present anymore");
                        publish_state("");
                    }

                    this->last_state_ = this->current_state_;
                }
            }
        }

        void CustomRFIDReader::dump_config()
        {
            ESP_LOGCONFIG(TAG, "Custom arduino-based RFID reader device component v1.0.0");
        }

    } // namespace custom_rfid_sensor
} // namespace esphome