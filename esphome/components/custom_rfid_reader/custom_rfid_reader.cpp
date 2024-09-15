#include "esphome/core/log.h"
#include "custom_rfid_reader.h"
#include "esphome/core/log.h"

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
                    publish_state(buffer);
                }
            }
        }

        void CustomRFIDReader::dump_config()
        {
            ESP_LOGCONFIG(TAG, "Custom RFID Reader");
        }

    } // namespace empty_UART_sensor
} // namespace esphome