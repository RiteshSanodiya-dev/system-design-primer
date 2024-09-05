# call center problem description

**Problem:** There is a call center in which there is a hierarchy of employees who can attend the call. Freshers should
attend the call first, followed by leads and finally the manager. If the fresher wants to escalate the call he/she can
escalate it to the leads. Also, a lead can escalate the call to the manager. We can suppose that there are many freshers,
many leads, and only one manager. If at any point in time no employees are free to attend the call, the caller should wait
in the queue. Once an employee is free he/she can take the call.

**We can thinkof the solution as below:**

What are the classes we can think of to define in the system

Employee (Fresher, Lead, Manager)
Customer
Call
CallManager
Here we will have an Employee class. Fresher, Lead, and Manager classes will be extending Employee class.

Let’s see how our Employee class will look like. It will have properties like name, free (either true or false), rank
(to identify whether it is a fresher, a lead or a manager), and an instance of CallManager class. What behaviors we can
think about this class?
