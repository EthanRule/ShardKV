#include <iostream>
#include <list>
#include <string>

class IObserver {
public:
    virtual void update(const std::string &message_from_subject) = 0;
    virtual void addSubscriber(IObserver *observer) = 0;
    virtual void removeSubscriber(IObserver *observer) = 0;
    virtual void notify() = 0;
};

/**
 * The Subject owns some important state and notifies observers when the state
 * changes.
 */

class Observer : public IObserver {
public:
    // // finds another su
    // Observer(Observer &subject) : subject_(subject) {
    //     this->subject_.Attach(this);
    //     ++Observer::static_number_;
    //     this->number_ = Observer::static_number_;
    // }
    IObserver* subscription; // Receives events from this publisher
    std::list<IObserver*> subscribers; // Sends events to these
    std::string message_;
    static int static_number_;
    int number_;

    // Should be able to publish event to subscribers, and receive events from publishers its subscribed to.

    // void update(const std::string &message_from_subject) override {
    //     message_from_subject_ = message_from_subject;
    //     PrintInfo();
    // }

    //
    void addSubscriber(IObserver *observer) override {
        subscribers.push_back(observer);
    }

    void removeSubscriber(IObserver *observer) override {
        subscribers.remove(observer);
    }

    void notify() override {
        std::list<IObserver *>::iterator iterator = subscribers.begin();
        howManySubscribers();
        while (iterator != subscribers.end()) {
            (*iterator)->update(message_);
            ++iterator;
        }
    }

    // This message will need to be generic and handle Command and string types.
    void CreateMessage(std::string message = "Empty") {
        this->message_ = message;
        notify();
    }

    void howManySubscribers() {
        std::cout << "There are " << subscribers.size() << " observers in the list.\n";
    }

    void SomeBusinessLogic() {
        this->message_ = "change message message";
        notify();
        std::cout << "I'm about to do some thing important\n";
    }
};
