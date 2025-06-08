#include "LoggingMessageHandler.h"
#include <iostream>

void LoggingMessageHandler::eventsAvailable() {
    drainEvents(); // Trigger the event processing
}

void LoggingMessageHandler::handleMessageEvent(const RNBO::MessageEvent& event) {
   if (event.getType() == RNBO::MessageEvent::Number) {
        double value = event.getNumValue();
        std::cout << "Received value " << value << " with tag " << event.getTag() << "\n";
        m_processor.setRT60Value(value); // Update RT60 value in PluginProcessor
    }
}




