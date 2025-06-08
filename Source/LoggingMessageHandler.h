#pragma once

#include "RNBO.h"
#include "PluginProcessor.h"

class LoggingMessageHandler : public RNBO::EventHandler {
public:
    LoggingMessageHandler(PluginProcessor& processor)
        : m_processor(processor) {}

    void eventsAvailable() override;
    void handleMessageEvent(const RNBO::MessageEvent& event) override;

private:
    PluginProcessor& m_processor;
};
