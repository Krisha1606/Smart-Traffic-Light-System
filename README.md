# Smart-Traffic-Light-System
In most cities, traffic lights operate on fixed timers, typically cycling through red, green, and yellow lights at preset intervals — often 60 seconds per light. While this system is simple, it fails to account for real-time traffic conditions, leading to multiple inefficiencies
This project addresses these issues by implementing a Smart Red Light System that adjusts red light duration based on vehicle density.
In this project the timing of red light increases as the traffic density increases and vice versa.
Other features are :
In the time of emergency the timing of green light increases
it also cover oop topics like:
OOP Concept	Where Used
Class-->	 TrafficSignal, SmartSignal, TrafficController
Object-->	 Instances of SmartSignal (e.g., roads vector)
Inheritance-->	SmartSignal inherits from TrafficSignal
Encapsulation-->	Members like vehicleCount, redTime
Polymorphism-->	  Virtual methods overridden in SmartSignal
Friend Class-->	 TrafficController accesses TrafficSignal internals
Operator Overload-->	operator for sorting traffic signals
Dynamic Memory-->	 new, delete used for SmartSignal objects
Constructor/Destructor-->	 For setup and cleanup
Abstraction-->  Hides implementation via methods like simulateTraffic()
