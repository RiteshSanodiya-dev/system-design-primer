/*
 * This is Equivalent C++ code for existing pythone programe for call center problem.
 * problem description for this can be seen at : call_center_problem.md
 * 
 * Explanation:
 * The Employee class is abstract (pure virtual function escalateCall()), and it serves as the base class for Operator,
 * Supervisor, and Director.
 * The Rank and CallState enums represent the employee rank and call state, respectively.
 * The CallCenter class handles dispatching calls to the appropriate employees based on their rank.
 * The use of STL containers like vector and deque mimics Python's lists and deque.
 * Exception handling (throw std::runtime_error) is used in the Director class's escalateCall method to enforce that directors
 * cannot escalate calls.
 * This C++ implementation captures the essential features of the original Python code, including inheritance, polymorphism, and
 * data encapsulation.
*/

#include <iostream>
#include <deque>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

// Enum for Rank
enum class Rank {
    OPERATOR = 0,
    SUPERVISOR,
    DIRECTOR
};

// Enum for CallState
enum class CallState {
    READY = 0,
    IN_PROGRESS,
    COMPLETE
};

class Call; // Forward declaration
class CallCenter; // Forward declaration

// Abstract base class for Employee
class Employee {
protected:
    int employee_id;
    std::string name;
    Rank rank;
    Call* call;
    CallCenter* call_center;

public:
    Employee(int id, const std::string& name, Rank rank, CallCenter* center)
        : employee_id(id), name(name), rank(rank), call(nullptr), call_center(center) {}

    virtual ~Employee() = default;

    virtual void takeCall(Call* call);
    virtual void completeCall();
    virtual void escalateCall() = 0;

protected:
    void escalateCurrentCall();
};

// Derived class for Operator
class Operator : public Employee {
public:
    Operator(int id, const std::string& name, CallCenter* center)
        : Employee(id, name, Rank::OPERATOR, center) {}

    void escalateCall() override;
};

// Derived class for Supervisor
class Supervisor : public Employee {
public:
    Supervisor(int id, const std::string& name, CallCenter* center)
        : Employee(id, name, Rank::SUPERVISOR, center) {}

    void escalateCall() override;
};

// Derived class for Director
class Director : public Employee {
public:
    Director(int id, const std::string& name, CallCenter* center)
        : Employee(id, name, Rank::DIRECTOR, center) {}

    void escalateCall() override {
        throw std::runtime_error("Directors must be able to handle any call");
    }
};

// Class for Call
class Call {
public:
    CallState state;
    Rank rank;
    Employee* employee;

    Call(Rank rank) : state(CallState::READY), rank(rank), employee(nullptr) {}
};

// Class for CallCenter
class CallCenter {
private:
    std::vector<Operator> operators;
    std::vector<Supervisor> supervisors;
    std::vector<Director> directors;
    std::deque<Call*> queued_calls;

public:
    CallCenter(const std::vector<Operator>& operators, 
               const std::vector<Supervisor>& supervisors, 
               const std::vector<Director>& directors)
        : operators(operators), supervisors(supervisors), directors(directors) {}

    void dispatchCall(Call* call);
    void notifyCallEscalated(Call* call) {}
    void notifyCallCompleted(Call* call) {}
    void dispatchQueuedCallToNewlyFreedEmployee(Call* call, Employee* employee) {}

private:
    Employee* dispatchCallToEmployees(Call* call, std::vector<Operator>& employees);
    Employee* dispatchCallToEmployees(Call* call, std::vector<Supervisor>& employees);
    Employee* dispatchCallToEmployees(Call* call, std::vector<Director>& employees);
};

// Method definitions

void Employee::takeCall(Call* call) {
    this->call = call;
    call->employee = this;
    call->state = CallState::IN_PROGRESS;
}

void Employee::completeCall() {
    call->state = CallState::COMPLETE;
    call_center->notifyCallCompleted(call);
}

void Employee::escalateCurrentCall() {
    call->state = CallState::READY;
    Call* currentCall = call;
    call = nullptr;
    call_center->notifyCallEscalated(currentCall);
}

void Operator::escalateCall() {
    call->rank = Rank::SUPERVISOR;
    escalateCurrentCall();
}

void Supervisor::escalateCall() {
    call->rank = Rank::DIRECTOR;
    escalateCurrentCall();
}

void CallCenter::dispatchCall(Call* call) {
    if (call->rank != Rank::OPERATOR && call->rank != Rank::SUPERVISOR && call->rank != Rank::DIRECTOR) {
        throw std::invalid_argument("Invalid call rank");
    }

    Employee* employee = nullptr;
    if (call->rank == Rank::OPERATOR) {
        employee = dispatchCallToEmployees(call, operators);
    }
    if (call->rank == Rank::SUPERVISOR || employee == nullptr) {
        employee = dispatchCallToEmployees(call, supervisors);
    }
    if (call->rank == Rank::DIRECTOR || employee == nullptr) {
        employee = dispatchCallToEmployees(call, directors);
    }
    if (employee == nullptr) {
        queued_calls.push_back(call);
    }
}

Employee* CallCenter::dispatchCallToEmployees(Call* call, std::vector<Operator>& employees) {
    for (auto& employee : employees) {
        if (employee.call == nullptr) {
            employee.takeCall(call);
            return &employee;
        }
    }
    return nullptr;
}

Employee* CallCenter::dispatchCallToEmployees(Call* call, std::vector<Supervisor>& employees) {
    for (auto& employee : employees) {
        if (employee.call == nullptr) {
            employee.takeCall(call);
            return &employee;
        }
    }
    return nullptr;
}

Employee* CallCenter::dispatchCallToEmployees(Call* call, std::vector<Director>& employees) {
    for (auto& employee : employees) {
        if (employee.call == nullptr) {
            employee.takeCall(call);
            return &employee;
        }
    }
    return nullptr;
}
