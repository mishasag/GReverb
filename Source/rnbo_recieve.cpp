#include <iostream>
#include "RNBO.h"

using namespace RNBO;

class LoggingMessageHandler : EventHandler {
public:
  LoggingMessageHandler(std::function<RNBO::MessageTagInfo(RNBO::MessageTag)> tagResolver) : tagResolver(tagResolver) {}

private:

  void eventsAvailable() override {
    drainEvents();
  }

  void handleMessageEvent(const MessageEvent& event) override {
    if (event.getType() == MessageEvent::Bang) {
      std::cout << "Received bang with tag " << tagResolver(event.getTag()) << "\n";
    } else if (event.getType() == MessageEvent::Number) {
      std::cout << "Received value " << event.getNumValue() << " with tag " << tagResolver(event.getTag()) << "\n";
    } else if (event.getType() == MessageEvent::List) {
      std::cout << "Received list value ";
      auto list = event.getListValue().get();
      for (int i = 0; i < list->length; i++) {
        if (i != 0) std::cout << ", ";
        std::cout << list->operator[](i);
      }
      std::cout << " with tag " << tagResolver(event.getTag()) << "\n";
    }
  }

  std::function<RNBO::MessageTagInfo(RNBO::MessageTag)> tagResolver;
};

int main(int argc, const char * argv[]) {
  CoreObject rnboObject;
  auto tagResolver = [&rnboObject](RNBO::MessageTag tag) { return rnboObject.resolveTag(tag); };
  LoggingMessageHandler handler(tagResolver);

  auto interface = rnboObject.createParameterInterface(ParameterEventInterface::MultiProducer, (EventHandler *) &handler);

  rnboObject.prepareToProcess(44100, 64);

  SampleValue** inputs = nullptr;
  SampleValue** outputs = new SampleValue*[1];
  outputs[0] = new double[64];

  while (true) {
    rnboObject.process(inputs, 0, outputs, 1, 64);
    
    // Send a bang to in1
    rnboObject.sendMessage(TAG("in1"), TAG(""));

    // Send a number to in2
    rnboObject.sendMessage(TAG("in2"), 74, TAG(""));

    // Send a list to in3
    auto l = make_unique<RNBO::list>();
    l->push(1), l->push(2), l->push(3);
    rnboObject.sendMessage(TAG("in3"), std::move(l), TAG(""));
  }

  delete [] outputs[0];
  delete [] outputs;

  return 0;
}
